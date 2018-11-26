; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; MIT License
;
; Copyright (c) 2018 Kirill Diduk
;
; Permission is hereby granted, free of charge, to any person obtaining a copy
; of this software and associated documentation files (the "Software"), to
; deal in the Software without restriction, including without limitation the
; rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
; sell copies of the Software, and to permit persons to whom the Software is
; furnished to do so, subject to the following conditions:
;
; The above copyright notice and this permission notice shall be included in
; all copies or substantial portions of the Software.
;
; THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
; IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
; FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
; AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
; LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
; FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
; IN THE SOFTWARE.
;
; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Created on: 15 October, 2018
; Barcelona, Spain

    .EXPORT     LEVEL_LOAD, LEVEL_UPDATE, LEVEL_RENDER
    .IMPORTZP   FRAME_CNT, SCROLL_X, SCROLL_Y, TEMP
    .IMPORTZP   PPU_CTRL_VAR, PPU_MASK_VAR, VRAM_UPDATE
    .IMPORT     PAL_BUF
    .INCLUDE    "ppu.inc"


MAX_SCROLL_Y    = 240
LEVEL_WIDTH     = 16
ROW_MAX         = 15
COL_MAX         = 16


.RODATA

LEVEL_MAP:
    .INCBIN "level.bin"
LEVEL_MAP_END:
BG_PALETTE:
    .BYTE   $11, $22, $32, $32
    .BYTE   $11, $22, $27, $26
    .BYTE   $11, $17, $27, $26

PLTMAP:
    .BYTE   $01, $01, $01, $00, $00, $00, $00, $00
    .BYTE   $01, $02, $01, $01, $01, $00, $00, $00
    .BYTE   $01, $01, $01, $01, $01, $00, $00, $00

.ZEROPAGE

LEVEL_PTR:  ; address of the current metatile in the level map
    .RES    2


.BSS

BASE:
    .RES    1
ROW:
    .RES    1
COL:
    .RES    1
METATILE:
    .RES    1
NTAB_PTR:
    .RES    2


.CODE


.PROC INIT_LEVEL_PTR
    LDA #.LOBYTE(LEVEL_MAP)
    STA LEVEL_PTR
    LDA #.HIBYTE(LEVEL_MAP)
    STA LEVEL_PTR+1
    RTS
.ENDPROC


.PROC SET_METATILE
    LDY COL
    DEY
    LDA (LEVEL_PTR), Y
    STA METATILE
    RTS
.ENDPROC


; ------------------------------------------------------------------------------
; Calculate current address of the bottom left tile in the nametable.
; The formula is:
; ptr = (base << 8) + ((row-1)*2*32 + (col-1))
;
; TODO: testing is needed
; ------------------------------------------------------------------------------
.PROC SET_NTAB_PTR
    LDX #$00
    STX NTAB_PTR ; this will be the low byte of the address

    LDX ROW
    DEX
    TXA
    CLC
    ROR
    ROR NTAB_PTR
    ROR
    ROR NTAB_PTR
    ADC BASE
    STA NTAB_PTR+1 ; high byte of the address

    LDX COL
    DEX
    TXA
    ASL
    CLC
    ADC NTAB_PTR
    STA NTAB_PTR
    RTS
.ENDPROC


.PROC LOAD_METATILE
    LDY PPU_STATUS
    LDX NTAB_PTR+1
    STX PPU_ADDR
    LDA NTAB_PTR
    STA PPU_ADDR

    LDY METATILE
    STY PPU_DATA
    INY
    STY PPU_DATA

    LDY PPU_STATUS
    CLC
    ADC #$20    ; next row in VRAM
    BCC :+
    INX
:
    STX PPU_ADDR
    STA PPU_ADDR

    CLC
    LDA METATILE
    ADC #$10
    STA PPU_DATA

    CLC
    ADC #$01
    STA PPU_DATA

    RTS
.ENDPROC

; ------------------------------------------------------------------------------
; Increase level map pointer by 16, i.e. to the next row.
; If the pointer is reached the level data end, it's reset to the beginning.
; TODO: testing is needed.
; ------------------------------------------------------------------------------
.PROC INC_LEVEL_PTR
    CLC
    LDA LEVEL_PTR
    ADC #COL_MAX
    STA LEVEL_PTR

    LDX LEVEL_PTR+1
    BCC @LCMP           ; if carry flag was set, increment high byte
    INX
    STX LEVEL_PTR+1

    ; Check if we reached the end of the level map.
@LCMP:
    CPX #.HIBYTE(LEVEL_MAP_END) ; compare high byte of the address
    BCC @LDONE
    CMP #.LOBYTE(LEVEL_MAP_END) ; compare low byte of the address
    BCC @LDONE
    JMP INIT_LEVEL_PTR
@LDONE:
    RTS
.ENDPROC


.PROC INIT_NAMETABLE
    LDA #ROW_MAX
    STA ROW
@LROW:
    LDA #COL_MAX
    STA COL
@LCOL:
    JSR SET_METATILE
    JSR SET_NTAB_PTR
    JSR LOAD_METATILE
    DEC COL
    BNE @LCOL

    JSR INC_LEVEL_PTR
    DEC ROW
    BNE @LROW

    RTS
.ENDPROC


LEVEL_LOAD:
    LDA PPU_STATUS  ; reset address latch
    LDA #$3F
    STA PPU_ADDR
    LDA #$00
    STA PPU_ADDR
    TAX
@L01:
    LDA BG_PALETTE,X
    STA PPU_DATA
    INX
    CPX #$04
    BNE @L01

    LDA PPU_CTRL_VAR   ; set background tiles bank to 1
    ORA #%00010000
    STA PPU_CTRL_VAR

    JSR INIT_LEVEL_PTR

    LDA #$20
    STA BASE
    JSR INIT_NAMETABLE

    LDA #$28
    STA BASE
    JSR INIT_NAMETABLE

    LDX #0
    LDY #(MAX_SCROLL_Y-1)
    STX <SCROLL_X
    STY <SCROLL_Y

    RTS

; Subroutine which is called every frame from the main game loop.
; It updates the state of the level.
; On even frames it scrolls the background Y.
; TODO: On odd frames we load a piece of level (1 metatile) off the screen.
LEVEL_UPDATE:
    LDA #%00000001  ; check if the current frame is odd or even
    BIT <FRAME_CNT
    BEQ @scroll

    NOP
    JMP @done

@scroll:
    LDX <SCROLL_Y
    BNE @ydec

    LDX #MAX_SCROLL_Y
    LDA <PPU_CTRL_VAR   ; switch base nametable to display
    EOR #$02
    STA <PPU_CTRL_VAR

@ydec:
    DEX
    STX <SCROLL_Y

@done:
    RTS


LEVEL_RENDER:
    RTS

; end of file

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
; ptr = (base << 8) + ((row-1)*2*32 + (col-1)
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
    LDA PPU_STATUS
    LDA NTAB_PTR+1
    STA PPU_ADDR
    LDX NTAB_PTR
    STX PPU_ADDR

    LDA METATILE
    STA PPU_DATA

    CLC
    ADC #$10
    STA PPU_DATA


    LDA PPU_STATUS
    LDA NTAB_PTR+1
    STA PPU_ADDR
    LDX NTAB_PTR
    INX
    STX PPU_ADDR

    CLC
    LDA METATILE
    ADC #$01
    STA PPU_DATA

    CLC
    ADC #$10
    STA PPU_DATA

    RTS
.ENDPROC

; ------------------------------------------------------------------------------
; Increase level data pointer by 16, i.e. to the next row.
; If the pointer is reached the level data end, it's reset to the beginning.
;
;    LEVEL_PTR += 16 (COL_MAX)
;    IF LEVEL_PTR >= LEVEL_MAP_END:
;        LEVEL_PTR := LEVEL_MAP
;    ENDIF
;
; TODO: testing is needed.
; ------------------------------------------------------------------------------
.PROC INC_LEVEL_PTR
    ; ----------------------------------------------------------------
    ; Increment 16-bit pointer of the level data by 32

    ; add 16 (COL_MAX) to the low byte of the address
    CLC
    LDA LEVEL_PTR
    TAX                     ; keep low byte of the ptr in rX
    ADC #COL_MAX
    STA LEVEL_PTR

    ; if carry flag was set, increment high byte
    LDA LEVEL_PTR+1
    ADC #$00
    STA LEVEL_PTR+1
    ; ----------------------------------------------------------------

    ; ----------------------------------------------------------------
    ; Check if we reached end of the level data.
    ; If so, set level pointer to the beginning of the level data.
    ; Now rA contains high byte of the level pointer,
    ;   and rX contains the low byte of the level pointer.

    CMP #.HIBYTE(LEVEL_MAP_END) ; compare high byte
    BCC @LDONE
    CPX #.LOBYTE(LEVEL_MAP_END) ; compare low byte
    BCC @LDONE

    ; set level pointer to the beginning of the level data
    LDA #.LOBYTE(LEVEL_MAP)
    STA LEVEL_PTR
    LDA #.HIBYTE(LEVEL_MAP)
    STA LEVEL_PTR+1
    ; ----------------------------------------------------------------
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


; Subroutine that fills nametable in PPU VRAM, both tiles and attributes.
; Caller should set nametable address in PPU before calling this subroutine.
;.PROC   fill_nametable
;    LDY #30             ; number of rows in a nametable
;@L0:
;    LDX #LEVEL_WIDTH    ; number of tiles in a row
;@L1:
;    TYA
;    AND #$01        ; for even rows, tiles are 00 and 01; for odd: 10 and 11
;    ASL
;    ASL
;    ASL
;    ASL             ; now for even rows rA has $10, and for odd it's $00
;    ORA #$06
;    STA PPU_DATA
;    ORA #$01
;    STA PPU_DATA
;    DEX
;    BNE @L1
;    DEY
;    BNE @L0
;
;    LDA #$00
;    LDX #64 ; fill attribute table
;@L2: STA PPU_DATA
;    DEX
;    BNE @L2
;
;    RTS
;.ENDPROC


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
    ORA #%00010100      ; and set VRAM address increment to 32
    STA PPU_CTRL_VAR
    STA PPU_CTRL

    LDA #.LOBYTE(LEVEL_MAP)
    STA LEVEL_PTR
    LDA #.HIBYTE(LEVEL_MAP)
    STA LEVEL_PTR+1

    LDA #$20
    STA BASE
    JSR INIT_NAMETABLE
    ;LDA PPU_STATUS  ; reset address latch
    ;LDA #$20
    ;STA PPU_ADDR
    ;LDA #$00
    ;STA PPU_ADDR
    ;JSR fill_nametable

    LDA #$28
    STA BASE
    JSR INIT_NAMETABLE
    ;LDA PPU_STATUS  ; reset address latch
    ;LDA #$28
    ;STA PPU_ADDR
    ;LDA #$00
    ;STA PPU_ADDR
    ;JSR fill_nametable

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

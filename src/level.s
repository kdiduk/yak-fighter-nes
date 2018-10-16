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

    .export     _level_load, _level_update, _level_render
    .importzp   FRAME_CNT1, SCROLL_X, SCROLL_Y, TEMP
    .importzp   PPU_CTRL_VAR, PPU_MASK_VAR, VRAM_UPDATE
    .import     PAL_BUF
    .include    "ppu.s"


MAX_SCROLL_Y = 240


.SEGMENT "RODATA"


bg_palette:
    .BYTE   $02, $12, $22, $32
    .BYTE   $00, $00, $00, $00
    .BYTE   $00, $00, $00, $00
    .BYTE   $00, $00, $00, $00


.SEGMENT "CODE"


; Subroutine that fills nametable in PPU VRAM, both tiles and attributes.
; Caller should set nametable address in PPU before calling this subroutine.
.PROC   fill_nametable
    LDY #30         ; number of rows in a nametable
L0: LDX #16         ; number of tiles in a row
L1: TYA
    AND #$01        ; for even rows, tiles are 00 and 01; for odd: 10 and 11
    ASL
    ASL
    ASL
    ASL
    STA PPU_DATA
    ORA #$01
    STA PPU_DATA
    DEX
    BNE L1
    DEY
    BNE L0

    LDA #$00
    LDX #64 ; fill attribute table
L2: STA PPU_DATA
    DEX
    BNE L2

    RTS
.ENDPROC


_level_load:
    ;LDA PPU_STATUS  ; reset address latch
    ;LDA #$3F
    ;STA PPU_ADDR
    ;LDA #$00
    ;STA PPU_ADDR
    ;TAX
    LDX #$00
@L01:
    LDA bg_palette,X
    STA PAL_BUF,X
    INX
    CPX #$0F
    BNE @L01

    LDA <PPU_CTRL_VAR   ; set background tiles bank to 1
    ORA #%00010000
    STA <PPU_CTRL_VAR

    LDA PPU_STATUS  ; reset address latch
    LDA #$20
    STA PPU_ADDR
    LDA #$00
    STA PPU_ADDR
    JSR fill_nametable

    LDA PPU_STATUS  ; reset address latch
    LDA #$28
    STA PPU_ADDR
    LDA #$00
    STA PPU_ADDR
    JSR fill_nametable

    LDX #0
    LDY #(MAX_SCROLL_Y-1)
    STX <SCROLL_X
    STY <SCROLL_Y

    RTS


_level_update:

    LDA #%00000001
    BIT <FRAME_CNT1
    BNE @xscroll    ; we move scroll Y when frame counter is even

    LDX <SCROLL_Y
    CPX #0
    BNE @ydec

    LDX #MAX_SCROLL_Y
    LDA <PPU_CTRL_VAR
    EOR #$02
    STA <PPU_CTRL_VAR

@ydec:
    DEX
    STX <SCROLL_Y

@xscroll:
    RTS


_level_render:
    RTS

; end of file

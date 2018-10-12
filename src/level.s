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

    .export     _level_load_scroll, _level_update
    .importzp   FRAME_CNT1, SCROLL_X, SCROLL_Y, TEMP
    .importzp   PPU_CTRL_VAR, PPU_MASK_VAR


MAX_SCROLL_Y = 240

_level_load_scroll:
    LDX #0
    LDY #(MAX_SCROLL_Y-1)
    STX <SCROLL_X
    STY <SCROLL_Y

    LDA <PPU_CTRL_VAR
    EOR #$02
    STA <PPU_CTRL_VAR


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

; end of file

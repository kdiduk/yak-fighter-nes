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

; Implementation of NMI handler.
;
; Created on: 22 October, 2018
; Barcelona, Spain

    .EXPORT     NMI, IRQ
    .IMPORT     OAM_BUF
    .IMPORTZP   FRAME_CNT1, SCROLL_X, SCROLL_Y, PPU_CTRL_VAR, PPU_MASK_VAR
    .INCLUDE    "ppu.inc"


.CODE

NMI:
    PHA     ; push registers onto stack
    TXA
    PHA
    TYA
    PHA

    LDA #%00011000
    BIT <PPU_MASK_VAR
    BEQ @LSKIP          ; skip OAM update and scroll if rendering is disabled

    LDA #>OAM_BUF
    STA PPU_OAM_DMA

    ; TODO: background graphics update should be here

    LDA #0
    STA PPU_ADDR
    STA PPU_ADDR

    LDA <SCROLL_X
    STA PPU_SCROLL
    LDA <SCROLL_Y
    STA PPU_SCROLL

    LDA <PPU_CTRL_VAR
    STA PPU_CTRL

@LSKIP:
    LDA <PPU_MASK_VAR
    STA PPU_MASK

    INC <FRAME_CNT1

    PLA     ; restore registers values (pull from the stack)
    TAY
    PLA
    TAX
    PLA
IRQ:
    RTI


; end of file

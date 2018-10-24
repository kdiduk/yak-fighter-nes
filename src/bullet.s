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

; Implementation of player's bullets.
;
; Created on: 22 October, 2018
; Barcelona, Spain

    .EXPORT     BULLET_INIT, BULLET_FIRE, BULLET_UPDATE, BULLET_RENDER
    .IMPORT     OAM_BUF


MAX_BULLETS     =   32  ; maximum allowed number of bullets on the screen
SPRITE_TILE     =   $62
SPRITE_ATTR     =   $00
BULLET_OAMADDR  =   $30

.BSS

BULLET_COUNT:
    .BYTE   $00     ; current number of bullets active

BULLET_X:
    .RES    MAX_BULLETS, $00    ; array of x-coordinates of the bullets

BULLET_Y:
    .RES    MAX_BULLETS, $00    ; array of y-coordinates of the bullets


.CODE

; Initialize the module
BULLET_INIT:
    LDA #$00
    STA BULLET_COUNT
    RTS

; Adds a new bullet. Invoked when player fires.
; Parameters:
;   rX - position X of the bullet sprite
;   rY - position Y of the bullet sprite
BULLET_FIRE:
    TXA
    LDX BULLET_COUNT
    INX
    CPX #MAX_BULLETS    ; check if we reached maximum number of bullets
    BEQ @LDONE

    STA BULLET_X, X
    TYA
    STA BULLET_Y, X
    STX BULLET_COUNT
@LDONE:
    RTS


BULLET_UPDATE:
    LDX BULLET_COUNT
    LDY BULLET_COUNT
    BEQ @DONE
@ULOOP:
    LDA BULLET_Y-1, X
    SEC
    SBC #$02
    BPL @LKEEP
    DEY
    LDA BULLET_X, Y
    STA BULLET_X-1, X
    LDA BULLET_Y, Y
@LKEEP:
    STA BULLET_Y-1, X
    DEX
    BNE @ULOOP

@DONEA:
    STY BULLET_COUNT
    LDY #BULLET_OAMADDR
    LDX BULLET_COUNT
    BEQ @DONE
@RLOOP:
    LDA BULLET_Y-1, X      ; y position of the tile
    STA OAM_BUF, Y
    INY

    LDA #SPRITE_TILE    ; tile index
    STA OAM_BUF, Y
    INY

    LDA #SPRITE_ATTR     ; tile attributes
    STA OAM_BUF, Y
    INY

    LDA BULLET_X-1, X      ; x position of the tile
    STA OAM_BUF, Y
    INY

    DEX
    BNE @RLOOP
@DONE:
    RTS

BULLET_RENDER:
    RTS

; end of file

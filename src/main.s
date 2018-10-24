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

; Implementation main entry point: game initialization and game loop.
;
; Created on: 22 October, 2018
; Barcelona, Spain

    .EXPORT     MAIN
    .IMPORT     PLAYER_INIT, PLAYER_UPDATE, PLAYER_RENDER
    .IMPORT     LEVEL_LOAD, LEVEL_UPDATE, LEVEL_RENDER
    .IMPORTZP   FRAME_CNT1
    .IMPORTZP   PPU_MASK_VAR
    .IMPORTZP   PAD_STATE
    .INCLUDE    "bullet.inc"

GAMEPAD_PORT    =   $4016

.CODE

MAIN:
    LDA <PPU_MASK_VAR   ; disable background and sprites
    AND #%11100111
    STA <PPU_MASK_VAR

    JSR PLAYER_INIT
    JSR LEVEL_LOAD
    JSR BULLET_INIT

    LDA <PPU_MASK_VAR   ; enable background and sprites
    ORA #%00011000
    STA <PPU_MASK_VAR

@LOOP:

    LDA #$01            ; read gamepad status
    STA GAMEPAD_PORT
    STA <PAD_STATE      ; zero bit is set to be used as a loop counter 8 times
    LDA #$00            ; also "LSR A" is 1 byte less
    STA GAMEPAD_PORT
:   LDA GAMEPAD_PORT
    LSR A               ; bit 0 --> Cf
    ROL <PAD_STATE      ; Cf <-- bit 7 <-- ... <-- bit 0 <-- Cf
    BCC :-

    JSR LEVEL_UPDATE
    JSR PLAYER_UPDATE
    JSR BULLET_UPDATE

    LDA <FRAME_CNT1     ; wait for VBLANK
:   CMP <FRAME_CNT1
    BEQ :-

    JSR LEVEL_RENDER
    JSR PLAYER_RENDER
    JSR BULLET_RENDER

    JMP @LOOP

; end of file

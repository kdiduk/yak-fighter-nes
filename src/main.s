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
    .IMPORT     _player_init, _player_update, _player_render
    .IMPORT     _level_load, _level_update, _level_render
    .IMPORTZP   FRAME_CNT1
    .IMPORTZP   PPU_MASK_VAR
    .IMPORTZP   PAD_STATE

GAMEPAD_PORT    =   $4016

.CODE

MAIN:
    LDA <PPU_MASK_VAR   ; disable background and sprites
    AND #%11100111
    STA <PPU_MASK_VAR

    JSR _player_init
    JSR _level_load

    LDA <PPU_MASK_VAR   ; enable background and sprites
    ORA #%00011000
    STA <PPU_MASK_VAR

@LOOP:

    LDA #$01            ; read gamepad status
    STA GAMEPAD_PORT
    STA <PAD_STATE      ; zero bit is set to be used as a loop counter 8 times
    LDA #$00            ; also "LSD A" is 1 byte less
    STA GAMEPAD_PORT
:   LDA GAMEPAD_PORT
    LSR A               ; bit 0 --> Cf
    ROL <PAD_STATE      ; Cf <-- bit 7 <-- ... <-- bit 0 <-- Cf
    BCC :-

    JSR _level_update
    JSR _player_update

    LDA <FRAME_CNT1     ; wait for VBLANK
:   CMP <FRAME_CNT1
    BEQ :-

    JSR _level_render
    JSR _player_render

    JMP @LOOP

; end of file

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

; Implementation of NES gamepads state reading.
;
; Created on: 14 October, 2018
; Barcelona, Spain

    .export _gamepad_update, _gamepad_state
    .importzp PAD_STATE


GAMEPAD_PORT    =   $4016


_gamepad_update:
    LDA #$01
    STA GAMEPAD_PORT
    STA <PAD_STATE      ; zero bit is set to be used as a loop counter 8 times
    LDA #$00            ; also "LSD A" is 1 byte less
    STA GAMEPAD_PORT
@LOOP:
    LDA GAMEPAD_PORT
    LSR A               ; bit 0 --> Cf
    ROL <PAD_STATE      ; Cf <-- bit 7 <-- ... <-- bit 0 <-- Cf
    BCC @LOOP
    RTS


_gamepad_state:
    LDA <PAD_STATE
    LDX #$00
    RTS

; end of file

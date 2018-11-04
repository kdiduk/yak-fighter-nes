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

; Implementation of reset interrupt handler: NES initialization code.
;
; Created on: 03 November, 2018
; Barcelona, Spain


    .export _exit,__STARTUP__:absolute=1
    .exportzp FRAME_CNT, SCROLL_X, SCROLL_Y
    .exportzp PPU_CTRL_VAR, PPU_MASK_VAR
    .exportzp PAD_STATE
    .export OAM_BUF
    .import push0,popa,popax,zerobss,copydata

; Linker generated symbols
    .import __STACK_START__   ,__STACKSIZE__ ;changed
    .import __ROM0_START__  ,__ROM0_SIZE__
    .import __STARTUP_LOAD__,__STARTUP_RUN__,__STARTUP_SIZE__
    .import __CODE_LOAD__   ,__CODE_RUN__   ,__CODE_SIZE__
    .import __RODATA_LOAD__ ,__RODATA_RUN__ ,__RODATA_SIZE__
    .import MAIN, NMI, IRQ

    .importzp _PAD_STATE, _PAD_STATET ;added
    .include "zeropage.inc"
    .include "ppu.inc"


CTRL_PORT1  =$4016
CTRL_PORT2  =$4017

OAM_BUF     =$0200

.segment "ZEROPAGE"

FRAME_CNT:          .res 1
SCROLL_X:           .res 1
SCROLL_Y:           .res 1
PAD_STATE:          .res 2      ;one byte per controller
PPU_CTRL_VAR:       .res 1
PPU_MASK_VAR:       .res 1


.SEGMENT "STARTUP"

RESET:
_exit:

    SEI             ; ignore IRQ
    CLD             ; disable decimal mode

    LDX #$40
    STX CTRL_PORT2  ; disable APU frame IRQ

    LDX #$FF
    TXS             ; set up stack pointer
    INX             ; now X - 0
    STX PPU_CTRL    ; disable PPU NMI
    STX PPU_MASK    ; disable PPU rendering
    STX DMC_FREQ    ; disable DMC IRQs

    ; If we press "reset" during VBLANK, the VBLANK flag may keep true.
    ; Clear the flag so the following waiting loop reacts on actual VBLANK.
    LDA PPU_STATUS
@PPUWAIT01:
    LDA PPU_STATUS
    BPL @PPUWAIT01

    TXA
@RAMCLR:
    STA $0000, X
    STA $0100, X
    STA $0300, X    ; OAM buffer is at $02** so init it later
    STA $0400, X
    STA $0500, X
    STA $0600, X
    STA $0700, X
    INX
    BNE @RAMCLR

    LDA #$FF
@OAMCLR:
    STA OAM_BUF, X
    INX
    INX
    INX
    INX
    BNE @OAMCLR

@PPUWAIT02:
    BIT PPU_STATUS
    BPL @PPUWAIT02

    JSR zerobss
    JSR copydata

    LDA #<(__STACK_START__+__STACKSIZE__) ;changed
    STA sp
    LDA #>(__STACK_START__+__STACKSIZE__)
    STA sp+1            ; Set argument stack ptr

    LDA #%00000110
    STA <PPU_MASK_VAR   ; turn off sprites and background

    LDA #%10000000
    STA <PPU_CTRL_VAR
    STA PPU_CTRL        ; enable PPU NMI

    LDA <FRAME_CNT
:
    CMP <FRAME_CNT
    BEQ :-

    LDA #0
    STA PPU_SCROLL
    STA PPU_SCROLL

    JMP MAIN


.SEGMENT "VECTORS"

    .WORD NMI   ;$fffa vblank nmi
    .WORD RESET ;$fffc reset
    .WORD IRQ   ;$fffe irq / brk


.SEGMENT "CHARS"

    .INCBIN "tileset.chr"

; end of file

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

; Implementation of the player.
;
; Created on: 17 October, 2018
; Barcelona, Spain

    .EXPORT     _player_init, _player_update, _player_render
    .IMPORTZP   PPU_CTRL_VAR, PAD_STATE
    .IMPORT     OAM_BUF
    .INCLUDE    "gamepad.inc"
    .INCLUDE    "ppu.inc"


NUM_TILES       =   10
SPRITE_WIDTH    =   32
SPRITE_HEIGHT   =   32
SPRITE_ADDR     =   4


.RODATA

spr_palette:
    .BYTE   $0F, $0A, $1A, $0D, $0F, $0A, $1A, $02
    .BYTE   $0F, $15, $25, $35, $0F, $19, $29, $39

spr_tiles:
    .BYTE   $01, $02, $10, $11, $12, $13, $21, $22, $31, $32

tile_dx:
    .BYTE   $08, $10, $00, $08, $10, $18, $08, $10, $08, $10

tile_dy:
    .BYTE   $00, $00, $08, $08, $08, $08, $10, $10, $18, $18

spr_attr:
    .BYTE   $00, $00, $00, $01, $01, $00, $00, $00, $00, $00


.BSS

xpos:
    .BYTE $00

ypos:
    .BYTE $00


.CODE

_player_init:
    LDA PPU_STATUS
    LDA #$3F
    STA PPU_ADDR
    LDA #$10
    STA PPU_ADDR
    LDX #$00
@L0:
    LDA spr_palette, X
    STA PPU_DATA
    INX
    CPX #$08
    BNE @L0

    LDA <PPU_CTRL_VAR
    AND  #%11010111     ; set sprite size to 8x8 and pattern table address to 0
    STA <PPU_CTRL_VAR

    LDA #$90    ; initialize player position to the center of the screen
    STA xpos
    LDA #$88
    STA ypos


_player_update:
    LDA #GAMEPAD_LEFT   ; check if button "left" is pressed
    BIT <PAD_STATE
    BEQ :+
    LDA xpos            ; check that "xpos > 0"
    BEQ :+
    DEC xpos            ; move player to the left
:
    LDA #GAMEPAD_RIGHT  ; check if button "right" is pressed
    BIT <PAD_STATE
    BEQ :+
    LDA xpos            ; check that "xpos + 32 < 256"
    CMP #(256-SPRITE_WIDTH)
    BCS :+
    INC xpos            ; move player to the right
:
    LDA #GAMEPAD_UP     ; check if button "up" is pressed
    BIT <PAD_STATE
    BEQ :+
    LDA ypos            ; check that "ypos > 0"
    BEQ :+
    DEC ypos            ; move player up
:
    LDA #GAMEPAD_DOWN   ; check if button "down" is pressed
    BIT <PAD_STATE
    BEQ :+
    LDA ypos            ; check that "ypos + 32 < 40"
    CMP #(240-SPRITE_HEIGHT)
    BCS :+
    INC ypos            ; move player to the right
:
    RTS


_player_render:

    LDY #SPRITE_ADDR
    LDX #$00
@LP:
    LDA tile_dy, X      ; y position of the tile
    ADC ypos
    STA OAM_BUF, Y
    INY

    LDA spr_tiles, X    ; tile index
    STA OAM_BUF, Y
    INY

    LDA spr_attr, X     ; tile attributes
    STA OAM_BUF, Y
    INY

    LDA tile_dx, X      ; x position of the tile
    ADC xpos
    STA OAM_BUF, Y
    INY

    INX
    CPX #NUM_TILES
    BNE @LP

    RTS

; end of file

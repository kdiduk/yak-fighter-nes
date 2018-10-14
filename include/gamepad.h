/* ****************************************************************************
 *
 * MIT License
 *
 * Copyright (c) 2018 Kirill Diduk
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * ************************************************************************* */

#ifndef YF_GAMEPAD_H
#define YF_GAMEPAD_H

#include <stdint.h>

#define GAMEPAD_A       (0x01 << 7)
#define GAMEPAD_B       (0x01 << 6)
#define GAMEPAD_SELECT  (0x01 << 5)
#define GAMEPAD_START   (0x01 << 4)
#define GAMEPAD_UP      (0x01 << 3)
#define GAMEPAD_DOWN    (0x01 << 2)
#define GAMEPAD_LEFT    (0x01 << 1)
#define GAMEPAD_RIGHT   (0x01)


void    fastcall gamepad_update(void);
uint8_t fastcall gamepad_state(void);


#endif /* YF_GAMEPAD_H */

# #############################################################################
#
# MIT License
#
# Copyright (c) 2018 Kirill Diduk
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
# #############################################################################


# "Yak Fighter", a simple shoot-em-up game for Nintendo Entertainment System
#
# This is the single makefile for GNU Make tool for cross-compiling the
# project using cc65 toolchain. It contains rules to compile/assemble C and
# Assembly source files. C files are compiled into Assembly files first.
#
# File created on 07 October, 2018
# Barcelona, Spain

SHELL = /bin/sh

.SUFFIXES:
.SUFFIXES: .c .s .o

VPATH = ./include:./src

BINDIR = bin
OBJDIR = obj
INCDIR = include
DATDIR = data

# Keep intermediate assembly files, generated when compiling C files
.PRECIOUS: $(OBJDIR)/%.c.s

ROMCFG = cartridge.cfg
TARGET = yak-fighter.nes
LABELS = labels.txt

OBJECTS = $(addprefix $(OBJDIR)/, \
	main.o		\
	nmi.o		\
	player.o	\
	level.o		\
	startup.o)
LIBS = nes.lib

AS = ca65
CC = cc65
LD = ld65

AFLAGS = -g -I $(INCDIR) --bin-include-dir $(DATDIR)
CFLAGS = -Oirs -I $(INCDIR) --add-source

# Rules

all: $(BINDIR)/$(TARGET)

# Create output directories before compiling any source files
$(OBJECTS): | $(OBJDIR)
$(OBJDIR):
	mkdir -p $(OBJDIR)
	mkdir -p $(BINDIR)

$(BINDIR)/$(TARGET): $(OBJECTS)
	$(LD) -C $(ROMCFG) $(OBJECTS) $(LIBS) -Ln $(OBJDIR)/$(LABELS) -o $@

# Compiling C files into Assembly files
$(OBJDIR)/%.c.s: %.c
	$(CC) $(CFLAGS) $< -o $@

# Assembly files created from C files by the previous rule (above)
$(OBJDIR)/%.o: $(OBJDIR)/%.s
	$(AS) -g $< -o $@

# Source assembly files of the project (not created from C files)
$(OBJDIR)/%.o: %.s
	$(AS) $(AFLAGS) $< -o $@


.PHONY: clean
clean:
	rm -rf obj

# end of file

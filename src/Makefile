CC65 = cc65
CA65 = ca65
LD65 = ld65
NAME = yak-fighter


$(NAME).nes: main.o startup.o
	$(LD65) -C cartridge.cfg -o $(NAME).nes startup.o main.o nes.lib -Ln labels.txt

startup.o: startup.s
	$(CA65) startup.s

main.o: main.s
	$(CA65) main.s -g

main.s: main.c
	$(CC65) -Oirs main.c --add-source

clean:
	rm main.s
	rm main.o
	rm startup.o
	rm labels.txt

# end of file
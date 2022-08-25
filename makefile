nsortdisplay: main.c menu.c algolsel.c delaysel.c ncomp.c bubble.c quick.c
	gcc -o $@ $^ -Werror -Wall -lncurses -lpthread
clean:
	rm nsortdisplay

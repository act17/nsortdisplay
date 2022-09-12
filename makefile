nsortdisplay: main.c menu.c arraysel.c algolsel.c delaysel.c ncomp.c sorts/bubble.c sorts/quick.c
	gcc -o $@ $^ -Werror -Wall -lncurses -lpthread
clean:
	rm nsortdisplay

nsortdisplay: main.c menu/menu.c menu/arraysel.c menu/algolsel.c menu/delaysel.c ncomp.c sorts/bubble.c sorts/quick.c
	gcc -o $@ $^ -Werror -Wall -lncurses -lpthread
clean:
	rm nsortdisplay

nsortdisplay: main.c menu.c algolsel.c delaysel.c
	gcc -o $@ $^ -Werror -Wall -lncurses -lpthread
clean:
	rm nsortdisplay

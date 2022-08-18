nsortdisplay: main.c menu.c algolsel.c delaysel.c
	gcc -o $@ $^ -w -Wall -lncurses -lpthread
clean:
	rm nsortdisplay

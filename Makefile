OBJS = src/main.c src/ncomp.c src/menu/algolsel.c src/menu/arraysel.c src/menu/delaysel.c src/menu/menu.c src/sorts/bubble.c src/sorts/quick.c src/sorts/insert.c
CFLAG = -Wall -Werror -Wpedantic
CC = gcc
INCLUDE =
LIBS = -lpthread -lncurses
# This is used for formatting.
FM = astyle
FFLAG = -s2 -n

nsortdisplay:${OBJ}
	${CC} ${CFLAG} ${INCLUDES} -o $@ ${OBJS} ${LIBS} -O2

format:${OBJ}
	${FM} ${OBJS} ${FFLAG} 

debug:${OBJ}
	${CC} ${CFLAG} ${INCLUDES} -o $@ ${OBJS} ${LIBS} -g

clean:
	rm nsortdisplay debug

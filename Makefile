# Makefile by Panteleakis Ioannis
# mail: pioann@csd.auth.gr

SRC = *.cpp

OBJ = $(SRC:.c=.o)

OPT = -g -O3 -DVERSION="\"$(shell git show | head -n 1 | cut -d" " -f 2)-$(shell date +"%s")\""
CC = gcc $(OPT) -Wall

# You might have to change GLU to MesaGLU depending on your Mesa version
GLLIBS = -lglut -lGL -lGLU -I/usr/X11R6/include -L/usr/X11R6/lib
LIBS = $(GLLIBS) -lm -L/usr/local/lib -lenet -I/usr/local/include

all: yafanwebatpc tests

.c.o:
	$(CC) -c $<

yafanwebatpc: $(OBJ)
	$(CC) -o $@ $^ $(LIBS)
tests: $(OBJ)
	$(CC) -DRUN_TESTS -o $@ $^ $(LIBS)

clean:
	rm -f yafanwebatpc *.o

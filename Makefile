PRG = evader
CC = gcc
CFLAGS = -Wall
GL = -lglut -lGL -lGLU

$(PRG):
	$(CC) -o $(PRG) main.c funkcije.c $(CFLAGS) $(GL)

.PHONY: clean

clean:
	rm $(PRG)

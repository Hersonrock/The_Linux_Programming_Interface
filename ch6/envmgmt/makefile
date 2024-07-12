CC=gcc
CFLAGS=-Wall -g
#----ProgramName----#
NAME=main
#----Dependencies---#
DEP1=other
#------------#
IDIR=./include
OBJ=./src/main.o 

%.o:%.c 
	$(CC) -c -o $@ $< $(CFLAGS) -I$(IDIR)

./bin/$(NAME): $(OBJ)
	$(CC) -o $@ $^

clean:
	rm -rf ./bin/$(NAME) ./src/*.o


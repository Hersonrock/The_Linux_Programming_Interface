CC=gcc
CFLAGS=-Wall -g
#----ProgramName----#
NAME=filehole
OBJ=./src/filehole.o 

%.o:%.c 
	$(CC) -c -o $@ $< $(CFLAGS) 

./bin/$(NAME): $(OBJ)
	$(CC) -o $@ $^

clean:
	rm -rf ./bin/$(NAME) ./src/*.o


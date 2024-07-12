CC=gcc
CFLAGS=-Wall -g
#----ProgramName----#
NAME=main
#----Dependencies---#
DEP1=other
#------------#
IDIR=./include
DEPS=$(IDIR)/$(DEP1).h
OBJ=./src/main.o ./src/$(DEP1).o

%.o:%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) -I$(IDIR)

./bin/$(NAME): $(OBJ)
	$(CC) -o $@ $^

clean:
	rm -rf ./bin/$(NAME) ./src/*.o


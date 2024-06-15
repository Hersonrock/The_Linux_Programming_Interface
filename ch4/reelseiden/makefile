CC=gcc
CFLAGS=-Wall -g
#----ProgramName----#
NAME=main
#----Dependencies---#
DEP1=fileio
DEP2=split
DEP3=merge
DEP4=mem
#------------#
IDIR=./include
DEPS=$(IDIR)/$(DEP1).h
OBJ=./src/main.o ./src/$(DEP1).o ./src/$(DEP2).o ./src/$(DEP3).o \
    ./src/$(DEP4).o

%.o:%.c $(DEPS)
	$(CC) -c -std=c2x -o $@ $< $(CFLAGS) -I$(IDIR)

./bin/$(NAME): $(OBJ)
	$(CC) -o $@ $^

clean:
	rm -rf ./bin/$(NAME) ./src/*.o


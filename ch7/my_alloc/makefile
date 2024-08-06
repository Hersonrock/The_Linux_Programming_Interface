CC=gcc
CFLAGS=-Wall -g
#----ProgramName----#
NAME=main
#----Dependencies---#
#DEP1=other
#------------#
IDIR=./include
#DEPS=$(IDIR)/$(DEP1).h
OBJ=./src/main.o

%.o:%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) -I$(IDIR)

./bin/$(NAME): $(OBJ)
	$(CC) -o $@.out $^

clean:
	rm -rf ./bin/$(NAME) ./src/*.o


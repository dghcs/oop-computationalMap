OBJ=base.o
OBJ+=input.o
OBJ+=main.o
OBJ+=node.o

all:test
	@echo build all
test:$(OBJ)
	g++ $(OBJ) -o $@
clean:
	rm -f test
	rm -f $(OBJ)
.PHONY : clean
PROJ_NAME=main

#.cc files
CC_SOURCE=$(wildcard ./files/sources/*.cc)

# .h files
H_SOURCE=$(wildcard ./files/headers/*.h)

# Object files
OBJ=$(subst .cc,.o,$(subst src,objects,$(CC_SOURCE)))

# Compiler
CMP=g++

# Flags for compiler
CMP_FLAGS=-c -W -ansi -pedantic -std=c++11 -g

# Compilation and Linking
all: objFolder $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	$(CMP) -o $@ $^

./objects/%.o: ./src/%.cc ./src/%.h
	$(CMP) -o $@ $< $(CMP_FLAGS)

./objects/main.o: ./src/main.cc $(H_SOURCE)
	$(CMP) -o $@ $< $(CMP_FLAGS)

objFolder:
	mkdir -p objects

clean:
	rm -rf ./objects/*.o *~ $(PROJ_NAME)
	rmdir objects

.PHONY: all clean

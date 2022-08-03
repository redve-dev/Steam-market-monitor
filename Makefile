CXX		?= g++
LFLAGS 	?= -lcurl
DFLAGS	?= -pedantic -Wall -W -Wextra -Werror
CFLAGS	?= -std=c++17
OBJECTS	?= bin/functions.o bin/main.o bin/Item.o

FLAGS	?= ${DFLAGS} ${CFLAGS} ${LFLAGS}

target:	$(OBJECTS)
	$(CXX) -o SMM $(OBJECTS) ${FLAGS}

bin/%.o: src/%.cpp | bin
	$(CXX) -c -o $@ $< $(FLAGS)

bin:
	mkdir -p $@

clean:
	rm -rf bin SMM

bin/Item.o: src/Item/Item.cpp | bin
	$(CXX) -c -o $@ $< $(FLAGS)

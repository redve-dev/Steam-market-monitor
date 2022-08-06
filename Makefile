OUTPUT	?= steam-market-monitor
CXX		?= g++
LFLAGS 	?= -lcurl
DFLAGS	?= -pedantic -Wall -W -Wextra -Werror
CFLAGS	?= -std=c++17
OBJECTS	?= bin/main.o bin/Item.o bin/Interface.o

FLAGS	?= ${DFLAGS} ${CFLAGS} ${LFLAGS}

target:	$(OBJECTS)
	$(CXX) -o ${OUTPUT} $(OBJECTS) ${FLAGS}

bin/%.o: src/%.cpp | bin
	$(CXX) -c -o $@ $< $(FLAGS)

bin:
	mkdir -p $@

clean:
	rm -rf bin ${OUTPUT}

bin/Item.o: src/Item/Item.cpp src/Item/Item.hpp | bin
	$(CXX) -c -o $@ $< $(FLAGS)

bin/Interface.o: src/Interface/Interface.cpp src/Interface/Interface.hpp | bin
	$(CXX) -c -o $@ $< $(FLAGS)

format:
	clang-format -i src/main.cpp src/Item/* src/Interface/*

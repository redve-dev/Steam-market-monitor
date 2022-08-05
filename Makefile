OUTPUT	?= steam-market-monitor
CXX		?= g++
LFLAGS 	?= -lcurl
DFLAGS	?= -pedantic -Wall -W -Wextra -Werror
CFLAGS	?= -std=c++17
OBJECTS	?= bin/main.o bin/Item.o bin/InputData.o

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

bin/InputData.o: src/InputData/InputData.cpp src/InputData/InputData.hpp | bin
	$(CXX) -c -o $@ $< $(FLAGS)

#Thank you Michael Liu for blessing me with the daddy to this beautiful makefile. All credit dude.

LDLIBS=-lsfml-graphics -lsfml-window -lsfml-system


SOURCES=$(wildcard src/*.cc)
HEADERS=$(wildcard src/*.hpp)
SRC_W_H=$(notdir $(HEADERS:.hpp=.cc))
OBJECTS=$(addprefix obj/,$(notdir $(SOURCES:.cc=.o)))


all: main $(SOURCES)
	@echo "\033[92mCompile Complete\033[0m"
    
main: $(OBJECTS)
	@echo "\033[94mLinking...\033[0m"
	@g++ -o main $(OBJECTS) $(LDLIBS)

obj/%.o:src/%.cc $(HEADERS)
	@echo "Compiling\033[91m $<... \033[0m"
	@g++ -o $@ -c $<

clean:
	@echo KABOOM
	rm -f obj/* main

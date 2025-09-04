#SANITIZERS=-fsanitize=address -fsanitize=leak -fsanitize=undefined -fsanitize=thread
#SANITIZERS=-fsanitize=address -fsanitize=leak -fsanitize=undefined 
CXXFLAGS=-std=gnu++17 -Wall -g ${SANITIZERS}
LDFLAGS=${SANITIZERS}
all:main
main:main.o icao.o
clean:
	rm -f main main.o icao.o

#clang-format -style=gnu -i *.cpp

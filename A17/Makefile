CFLAGS = -std=c++17 -O2
INC=-I ./headers
LDFLAGS = -lglfw -lvulkan -ldl -lpthread

VulkanTest: Assignment17.cpp
	g++ $(CFLAGS) $(INC) -o main Assignment17.cpp $(LDFLAGS)

.PHONY: test clean

test: main
	./main

clean:
	rm -f main
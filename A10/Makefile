CFLAGS = -std=c++17 -O2
INC=-I ./headers
LDFLAGS = -lglfw -lvulkan -ldl -lpthread

VulkanTest: main.cpp
	g++ $(CFLAGS) $(INC) -o main main.cpp $(LDFLAGS)

.PHONY: test clean

test: main
	./main

clean:
	rm -f main
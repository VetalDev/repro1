CXX=g++
CC=gcc
WHERE=home

INCLUDES=-I./

LIBS=

DEFINEDS=-D_GNU_SOURCE -DGL_GLEXT_PROTOTYPES

CFLAGS=$(INCLUDES) $(LIBS) -O0 -ggdb3

all:
	@$(CXX) $(CFLAGS) $(DEFINEDS) -std=c++11 -c simple_reproducer.cpp -lX11 -lGL -ldl  -o simple_reproducer.o
	@$(CXX) $(CFLAGS) $(DEFINEDS) simple_reproducer.o -lX11 -lGL -ldl -lglfw -lGLEW -o simple_reproducer
	@echo "simple_reproducer completed."
	@chmod +x simple_reproducer

clean:
	rm -f *.o
	rm -f simple_reproducer
GCC = g++
CFLAGS = -std=c++11
LIBS = -lGL -lGLU -lglut
OBJS = main.o
EXE = main

$(EXE): $(OBJS)
	$(GCC) $(LIBS) $(OBJS) -o $(EXE)

main.o: main.cpp
	$(GCC) $(CFLAGS) -c main.cpp

clean:
	rm $(OBJS) $(EXE)

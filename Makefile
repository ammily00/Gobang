CXX = g++
CXXFLAGS = -Wall -Werror -g
OPENCV = `pkg-config opencv --cflags --libs`

main: main.o \
      Board.o \
      Game.o \
	  Guiboard.o \
	  Guigame.o
	$(CXX) $(CXXFLAGS) -o main \
           main.o Board.o Game.o \
		   Guiboard.o Guigame.o \
		   $(OPENCV)

main.o: main.cpp \
	Board.cpp \
	Game.cpp \
	Guiboard.cpp \
	Guigame.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

Board.o: Stone.h Board.h

Game.o: Stone.h Board.h Move.h Game.h

Guiboard.o: Stone.h Board.h Guiboard.h

Guigame.o: Stone.h Board.h Move.h Game.h Guiboard.h Guigame.h 

clean:
	rm main \
       main.o Board.o Game.o \
	   Guiboard.o Guigame.o \

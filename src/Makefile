PROGRAM_NAME = boids

RM = /bin/rm -f

LIBRARIES = -lglut -lGL -lGLU -lm
INCLUDE = -I/usr/X11R6/include/
LIBRARIES_DIRECTORY  = -L/usr/X11R6/lib
CC = g++ -Wall

######################################################################

MODULES = GameEngine.o GameObject.o Boid.o LeaderBoid.o Tower.o Drawing.o Vector.o Box.o

######################################################################

first: clean run

run: $(PROGRAM_NAME)
	@./$(PROGRAM_NAME)

######################################################################

$(PROGRAM_NAME): Main.cpp $(MODULES)
	$(CC) $(INCLUDE) $(LIBRARIES_DIRECTORY) $(MODULES) -o $(PROGRAM_NAME) $< $(LIBRARIES)

######################################################################

# Auxiliary modules

GameEngine.o: GameEngine.cpp GameEngine.hpp
	$(CC) -c GameEngine.cpp

GameObject.o: GameObject.cpp GameObject.hpp
	$(CC) -c GameObject.cpp

Boid.o: Boid.cpp Boid.hpp
	$(CC) -c Boid.cpp

LeaderBoid.o: LeaderBoid.cpp LeaderBoid.hpp
	$(CC) -c LeaderBoid.cpp

Tower.o: Tower.cpp Tower.hpp
	$(CC) -c Tower.cpp

Drawing.o: Drawing.cpp Drawing.hpp
	$(CC) -c Drawing.cpp

Box.o: Box.cpp Box.hpp
	$(CC) -c Box.cpp

Vector.o: Vector.cpp Vector.hpp
	$(CC) -c Vector.cpp

######################################################################

clean:
	@$(RM) *.o core $(PROGRAM_NAME)
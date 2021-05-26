# $(BIN) est le nom du binaire généré
BIN = visu
# FLAG
FLAGS = -Wall -O3
# INCLUDES
INC = -I./
# INCLUDES
LIBS = -lglut -lGLU -lGL -lm -lstdc++ -Wall -lSDL -lSDL_image
# INCLUDES
LIBDIR =
# Compilateur
GCC = gcc
# $(OBJECTS) sont les objets qui seront générés après la compilation
OBJECTS = geometry.o light.o gldrawing.o visu.o create_object.o valDeGris.o quadtree.o

default: $(BIN)

all: $(OBJECT)

$(BIN): $(OBJECTS)
	@echo "**** PHASE DE LIEN ****"
	$(GCC) $(OBJECTS) $(FLAGS) -o $(BIN) $(LIBDIR) $(LIBS) 

geometry.o: geometry.cpp geometry.h
	@echo "**** $@ ****"
	$(GCC) $(INC) $(FLAGS) -c $< -o $@

light.o: light.cpp light.h
	@echo "**** $@ ****"
	$(GCC) $(INC) $(FLAGS) -c $< -o $@


visu.o: visu.cpp visu.h
	@echo "**** td1_maze.c ****"
	$(GCC) $(INC) $(FLAGS) -c $< -o $@

gl_drawing.o: gl_drawing.cpp gl_drawing.h
	@echo "**** $@ ****"
	$(GCC) $(INC) $(FLAGS) -c $< -o $@

create_object.o: create_object.cpp create_object.h
	@echo "**** $@ ****"
	$(GCC) $(INC) $(FLAGS) -c $< -o $@

	
valDeGris.o: valDeGris.cpp valDeGris.h
	@echo "**** $@ ****"
	$(GCC) $(INC) $(FLAGS) -c $< -o $@

quadtree.o: quadtree.cpp quadtree.h
	@echo "**** $@ ****"
	$(GCC) $(INC) $(FLAGS) -c $< -o $@
	


clean:
	rm -f *.o $(BIN)
	find . -name "*~" -exec rm {} \;

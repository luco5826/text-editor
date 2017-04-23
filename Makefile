CPP=g++
FLAGS= -std=c++11
LIBS= -lsfml-graphics -lsfml-window -lsfml-system

all: editor

editor: Editor.cpp TextView.cpp TextDocument.cpp
		@echo "** Building main"
		g++ $(FLAGS) -o editor Editor.cpp TextView.cpp TextDocument.cpp $(LIBS)

clean:
		@echo "** Cleaning..."
		rm -f editor *.o
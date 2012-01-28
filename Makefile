ifeq ($(SHELL), sh.exe) 
	OS := Win
else
	OS := $(shell uname)
endif

LIBS = -lsfml-graphics -lsfml-window -lsfml-system
EXE := GameEngine

ifeq ($(OS), Darwin) #Mac OS X Ici l'ordre est inverse mais je ne suis pas certain si c'est important car en changeant l'ordre tout compile et se lance bien
	LIBS := -framework sfml-system -framework sfml-window -framework sfml-graphics -framework sfml-audio
	DEL := rm
	EXE := GameEngine.out
endif

ifeq ($(OS), Win))
	LIBS := -lsfml-graphics -lsfml-window -lsfml-system
	DEL := del
	EXE := GameEngine.exe
endif


CPP = g++

C = $(wildcard *.cpp)
O = $(C:.cpp=.o)
H = $(C:.cpp=.h)
OPTION = -Wall -pedantic

all : $(EXE)
	$(DEL) *.o
	./$(EXE)

$(EXE) : $(O)
	$(CPP) $^ -o $@ $(LIBS)

%.o : %.cpp %.h
	$(CPP) $(OPTION) -c $< -o $@
	
os:
	echo $(OS)

clean:
	$(DEL) *.o $(EXE)

git:
	git commit -a -m '[Commit depuis le MakeFile]' ; \
	git push -u origin master git@github.com:JumpingNinja/GameEngine.git

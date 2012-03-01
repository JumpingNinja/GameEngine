ifeq ($(SHELL), sh.exe) 
	OS := Win
else
	OS := $(shell uname)
endif

LIBS = -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
EXE := GameEngine
OBJ_DIR := obj
BIN_DIR := bin
MKDIR := mkdir -p
OPENFILE := open
NEWFILE := touch

ifeq ($(OS), Darwin) #Mac OS X Ici l'ordre est inverse mais je ne suis pas certain si c'est important car en changeant l'ordre tout compile et se lance bien
	LIBS := -framework sfml-system -framework sfml-window -framework sfml-graphics -framework sfml-audio
	DEL := rm
	EXE := GameEngine.out
	MKDIR := mkdir -p
	OPENFILE := open
	NEWFILE := touch
endif

ifeq ($(OS), Win)
	LIBS := -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
	DEL := del
	EXE := GameEngine.exe
	MKDIR := mkdir
	#A trouver les commandes �quivalentes
	OPENFILE := echo
	NEWFILE := echo
endif


CPP := g++

C := $(wildcard *.cpp)
_O := $(C:.cpp=.o)
O := $(patsubst %,$(OBJ_DIR)/%,$(_O)) #�a permet de mettre les .o dans le dossier obj/
#H := $(C:.cpp=.h)
H := $(wildcard *.h)
HPP := $(wildcard *.hpp)
OPTION := -pedantic -Wall -Wextra -Wold-style-cast -Woverloaded-virtual -Wfloat-equal -Wwrite-strings -Wpointer-arith -Wcast-qual -Wcast-align -Wconversion -Wshadow -Weffc++ -Wredundant-decls -Winit-self -Wswitch-default -Wswitch-enum -Wundef -Winline -s

ifeq ($(OS), Win)
all : $(EXE)
else
all : dirs $(EXE)
endif
#$(DEL) *.o
	./$(BIN_DIR)/$(EXE)
	
debug: debug_option all

debug_option:
OPTION := -pedantic -Wall -Wextra -Wold-style-cast -Woverloaded-virtual -Wfloat-equal -Wwrite-strings -Wpointer-arith -Wcast-qual -Wcast-align -Wconversion -Wshadow -Weffc++ -Wredundant-decls -Winit-self -Wswitch-default -Wswitch-enum -Wundef -Winline -s -ggdb
	
dirs: #Permet de creer des dossiers pour mettre les obj et les bin. L'option -p permet de cr�er les dossier que s'ils n'existent pas (elle cr�e aussi tous les dossier intermediaires). Le @ sert � ne pas afficher l'appel de la commande
	@$(MKDIR) obj
	@$(MKDIR) bin

$(EXE) : $(O)
	$(CPP) $^ -o $(BIN_DIR)/$@ $(LIBS)

$(OBJ_DIR)/%.o : %.cpp %.h
	$(CPP) $(OPTION) -c $< -o $@
	
$(OBJ_DIR)/IniParser.o : IniParser.cpp IniParser.hpp
	$(CPP) $(OPTION) -c $< -o $@
	
#On a besoin de sp�cifier manuellement pour main.o (sinon erreur)
$(OBJ_DIR)/main.o : main.cpp
	$(CPP) $(OPTION) -c $< -o $@
	
os:#Permet de savoir l'OS
	@echo $(OS)

clean:
	$(DEL) $(OBJ_DIR)/*.o $(BIN_DIR)/$(EXE)

git: #� utiliser le moins souvent possible car pas de description du commit :(
	git commit -a -m '[Commit depuis le MakeFile]' ; \
	git push -u git@github.com:JumpingNinja/GameEngine.git
	
#Fait la doc. J'utilise un dummy.file pour permettre l'�x�cution de doxygen toujours (pas de message de make du genre "doc is up to date"
doc: dummy.file
	@echo 'G�n�ration de la documentation dans doc'
	@$(MKDIR) doc
	@doxygen Doxyfile 
	@$(DEL) dummy.file
	@$(OPENFILE) doc/html/index.html
dummy.file:
	@$(NEWFILE) dummy.file

ifeq ($(SHELL), sh.exe) 
	OS := Win
else
	OS := $(shell uname)
endif

CPP = g++
EXE = SFML_Test.exe
C = $(wildcard *.cpp)
O = $(C:.cpp=.o)
H = $(C:.cpp=.h)
OPTION = -Wall -pedantic
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

all : $(EXE)

$(EXE) : $(O)
	$(CPP) $^ -o $@ $(LIBS)

%.o : %.cpp %.h
	$(CPP) $(OPTION) -c $< -o $@
	
os:
	echo $(OS)

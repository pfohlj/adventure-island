##########################################################################################
# Joseph A Pfohl // makefile for Final Project
# 
# - To make the game: "make all" or "make gameMain"
# - To make any indivdual object: make "objectname.o" whre objectName is replaced with the
# name of the file you are building.
# - To clean the directory: "make clean"
##########################################################################################
CXX = g++
CXXFLAGS = -std=c++11
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g

HDRS = Basement.hpp Beach.hpp Cave.hpp Clearing.hpp Cliff.hpp Dungeon.hpp GameManager.hpp HelperFunctions.hpp Hut.hpp Island.hpp Item.hpp List.hpp Location.hpp Player.hpp Reef.hpp Ruins.hpp Temple.hpp
SRCS = Basement.cpp Beach.cpp Cave.cpp Clearing.cpp Cliff.cpp Dungeon.cpp gameMain.cpp GameManager.cpp HelperFunctions.cpp Hut.cpp Island.cpp Item.cpp List.cpp Location.cpp Player.cpp Reef.cpp Ruins.cpp Temple.cpp
OBJS = Basement.o Beach.o Cave.o Clearing.o Cliff.o Dungeon.o gameMain.o GameManager.o HelperFunctions.o Hut.o Island.o Item.o List.o Location.o Player.o Reef.o Ruins.o Temple.o
PROGS = gameMain

all: ${PROGS}

gameMain: ${OBJS}
	${CXX} ${OBJS} -o gameMain
	
${OBJS}: ${SRCS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)

clean:
	rm -f ${PROGS} *.o *~
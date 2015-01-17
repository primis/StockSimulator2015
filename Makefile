###############################################################################
##        Stock Simulator 2015 Makefile - Updated 1/17/2015 (primis)         ##
###############################################################################

CPP_SOURCES = $(shell ls *.cpp)
OBJS		= $(CPP_SOURCES:.cpp=.o)

CC 			= g++
CPP_FLAGS	= -w
LINK_FLAGS	= -lSDL2 -lSDL2_mixer

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINK_FLAGS) -o StockSimulator2015
clean:
	rm *.o

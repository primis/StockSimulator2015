###############################################################################
##        Stock Simulator 2015 Makefile - Updated  02/05/17 (primis)         ##
###############################################################################
## Updates:
## 1/17/15: Initial Writeup (primis)
## 2/05/17: Fix for Mingw (primis)

CPP_SOURCES = $(shell ls *.cpp)
OBJS		= $(CPP_SOURCES:.cpp=.o)

CPP_FLAGS	= -w
LINK_FLAGS	= -lSDL2 -lSDL2_mixer
WIN_FLAGS	= -lmingw32 -lSDL2main -mconsole -lSDL2 -lSDL2_mixer

all : $(OBJS)
	$(CXX) $(OBJS) $(LINK_FLAGS) -o StockMarketSimulator2015
win :
	$(CXX) $(CPP_SOURCES) $(CPP_FLAGS) $(WIN_FLAGS) -o StockMarketSimulator2015.exe

clean:
	rm *.o

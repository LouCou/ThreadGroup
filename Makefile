include inc.mk

.PHONY: all clean

SOURCES = ${wildcard *.cpp}
OBJECTS = ${SOURCES:.cpp=.o}

all: $(OBJECTS)
	$(COMPILER) -o run.exe *.o $(LIBS)

clean:
	rm -f ./*.o
	rm -f ./*.exe
	
%.o: %.cpp
	$(COMPILER) -o $@ -c $< 


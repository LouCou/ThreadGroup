include inc.mk

.PHONY: all clean

SOURCES = ${wildcard *.cpp}
OBJECTS = ${SOURCES:.cpp=.o}
EXECNAME = run.out

all: $(OBJECTS)
	$(COMPILER) -o $(EXECNAME) *.o $(LIBS)

clean:
	rm -f *.o
	rm -f $(EXECNAME)
	
%.o: %.cpp
	$(COMPILER) -o $@ -c $<


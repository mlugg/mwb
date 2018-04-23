.POSIX:
.PHONY: all clean

CXXFLAGS := -Wall -Werror
LDFLAGS :=

include config.mk

SOURCE := $(wildcard *.cpp)
OBJECTS := $(patsubst %.cpp,%.o,$(SOURCE))

all: mwb

clean:
	rm -f mwb
	rm -f *.o

mwb: $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $<


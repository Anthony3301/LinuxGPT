CXX = g++-11 -std=c++20
CXXFLAGS = -Wall -g -MMD -I./include # use -MMD to generate dependencies
SOURCES = $(wildcard src/*.cc)   # list of all .cc files in the current directory
OBJECTS = ${SOURCES:src/%.cc=build/%.o}  # .o files depend upon .cc files with same names
DEPENDS = ${OBJECTS:.o=.d}   # .d file is list of dependencies for corresponding .cc file
EXEC= linuxGPT

# First target in the makefile is the default target.
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC)  $(LIBFLAGS)

build/%.o: src/%.cc 
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(LIBFLAGS)

-include ${DEPENDS}

.PHONY: clean tests
clean:
	rm  -f $(OBJECTS) $(DEPENDS) $(EXEC)


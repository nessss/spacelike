CC   	   := g++

$(shell mkdir -p build bin .d > /dev/null)

CXXFLAGS   := -std=c++11 -Wall -I ../include
LFLAGS     := -lncursesw
EXTRAGLAGS := -g

DEPFLAGS    = -MT $@ -MMD -MP -MF .d/$*.Td
POSTCOMPILE = mv -f .d/$*.Td .d/$*.d

.SUFFIXES: cpp o d

SOURCES     := $(shell find ../src -type f -name '*.cpp')
SOURCES		:= $(filter-out ../src/main.cpp, $(SOURCES))
TESTSOURCES := $(shell find . -type f -name '*.cpp')

OBJECTS     := $(patsubst ../src/%,../build/%,$(SOURCES:.cpp=.o))
TESTOBJECTS := $(patsubst ./%,build/%,$(TESTSOURCES:.cpp=.o))

INCLUDES    := $(patsubst ./%,.d/%,$(SOURCES:.cpp=.d))

all: bin/test

bin/test: $(TESTOBJECTS) $(OBJECTS)
	$(CC) $(OBJECTS) $(TESTOBJECTS) -o $@ $(LFLAGS)

clean:
	@-rm -rf build/*

build/%.o: ./%.cpp .d/%.d
	$(CC) $(DEPFLAGS) $(EXTRAFLAGS) $(CXXFLAGS) -c $< -o $@
	$(POSTCOMPILE)

.d/%.d: ;
.PRECIOUS: .d/%.d

.PHONY: all clean

-include $(INCLUDES)

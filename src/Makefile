CC   	  := g++
TARGET 	  := spacelike

CXXFLAGS  := -g -std=c++11 -Wall -I ../include/
LFLAGS    := -lncurses
GUIDFLAGS := 

SRC       := .
INCLUDE   := ../include
BUILD 	  := ../build
BIN       := ../bin
SRCEXT    := cpp
OBJEXT    := o

SOURCES   := $(shell find $(SRC) -type f -name '*.$(SRCEXT)')
OBJECTS   := $(patsubst $(SRC)/%,$(BUILD)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))
NAMES	  := $(notdir $(basename $(SOURCES)))

UNAME := "$(shell uname -a)"

ifneq (,$(findstring Cygwin, $(UNAME)))
	GUIDFLAGS = -DGUID_WINDOWS
	LFLAGS += -lOle32
endif

ifneq (,$(findstring Darwin, $(UNAME)))
	GUIDFLAGS = -DGUID_CFUUID
	LFLAGS += -framework CoreFoundation
endif

all: directories $(TARGET)

$(NAMES): % : $(BUILD)/%.$(OBJEXT) $(directories)

test:
	@echo "$(NAMES)"

directories:
	@mkdir -p $(BUILD)
	@mkdir -p $(BIN)

clean:
	@-rm -rf ../build/*

$(TARGET): $(directories) $(OBJECTS)
	$(CC) $(OBJECTS) -o $(BIN)/$(TARGET) $(LFLAGS)

$(BUILD)/%.$(OBJEXT): $(SRC)/%.$(SRCEXT)
	$(CC) $(CXXFLAGS) -c $< -o $@

$(BUILD)/guid.o: $(directories) $(SRC)/guid.cpp
	$(CC) $(CXXFLAGS) -c $(SRC)/guid.cpp -o ../build/guid.o $(GUIDFLAGS)

.PHONY: all directories clean $(NAMES)

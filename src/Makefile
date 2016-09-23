CC   	  := g++
TARGET 	  := spacelike

SRCDIR    := .
INCDIR    := ../include
BUILDDIR  := ../build
BINDIR    := ../bin
DEPDIR    := .d

SRCEXT    := cpp
OBJEXT    := o
DEPEXT    := d

CXXFLAGS  := -g -std=c++11 -Wall -I $(INCDIR)
LFLAGS    := -lncurses
GUIDFLAGS := 

DEPFLAGS   = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
POSTCOMPILE = mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d

.SUFFIXES: $(SRCEXT) $(OBJEXT) $(DEPEXT)

SOURCES   := $(shell find $(SRCDIR) -type f -name '*.$(SRCEXT)')
OBJECTS   := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))
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

$(NAMES): % : $(BUILDDIR)/%.$(OBJEXT) $(directories)

test:
	@echo "$(NAMES)"

directories:
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(BINDIR)
	@mkdir -p $(DEPDIR)

clean:
	@-rm -rf ../build/*
	@-rm -rf .d

$(TARGET): $(directories) $(OBJECTS)
	$(CC) $(OBJECTS) -o $(BINDIR)/$(TARGET) $(LFLAGS)

$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT) $(DEPDIR)/%.d
	$(CC) $(GUIDFLAGS) $(DEPFLAGS) $(CXXFLAGS) -c $< -o $@
	$(POSTCOMPILE)

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

.PHONY: all directories clean $(NAMES)

-include $(patsubst $(SRCDIR)/%,%,$(SOURCES:.$(SRCEXT)=.$(DEPEXT)))

CC   	  := g++
TARGET 	  := spacelike

SRCDIR    := .
INCDIR    := ../include
BUILDDIR  := ../build
BINDIR    := ../bin
DEPDIR    := .d

$(shell mkdir -p $(BUILDDIR) $(BINDIR) $(DEPDIR) > /dev/null)

SRCEXT    := cpp
OBJEXT    := o
DEPEXT    := d

CXXFLAGS   := -std=c++11 -Wall -I $(INCDIR)
LFLAGS     := -lncurses
EXTRAFLAGS := -g

DEPFLAGS    = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
POSTCOMPILE = mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d

.SUFFIXES: $(SRCEXT) $(OBJEXT) $(DEPEXT)

SOURCES   := $(shell find $(SRCDIR) -type f -name '*.$(SRCEXT)')
OBJECTS   := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))
NAMES	  := $(notdir $(basename $(SOURCES)))

UNAME := "$(shell uname -a)"

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(BINDIR)/$(TARGET) $(LFLAGS)

optimize:: EXTRAFLAGS := -O3
optimize:: clean all

$(NAMES): % : $(BUILDDIR)/%.$(OBJEXT) $(directories)

test:
	@echo "$(NAMES)"

clean:
	@-rm -rf ../build/*

$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT) $(DEPDIR)/%.d
	$(CC) $(DEPFLAGS) $(EXTRAFLAGS) $(CXXFLAGS) -c $< -o $@
	$(POSTCOMPILE)

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

.PHONY: all directories clean $(NAMES)

-include $(patsubst $(SRCDIR)/%,%,$(SOURCES:.$(SRCEXT)=.$(DEPEXT)))

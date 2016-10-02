CC   	   := g++

SRCDIR     := .
INCDIR     := ../include
BUILDDIR   := ../build
BINDIR     := ../bin
DEPDIR     := .d

TARGET 	   := $(BINDIR)/spacelike

$(shell mkdir -p $(BUILDDIR) $(BINDIR) $(DEPDIR) > /dev/null)

SRCEXT     := cpp
OBJEXT     := o
DEPEXT     := d

CXXFLAGS   := -std=c++11 -Wall -I $(INCDIR)
LFLAGS     := -lncursesw
EXTRAFLAGS := -g

DEPFLAGS    = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
POSTCOMPILE = mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d

.SUFFIXES: $(SRCEXT) $(OBJEXT) $(DEPEXT)

SOURCES    := $(shell find $(SRCDIR) -type f -name '*.$(SRCEXT)')
OBJECTS    := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))
INCLUDES   := $(patsubst $(SRCDIR)/%,$(DEPDIR)/%,$(SOURCES:.$(SRCEXT)=.$(DEPEXT)))
NAMES	   := $(notdir $(basename $(SOURCES)))


UNAME := "$(shell uname -a)"

all: $(TARGET) test

test:
	@-cd ../test && $(MAKE)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(BINDIR)/$(TARGET) $(LFLAGS)

optimize:: EXTRAFLAGS := -O3
optimize:: clean all

$(NAMES): % : $(BUILDDIR)/%.$(OBJEXT)

clean:
	@-rm -rf ../build/*

print-%: ; @echo $* = $($*) @true

$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT) $(DEPDIR)/%.d
	$(CC) $(DEPFLAGS) $(EXTRAFLAGS) $(CXXFLAGS) -c $< -o $@
	$(POSTCOMPILE)

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

.PHONY: all clean $(NAMES)

-include $(INCLUDES)

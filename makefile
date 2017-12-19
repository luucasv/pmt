CXX=g++
RM=rm -f
MK=mkdir -p
CPPFLAGS=-std=c++11 -O2  -Wall -Werror -Wconversion -flto
LDLIB=-lm -flto -O2

OUTPUTDIR=bin
SRCDIR=src
SRCEXT=cc

SRCS=$(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJS=$(subst .cc,.o,$(SRCS))

all: mkdirs pmt clean

pmt: $(OBJS)
	$(CXX) -o $(OUTPUTDIR)/pmt $(OBJS) $(LDLIB)

%.o : $(SRCDIR)/%.cc
	$(CXX) $(CPPFLAGS) -c $< -o $(OUTPUTDIR)/$@ $(DEFS)

mkdirs:
	$(MK) $(OUTPUTDIR)

clean:
	$(RM) $(OBJS)

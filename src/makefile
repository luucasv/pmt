CXX=g++
RM=rm -rf
MK=mkdir
CPPFLAGS=-std=c++11 -O2 -Wall -Werror -Wconversion
LDLIB=-lm
OUTPUT_DIR=../bin

SRCS=pmt.cc lib/util.cc lib/parse_args.cc
OBJS=$(subst .cc,.o,$(SRCS))

all: rmdirs mkdirs pmt clean

pmt: $(OBJS)
	$(CXX) -o $(OUTPUT_DIR)/pmt $(OBJS) $(LDLIB)

%.o : %.cc
	$(CXX) $(CPPFLAGS) -c $< -o $@

rmdirs:
	$(RM) $(OUTPUT_DIR)

mkdirs:
	$(MK) $(OUTPUT_DIR)

clean:
	$(RM) $(OBJS)
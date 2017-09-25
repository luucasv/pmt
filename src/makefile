CXX=g++
RM=rm -rf
MK=mkdir
CPPFLAGS=-std=c++11 -O2
LDLIB=-lm
OUTPUT_DIR=../bin

SRCS=pmt.cpp lib/util.cpp lib/parse_args.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: rmdirs mkdirs pmt clean

pmt: $(OBJS)
	$(CXX) -o $(OUTPUT_DIR)/pmt $(OBJS) $(LDLIB)

%.o : %.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

rmdirs:
	$(RM) $(OUTPUT_DIR)

mkdirs:
	$(MK) $(OUTPUT_DIR)

clean:
	$(RM) $(OBJS)
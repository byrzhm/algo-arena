CXX = g++
CXXFLAGS = -Wall -Wextra -g

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
PROGS = $(patsubst %.cpp, %, $(basename $(notdir $(SRCS))))

all: $(PROGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%: %.o
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(OBJS) $(PROGS)

.PHONY: all clean
CXX       = g++
CXXFLAGS  = --std=c++17
SRCS      = $(wildcard *.cpp) 
OBJS      = $(filter %.o,$(SRCS:.cpp=.o) $(SRCS:.cc=.o))

test: $(OBJS)
	$(CXX) -o $@ $(OBJS) -g

%.o: %.cc 
	$(CXX) $(CXXFLAGS) -c $< -O0 -o $@ -g

clean:
	@rm -f *.o
	@rm -f test

.PHONY: clean valgrind

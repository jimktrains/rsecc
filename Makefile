CXX=g++
CXXFLAGS=--std=c++1z -lstdc++ -Wall -Wextra -Werror

all: test 

test: gftest.exe

gftest.exe: gftest.o
	$(CXX) -g $(CXXFLAGS) -o $@ $^

%.o: %.cpp gf.h gfpoly.h
	$(CXX) -g $(CXXFLAGS) -c $<

clean:
	rm -f *.o *.out *.exe


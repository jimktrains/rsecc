CXX=g++
CXXFLAGS=--std=c++1z

all: test 

test: gftest

gftest.exe: gftest.o
	$(CXX) -g $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) -g $(CXXFLAGS) -c $<

clean:
	rm -f *.o gftest


# the compiler: clang++ for C++ programs, use just clang for C programs
CXX = clang++

# compiler flags:
#  -g    		adds debugging information to the executable file
#  -Wall 		turns on most, but not all, compiler warnings
#  -std=c++11 	Allow C++11 code
CFLAGS = -g -Wall -std=c++11

# the build target executables
TARGET = d1s1 d1s2 d2s1 d2s2 d3s1 d4s1 d4s2 d5s1 d5s2 d6s1 d6s2 d7s1 d7s2 d8s1 d8s2 d9s1 d9s2 d10s1 d10s2 d11s1 d11s2 d12s1 d12s2 d13s1 d13s2 d14s1 d14s2 d15s1 d15s2 d16s2 d17s1 d17s2

# the all rule that "make" defaults to
all: $(TARGET)

# Rule for building binaries with .cc inputs
$(TARGET): %: %.cc
	$(CXX) $(CFLAGS) -o $@ $<

# the "make clean" rule
clean:
	$(RM) -rf $(TARGET) *.dSYM

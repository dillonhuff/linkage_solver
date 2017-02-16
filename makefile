CXX_FLAGS= -I/Users/dillon/CppWorkspace/ThmProving/z3/src/api/c++/ -I/Users/dillon/CppWorkspace/ThmProving/z3/src/api/

LINK_FLAGS= -L/Users/dillon/CppWorkspace/ThmProving/z3/build/ -lz3

all:
	clang++ $(CXX_FLAGS) $(LINK_FLAGS) main.cpp

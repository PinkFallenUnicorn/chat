all: createexecutable

createexecutable: test.cpp user.hpp data.hpp user.cpp data.cpp 
	g++ -o main test.cpp user.cpp data.cpp 
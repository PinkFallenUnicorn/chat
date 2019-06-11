all: createexecutable

createexecutable: test.cpp user.hpp data.hpp user.cpp data.cpp chat.cpp
	g++ -o main test.cpp user.cpp data.cpp chat.cpp
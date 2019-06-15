all: createexecutable

createexecutable: test.cpp user.hpp data.hpp user.cpp data.cpp chat.cpp server_data.cpp server_data.hpp
	g++ -o main test.cpp user.cpp data.cpp chat.cpp server_data.cpp
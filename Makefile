all: createexecutable createexecutablee

createexecutable: client_app.cpp user.hpp data.hpp user.cpp data.cpp chat.cpp server_data.cpp server_data.hpp net.cpp net.hpp
	g++ -o main client_app.cpp user.cpp data.cpp chat.cpp server_data.cpp net.cpp

createexecutablee: server_app.cpp user.hpp data.hpp user.cpp data.cpp chat.cpp server_data.cpp server_data.hpp net.cpp net.hpp
	g++ -o server server_app.cpp user.cpp data.cpp chat.cpp server_data.cpp net.cpp
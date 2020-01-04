all: create_client_exe create_server_exe

create_client_exe: client_app.cpp user.hpp data.hpp user.cpp data.cpp chat.cpp net.cpp net.hpp client.cpp client.hpp
	g++ -o main client_app.cpp user.cpp data.cpp chat.cpp net.cpp client.cpp

create_server_exe: server_app.cpp user.hpp data.hpp user.cpp data.cpp chat.cpp net.cpp net.hpp server.cpp server.hpp
	g++ -o server server_app.cpp user.cpp data.cpp chat.cpp net.cpp server.cpp
#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <string>

class	Client
{
	public:
		int			fd;
		std::string	nick;
		std::string	username;
		std::string	hostname;

		bool		has_pass;
		bool		has_nick;
		bool		has_user;
		bool		registered;

		std::string	recvBuffer;
		std::string	sendBuffer;

		Client(int fd);
		~Client();
};

#endif


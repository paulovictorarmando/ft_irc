/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:35:29 by lantonio          #+#    #+#             */
/*   Updated: 2026/01/19 11:35:33 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "Client.hpp"
#include "irc.hpp"

class Server
{
	private:
		int _serverFd;
		std::string _password;
		std::vector<struct pollfd> _pollfds;
		std::map<int, Client*> _clients;

		void setupSocket(int port);
		void acceptClient();
		void receiveData(int clientFd);
		void sendData(int clientFd);
		void removeClient(int clientFd);

	public:
		Server(int port, const std::string& password);
		~Server();
		void run();
		
};

#endif

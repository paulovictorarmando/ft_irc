/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 09:35:28 by lantonio          #+#    #+#             */
/*   Updated: 2026/02/03 11:22:50 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/irc.hpp"
#include "../../includes/Server.hpp"

std::string	Server::_topic(commandRequest& request, int sender_fd) {
	if (!_clients[sender_fd]->isAuth())
		return ":localhost 451 * :You have not registered\r\n";

	std::string	channel;
	if (request.args.size())
	{
		if (request.args[0][0] != '#')
			return ":localhost 461 * :First param must be the channel name\r\n";

		// ask to see channel topic
		if (request.args.size() == 1)
		{
			// channel exists and user is in it
			if (_channels.find(request.args[0]) != _channels.end() && _channels[request.args[0]]->isMember(sender_fd))
			{
				if (_channels[request.args[0]]->getHasTopic())
					return "localhost 331 * :";
				return "localhost 332 * :" + _channels[request.args[0]]->getTopic();
			} else
				return ":localhost 403 * :Non-existent channel\r\n";
		}

		if (request.args.size() == 2)
		{
			// channel exists and user is in it
			if (_channels.find(request.args[0]) != _channels.end() && _channels[request.args[0]]->isMember(sender_fd))
			{
				// if channel is in mode +t and user is not an operatorm return 482 
				_channels[request.args[0]]->setTopic(sender_fd, request.args[1]);
				
				// Broadcast the topic change to all members
				std::string nick = _clients[sender_fd]->getNickname();
				std::string broadcastMsg = ":" + nick + " TOPIC " + request.args[0] + " :" + request.args[1] + "\r\n";
				_channels[request.args[0]]->broadcastMessage(broadcastMsg, sender_fd);
				
				return "";
			}
		}
	}
	return ":localhost 461 * :Not enounth params\r\n";
}

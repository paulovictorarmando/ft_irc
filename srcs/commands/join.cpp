/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 12:17:26 by hmateque          #+#    #+#             */
/*   Updated: 2026/01/30 12:17:47 by hmateque         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/Server.hpp"

std::string Server::_joinChannel(commandRequest& request, int fd)
{
    if (!_clients[fd]->isAuth())
        return ":localhost 464 * :You need to register first.\r\n";

    if (request.args.empty())
        return ":localhost 461 * JOIN :Not enough parameters\r\n";

    std::string channelName = request.args[0];

    if (!_channels[channelName])
    {
        _channels[channelName] = new Channel(channelName, _clients[fd]);
        return ":localhost 331 " + _clients[fd]->getNickname() + " " + channelName + " :No topic is set\r\n";
    }
    else if (_channels[channelName]->isMember(fd))
    {
        return ":localhost 443 " + _clients[fd]->getNickname() + " " + channelName + " :You're already on that channel\r\n";
    }

    _channels[channelName]->addMember(_clients[fd]);
    return ":localhost 331 " + _clients[fd]->getNickname() + " " + channelName + " :No topic is set\r\n";
}
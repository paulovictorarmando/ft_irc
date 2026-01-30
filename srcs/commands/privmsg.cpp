/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 12:22:50 by hmateque          #+#    #+#             */
/*   Updated: 2026/01/30 12:22:57 by hmateque         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/Server.hpp"

std::string Server::_privmsg(commandRequest& request, int sender_fd)
{
    if (!_clients[sender_fd]->isAuth())
        return ":localhost 451 * :You have not registered\r\n";
    if (request.args.size() < 1)
        return ":localhost 461 PRIVMSG :Not enough parameters\r\n";
    int recv_fd = -1;
    for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end();++it)
    {
        if (it->second->getNickname() == request.args[0])
            recv_fd = it->first;
    }
    if (recv_fd == -1)
        return ":localhost 401 " + _clients[sender_fd]->getNickname() + " " + request.args[0]+" :No such nick\r\n";
    
    std::string msg = ":" + _clients[sender_fd]->getNickname() + "!" + _clients[sender_fd]->getUsername() + "@localhost PRIVMSG " + request.args[0] +" :" + request.args[1] + "\r\n";

    _clients[recv_fd]->setSendBuffer(_clients[recv_fd]->getSendBuffer() + msg);
    enablePollout(recv_fd);
    return "";
}
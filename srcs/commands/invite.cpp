#include "../../includes/Server.hpp"

std::string Server::_invite(commandRequest& request, int fd)
{
    if (!_clients[fd]->isAuth())
        return ":localhost 451 * :You have not registered\r\n";

    if (request.args.size() < 2)
        return ":localhost 461 * INVITE :Not enough parameters\r\n";

    std::string channel = request.args[1];

    if (_channels.find(channel) == _channels.end())
        return ":localhost 403 " + _clients[fd]->getNickname() + " " + channel + " :No such channel\r\n";

    if (!_channels[channel]->isMember(fd))
        return ":localhost 442 " + _clients[fd]->getNickname() + " " + channel + " :You're not on that channel\r\n";

    if (!_channels[channel]->isOperator(fd))
        return ":localhost 482 " + _clients[fd]->getNickname() + " " + channel + " :You're not operator\r\n";


    std::string nick_name = request.args[0];
    int invited_fd = -1;

    for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
    {
        if (it->second->getNickname() == nick_name)
        {
            invited_fd = it->first;
            break;
        }
    }

    if (invited_fd == -1)
        return ":localhost 401 " + _clients[fd]->getNickname() + " " + nick_name + " :No such nick\r\n";

    if (_channels[channel]->isMember(invited_fd))
        return ":localhost 443 " + _clients[fd]->getNickname() + " " + channel + " " + nick_name + " :Is already on that channel\r\n";


    _channels[channel]->addEnvited(_clients[invited_fd]);

    std::string msgToTarget =
        ":" + _clients[fd]->getNickname() + " INVITE " + nick_name + " :" + channel + "\r\n";

    std::string msgToSender =
        ":localhost 341 " + _clients[fd]->getNickname() + " " + nick_name + " " + channel + "\r\n";

    _clients[invited_fd]->setSendBuffer(_clients[invited_fd]->getSendBuffer() + msgToTarget);
    enablePollout(invited_fd);

    _clients[fd]->setSendBuffer(_clients[fd]->getSendBuffer() + msgToSender);
    enablePollout(fd);

    return "";
}


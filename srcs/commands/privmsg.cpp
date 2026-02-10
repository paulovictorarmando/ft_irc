/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 12:22:50 by hmateque          #+#    #+#             */
/*   Updated: 2026/02/09 15:08:48 by hmateque         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../includes/Server.hpp"

std::string Server::_privmsg(commandRequest& request, int sender_fd)
{
    // PROTEÇÃO: Verificar se o cliente remetente ainda existe
    if (_clients.find(sender_fd) == _clients.end())
        return "";
    
    // 1. Verificar autenticação
    if (!_clients[sender_fd]->isAuth())
        return ":localhost 451 * :You have not registered\r\n";
    
    // 2. Verificar parâmetros (precisa de destino e mensagem)
    if (request.args.size() < 2)
        return ":localhost 461 " + _clients[sender_fd]->getNickname() + " PRIVMSG :Not enough parameters\r\n";
    
    std::string target = request.args[0];
    std::string message = request.args[1];
    
    // 3. Montar o prefixo da mensagem (quem enviou)
    std::string prefix = ":" + _clients[sender_fd]->getNickname() + "!" + 
                        _clients[sender_fd]->getUsername() + "@localhost";
    
    // 4. Verificar se o destino é um CANAL (começa com #)
    if (target[0] == '#')
    {
        // Verificar se o canal existe
        if (_channels.find(target) == _channels.end())
            return ":localhost 403 " + _clients[sender_fd]->getNickname() + " " + target + " :No such channel\r\n";
        
        // Verificar se o remetente está no canal
        if (!_channels[target]->isMember(sender_fd))
            return ":localhost 442 " + _clients[sender_fd]->getNickname() + " " + target + " :You're not on that channel\r\n";
        
        // Coletar apenas os FDs dos membros (não os ponteiros!)
        std::map<int, Client*> const &members = _channels[target]->getMembers();
        std::vector<int> memberFds;
        for (std::map<int, Client*>::const_iterator it = members.begin(); it != members.end(); ++it)
        {
            if (it->first != sender_fd)
                memberFds.push_back(it->first);
        }
        
        // Montar a mensagem
        std::string fullMsg = prefix + " PRIVMSG " + target + " :" + message + "\r\n";
        
        // Enviar usando os FDs e verificando no mapa _clients do servidor
        for (size_t i = 0; i < memberFds.size(); ++i)
        {
            int fd = memberFds[i];
            // PROTEÇÃO: Verificar se o cliente ainda existe no mapa PRINCIPAL do servidor
            if (_clients.find(fd) != _clients.end())
            {
                _clients[fd]->setSendBuffer(_clients[fd]->getSendBuffer() + fullMsg);
                enablePollout(fd);
            }
        }
        
        return ""; // Sucesso (sem resposta ao remetente)
    }
    
    // 5. Se não é canal, é mensagem PRIVADA para usuário
    int recv_fd = -1;
    for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
    {
        if (it->second->getNickname() == target)
        {
            recv_fd = it->first;
            break;
        }
    }
    
    // Verificar se o usuário existe
    if (recv_fd == -1)
        return ":localhost 401 " + _clients[sender_fd]->getNickname() + " " + target + " :No such nick/channel\r\n";
    
    // Enviar mensagem privada
    std::string fullMsg = prefix + " PRIVMSG " + target + " :" + message + "\r\n";
    _clients[recv_fd]->setSendBuffer(_clients[recv_fd]->getSendBuffer() + fullMsg);
    enablePollout(recv_fd);
    
    return ""; // Sucesso
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:32:03 by lantonio          #+#    #+#             */
/*   Updated: 2026/01/20 11:22:00 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"
#include "../includes/Server.hpp"

void input_builder(std::string &bufferAcumulado, char *newBuffer, int bytesRead) {
    bufferAcumulado.append(newBuffer, bytesRead);

    size_t pos;
    while ((pos = bufferAcumulado.find("\r\n")) != std::string::npos) {
        std::string comando = bufferAcumulado.substr(0, pos);
        
        std::cout << "Comando pronto para execução: [" << comando << "]" << std::endl;

        bufferAcumulado.erase(0, pos + 2);
    }
}

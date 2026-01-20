/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:52:04 by lantonio          #+#    #+#             */
/*   Updated: 2026/01/20 13:49:51 by lantonio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"

Command::Command() {
	prefix = "";
	command = "";
	params = std::vector<std::string>(0);
	trailing = "";
}

std::string Command::input_builder(std::string &bufferAcumulado, char *newBuffer, int bytesRead) {
	bufferAcumulado.append(newBuffer, bytesRead);

	size_t pos;
	while ((pos = bufferAcumulado.find("\r\n")) != std::string::npos) {
		std::string comando = bufferAcumulado.substr(0, pos);		
		return comando;		
	}
	return bufferAcumulado;
}

void    Command::command_builder(std::string buffer) {
	std::cout << "Comando final: " << buffer << " | Pos 0 " << buffer.at(0) << std::endl;
	if (buffer.at(0) == ':')
	{
		std::cout << "Com prefixo" << std::endl;
	} else
		std::cout << "Sem prefixo" << std::endl;
}

Command::~Command() {}

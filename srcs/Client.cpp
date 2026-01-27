/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmateque <hmateque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 09:02:59 by hmateque          #+#    #+#             */
/*   Updated: 2026/01/27 09:14:16 by hmateque         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/Client.hpp"
// Constructor and Destructor
Client::Client(int fd) : fd(fd),recvBuffer(""), sendBuffer(""),nickName(""), 
userName(""), hasPass(false), hasNick(false), hasUser(false), auth(false) {}

Client::~Client() {}


// Getters
int Client::getClientfd() const { return this->fd; }
std::string Client::getRecvBuffer() const { return this->recvBuffer; }
std::string Client::getSendBuffer() const { return this->sendBuffer; }
std::string Client::getNickname() const { return this->nickName; }
std::string Client::getUsername() const { return this->userName; }
bool Client::getHasPass() const { return this->hasPass; }
bool Client::getHasNick() const { return this->hasNick; }
bool Client::getHasUser() const { return this->hasUser; }
bool Client::isAuth() const { return this->auth; }

// Setters
void Client::setClientfd(int fd) { this->fd = fd; }
void Client::setRecvBuffer(const std::string& buffer) { this->recvBuffer = buffer; }
void Client::setSendBuffer(const std::string& buffer) { this->sendBuffer = buffer; }
void Client::setNickname(const std::string& nick) { this->nickName = nick; }
void Client::setUsername(const std::string& user) { this->userName = user; }
void Client::setHasPass(bool hasPass) { this->hasPass = hasPass; }
void Client::setHasNick(bool hasNick) { this->hasNick = hasNick; }
void Client::setHasUser(bool hasUser) { this->hasUser = hasUser; }
void Client::setAuth(bool auth) { this->auth = auth; }
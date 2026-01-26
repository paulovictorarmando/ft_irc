#include "../includes/Client.hpp"

Client::Client(int fd) : fd(fd), auth(false), readyCommand(false) {
	command = new Command();
}

Client::~Client() {
	delete command;
}

int Client::getClientfd() const { return this->fd; }

void    Client::setReadyCommand(bool status) {
    this->readyCommand = status;
}

bool    Client::getReadyCommand() const { return this->readyCommand; }

*This project has been created as part of the 42 curriculum by hmateque, lantonio, parmando.*

# ft_irc

## Description
**ft_irc** is a minimal IRC server written in C++. Its goal is to implement the core IRC protocol features required by the 42 curriculum, including client registration, basic commands, channels, and operator privileges. The project focuses on networking fundamentals (TCP, sockets, polling), command parsing, and correct protocol replies.

## Instructions

### Build
Use the provided Makefile:

- Build:
	- `make`
- Clean:
	- `make clean`
- Full clean:
	- `make fclean`
- Rebuild:
	- `make re`
- Start server:
    - `make run`

### Run
Start the server with a port and a password:

```
./ircserv <port> <password> 
```

Example:

```
./ircserv 3000 1234
```

Then connect with any IRC client using the same port and password.

## Resources
- RFC 1459: Internet Relay Chat Protocol
- RFC 2812: Internet Relay Chat: Client Protocol
- Beej’s Guide to Network Programming

### AI Usage
AI was used to:
- Review logic for command handling and operator permissions.
- Suggest safer container access patterns and edge-case checks.
- Draft and structure this README for clarity and compliance with the project requirements.
- Consult IRC protocol response codes and numeric replies.
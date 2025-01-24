# C++ Socket Chat Application

## Overview

A simple multi-client chat application implemented in C++ using socket programming and pthreads. The project consists of a server and client that can communicate in real-time.

## Features

- TCP/IPv4 socket communication
- Multi-client support
- Threaded message sending and receiving
- Username-based messaging
- Broadcast Messaging

## Prerequisites

- C++ compiler with C++11 support
- POSIX threads (pthread) library
- Linux/Unix-based system

## Project Structure

- Client.cpp: Client-side implementation
- Server.cpp: Server-side implementation
- SocketUtil.hpp: Socket utility header
- SocketUtil.cpp: Socket utility implementation

## Compilation

Compile the server and client separately:

```bash
# Compile Server
g++ -std=c++11 Server.cpp -o server -pthread

# Compile Client
g++ -std=c++11 Client.cpp -o client -pthread
```

## Usage

1. Start the server:

```bash
./server
```

2. In separate terminals, start multiple clients:

```bash
./client
```

3. Enter a username for each client
4. Start messaging
5. Type exit to disconnect



## Key Functions

- createTCPIpv4Socket(): Creates a TCP IPv4 socket
- createIPv4Address(): Configures socket address
- acceptIncomingConnection(): Handles new client connections
- listenAndDisplay(): Manages message receiving
- broadcastReceivedMessage(): Sends messages to all connected clients

## Limitations

- Maximum 10 concurrent client connections
- Basic error handling
- No encryption or advanced security features


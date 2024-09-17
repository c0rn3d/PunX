# README for PunX Cyberpunk Client-Server Application
# Overview

This project is a simple client-server communication system built using sockets in C. It allows multiple clients to connect to a server, send messages, and receive responses. The server can handle multiple clients simultaneously using pthreads (POSIX threads), simulating the feel of a "cyberpunk" hacking environment.

The application includes two components:

    PunX Server: Accepts connections from multiple clients, receives their messages, and echoes them back.
    PunX Client: Connects to the server, sends messages, and displays server responses.

How to Compile and Run
Compile the Server


gcc server.c -o server -pthread

Compile the Client


gcc client.c -o client

Run the Server


./server

Run the Client (in another terminal or machine)


./client

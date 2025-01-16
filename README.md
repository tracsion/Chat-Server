# Chat Application

This project is a simple multithreaded chat application written in C++. It includes a **server** and a **client** implementation, allowing multiple clients to connect and exchange messages anonymously.

## Features

- **Anonymous Communication**: Each client is assigned a random unique name upon connection.
- **Multithreading**: The server handles multiple client connections concurrently.
- **Message Broadcasting**: Messages sent by one client are broadcast to all other connected clients.

## Folder Structure

```
ChatApplication/
├── server/
│   ├── chat_server.cpp
│   ├── Makefile
├── client/
│   ├── chat_client.cpp
│   ├── Makefile
├── README.md
└── LICENSE
```

## Requirements

- A Linux-based operating system or WSL (Windows Subsystem for Linux).
- A C++ compiler supporting C++11 or later (e.g., `g++`).

## Compilation

### Server
1. Navigate to the `server/` directory:
   ```bash
   cd server
   ```
2. Compile the server code using the Makefile:
   ```bash
   make
   ```

### Client
1. Navigate to the `client/` directory:
   ```bash
   cd client
   ```
2. Compile the client code using the Makefile:
   ```bash
   make
   ```

## Usage

### Running the Server
1. Start the server by running the compiled executable:
   ```bash
   ./chat_server
   ```
2. The server will start listening for incoming connections on port `8080` by default.

### Running the Client
1. Start the client by running the compiled executable:
   ```bash
   ./chat_client
   ```
2. Enter the IP address of the server when prompted.
3. Begin chatting! Messages will be sent with a randomly assigned anonymous name.
4. Type `exit` to disconnect from the server.

### Example Interaction

#### Server:
```plaintext
Server started on port 8080. Waiting for clients...
New client connected.
New client connected.
Received message from client: [AnonUser1]: Hello, everyone!
Received message from client: [AnonUser2]: Hi!
```

#### Client 1:
```plaintext
Enter server IP address: 127.0.0.1
Connected to server as AnonUser1. You can start typing messages.
[AnonUser1]: Hello, everyone!
```

#### Client 2:
```plaintext
Enter server IP address: 127.0.0.1
Connected to server as AnonUser2. You can start typing messages.
[AnonUser2]: Hi!
```

## Notes

- Ensure the server is running before starting the client.
- The default communication port is `8080`. Modify it in the code if needed.

## Disclaimer

This project is for educational purposes only. It is not intended for use in production environments. Always ensure proper authorization before deploying network applications.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

## Author

Developed by Hector.


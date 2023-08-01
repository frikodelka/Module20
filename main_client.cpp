﻿#include "chat.h"
#include "client.h"

int main()
{
    Chat chat;

    chat.createChat();

    Client& c = Client::Instance();
    char message[MESSAGE_LENGTH];

    while (chat.isChatWorking())
    {
        bzero(message, sizeof(message));
        std::cout << std::endl;
        std::cout << "Enter a message you want to send to the server: " << std::endl;
        std::cin >> message;
        if (strncmp("End", message, 3) == 0)
        {
            write(c.getSocket_file_descriptor(), message, sizeof(message));
            std::cout << "Client is gone..." << std::endl;
            chat.closeChat();
            continue;
        }
        ssize_t bytes = write(c.getSocket_file_descriptor(), message, sizeof(message));
        if (bytes >= 0)
        {
            std::cout << std::endl;
            std::cout << "Message is sent successfully to the server!" << std::endl;
        }
        bzero(message, sizeof(message));
        read(c.getSocket_file_descriptor(), message, sizeof(message));
        std::cout << std::endl;
        std::cout << "Message received from the server: " << std::endl << message << std::endl;
    }

    return 0;
}
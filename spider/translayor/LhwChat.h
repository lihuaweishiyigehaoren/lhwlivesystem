#pragma once

#include <string>
#include "LhwSocket.h"

namespace translayor
{
    class LhwChat
    {
    public:
        LhwChat(const std::string& username, const std::string& roomName, int flag, Socket* socket);
        LhwChat();
        std::string getUserName()const;
        std::string getRoomName()const;
        int getFlag()const;
        Socket* getSocket()const;
    private:
        std::string username;
        std::string roomName;
        int flag;
        Socket *socket;

    };
}
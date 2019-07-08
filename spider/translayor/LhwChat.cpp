#include "LhwChat.h"

namespace translayor
{
    LhwChat::LhwChat(const std::string& username, const std::string& roomName, int flag, Socket* socket)
        :username(username), roomName(roomName),flag(flag), socket(socket)
    {


    }

    LhwChat::LhwChat()
    {

    }

    std::string LhwChat::getUserName()const
    {
        return username;
    }

    std::string LhwChat::getRoomName()const
    {
        return roomName;
    }

    int LhwChat::getFlag ()const
    {
        return flag;
    }

    Socket* LhwChat::getSocket ()const
    {
        return socket;
    }
}
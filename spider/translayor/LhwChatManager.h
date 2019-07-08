#pragma once 
#include <vector>
#include <string>
#include <mutex>

#include "LhwChat.h"

namespace translayor
{
    class LhwChatManager
    {
    public:
        static LhwChatManager* getInstance();
        void insertChat(const LhwChat& chat);
        void eraseChat(const std::string& name);
        std::vector<LhwChat> getAllChat()const;
    private:
        static LhwChatManager* instance;
        LhwChatManager();
        std::vector<LhwChat> chatrooms;
        static std::mutex mutex;
    };
}
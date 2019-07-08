#include "LhwChatManager.h"

namespace translayor
{
    LhwChatManager *LhwChatManager::instance = 0;
    std::mutex LhwChatManager::mutex;

    LhwChatManager::LhwChatManager()
    {

    }


    LhwChatManager* LhwChatManager::getInstance()
    {
        if(instance == 0){
            mutex.lock();
            if(0 == instance){
                instance = new LhwChatManager();
            }
            mutex.unlock();
        }
        return instance;
    }

    void LhwChatManager::insertChat(const LhwChat& chat)
    {
        chatrooms.push_back (chat);
    }

    void LhwChatManager::eraseChat(const std::string& name)
    {
        std::vector<LhwChat>::iterator it;
        for(it = chatrooms.begin (); it != chatrooms.end (); ++it){
            LhwChat chat = *it;
            if(chat.getUserName () == name){
                chatrooms.erase (it);
                break;
            }
        }
    }

    std::vector<LhwChat> LhwChatManager::getAllChat()const
    {
        return chatrooms;
    }

}
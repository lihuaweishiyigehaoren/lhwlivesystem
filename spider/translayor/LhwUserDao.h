#pragma once

#include "LhwUser.h"
#include <string>

namespace translayor 
{
    class LhwUserDao
    {
        public:
            LhwUserDao();
            virtual ~LhwUserDao();
            virtual bool addUser(User user) = 0;
            virtual User findUser(const std::string& name) = 0;
    };
} 

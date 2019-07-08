#pragma once

#include "LhwUserDao.h"

namespace translayor 
{
    class LhwUserDaoImp : public LhwUserDao
    {
        public:
            LhwUserDaoImp();
            virtual bool addUser(User user);
            virtual User findUser(const std::string& name);
    };
} 

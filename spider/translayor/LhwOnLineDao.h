#pragma once 

#include <vector>

#include "LhwDBHelper.h"
#include "LhwUser.h"


namespace translayor
{
    class OnlineDao
    {
    public:
        OnlineDao();
        virtual ~OnlineDao();
        virtual bool addOnline(std::string& name) = 0;
        virtual char* findOnline(std::string& name) = 0;
        virtual bool delOnline(std::string& name) = 0;
        virtual std::vector<std::string> selectOnline() = 0;
    };

}
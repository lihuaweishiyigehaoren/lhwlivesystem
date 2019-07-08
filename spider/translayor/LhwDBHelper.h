#pragma once

#include <mysql/mysql.h>
#include <string>

namespace translayor
{
    class LhwDBHelper
    {
        public:
            static LhwDBHelper* getInstance();

            ~LhwDBHelper();
            bool initDB(std::string host, std::string user, std::string pwd, std::string db_name);
	        bool exeSQL(std::string sql);

        private:
            static LhwDBHelper* instance;
            LhwDBHelper();
        private:

            MYSQL * connection;
            MYSQL_RES * result;
            MYSQL_ROW row;
    
    };
}
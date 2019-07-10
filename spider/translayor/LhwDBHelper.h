#pragma once

#include <mysql/mysql.h>
#include <string>

#include "LhwUser.h"

namespace translayor
{
    class LhwDBHelper
    {
        public:
            static LhwDBHelper* getInstance();

            ~LhwDBHelper();
            bool initDB(std::string host, std::string user, std::string pwd, std::string db_name);
	        bool exeSQL(std::string sql,User &user);

            void closeMysql();

            MYSQL * getConnection() const
            {
                return connection;
            }

            // MYSQL_RES * getResult() const
            // {
            //     return result;
            // }

        private:
            static LhwDBHelper* instance;
            LhwDBHelper();
        private:

            MYSQL * connection;

        public:
            MYSQL_RES * result;
            MYSQL_ROW row;
    
    };
}
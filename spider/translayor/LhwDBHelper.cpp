#include "LhwDBHelper.h"
#include "Logging.h"
#include "LhwUser.h"

#include <iostream>
#include <cstdlib>

namespace translayor
{
    LhwDBHelper* LhwDBHelper::instance = 0;

    LhwDBHelper* LhwDBHelper::getInstance()
    {
        if(instance == 0)
        {
            instance = new LhwDBHelper();
        }
        return instance;
    }

    LhwDBHelper::LhwDBHelper()
    {
        connection = mysql_init(NULL); // 初始化数据库连接变量
    	if(connection == NULL)
    	{
    		LOG(LOG_DEBUG)  << "Error:" << mysql_error(connection);
    		exit(1);
    	}
    }

	void LhwDBHelper::closeMysql()
	{
		if(connection != NULL)  // 关闭数据库连接
    	{
    		mysql_close(connection);
    	}
	}

    LhwDBHelper::~LhwDBHelper()
    {
    	if(connection != NULL)  // 关闭数据库连接
    	{
    		mysql_close(connection);
    	}
    }
    
    bool LhwDBHelper::initDB(std::string host, std::string user, std::string pwd, std::string db_name)
    {
    	// 函数mysql_real_connect建立一个数据库连接
    	// 成功返回MYSQL*连接句柄，失败返回NULL
    	connection = mysql_real_connect(connection, host.c_str(),
    			user.c_str(), pwd.c_str(), db_name.c_str(), 0, NULL, 0);
    	if(connection == NULL)
    	{
    		LOG(LOG_DEBUG)  << "Error:" << mysql_error(connection);
    		exit(1);
    	}
    	return true;
    }
    
    bool LhwDBHelper::exeSQL(std::string sql,User &user)
    {
    	// mysql_query()执行成功返回0，失败返回非0值。与PHP中不一样
    	if(mysql_query(connection, sql.c_str()))
    	{
    		LOG(LOG_DEBUG) << "Query Error:" << mysql_error(connection);
    		exit(1);
    	}
    	else
    	{
    		result = mysql_use_result(connection); // 获取结果集
    		// mysql_field_count()返回connection查询的列数
    		for(int i=0; i < mysql_field_count(connection); ++i)
    		{
    			// 获取下一行
    			row = mysql_fetch_row(result);
    			if(row <= 0)
    			{
    				break;
    			}
    			// mysql_num_fields()返回结果集中的字段数
    			for(int j=0; j < mysql_num_fields(result); ++j)
    			{
    				LOG(LOG_DEBUG) << row[j] << " ";
    			}
    			// std::cout << std::endl;
    		}
    		// 释放结果集的内存
    		mysql_free_result(result);
    	}
    	return true;
    }
}
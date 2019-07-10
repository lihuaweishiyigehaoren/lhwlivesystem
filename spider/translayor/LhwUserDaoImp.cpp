#include "LhwUserDaoImp.h"
#include "LhwDBHelper.h"
#include "Logging.h"
#include <string.h>

namespace translayor 
{
    LhwUserDaoImp::LhwUserDaoImp()
    {

    }

    bool LhwUserDaoImp::addUser(User user)
    {
        //将网络编码转化为本地unicode编码
        std::string qname = user.username;
        std::string qpasswd = user.userpasswd;

        LhwDBHelper *helper = LhwDBHelper::getInstance();
        helper->initDB("127.0.0.1","root","renshi123","user");
        std::string sqlUse = "insert into tb_user(name, passwd)values("+qname+", "+qpasswd+");";
        if(mysql_query(helper->getConnection(), sqlUse.c_str()))
    	{
    		LOG(LOG_DEBUG) << "Query Error:" << mysql_error(helper->getConnection());
    		return false;
    	}
        helper->closeMysql();
        return true;
    }

    User LhwUserDaoImp::findUser(const std::string& name)
    {
        User user;
        LhwDBHelper *helper = LhwDBHelper::getInstance();
        helper->initDB("127.0.0.1","root","renshi123","user");
        // helper->exeSQL("select name, passwd from tb_user;");
        std::string sqlUse = "select name, passwd from tb_user;";
        if(mysql_query(helper->getConnection(), sqlUse.c_str()))
    	{
    		LOG(LOG_DEBUG) << "Query Error:" << mysql_error(helper->getConnection());
    		exit(1);
    	}
    	else
    	{
    		helper->result = mysql_use_result(helper->getConnection()); // 获取结果集
    		// mysql_field_count()返回connection查询的列数
    		for(int i=0; i < mysql_field_count(helper->getConnection()); ++i)
    		{
    			// 获取下一行
    			helper->row = mysql_fetch_row(helper->result);
    			if(helper->row <= 0)
    			{
    				break;
    			}
    			// mysql_num_fields()返回结果集中的字段数
    			// for(int j=0; j < mysql_num_fields(helper->result); ++j)
    			// {
    			// 	LOG(LOG_DEBUG) << row[j] << " ";
    			// }
    			// std::cout << std::endl;
                std::string username = helper->row[0];
                std::string userpasswd = helper->row[1];
                if(name == username)
                {
                    const char* pname = username.data();
                    const char* ppasswd = userpasswd.data();
                    strncpy(user.username, pname, 20);
                    strncpy(user.userpasswd, ppasswd, 20);
                    // helper->destoryConn();
                    helper->closeMysql();
                    return user;
                }
    		}
    		// 释放结果集的内存
    		mysql_free_result(helper->result);
    	}

        // QSqlQuery query;
        // query.exec("select name, passwd from tb_user;");
        // while(query.next()){
        //     QString username = query.value(0).toString();
        //     QString userpasswd = query.value(1).toString();
        //     if(name == username){
        //         char* pname = username.toLocal8Bit().data();
        //         char* ppasswd = userpasswd.toLocal8Bit().data();
        //         strncpy(user.username, pname, 20);
        //         strncpy(user.userpasswd, ppasswd, 20);
        //         helper->destoryConn();
        //         return user;
        //     }
        // }
        // helper->destoryConn();
        helper->closeMysql();
        strcpy(user.username, "");
        return user;
    }
} 

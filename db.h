#ifndef DB_H
#define DB_H

#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <string>
#include <vector>

class DB {
public:
    DB(const std::string& host, const std::string& user, const std::string& password, const std::string& database);
    ~DB();

    void connect();
    std::vector<std::string> getOrders(int limit);

private:
    std::string host_, user_, password_, database_;
    sql::Driver* driver_;
    sql::Connection* con_;
};

#endif // DB_H





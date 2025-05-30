#include "db.h"
#include <iostream>
#include <sstream>

DB::DB(const std::string& host, const std::string& user, const std::string& password, const std::string& database)
    : host_(host), user_(user), password_(password), database_(database), driver_(nullptr), con_(nullptr) {}

DB::~DB() {
    if (con_) {
        con_->close();
        delete con_;
    }
}

void DB::connect() {
    try {
        driver_ = get_driver_instance();
        con_ = driver_->connect(host_, user_, password_);
        con_->setSchema(database_);
        std::cout << "Connected to database." << std::endl;
    } catch (sql::SQLException &e) {
        std::cerr << "Error connecting to database: " << e.what() << std::endl;
        con_ = nullptr;
    }
}

std::vector<std::string> DB::getOrders(int limit) {
    std::vector<std::string> results;

    if (!con_) {
        std::cerr << "Not connected to DB" << std::endl;
        return results;
    }

    try {
        std::unique_ptr<sql::Statement> stmt(con_->createStatement());
        std::stringstream ss;
        ss << "SELECT order_id, date, status, amount FROM orders LIMIT " << limit;
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(ss.str()));

        while (res->next()) {
            std::string order = "Order ID: " + res->getString("order_id") +
                                ", Date: " + res->getString("date") +
                                ", Status: " + res->getString("status") +
                                ", Amount: " + std::to_string(res->getDouble("amount"));
            results.push_back(order);
        }
    } catch (sql::SQLException &e) {
        std::cerr << "Query error: " << e.what() << std::endl;
    }

    return results;
}




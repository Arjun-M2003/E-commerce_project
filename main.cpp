#include <iostream>
#include "db.h"

int main() {
    DB db("tcp://127.0.0.1:3306", "root", "Snoopydog20@", "ecomm");
    try{
        db.connect();
    } catch (const std::exception& e) {
        std::cerr << "Connection failed: " << e.what() << std::endl;
        return 1;
    }

    auto orders = db.getOrders(5);

    for (const auto& order : orders) {
        std::cout << order << std::endl;
    }

    return 0;
}

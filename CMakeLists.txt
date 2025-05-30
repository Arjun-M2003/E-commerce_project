cmake_minimum_required(VERSION 3.10)
project(EcommCLI)

set(CMAKE_CXX_STANDARD 17)

# Set MySQL Connector/C++ path
set(MYSQL_CONNECTOR_ROOT "${CMAKE_SOURCE_DIR}/mysql-connector-c++-9.3.0-winx64/mysql-connector-c++-9.3.0-winx64")

# Include directory for headers
include_directories(${MYSQL_CONNECTOR_ROOT}/include/jdbc)
message(STATUS "Using MySQL Connector include: ${MYSQL_CONNECTOR_ROOT}/include/jdbc")

link_directories(${MYSQL_CONNECTOR_ROOT}/lib64/vs14)

# Add source files
add_executable(ecomm_cli main.cpp db.cpp)


# Option 1: Use the dynamic lib (easier)
target_link_libraries(ecomm_cli mysqlcppconn)

# Option 2 (alternative): Use the static lib — uncomment below if you prefer it
# add_definitions(-DSTATIC_CONCPP)
# target_link_libraries(ecomm_cli mysqlcppconn-static)




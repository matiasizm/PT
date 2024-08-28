cmake_minimum_required(VERSION 3.29)
project(PT_Fintual)

set(CMAKE_CXX_STANDARD 17)

add_executable(PT_Fintual main.cpp
        YahooFinanceAPI.cpp
        YahooFinanceAPI.h
        Date.cpp
        Date.h
        Stock.cpp
        Stock.h
        Portfolio.cpp
        Portfolio.h
)
# Encontrar la biblioteca CURL
find_package(CURL REQUIRED)

# Enlazar la biblioteca CURL con tu proyecto
target_link_libraries(PT_Fintual CURL::libcurl)
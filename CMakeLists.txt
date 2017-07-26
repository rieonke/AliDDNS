cmake_minimum_required(VERSION 3.8)
project(aliddns)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILE_TYPE RELEASE)

include_directories(thirdparty/curl-7.54.1/include thirdparty/rapidjson/include thirdparty/sole thirdparty/cryptopp thirdparty/spdlog/include)

add_subdirectory(thirdparty/cryptopp)
add_subdirectory(thirdparty/spdlog)

set(SOURCE_FILES main.cpp ipchecker.cpp ipchecker.h config.cpp config.h  api.cpp api.h configuration.cpp config.h urlencoder.cpp urlencoder.h crypto.cpp crypto.h curl.cpp curl.h logger.cpp logger.h)
add_executable(aliddns ${SOURCE_FILES})

target_link_libraries(aliddns curl cryptopp-static spdlog)

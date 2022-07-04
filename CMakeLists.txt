cmake_minimum_required(VERSION 3.17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_BINARY_DIR})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

project(qttgbot LANGUAGES CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(KEEP_RPATHS)

find_package(
    Qt6
        COMPONENTS
            Core
            Network
)

set(
    SOURCES
        src/Bot.cpp
        src/Bot.h
        src/BotApi/AccessManager.cpp
        src/BotApi/AccessManager.h
        src/Chat/Chat.cpp
        src/Chat/Chat.h
        src/Message/Message.cpp
        src/Message/Message.h
        src/Reply/Reply.h
        src/Update/Update.cpp
        src/Update/Update.h
        src/User/User.cpp
        src/User/User.h
)

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PUBLIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC src)

target_link_libraries(${PROJECT_NAME} PUBLIC Qt6::Core Qt6::Network)

if(APPLE)
    target_link_libraries(${PROJECT_NAME} PUBLIC "-framework SystemConfiguration")
    target_link_libraries(${PROJECT_NAME} PUBLIC "-framework GSS")
endif()

set(
    PROJECT_PUBLIC_HEADERS
        Reply/Reply.h
        Chat/Chat.h
        User/User.h
        Message/Message.h
        Bot.h
        Update/Update.h
        BotApi/AccessManager.h
)

install(
    TARGETS ${PROJECT_NAME}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

foreach(header_file ${PROJECT_PUBLIC_HEADERS})
    get_filename_component(dir ${header_file} DIRECTORY)
    install(FILES src/${header_file} DESTINATION include/${dir})
endforeach()

add_subdirectory(examples)
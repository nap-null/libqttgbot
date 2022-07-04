add_executable(
    echo
        main.cpp
        EchoBot/EchoBot.cpp
        EchoBot/EchoBot.h
        Main/Main.cpp
        Main/Main.h
)

target_link_libraries(echo qttgbot)

target_include_directories(echo PRIVATE .)

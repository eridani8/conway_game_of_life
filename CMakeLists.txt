cmake_minimum_required(VERSION 3.30)
project(conway_game_of_life C)

# Установка стандарта C
set(CMAKE_C_STANDARD 23)

# Поиск библиотеки SDL2
find_package(SDL2 REQUIRED)

# Добавление исполняемого файла
add_executable(conway_game_of_life main.c)

# Подключение библиотеки SDL2 к вашему проекту
target_link_libraries(conway_game_of_life PRIVATE SDL2::SDL2)
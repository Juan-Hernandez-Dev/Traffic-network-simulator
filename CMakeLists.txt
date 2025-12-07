cmake_minimum_required(VERSION 3.20)
project(MenuSystem VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(menu_app
    main.cpp
    src/models/Graph.cpp
    src/models/HashTable.cpp
    src/views/MenuView.cpp
    src/views/NetworkView.cpp
    src/views/VehicleView.cpp
    src/controllers/NetworkController.cpp
    src/controllers/VehicleController.cpp
    src/services/UIService.cpp
    src/services/SelectionService.cpp
    src/services/FileService.cpp
    src/services/ValidationService.cpp
    src/services/MessageService.cpp
    src/Dijkstra.cpp
    src/BFS.cpp
    src/DFS.cpp
)

target_include_directories(menu_app PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/models
    ${CMAKE_SOURCE_DIR}/src/controllers
    ${CMAKE_SOURCE_DIR}/src/views
    ${CMAKE_SOURCE_DIR}/src/services
)

if(MSVC)
    target_compile_options(menu_app PRIVATE /W4)
else()
    target_compile_options(menu_app PRIVATE -Wall -Wextra -pedantic)
endif()

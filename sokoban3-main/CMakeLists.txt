cmake_minimum_required(VERSION 3.23.2)
project(Sokoban)

set(CMAKE_CXX_STANDARD 17)

add_executable(Sokoban main.cpp level_generator.cpp)

include_directories(c:/SFML/include c:/SFML/include/SFML )

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

find_package(SFML REQUIRED system window graphics audio)

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Sokoban ${SFML_LIBRARIES})

endif()

#file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

if (WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

cmake_minimum_required(VERSION 3.10)
project(MYGAME_Bikec)

# Nastavitve
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SDL2_PATH "C:/SDL2")
include_directories(${SDL2_PATH}/include)
link_directories(${SDL2_PATH}/lib/x64)

# Poišči knjižnice
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)  # Za zvoke

# Vsi izvorni file-i
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h")

# Glavni program
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Povezave
target_include_directories(${PROJECT_NAME} PRIVATE
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
    src/
)

target_link_libraries(${PROJECT_NAME}
    ${SDL2_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
)

# Kopiraj assete v build mapo
file(COPY assets/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
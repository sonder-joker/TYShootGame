cmake_minimum_required(VERSION 3.12)
project(TYShootGame VERSION 0.1.0)

set (CMAKE_CXX_STANDARD 14)
include(CTest)
enable_testing()

add_subdirectory(external)

file(GLOB TYShootGame_SRC CONFIGURE_DEPENDS "src/*.cpp")

add_executable(${PROJECT_NAME} WIN32 ${TYShootGame_SRC})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} GameEngine)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

ADD_DEFINITIONS(-DUNICODE)
ADD_DEFINITIONS(-D_UNICODE)

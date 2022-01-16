project(GameEngine)

file(GLOB GameEngine_SRC CONFIGURE_DEPENDS "src/*.cpp")

add_library(${PROJECT_NAME} ${GameEngine_SRC} include/T_Map.h src/T_Map.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

ADD_DEFINITIONS(-DUNICODE)
ADD_DEFINITIONS(-D_UNICODE)
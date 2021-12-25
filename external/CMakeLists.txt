project(GameEngine)

file(GLOB GameEngine_SRC CONFIGURE_DEPENDS "src/*.cpp")

add_library(${PROJECT_NAME} ${GameEngine_SRC})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

ADD_DEFINITIONS(-DUNICODE)
ADD_DEFINITIONS(-D_UNICODE)
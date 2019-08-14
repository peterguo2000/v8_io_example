cmake_minimum_required(VERSION 3.2)
project(v8app)

set(PROJECT_ROOT /root/shared/v8_app/v8_io_example/)

include_directories(
	${PROJECT_ROOT}/include
    ${PROJECT_ROOT}/src/include
)

link_directories(
    ${PROJECT_ROOT}/lib
)
link_libraries(
    v8_monolith
    pthread
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
${PROJECT_ROOT}/src/main.cpp
${PROJECT_ROOT}/src/tcp_server/TcpServer.cpp
${PROJECT_ROOT}/src/tcp_server/TcpServerWrapper.cpp
${PROJECT_ROOT}/src/console/ConsoleWrapper.cpp)

set(EXECUTABLE_OUTPUT_PATH 
${PROJECT_ROOT}/out/obj)

add_executable(v8_io_example ${SOURCE_FILES})

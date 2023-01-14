cmake_minimum_required(VERSION 3.11)

project(request_helper CXX)
set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_executable(request_helper
    src/request_manager.cpp
    src/json_parser.cpp
    src/use_cases.cpp
    src/menu.cpp
    src/view.cpp
	src/main.cpp
)
target_link_libraries(request_helper PRIVATE CONAN_PKG::nlohmann_json CONAN_PKG::libcurl)

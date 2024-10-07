CMAKE_MINIMUM_REQUIRED(VERSION 3.22 FATAL_ERROR)

project(reflect-cpp-play)

find_package(yaml-cpp CONFIG REQUIRED)

add_executable(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20)
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_subdirectory(vendor/reflect-cpp)
set(REFLECTCPP_YAML ON) # Optional

add_subdirectory(src)

target_link_libraries(${PROJECT_NAME} PRIVATE reflectcpp yaml-cpp::yaml-cpp)
target_include_directories(${PROJECT_NAME} PRIVATE vendor/reflect-cpp/include)

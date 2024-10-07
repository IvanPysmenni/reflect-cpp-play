CMAKE_MINIMUM_REQUIRED(VERSION 3.22 FATAL_ERROR)

target_include_directories(${PROJECT_NAME} PRIVATE .)

target_sources(
    ${PROJECT_NAME} 
    PRIVATE 
    main.cpp 
)
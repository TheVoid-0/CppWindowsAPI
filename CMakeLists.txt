cmake_minimum_required(VERSION 3.11-3.18)

project(atividadesIH)

#Definitions
add_definitions(-DPSAPI_VERSION=1)

add_executable(atividade-1 
    src/atividade-1.cpp
    common/winpsapi/winpsapi.cpp
    common/winpsapi/winpsapi.h
    src/process/process.h
    src/process/process.cpp)
    
target_link_libraries(atividade-1
    Psapi.lib)

target_compile_features(atividade-1 PUBLIC cxx_std_20)
cmake_minimum_required(VERSION 3.16)
PROJECT(alog-extensions)

if (NOT TARGET alog)
    add_subdirectory(3rd-party/alog)
endif()

FILE(GLOB_RECURSE SOURCES src/*.cpp src/*.h headers/*.h)

add_library(alog-extensions STATIC ${SOURCES})
set_property(TARGET alog-extensions PROPERTY CXX_STANDARD 17)
target_link_libraries(alog-extensions PUBLIC alog)
target_include_directories(alog-extensions PUBLIC headers)

if(TARGET p7)
    target_link_libraries(alog-extensions PRIVATE p7)
    target_compile_definitions(alog-extensions PUBLIC -DALOG_HAS_P7_LIBRARY)
endif()

find_package(Qt5 QUIET OPTIONAL_COMPONENTS Core)

if(Qt5_FOUND)
    target_link_libraries(alog-extensions PRIVATE Qt5::Core)
    target_compile_definitions(alog-extensions PUBLIC -DALOG_HAS_QT_LIBRARY)
endif()

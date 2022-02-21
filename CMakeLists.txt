cmake_minimum_required(VERSION 3.16)
PROJECT(alog-extensions)

option(ALOG_EXT_ENABLE_TESTS     "ALog-ext: Enable tests" OFF)
option(ALOG_EXT_ENABLE_BENCHMARK "ALog-ext: Enable benchmark" OFF)

if (NOT TARGET alog)
    add_subdirectory(3rd-party/alog)
endif()

FILE(GLOB_RECURSE SOURCES src/*.cpp src/*.h headers/*.h)

add_library(alog-extensions STATIC ${SOURCES})
target_compile_features(alog-extensions PUBLIC cxx_std_17)
target_link_libraries(alog-extensions PUBLIC alog)
target_include_directories(alog-extensions PUBLIC headers)

if(MSVC)
    target_link_options(alog-extensions PRIVATE "/ignore:4221")
    set_target_properties(alog-extensions PROPERTIES STATIC_LIBRARY_OPTIONS "/ignore:4221")
    target_compile_definitions(alog-extensions
        PRIVATE _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
        PUBLIC _CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_WARNINGS)
endif()

if(TARGET p7)
    target_link_libraries(alog-extensions PRIVATE p7)
    target_compile_definitions(alog-extensions PUBLIC -DALOG_HAS_P7_LIBRARY)
endif()

find_package(Qt5 QUIET OPTIONAL_COMPONENTS Core)

if(Qt5_FOUND)
    target_link_libraries(alog-extensions PUBLIC Qt5::Core)
    target_compile_definitions(alog-extensions PUBLIC -DALOG_HAS_QT_LIBRARY)
endif()

add_subdirectory(tests)

cmake_minimum_required (VERSION 3.8)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

add_compile_definitions(_CRT_SECURE_NO_WARNINGS)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

ADD_LIBRARY(img STATIC img.c img.h "util.h")
ADD_LIBRARY(bmp STATIC bmp.c bmp.h "util.h")
ADD_LIBRARY(qoi STATIC qoi.c qoi.h "util.h")

add_executable (elerrina main.c main.h "util.h")

TARGET_LINK_LIBRARIES (elerrina img bmp qoi)
TARGET_LINK_LIBRARIES (elerrina ${CONAN_LIBS})


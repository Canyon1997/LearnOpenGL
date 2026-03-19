cmake_minimum_required(VERSION 3.25)
project(DaGrandRenderer)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

add_executable(DaGrandRenderer
		DaGrandRenderer/Source/main.cpp
		External/glad/src/glad.c
)

target_include_directories(DaGrandRenderer
		PRIVATE
		${CMAKE_SOURCE_DIR}/External/glad/include
		${CMAKE_SOURCE_DIR}/External/glfw/include
		${CMAKE_SOURCE_DIR}/DaGrandRenderer/Header
)

target_link_libraries(DaGrandRenderer
		PRIVATE
		${CMAKE_SOURCE_DIR}/External/glfw/lib/glfw3.lib
		OpenGL::GL
)

target_compile_definitions(DaGrandRenderer PRIVATE
	PROJECT_ROOT="${CMAKE_SOURCE_DIR}/"
)

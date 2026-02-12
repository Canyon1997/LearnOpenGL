cmake_minimum_required(VERSION 3.25)
project(DaGrandRenderer)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

add_executable(DaGrandRenderer DaGrandRenderer/Source/main.cpp)

target_include_directories(DaGrandRenderer
		PRIVATE
		${CMAKE_SOURCE_DIR}/External/SDL-release-3.4.0/include
		${CMAKE_SOURCE_DIR}/build/SDL_3.4.0_build/include-config-debug/build_config
)

target_link_libraries(DaGrandRenderer
		PRIVATE
		${CMAKE_SOURCE_DIR}/build/SDL_3.4.0_build/$<CONFIG>/SDL3.lib
		OpenGL::GL
)

add_custom_command(TARGET DaGrandRenderer POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
	    ${CMAKE_SOURCE_DIR}/build/SDL_3.4.0_build/Debug/SDL3.dll
	    $<TARGET_FILE_DIR:DaGrandRenderer>
)

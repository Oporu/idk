cmake_minimum_required(VERSION 3.16)
project(idk LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
include(FetchContent)
# include SFML
set(SFML_STATIC_LIBRARIES FALSE)
if(UNIX)
	find_package(SFML 2.6 COMPONENTS graphics window system audio QUIET)
endif()

if (SFML_FOUND)
elseif(UNIX)
	set(SFML_STATIC_LIBRARIES TRUE)
	find_package(SFML 2.6 COMPONENTS graphics window system audio QUIET)
endif()
if(SFML_FOUND)
	message("using sfml ${SFML_VERSION} from local")
else()
	message("getting sfml from github if not downloaded...")
	FetchContent_Declare(SFML
			GIT_REPOSITORY https://github.com/SFML/SFML.git
			GIT_TAG 2.6.x)
	FetchContent_MakeAvailable(SFML)
	message("done, SFML source directory = ${SFML_SOURCE_DIR}")
endif()
# /include SFML
file(GLOB_RECURSE source_files CONFIGURE_DEPENDS "src/*.cpp")
add_executable(${PROJECT_NAME} ${source_files})
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

if (WIN32)
    add_custom_command(
            TARGET ${PROJECT_NAME}
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
            VERBATIM)
endif ()

install(TARGETS ${PROJECT_NAME})

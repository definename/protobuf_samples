cmake_minimum_required(VERSION 3.14.4)

project(qwer)

message(STATUS "Running...")


set(PROTOBUF_ROOT "" CACHE STRING "Protobuf root directory path")
if (${PROTOBUF_ROOT} STREQUAL "")
	message(FATAL_ERROR "PROTOBUF_ROOT is empty")
endif()

message(STATUS "Protobuf root directory path: ${PROTOBUF_ROOT}")

set(Protobuf_INCLUDE_DIR ${PROTOBUF_ROOT}/include)
set(Protobuf_PROTOC_EXECUTABLE ${PROTOBUF_ROOT}/bin/protoc.exe)
set(Protobuf_LIBRARY
	debug ${PROTOBUF_ROOT}/lib/libprotobufd.lib
	optimized ${PROTOBUF_ROOT}/lib/libprotobuf.lib
	)
set(Protobuf_PROTOC_LIBRARY
	debug ${PROTOBUF_ROOT}/lib/libprotocd.lib
	optimized ${PROTOBUF_ROOT}/lib/libprotoc.lib
	)
set(Protobuf_LITE_LIBRARY
	debug ${PROTOBUF_ROOT}/lib/libprotobuf-lited.lib
	optimized ${PROTOBUF_ROOT}/lib/libprotobuf-lite.lib
	)

find_package(Protobuf REQUIRED)

set(PROTOFILES "" CACHE STRING "Protofile list")
if (${PROTOFILES} STREQUAL "")
	message(FATAL_ERROR "Empty protofile list was given")
endif()

message(STATUS "Protofiles: ${PROTOFILES}")

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTOFILES})
set(PROTOBUF_SOURCES
	${PROTO_SRCS}
	${PROTO_HDRS}
	)

set(PROJECT_SOURCES
	src/main.cpp
	)
set(PROJECT_HEADERS
	)
set(MISC
	src/pch.h
	src/pch.cpp
	)
	
add_executable(${PROJECT_NAME}
	${PROJECT_HEADERS}
	${PROJECT_RESOURCES}
	${PROJECT_SOURCES}
	${MISC}
	)

add_custom_target(${PROJECT_NAME}-gen
	DEPENDS ${PROTOBUF_SOURCES}
	)
	
add_dependencies(${PROJECT_NAME}
	${PROJECT_NAME}-gen
	)

message(STATUS "Protofiles were generated: ${PROTOBUF_SOURCES}")

install(FILES ${PROTOBUF_SOURCES} DESTINATION ${CMAKE_INSTALL_PREFIX})

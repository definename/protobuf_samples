cmake_minimum_required(VERSION 3.14.4)

project(protogen)

if (EXISTS ${PROTOFILES_ROOT})
	file(GLOB PROTOFILES "${PROTOFILES_ROOT}/*.proto")
	message(STATUS "Protofiles to be processed: ${PROTOFILES}")
else()
	message(FATAL_ERROR "Protofile root path is invalid")
endif()

if (EXISTS ${PROTOBUF_ROOT})
	message(STATUS "Protobuf root directory path: ${PROTOBUF_ROOT}")
else()
	message(FATAL_ERROR "Protobuf root path is invalid")
endif()

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
set(Protobuf_DEBUG ON)
set(Protobuf_USE_STATIC_LIBS ON)

find_package(Protobuf REQUIRED)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTOFILES})
set(PROTOBUF_SOURCES
	${PROTO_SRCS}
	${PROTO_HDRS}
	)

add_custom_target(${PROJECT_NAME} ALL
	DEPENDS ${PROTOBUF_SOURCES}
	COMMENT "Protofiles is being generated: ${PROTOBUF_SOURCES}"
	)

install(FILES ${PROTOBUF_SOURCES} DESTINATION ${CMAKE_INSTALL_PREFIX})

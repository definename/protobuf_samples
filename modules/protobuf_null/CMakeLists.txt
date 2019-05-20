project(protobuf_null)

set(PROJECT_SOURCES
	src/main.cpp
	)
set(PROJECT_HEADERS
	)
set(MISC
	src/pch.h
	src/pch.cpp
	)

set(PROTOFILE_PATH ${CMAKE_CURRENT_LIST_DIR}/protofiles)
set(PROTOFILES
	${PROTOFILE_PATH}/Boss.proto
	${PROTOFILE_PATH}/Slave.proto
	)
# protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTOFILES})
set(PROTOBUF_SOURCES
	${PROTO_SRCS}
	${PROTO_HDRS}
	)

add_definitions(
	-DUNICODE
	-D_UNICODE
	)

source_group("Source Files" FILES ${PROJECT_SOURCES})
source_group("Header Files" FILES ${PROJECT_HEADERS})
source_group("Protobuf" FILES ${PROTOBUF_SOURCES})
source_group("" FILES ${MISC})

set_source_files_properties(${PROTO_SRCS} ${PROTO_HDRS} PROPERTIES COMPILE_FLAGS "/Y-")

add_executable(${PROJECT_NAME}
	${PROJECT_SOURCES}
	${PROJECT_HEADERS}
	${MISC}
	${PROTOBUF_SOURCES}
	)

add_precompiled_headers(${PROJECT_NAME} "src/")

include_directories(
	include
	${CMAKE_CURRENT_BINARY_DIR}
	${ZLIB_INCLUDE_DIRS}
	${Protobuf_INCLUDE_DIRS}
	)

target_link_libraries(${PROJECT_NAME}
	${ZLIB_LIBRARIES}
	${Protobuf_LIBRARIES}
	)

add_dependencies(${PROJECT_NAME}
	zlib
	protobuf
	)

#set_target_properties(${PROJECT_NAME} PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD 1)
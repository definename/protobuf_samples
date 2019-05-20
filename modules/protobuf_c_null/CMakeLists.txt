project(protobuf_c_null)

include(PCHSupport)
include(CRTLinkage)

set(PROJECT_SOURCES
	src/main.cpp
	)
set(PROJECT_HEADERS
	)
set(MISC
	src/pch.h
	src/pch.cpp
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
	${ZLIB_INCLUDE_DIR}
	${Protobuf_INCLUDE_DIRS}
	)

target_link_libraries(${PROJECT_NAME}
	${ZLIB_LIBRARY}
	${Protobuf_LIBRARIES}
	)

add_dependencies(${PROJECT_NAME}
	zlib
	protobuf
	protobuf-c
	)

set(PROTOFILE_PATH ${CMAKE_CURRENT_LIST_DIR}/protofiles)
set(PROTOBUF_C_SRC ${CMAKE_CURRENT_BINARY_DIR}/EmployeeC.pb-c.c)
set(PROTOBUF_C_HDR ${CMAKE_CURRENT_BINARY_DIR}/EmployeeC.pb-c.h)
message(STATUS "Here is your proto files => ${CMAKE_CURRENT_BINARY_DIR}")

# add_custom_command(
	# OUTPUT ${PROTOBUF_C_SRC}
		# ${PROTOBUF_C_HDR}
	# COMMAND ${Protobuf_PROTOC_EXECUTABLE}
		# "--plugin=${Protobuf_PROTOC_GEN_C}"
		# "--proto_path=${PROTOFILE_PATH}"
		# "${PROTOFILE_PATH}/Employee.proto"
		# "--c_out=${CMAKE_CURRENT_BINARY_DIR}"
	# DEPENDS protobuf-c
	# COMMENT "Running C protocol buffer compiler..."
	# VERBATIM
	# )

add_custom_command(
	TARGET ${PROJECT_NAME}
	PRE_BUILD
	COMMAND ${Protobuf_PROTOC_EXECUTABLE}
		"--plugin=${Protobuf_PROTOC_GEN_C}"
		"--proto_path=${PROTOFILE_PATH}"
		"${PROTOFILE_PATH}/EmployeeC.proto"
		"--c_out=${CMAKE_CURRENT_BINARY_DIR}"
	DEPENDS protobuf-c
	COMMENT "Running C protocol buffer compiler..."
	VERBATIM
	)

#set_target_properties(${PROJECT_NAME} PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD 1)
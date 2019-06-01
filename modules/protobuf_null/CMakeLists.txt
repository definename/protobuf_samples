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

add_definitions(
	-DUNICODE
	-D_UNICODE
	)

source_group("Source Files" FILES ${PROJECT_SOURCES})
source_group("Header Files" FILES ${PROJECT_HEADERS})
source_group("" FILES ${MISC})

add_executable(${PROJECT_NAME}
	${PROJECT_SOURCES}
	${PROJECT_HEADERS}
	${MISC}
	)

add_precompiled_headers(${PROJECT_NAME} "src/")

include_directories(
	include
	${CMAKE_CURRENT_BINARY_DIR}
	${ZLIB_INCLUDE_DIRS}
	${Protobuf_INCLUDE_DIRS}
	${Protogen_INCLUDE_DIRS}
	)

target_link_libraries(${PROJECT_NAME}
	${ZLIB_LIBRARIES}
	${Protobuf_LIBRARIES}
	${Protogen_LIBRARIES}
	)

add_dependencies(${PROJECT_NAME}
	zlib
	protobuf
	protogen
	)
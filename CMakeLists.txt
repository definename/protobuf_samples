cmake_minimum_required(VERSION 3.14.4)

project(protobuf_samples)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

###########################################################
# Build options ###########################################

option(BUILD_WITH_PROTOBUF_CPP "Build with protobuf CPP" ON)
option(BUILD_WITH_PROTOBUF_C "Build with protobuf C" OFF)

###########################################################
# Includes ################################################

include(PCHSupport)
include(CRTLinkage)
include(ExternalProject)

# External directory
set(EXTERNAL_PATH ${CMAKE_SOURCE_DIR}/external)
# Patch directory
set(PATCH_PATH ${EXTERNAL_PATH}/patches)
# External install directory
set(EXTERNAL_INSTALL_PATH ${CMAKE_BINARY_DIR}/external)
# Sets executable output folder
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

###########################################################
# ZLIB ####################################################

set(ZLIB_ROOT ${EXTERNAL_INSTALL_PATH}/ZLIB)
ExternalProject_Add(
	zlib
	URL "${EXTERNAL_PATH}/zlib-1.2.8.zip"
	URL_MD5 D34BAA0DA16E33A5EF095E7EEF7D2472
	CMAKE_ARGS
		-DCMAKE_INSTALL_PREFIX:PATH=${ZLIB_ROOT}
		-DBUILD_SHARED_LIBS:BOOL=OFF
	PATCH_COMMAND 
		${CMAKE_COMMAND} -P ${PATCH_PATH}/zlib-1.2.8.patches/patch.cmake ${CMAKE_SOURCE_DIR}
	)

set(ZLIB_INCLUDE_DIRS ${ZLIB_ROOT}/include)
set(ZLIB_LIBRARIES
	debug ${ZLIB_ROOT}/lib/zlibstaticd.lib
	optimized ${ZLIB_ROOT}/lib/zlibstatic.lib
	)
SET_PROPERTY(TARGET zlib PROPERTY FOLDER "External")

############################################################
# PROTOBUF-CPP #############################################

if(BUILD_WITH_PROTOBUF_CPP)
	set(PROTOBUF_ROOT ${EXTERNAL_INSTALL_PATH}/PROTOBUF)
	ExternalProject_Add(
		protobuf
		DEPENDS
			zlib
		URL "${EXTERNAL_PATH}/protobuf-cpp-3.7.1.zip"
		URL_MD5 7d819ec1943f1fef3a85aaad32e122f4
		CMAKE_ARGS
			-DCMAKE_INSTALL_PREFIX:PATH=${PROTOBUF_ROOT}
			-DZLIB_ROOT:PATH=${ZLIB_ROOT}
			-Dprotobuf_BUILD_TESTS=OFF
			-DBUILD_SHARED_LIBS=OFF
			-Dprotobuf_VERBOSE=ON
		SOURCE_SUBDIR cmake
		PATCH_COMMAND 
			${CMAKE_COMMAND} -P ${PATCH_PATH}/protobuf-cpp-3.7.1.patches/patch.cmake ${CMAKE_SOURCE_DIR}
		)
	SET_PROPERTY(TARGET protobuf PROPERTY FOLDER "External")
	
	set(PROTOFILE_PATH ${CMAKE_CURRENT_LIST_DIR}/modules/protobuf_null/protofiles)
	set(PROTOFILES
		${PROTOFILE_PATH}/Boss.proto
		${PROTOFILE_PATH}/Slave.proto
		)

	set(PROTOBUF_GEN_ROOT ${EXTERNAL_INSTALL_PATH}/PROTOBUF_GEN)
	ExternalProject_Add(
		protobuf-gen
		DEPENDS
			protobuf
		URL "${EXTERNAL_PATH}/protobuf-gen.zip"
		URL_MD5 03cdfc39a49675b4948bea24ea8b3db3
		CMAKE_ARGS
			-DCMAKE_INSTALL_PREFIX:PATH=${PROTOBUF_GEN_ROOT}
			-DPROTOBUF_ROOT=${PROTOBUF_ROOT}
			-DPROTOFILES=${PROTOFILES}
		PATCH_COMMAND 
			${CMAKE_COMMAND} -P ${PATCH_PATH}/protobuf-gen.patches/patch.cmake ${CMAKE_SOURCE_DIR}
		)
	SET_PROPERTY(TARGET protobuf-gen PROPERTY FOLDER "External")
	# set(Protobuf_PROTOC_EXECUTABLE ${PROTOBUF_ROOT}/bin/protoc.exe)
	# set(Protobuf_LIBRARY
		# debug ${PROTOBUF_ROOT}/lib/libprotobufd.lib
		# optimized ${PROTOBUF_ROOT}/lib/libprotobuf.lib
		# )
	# set(Protobuf_PROTOC_LIBRARY
		# debug ${PROTOBUF_ROOT}/lib/libprotocd.lib
		# optimized ${PROTOBUF_ROOT}/lib/libprotoc.lib
		# )
	# set(Protobuf_LITE_LIBRARY
		# debug ${PROTOBUF_ROOT}/lib/libprotobuf-lited.lib
		# optimized ${PROTOBUF_ROOT}/lib/libprotobuf-lite.lib
		# )
	# find_package(Protobuf REQUIRED)
	
	add_subdirectory(modules/protobuf_null)
endif()

############################################################
# PROTOBUF-C ###############################################

if(BUILD_WITH_PROTOBUF_C)
	set(PROTOBUF_C_ROOT ${EXTERNAL_INSTALL_PATH}/PROTOBUF_C)
	
	set(Protobuf_LIBRARY_debug ${PROTOBUF_ROOT}/lib/libprotobufd.lib)
	set(Protobuf_LIBRARY_optimized ${PROTOBUF_ROOT}/lib/libprotobuf.lib)
	
	set(Protobuf_PROTOC_LIBRARY_debug ${PROTOBUF_ROOT}/lib/libprotocd.lib)
	set(Protobuf_PROTOC_LIBRARY_optimized ${PROTOBUF_ROOT}/lib/libprotoc.lib)
	
	ExternalProject_Add(
		protobuf-c
		DEPENDS
			protobuf
		URL "${EXTERNAL_PATH}/protobuf-c-1.3.0.zip"
		URL_MD5 27e0d99d8211cfe84d498c901fff2b2d
		CMAKE_ARGS
			-DCMAKE_INSTALL_PREFIX:PATH=${PROTOBUF_C_ROOT}
			-DProtobuf_INCLUDE_DIR:PATH=${Protobuf_INCLUDE_DIR}
			-DProtobuf_PROTOC_EXECUTABLE:PATH=${Protobuf_PROTOC_EXECUTABLE}
			-DProtobuf_LIBRARY_debug:PATH=${Protobuf_LIBRARY_debug}
			-DProtobuf_LIBRARY_optimized:PATH=${Protobuf_LIBRARY_optimized}
			-DProtobuf_PROTOC_LIBRARY_debug:PATH=${Protobuf_PROTOC_LIBRARY_debug}
			-DProtobuf_PROTOC_LIBRARY_optimized:PATH=${Protobuf_PROTOC_LIBRARY_optimized}
			-DMSVC_STATIC_BUILD:BOOL=ON
			-DBUILD_PROTO3:BOOL=ON
		SOURCE_SUBDIR build-cmake
		PATCH_COMMAND
			${CMAKE_COMMAND} -P ${PATCH_PATH}/protobuf-c-1.3.0.patches/patch.cmake ${CMAKE_SOURCE_DIR}
			)
	SET_PROPERTY(TARGET protobuf-c PROPERTY FOLDER "External")

	set(Protobuf_C_INCLUDE_DIR
		${PROTOBUF_C_ROOT}/include)
	set(Protobuf_PROTOC_GEN_C
		${PROTOBUF_C_ROOT}/bin/protoc-gen-c.exe)
		
	add_subdirectory(modules/protobuf_c_null)
endif()
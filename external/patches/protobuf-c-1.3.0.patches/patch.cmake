set(PROJECT_ROOT_DIR "${CMAKE_ARGV3}")
set(PATCH_SOURCE_DIR "${PROJECT_ROOT_DIR}/external/patches/protobuf-c-1.3.0.patches")

message(STATUS "Patching protobuf-c...")

execute_process(COMMAND ${CMAKE_COMMAND} -E copy ${PATCH_SOURCE_DIR}/build-cmake/CMakeLists.txt build-cmake/CMakeLists.txt)
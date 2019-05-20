set(PROJECT_ROOT_DIR "${CMAKE_ARGV3}")
set(PATCH_SOURCE_DIR "${PROJECT_ROOT_DIR}/external/patches/protobuf-gen.patches")

message(STATUS "Patching protobuf-gen...")
execute_process(COMMAND ${CMAKE_COMMAND} -E copy ${PATCH_SOURCE_DIR}/CMakeLists.txt CMakeLists.txt)

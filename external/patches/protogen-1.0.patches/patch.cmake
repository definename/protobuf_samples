set(PROJECT_ROOT_DIR "${CMAKE_ARGV3}")
set(PATCH_SOURCE_DIR "${PROJECT_ROOT_DIR}/external/patches/protogen-1.0.patches")

message(STATUS "Patching protogen...")
execute_process(COMMAND ${CMAKE_COMMAND} -E copy ${PATCH_SOURCE_DIR}/CMakeLists.txt CMakeLists.txt)

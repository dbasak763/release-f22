# CMAKE generated file: DO NOT EDIT!
# Generated by CMake Version 3.22
cmake_policy(SET CMP0009 NEW)

# cs225_sources at lib/CMakeLists.txt:12 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/workspaces/CS225/release-f22/lab_huffman/lib/cs225/*.cpp")
set(OLD_GLOB
  "/workspaces/CS225/release-f22/lab_huffman/lib/cs225/HSLAPixel.cpp"
  "/workspaces/CS225/release-f22/lab_huffman/lib/cs225/PNG.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/workspaces/CS225/release-f22/lab_huffman/build/CMakeFiles/cmake.verify_globs")
endif()

# lodepng_sources at lib/CMakeLists.txt:6 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/workspaces/CS225/release-f22/lab_huffman/lib/lodepng/*.cpp")
set(OLD_GLOB
  "/workspaces/CS225/release-f22/lab_huffman/lib/lodepng/lodepng.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/workspaces/CS225/release-f22/lab_huffman/build/CMakeFiles/cmake.verify_globs")
endif()

# lodepng_sources at lib/CMakeLists.txt:6 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/workspaces/CS225/release-f22/lab_huffman/lib/lodepng/*.h")
set(OLD_GLOB
  "/workspaces/CS225/release-f22/lab_huffman/lib/lodepng/lodepng.h"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/workspaces/CS225/release-f22/lab_huffman/build/CMakeFiles/cmake.verify_globs")
endif()

# src_sources at src/CMakeLists.txt:5 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/workspaces/CS225/release-f22/lab_huffman/src/*.cpp")
set(OLD_GLOB
  "/workspaces/CS225/release-f22/lab_huffman/src/binary_file_reader.cpp"
  "/workspaces/CS225/release-f22/lab_huffman/src/binary_file_writer.cpp"
  "/workspaces/CS225/release-f22/lab_huffman/src/decoder.cpp"
  "/workspaces/CS225/release-f22/lab_huffman/src/encoder.cpp"
  "/workspaces/CS225/release-f22/lab_huffman/src/frequency.cpp"
  "/workspaces/CS225/release-f22/lab_huffman/src/huffman_tree.cpp"
  "/workspaces/CS225/release-f22/lab_huffman/src/print_as_ascii.cpp"
  "/workspaces/CS225/release-f22/lab_huffman/src/view_tree.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/workspaces/CS225/release-f22/lab_huffman/build/CMakeFiles/cmake.verify_globs")
endif()

# tests_src at CMakeLists.txt:131 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/workspaces/CS225/release-f22/lab_huffman/tests/*.cpp")
set(OLD_GLOB
  "/workspaces/CS225/release-f22/lab_huffman/tests/tests.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/workspaces/CS225/release-f22/lab_huffman/build/CMakeFiles/cmake.verify_globs")
endif()

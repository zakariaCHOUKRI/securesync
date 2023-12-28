# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\securesync_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\securesync_autogen.dir\\ParseCache.txt"
  "securesync_autogen"
  )
endif()

# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\blockTcpClient_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\blockTcpClient_autogen.dir\\ParseCache.txt"
  "blockTcpClient_autogen"
  )
endif()

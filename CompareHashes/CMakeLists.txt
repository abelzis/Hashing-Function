cmake_minimum_required(VERSION 3.12.2)

project(CompareHashes)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release"
    CACHE STRING "Configuration types" FORCE)

add_executable(CompareHashes
  "CompareHashes.cpp"
  hash.h
)
# Preprocessor definitions
target_compile_definitions(CompareHashes PRIVATE
  $<$<CONFIG:Debug>:_UNICODE;_DEBUG;_CONSOLE>
  $<$<CONFIG:Release>:_UNICODE;NDEBUG;_CONSOLE>
)

# SDL check
target_compile_options(CompareHashes PRIVATE
  "$<$<CONFIG:Debug>:/sdl>"
  "$<$<CONFIG:Release>:/sdl>"
)

# Minimal rebuild
if (MSVC)
  target_compile_options(CompareHashes PRIVATE
    "$<$<CONFIG:Debug>:/Gm->"
    "$<$<CONFIG:Release>:/Gm->"
  )
endif ()

# Precompiled header files
if (MSVC)
  target_compile_options(CompareHashes PRIVATE
    ""
  )
endif ()

# Find all the headers in the library.
file(GLOB_RECURSE LIBUBT_HEADERS CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)

# Find all the sources in the library.
file(GLOB_RECURSE LIBUBT_SOURCES CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

# Create the ubt library.
add_library(ubt STATIC ${LIBUBT_HEADERS} ${LIBUBT_SOURCES})
target_include_directories(ubt PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

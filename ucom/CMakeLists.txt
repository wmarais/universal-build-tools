# Find all the headers in the library.
file(GLOB_RECURSE UCOM_HEADERS CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)

# Find all the sources in the library.
file(GLOB_RECURSE UCOM_SOURCES CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

# Build the ucom application.
add_executable(ucom ${UCOM_HEADERS} ${UCOM_SOURCES})
target_link_libraries(ucom ubt)


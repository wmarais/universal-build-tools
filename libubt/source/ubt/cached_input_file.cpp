#include "ubt/cached_input_file.hpp"

#include <algorithm>
#include <fstream>
#include <filesystem>

using namespace ubt;

//==============================================================================
cached_input_file::cached_input_file(const std::string & path)
{
  // Allocate enough space to read the whole file to memory. Ideally as long as
  // the file do not change between reservation and copying, it should not
  // result in any further allocations. 
  m_text.reserve(std::filesystem::file_size(path));

  // Open the source file. Ideally we can open the files exclusively to prevent
  // the file from chaning, but it will not work well with IDEs and editors so
  // we dont.
  std::ifstream input_file(path);

  // Copy the contents of the file into the string.
  std::copy(std::istream_iterator<std::uint8_t>(input_file),
    std::istream_iterator<std::uint8_t>(input_file),
    std::back_inserter(m_text));
}

//==============================================================================
std::size_t cached_input_file::length() const
{
  return m_text.length();
}

//==============================================================================
std::string::const_iterator cached_input_file::cbegin() const
{
  return m_text.cbegin();
}

//==============================================================================
std::string::const_iterator cached_input_file::cend() const
{
  return m_text.cend();
}

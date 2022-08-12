#pragma once

#include <array>
#include <cstdint>
#include <memory>
#include <string>

namespace ubt
{
  // Load the entire contents of a code file into memory so it can be parsed in
  // RAM. To allow concurrent reading from the same file, the file is not 
  // writeable, avoiding the need for locking which has a significant
  // performance impact. This supports any language and file type and does not
  // need to be modified to support additional languages.
  class cached_input_file final
  {
      // The file contents.
      std::string m_text;
    public:
      // Create an empty file object. Needed for storage in vectors etc.
      cached_input_file() = default;
    
      // Create a file and load the contents.
      cached_input_file(const std::string & path);

      // The length of the file in characters.
      std::size_t length() const;

      // Iterator pointing to the first byte in the file.
      std::string::const_iterator cbegin() const;

      // Iteartor pointing to the last byte + 1 in the file.
      std::string::const_iterator cend() const;
  };
}

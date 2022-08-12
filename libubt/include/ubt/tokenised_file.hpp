#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "cached_input_file.hpp"

namespace ubt
{
  // Parse the contents of a cached input file into tokens. To allow concurrent
  // reading from the same file, the file is not writeable, avoiding the need
  // for locking which has a significant performance impact. This supports any
  // language provided the correct token lists are provided.
  class tokenised_file final
  {
    public:
      class token final
      {
          std::int32_t m_row;
          std::int32_t m_col;
          std::string m_text;
        public:
          token() = default;
          token(std::int32_t row, std::int32_t col, const std::string & text);

          std::int32_t row() const;
          std::int32_t col() const;
          std::string text() const;
      };

      tokenised_file() = default;

      // Tokenise the cached input file into a series of tokens that can be
      // parsed into an AST, linting, documentation, etc. Two type of seperators
      // are used:
      //   1. discard_seperators: Seperators that split the string, but must be
      //                          discarded after the split. These are usually
      //                          seperators like space (" ") or ("\t\r\n") etc.
      //   2. retain_seperators:  Split the string but retain the seperator.
      //                          This is usually for operators like (), ++, etc
      //                          that must be retained for the code to have
      //                          meaning. Some language like python, indenting
      //                          and new lines are important.
      tokenised_file(const cached_input_file & file,
        const std::vector<std::string> & discard_seperators,
        const std::vector<std::string> & retain_seperators);

      std::vector<token>::const_iterator cbegin() const;
      std::vector<token>::const_iterator cend() const;

    private:
      // The list of tokens extracted from the cached input file.
      std::vector<token> m_tokens;

      void push_token(std::int32_t row, std::int32_t col, 
                      std::string::const_iterator begin,
                      std::string::const_iterator end);

  };
}

#include "ubt/tokenised_file.hpp"

#include <algorithm>

using namespace ubt;

//==============================================================================
tokenised_file::tokenised_file(const cached_input_file & file,
  const std::vector<std::string> & discard_seperators,
  const std::vector<std::string> & retain_seperators)
{
  // The current row and column in the file.
  std::int32_t row = 1, col = 1;

  // The position where the current token starts.
  auto token_start = file.cbegin();

  // Iterate through all the characters one at a time.
  for(auto cur_pos = file.cbegin(); cur_pos != file.cend(); cur_pos++)
  {
    // Check if it's a newline character.
    if((*cur_pos) == '\n')
    {
      ++row;
      col = 1;
    }

    // Check if it's a seperator to discard.
    for(auto seperator : discard_seperators)
    {
      // Check if there is enough characters left to fit this seperator. If not
      // skip to the next one.
      if(seperator.length() > std::distance(cur_pos, file.cend()))
        continue;

      // Calculate the end iterator to limit the search range.
      auto end_pos = cur_pos;
      std::advance(end_pos, seperator.length());

      // Check if the seperator exists.
      if(std::search(cur_pos, end_pos, seperator.cbegin(), seperator.cend()) 
        != end_pos)
      {
        // Create the token.
        push_token(row, col, cur_pos, end_pos);
        token_start = end_pos;

        // Skip past the sepertor.
        col += seperator.length();
        std::advance(cur_pos, seperator.length() - 1);
      }
      else
      {
        // Skip to the next character.
        ++col;
      }
    }

    // Check if it's a seperator to retain.
    for(auto seperator : retain_seperators)
    {
      // Check if there is enough characters left to fit this seperator. If not
      // skip to the next one.
      if(seperator.length() > std::distance(cur_pos, file.cend()))
        continue;

      // Calculate the end iterator to limit the search range.
      auto end_pos = cur_pos;
      std::advance(end_pos, seperator.length());

      // Check if the seperator exists.
      if(std::search(cur_pos, end_pos, seperator.cbegin(), seperator.cend()) 
        != end_pos)
      {
        // Create the token.
        push_token(row, col, cur_pos, end_pos);
        token_start = end_pos;

        // Push the seperator.
        push_token(row, col, seperator.cbegin(), seperator.cend());
        col += seperator.length();
        std::advance(cur_pos, seperator.length() - 1);
      }
      else
      {
        // Skip to the next character.
        ++col;
      }
    }
  }

  // Push the last token.
  push_token(row, col, token_start, file.cend());
}

//==============================================================================
void tokenised_file::push_token(std::int32_t row, std::int32_t col, 
                                std::string::const_iterator begin,
                                std::string::const_iterator end)
{
  // Discard and null tokens.
  if(begin == end)
    return;

  // Extract the token string.
  std::string token_str(begin, end);
  m_tokens.push_back(token(row, col, token_str));
}

//==============================================================================
std::vector<tokenised_file::token>::const_iterator 
  tokenised_file::cbegin() const
{
  return m_tokens.cbegin();
}

//==============================================================================
std::vector<tokenised_file::token>::const_iterator 
  tokenised_file::cend() const
{
  return m_tokens.cend();
}

//==============================================================================
tokenised_file::token::token(std::int32_t row, std::int32_t col, 
  const std::string & text) : m_row(row), m_col(col), m_text(text) {}

//==============================================================================
std::int32_t tokenised_file::token::row() const
{
  return m_row;
}

//==============================================================================
std::int32_t tokenised_file::token::col() const
{
  return m_col;
}

//==============================================================================
std::string tokenised_file::token::text() const
{
  return m_text;
}

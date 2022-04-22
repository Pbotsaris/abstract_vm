#include "../include/tokenizer.h"
namespace tokenizer
{
  using std::regex_constants::icase;
  using RegexPair = const std::pair<const token_type, const std::basic_regex<char> >;
  
  /* INSTRUCTIONS */
  RegexPair PUSH            (push, std::regex ("^push", icase));
  RegexPair POP             (pop, std::regex ("^pop", icase));
  RegexPair DUMP            (dump, std::regex ("^dump", icase));
  RegexPair ASSERT          (assert, std::regex ("^assert", icase));
  RegexPair ADD             (add, std::regex ("^add", icase));
  RegexPair SUB             (sub, std::regex ("^sub", icase));
  RegexPair MUL             (mul, std::regex ("^mul", icase));
  RegexPair DIV             (div, std::regex ("^div", icase));
  RegexPair MOD             (mod, std::regex ("^mod", icase));
  RegexPair PRINT           (print, std::regex ("^print", icase));
  RegexPair EXIT            (exit, std::regex ("^exit", icase));
  /* VALUES */
  RegexPair INT8            (int8, std::regex ("^int8", icase));
  RegexPair INT16           (int16, std::regex ("^int16", icase));
  RegexPair INT32           (int32, std::regex ("^int32", icase));
  /* SYNTAX  */
  RegexPair SPACE           (space, std::regex ("^\\s+"));
  RegexPair SEP             (sep, std::regex ("^\n"));
  RegexPair PARENTHESIS     (parenthesis, std::regex ("(^\\(|^\\))"));
  RegexPair COMMENT         (comment, std::regex ("^;")); // make sure it picks up the whole line;
  RegexPair END_OF_PROGRAM  (end_of_program, std::regex ("^;;"));
  /* NUMERIC */
  RegexPair INTEGERS        (integers, std::regex ("[-]?[0-9]+"));
  RegexPair FLOATS          (floats, std::regex ("[-]?[0-9].[0-9]+"));
  
  const std::array<RegexPair, 23> REGEXES = 
  { 
    PUSH, 
    POP, 
    DUMP, 
    ASSERT, 
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    PRINT,
    EXIT,
    INT8,
    INT16,
    INT32,
    SPACE,
    SEP,
    COMMENT, 
    END_OF_PROGRAM,
    PARENTHESIS,
    INTEGERS,
    FLOATS
  };
  
  Tokenizer::Tokenizer (std::string &text) : m_text (text), m_textlen (text.length ()), m_cursor (0)
  {}
  
  Token const tokenizer::Tokenizer::nextToken ()
  {
    const std::string sub_string = m_text.substr (m_cursor, m_textlen);
  
    for (const auto &regex : tokenizer::REGEXES)
    {
      std::smatch matched;

      if (std::regex_search (sub_string, matched, regex.second))
      {
        m_cursor += matched[0].length ();
        tokenizer::Token token = {regex.first, matched[0]};
  
        if (token.type == space)
          return tokenizer::Tokenizer::nextToken();
  
        return token;
      }
    }

   exceptions::UnexpectedToken::throwE();
  }
}

struct tokenizer::Tokenizer::Private {
  };



  TEST_CASE("Tokenizer dump")
  {
    SUBCASE("first")
      {
      try
        {
          std::string code = "push dump";
          tokenizer::Tokenizer tokenizer = tokenizer::Tokenizer (code);
          tokenizer::Token token = tokenizer.nextToken ();

          CHECK(token.type == tokenizer::push);
          CHECK(token.value == "push");
          std::cout << token.value << std::endl;

         tokenizer::Token token2 = tokenizer.nextToken ();

            CHECK(token2.type == tokenizer::dump);
            CHECK(token2.value == "dump");
            std::cout << token2.value << std::endl;
        }
        catch (exceptions::UnexpectedToken &err)
          {
            err.print();
          }

      };
  };

#include "../include/tokenizer.h"
namespace tokenizer
{
// REGEXES INSTRUCTIONS
const std::pair<const std::string,
                const std::basic_regex<char> > PUSH (std::string ("push"), std::regex ("^push", std::regex_constants::icase));
const std::pair<const std::string,
                const std::basic_regex<char> > POP (std::string ("pop"), std::regex ("^pop", std::regex_constants::icase));
const std::pair<const std::string,
                const std::basic_regex<char> > DUMP (std::string ("dump"), std::regex ("^dump", std::regex_constants::icase));
const std::pair<const std::string,
                const std::basic_regex<char> > ASSERT (std::string ("assert"), std::regex ("^assert", std::regex_constants::icase));
const std::pair<const std::string,
                const std::basic_regex<char> > ADD (std::string ("add"), std::regex ("^add", std::regex_constants::icase));
const std::pair<const std::string,
                const std::basic_regex<char> > SUB (std::string ("sub"), std::regex ("^sub", std::regex_constants::icase));
const std::pair<const std::string,
                const std::basic_regex<char> > MUL (std::string ("mul"), std::regex ("^mul", std::regex_constants::icase));
const std::pair<const std::string,
                const std::basic_regex<char> > DIV (std::string ("div"), std::regex ("^div", std::regex_constants::icase));
const std::pair<const std::string,
                const std::basic_regex<char> > MOD (std::string ("mod"), std::regex ("^mod", std::regex_constants::icase));
const std::pair<const std::string,
                const std::basic_regex<char> > PRINT (std::string ("print"), std::regex ("^print", std::regex_constants::icase));
const std::pair<const std::string,
                const std::basic_regex<char> > EXIT (std::string ("exit"), std::regex ("^exit", std::regex_constants::icase));

// REGEXES VALUES
const std::pair<const std::string,
                const std::basic_regex<char> > INT8 (std::string ("int8"), std::regex ("^int8", std::regex_constants::icase));
const std::pair<const std::string,
                const std::basic_regex<char> > INT16 (std::string ("int16"), std::regex ("^int16", std::regex_constants::icase));
const std::pair<const std::string,
                const std::basic_regex<char> > INT32 (std::string ("int32"), std::regex ("^int32", std::regex_constants::icase));
const std::pair<const std::string,
                const std::basic_regex<char> > FLOAT (std::string ("float"), std::regex ("^float", std::regex_constants::icase));
const std::pair<const std::string,
                const std::basic_regex<char> > DOUBLE (std::string ("double"), std::regex ("^double", std::regex_constants::icase));

// SYNTAX OTHER
const std::pair<const std::string,
                const std::basic_regex<char> > SPACE (std::string (" "), std::regex ("^ +"));
const std::pair<const std::string,
                const std::basic_regex<char> > SEP (std::string ("\n"), std::regex ("^\n"));
const std::pair<const std::string,
                const std::basic_regex<char> > PARENTHESIS (std::string ("("), std::regex ("(^\\(|^\\))"));
const std::pair<const std::string,
                const std::basic_regex<char> > COMMENT (std::string (";"), std::regex ("^;")); // make sure it picks up the whole line;
const std::pair<const std::string,
                const std::basic_regex<char> > END_OF_FILE (std::string (";;"), std::regex ("^;;"));
// NUMERIC
const std::pair<const std::string,
                const std::basic_regex<char> > INTEGERS (std::string ("integers"), std::regex ("[-]?[0-9]+"));
const std::pair<const std::string,
                const std::basic_regex<char> > FLOATS (std::string ("floats"), std::regex ("[-]?[0-9].[0-9]+"));

const std::array<std::pair<const std::string, const std::basic_regex<char> >, 23>
    REGEXES = {PUSH, POP, DUMP, ASSERT,
               ADD, SUB, MUL, DIV, MOD,
               PRINT, EXIT, INT8, INT16,
               INT32, DOUBLE, FLOAT, SPACE,
               SEP, COMMENT, END_OF_FILE, PARENTHESIS,
               INTEGERS, FLOATS};
}

tokenizer::Tokenizer::Tokenizer (std::string &text) : m_text (text), m_textlen (text.length ()), m_cursor (0)
{}

tokenizer::Token tokenizer::Tokenizer::nextToken ()
{
  const std::string sub_string = m_text.substr (m_cursor, m_textlen);

  for (const auto &regex : tokenizer::REGEXES)
    {
      if (std::regex_search (sub_string, regex.second))
        {
          m_cursor += regex.first.length ();
          tokenizer::Token token = {tokenizer::instr, regex.first};

          if (token.value == " ")
            return tokenizer::Tokenizer::nextToken();

          return token;
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
          std::string code = "push push";
          tokenizer::Tokenizer tokenizer = tokenizer::Tokenizer (code);
          tokenizer::Token token = tokenizer.nextToken ();

          CHECK(token.type == tokenizer::instr);
          CHECK(token.value == "push");
          std::cout << token.value << std::endl;

          tokenizer::Token token2 = tokenizer.nextToken ();

          CHECK(token2.type == tokenizer::instr);
          CHECK(token2.value == "push");
          std::cout << token2.value << std::endl;
        }
        catch (exceptions::UnexpectedToken &err)
          {
            err.print();
          }

      };
  };

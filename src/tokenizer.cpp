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
  RegexPair FLOAT           (float_t, std::regex ("^float", icase));
  RegexPair DOUBLE          (double_t, std::regex ("^double", icase));
  /* SYNTAX  */
  RegexPair SPACE           (space, std::regex ("^\\s+"));
  RegexPair PARENTHESIS     (parenthesis, std::regex ("(^\\(|^\\))"));
  RegexPair COMMENT         (comment, std::regex ("^;[^;].*")); // matches until linebreak
  RegexPair END_OF_PROGRAM  (end_of_program, std::regex ("^;;"));
  /* NUMERIC */
  RegexPair INTEGERS        (integers, std::regex ("(?!.*\\.)^[-]?[0-9]+")); // will ignore if . is found in pattern
  RegexPair FLOATS          (floats, std::regex ("^[-]?[0-9]+\\.[0-9]+"));
  /* IMPLEMENTATION  */
  
  const std::array<RegexPair, TOKENIZER_GRAMMAR_LENGTH> REGEXES = 
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
    FLOAT,
    DOUBLE,
    SPACE,
   // SEP, -> handled in nextToken function
    COMMENT, 
    END_OF_PROGRAM,
    PARENTHESIS,
    INTEGERS,
    FLOATS,
  };

/* Token constructors implementation */

Token::Token(const token_type typ, const std::string &val) : type(typ), value(val) { }
//Token::Token(Token &&other) : type(other.type), value(other.value) { }

/* Tokenizer Private Implementation */

 struct Tokenizer::Private
   {
    public:
       static Token handleLineBreak(Tokenizer &self)
       {
          self.m_cursor++;
          return {tokenizer::sep, "\n"};
       };

       static bool isLineBreak(char c) { return c == '\n'; };

  };

/* Constructor */

  Tokenizer::Tokenizer (const std::string &text) : m_text (text), m_textlen (text.length ()), m_cursor (0)
  {}


/* Public */
  
   Token Tokenizer::nextToken ()
  {
   if(m_cursor == m_textlen)   
      return Token(end_of_line, "");

    const std::string substring = m_text.substr (m_cursor, m_textlen);

    if(Private::isLineBreak(substring[0]))
       return Private::handleLineBreak(*this);
  
    for (const auto &regex : REGEXES)
    {
      std::smatch matched;

      if (std::regex_search (substring, matched, regex.second))
      {
        m_cursor += matched[0].length ();
        Token token = Token(regex.first, matched[0]);
  
        if (token.type == space)
          return nextToken();
  
        return token;
      }
    }

   exceptions::UnexpectedToken::throwE(substring);
  }


  }

TEST_CASE("Tokenizer")
{

  using TestPair = std::pair<const tokenizer::token_type, const std::string> ;

  SUBCASE("Single Keywords")
  {
    TestPair push_test      (tokenizer::push, "push");
    TestPair pop_test       ( tokenizer::pop, "pop");
    TestPair dump_test      ( tokenizer::dump, "dump");
    TestPair assert_test    ( tokenizer::assert, "assert");
    TestPair add_test       ( tokenizer::add, "add");
    TestPair sub_test       ( tokenizer::sub, "sub");
    TestPair mul_test       ( tokenizer::mul, "mul");
    TestPair div_test       ( tokenizer::div, "div");
    TestPair mod_test       ( tokenizer::mod, "mod");
    TestPair print_test     ( tokenizer::print, "print");
    TestPair exit_test      ( tokenizer::exit, "exit");
    TestPair int8_test      ( tokenizer::int8, "int8");
    TestPair int16_test     ( tokenizer::int16, "int16");
    TestPair int32_test     ( tokenizer::int32, "int32");
    TestPair float_test     ( tokenizer::float_t, "float");
    TestPair double_test    ( tokenizer::double_t, "double");
    TestPair sep_test       ( tokenizer::sep, "\n");
    TestPair paren_open     ( tokenizer::parenthesis, "(");
    TestPair paren_close    ( tokenizer::parenthesis, ")");
    TestPair eop_test       ( tokenizer::end_of_program, ";;");
    TestPair integers1_test  ( tokenizer::integers, "-10");
    TestPair floats1_test    ( tokenizer::floats, "-20.10");
    TestPair integers2_test  ( tokenizer::integers, "1000");
    TestPair floats2_test    ( tokenizer::floats, "2034.109");
    TestPair eol_test        ( tokenizer::end_of_line, "");

     std::array< TestPair, 26> instrs
     {
     push_test,
     push_test, 
     pop_test,   
     dump_test,  
     assert_test,
     add_test,   
     sub_test,  
     mul_test,  
     div_test,   
     mod_test,  
     print_test, 
     exit_test, 
     int8_test,
     int16_test,
     int32_test,
     float_test,
     double_test,
     sep_test,
     paren_open,
     paren_close,
     eop_test,
     integers1_test,
     floats1_test,
     integers2_test,
     floats2_test,
     eol_test,
     };

     for(auto &intr : instrs)
      {
      tokenizer::Tokenizer tokenizer = tokenizer::Tokenizer (intr.second);
      tokenizer::Token token = tokenizer.nextToken ();

      CHECK(token.type == intr.first);
      CHECK(token.value == intr.second);

    };

  };

  SUBCASE("Comments & EOP")
  {
      const std::string comment_with_eop = "; this is a comment with eop ;;";
      const std::string comment_followed_by_eop = "; this is a comment with eop\n;;";

      tokenizer::Tokenizer tokenizer = tokenizer::Tokenizer(comment_followed_by_eop);
      tokenizer::Token token = tokenizer.nextToken();
      CHECK(token.type == tokenizer::comment);

      tokenizer::Token token2 = tokenizer.nextToken();
      CHECK(token2.type == tokenizer::sep);

      tokenizer::Token token4 = tokenizer.nextToken();
      CHECK(token4.type == tokenizer::end_of_program);

      tokenizer::Tokenizer tokenizer2 = tokenizer::Tokenizer(comment_with_eop);
      tokenizer::Token token3 = tokenizer2.nextToken();
      CHECK(token3.type == tokenizer::comment);
  };


  SUBCASE("single expression")
  {
    TestPair assert_test (tokenizer::assert, "assert");
    TestPair int8_test (tokenizer::int8, "int8");
    TestPair paren_open (tokenizer::parenthesis, "(");
    TestPair integers_test (tokenizer::integers, "10");
    TestPair paren_close (tokenizer::parenthesis, ")");

    std::array<TestPair, 5> tests { assert_test, int8_test, paren_open, integers_test, paren_close };

    std::string expression = "assert int8(10)";
    
    tokenizer::Tokenizer tokenizer = tokenizer::Tokenizer(expression);

    for(auto &test : tests)
    {
       auto token = tokenizer.nextToken();
       CHECK(token.type == test.first);
       CHECK(token.value == test.second);
    }
  };

SUBCASE("expression followed by comment")
  {
    TestPair push_test (tokenizer::push, "push");
    TestPair int8_test (tokenizer::int8, "int8");
    TestPair paren_open (tokenizer::parenthesis, "(");
    TestPair integers_test (tokenizer::integers, "10");
    TestPair paren_close (tokenizer::parenthesis, ")");
    TestPair comment_test (tokenizer::comment, "; a comment here");

    std::array<TestPair, 6> tests { push_test, int8_test, paren_open, integers_test, paren_close, comment_test };

    std::string expression = "push int8(10) ; a comment here";
    
    tokenizer::Tokenizer tokenizer = tokenizer::Tokenizer(expression);

    for(auto &test : tests)
    {
       auto token = tokenizer.nextToken();
       CHECK(token.type == test.first);
       CHECK(token.value == test.second);
    }
  };

SUBCASE("multiple expression")
  {
    TestPair push_test   (tokenizer::push, "push");
    TestPair int8_test   (tokenizer::double_t, "double");
    TestPair paren_open  (tokenizer::parenthesis, "(");
    TestPair floats_test (tokenizer::floats, "10.1023");
    TestPair paren_close (tokenizer::parenthesis, ")");
    TestPair sep1_test   (tokenizer::sep, "\n");
    TestPair div_test    (tokenizer::div, "div");
    TestPair sep2_test   (tokenizer::sep, "\n");
    TestPair exit_test   (tokenizer::exit, "exit");
    TestPair sep3_test   (tokenizer::sep, "\n");
    TestPair eop_test    (tokenizer::end_of_program, ";;");

    std::array<TestPair, 11> tests {
      push_test, int8_test, paren_open, floats_test, paren_close, sep1_test,   /* first expression */
      div_test, sep2_test,                                                     /* second expression */
      exit_test, sep3_test,                                                    /* third expression */
      eop_test};                                                               /* fourth expression */

    std::string expression = "push double(10.1023)\ndiv\nexit\n;;";
    
    tokenizer::Tokenizer tokenizer = tokenizer::Tokenizer(expression);

    for(auto &test : tests)
    {
       auto token = tokenizer.nextToken();
       CHECK(token.type == test.first);
       CHECK(token.value == test.second);
    }
  };
};

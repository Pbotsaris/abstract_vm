#include "../include/factory.h"
#include "../include/calculator.h"

/* Constructor & Destructor */

template<typename T>
Operands<T>::Operands (T value)
{
  m_type = Private::getType ();
  m_precision = Private::getPrecision(m_type);
  m_value = Private::toString(value, m_precision);
  Private::removeTrailingZeros(m_value);
}

template<typename T>
Operands<T>::~Operands () = default;

/* Public Implementation */

template<typename T>
eOperandType Operands<T>::getType () const
{
  return m_type;
}

template<typename T>
int Operands<T>::getPrecision () const
{
  return m_precision;
}

template<typename T>
const std::string &Operands<T>::toString () const
{
  return m_value;
}

template<typename T>
IOperand *Operands<T>::operator+ (const IOperand &rhs) const
{
  eOperandType return_type = std::max (m_type, rhs.getType ());
  T left_side = Private::convert (m_value);

  std::string result = Calculator::sum (left_side, getPrecision(), rhs);
  return factory.create (return_type, result);
}

template<typename T>
IOperand *Operands<T>::operator- (const IOperand &rhs) const
{
  eOperandType return_type = std::max (m_type, rhs.getType ());
  T left_side = Private::convert (m_value);

  std::string result = Calculator::subtract (left_side, getPrecision(), rhs);
  return factory.create (return_type, result);
}

template<typename T>
IOperand *Operands<T>::operator* (const IOperand &rhs) const
{
  eOperandType return_type = std::max (m_type, rhs.getType ());
  T left_side = Private::convert (m_value);

  std::string result = Calculator::multiply (left_side, getPrecision(), rhs);
  return factory.create (return_type, result);
}

template<typename T>
IOperand *Operands<T>::operator/ (const IOperand &rhs) const
{
  eOperandType return_type = std::max (m_type, rhs.getType ());
  T left_side = Private::convert (m_value);

  std::string result = Calculator::divide (left_side, getPrecision(), rhs);
  return factory.create (return_type, result);
}

template<typename T>
IOperand *Operands<T>::operator% (const IOperand &rhs) const
{
  eOperandType return_type = std::max (m_type, rhs.getType ());
  T left_side = Private::convert (m_value);

  std::string result = Calculator::mod (left_side, getPrecision(), rhs);
  return factory.create (return_type, result);
}

/* Private Implementation */

template<typename T>
struct Operands<T>::Private {
  static eOperandType getType ()
  {
    if (std::is_same<T, int8_t>::value)
      return Int8_t;

    if (std::is_same<T, int16_t>::value)
      return Int16_t;

    if (std::is_same<T, int32_t>::value)
      return Int32_t;

    if (std::is_same<T, float>::value)
      return Float_t;

    if (std::is_same<T, double>::value)
      return Double_t;
  }

  static int getPrecision (eOperandType type)
  {
    if(type == Float_t)
      return FLOAT_PRECISION;

    if(type == Double_t)
      return DOUBLE_PRECISION;

    return INT_PRECISION;
  }

  static std::string toString(T value, int precision)
  {
    if(precision == INT_PRECISION)
       return std::to_string (value);

    std::ostringstream out;
    out.precision(precision);
    out << std::fixed << value;

    return out.str();
  }

  static void removeTrailingZeros(std::string &str)
  {
    if(str.find('.') != std::string::npos)
      {
        str = str.substr(0, str.find_last_not_of('0') + 1);
        if(str.find('.') == str.size() - 1)
          str = str.substr(0, str.size() - 1);
      }
  };

  static T convert (const std::string &value)
  {
    if (std::is_same<T, float>::value)
      return std::stof (value);

    if (std::is_same<T, double>::value)
      return std::stod (value);

    else
      return std::stoi (value);
  }
};

/* TESTS */
TEST_CASE("IOperands: Public methods") // NOLINT(cert-err58-cpp)
{
  auto i8 = Operands<int8_t> (2);
  auto i16 = Operands<int16_t> (200);
  auto i32 = Operands<int32_t> (200);
  auto f = Operands<float> (10.20);
  auto d = Operands<double> (10.20);

  SUBCASE("toString()")
    {
      CHECK("2" == i8.toString ());
      CHECK("200" == i16.toString ());
      CHECK("200" == i32.toString ());
      CHECK("10.2" == f.toString ());
      CHECK("10.2" == d.toString ());
    }

  SUBCASE("getPrecision() & getType()")
    {
      CHECK(Int8_t == i8.getType ());
      CHECK(Int16_t == i16.getType ());
      CHECK(Int32_t == i32.getType ());
      CHECK(Float_t == f.getType ());
      CHECK(Double_t == d.getType ());
    }
}

TEST_CASE("IOperands: Precision") // NOLINT(cert-err58-cpp)
{
  SUBCASE("same precision: int8_t")
    {
      auto n1 = Operands<int8_t> (10);
      auto n2 = Operands<int8_t> (30);

      auto *result = n1 + n2;
      CHECK(result->toString () == "40");

      delete result;

    }

  SUBCASE("same precision: int16_t")
    {
      Operands<int16_t> n1 = Operands<int16_t> (10);
      Operands<int16_t> n2 = Operands<int16_t> (30);

      auto *result = n1 + n2;
      CHECK(result->toString () == "40");

      delete result;
    }

  SUBCASE("same precision: int32_t")
    {
      Operands<int32_t> n2 = Operands<int32_t> (30);
      Operands<int32_t> n1 = Operands<int32_t> (10);

      auto *result = n1 + n2;
      CHECK(result->toString () == "40");

      delete result;
    }

  SUBCASE("same precision: float")
    {
      Operands<float> n1 = Operands<float> (10.10);
      Operands<float> n2 = Operands<float> (30.10);

      auto *result = n1 + n2;
      CHECK(result->toString () == "40.2");

      delete result;
    }

  SUBCASE("same precision: double")
    {
      Operands<double> n1 = Operands<double> (10.222);
      Operands<double> n2 = Operands<double> (30.222);

      auto *result = n1 + n2;
      CHECK(result->toString () == "40.444");

      delete result;
    }

  SUBCASE("different precisions and size: ints")
    {
      Operands<int16_t> n1 = Operands<int16_t> (10);
      Operands<int32_t> n2 = Operands<int32_t> (30);

      auto *result = n1 + n2;
      CHECK(result->toString () == "40");

      auto *result_two = n2 + n1;
      CHECK(result_two->toString () == "40");

      delete result;
      delete result_two;
    }

  SUBCASE("different precisions and size: int vs floats")
    {

      Operands<int16_t> n1 = Operands<int16_t> (10);
      Operands<float> n2 = Operands<float> (30.10);

      auto *result = n1 + n2;
      CHECK(result->toString () == "40.1");

      auto *result_two = n2 + n1;
      CHECK(result_two->toString () == "40.1");

      delete result;
      delete result_two;
    }

  SUBCASE("different precisions and size: int vs doubles")
    {
      Operands<int32_t> n1 = Operands<int32_t> (10);
      Operands<double> n2 = Operands<double> (30.10);
      auto *result = n1 + n2;

      CHECK(result->toString () == "40.1");

      auto *result_two = n2 + n1;
      CHECK(result_two->toString () == "40.1");

      delete result;
      delete result_two;
    }
  SUBCASE("different precisions and same size: int vs float")
    {
      Operands<int32_t> n1 = Operands<int32_t> (10);
      Operands<float> n2 = Operands<float> (30.10);

      auto *result = n1 + n2;
      CHECK(result->toString () == "40.1");

      auto *result_two = n2 + n1;
      CHECK(result_two->toString () == "40.1");

      delete result;
      delete result_two;
    }
}

TEST_CASE("IOperands: Operations") // NOLINT(cert-err58-cpp)
{
  SUBCASE("float <> double")
    {
      Operands<double> n1 = Operands<double> (10.20);
      Operands<float> n2 = Operands<float> (4.0f);

      auto *sum = n1 + n2;
      auto *difference = n1 - n2;
      auto *product = n1 * n2;
      auto *division = n1 / n2;
      auto *modulo = n1 % n2;

      CHECK(sum->toString () == "14.2");
      CHECK(difference->toString () == "6.2");
      CHECK(division->toString () == "2.55");
      CHECK(product->toString () == "40.8");
      CHECK(modulo->toString () == "2.2");

      delete sum;
      delete difference;
      delete product;
      delete division;
      delete modulo;
    }

  SUBCASE("double <> int")
    {
      Operands<double> n1 = Operands<double> (10.20);
      Operands<int16_t> n2 = Operands<int16_t> (4);

      auto *sum = n1 + n2;
      auto *difference = n1 - n2;
      auto *product = n1 * n2;
      auto *division = n1 / n2;
      auto *modulo = n1 % n2;

      CHECK(sum->toString () == "14.2");
      CHECK(difference->toString () == "6.2");
      CHECK(product->toString () == "40.8");
      CHECK(division->toString () == "2.55");
      CHECK(modulo->toString () == "2.2");

      delete sum;
      delete difference;
      delete product;
      delete division;
      delete modulo;
    }
}
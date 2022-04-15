#include "../include/factory.h"

/* Constructor & Destructor */

static Factory& factory = Factory::getInstance();

template <typename T>
  Operands<T>::Operands(T value)
  {
    m_value = std::to_string(value);
    Private::setType(*this);
  };

template <typename T>
  Operands<T>::~Operands() = default;

/* Public Implementation */

template <typename T>
  eOperandType Operands<T>::getType() const 
{
  return m_type;
}

template <typename T>
  int Operands<T>::getPrecision() const 
{
     return m_type;
}

template <typename T>
  const std::string& Operands<T>::toString() const
  {
     return m_value;
  }

template<typename T>
  IOperand* Operands<T>::operator+(const IOperand &rhs) const
{
    eOperandType return_type = std::max(m_type, rhs.getType());
    T left_side              = Private::convert(*this);
    auto right_side  = rhs.getType() >= FLOAT_INDEX  ? std::stod(rhs.toString()) : std::stoi(rhs.toString());
    std::string result       = std::to_string(left_side + right_side);

    return factory.create(return_type, result);
}

template<typename T>
  IOperand* Operands<T>::operator-(const IOperand &rhs) const
{
    eOperandType return_type = std::max(m_type, rhs.getType());
    T left_side              = Private::convert(*this);
    auto right_side  = rhs.getType() >= FLOAT_INDEX  ? std::stod(rhs.toString()) : std::stoi(rhs.toString());
    std::string result       = std::to_string(left_side - right_side);

    return factory.create(return_type, result);
}

template<typename T>
  IOperand* Operands<T>::operator*(const IOperand &rhs) const
{
    eOperandType return_type = std::max(m_type, rhs.getType());
    T left_side              = Private::convert(*this);
    auto right_side  = rhs.getType() >= FLOAT_INDEX  ? std::stod(rhs.toString()) : std::stoi(rhs.toString());
    std::string result       = std::to_string(left_side * right_side);

    return factory.create(return_type, result);
}

template<typename T>
  IOperand* Operands<T>::operator/(const IOperand &rhs) const
{
    eOperandType return_type = std::max(m_type, rhs.getType());
    T left_side              = Private::convert(*this);
    auto right_side  = rhs.getType() >= FLOAT_INDEX  ? std::stod(rhs.toString()) : std::stoi(rhs.toString());
    std::string result       = std::to_string(left_side / right_side);

    return factory.create(return_type, result);
}


template<typename T>
  IOperand* Operands<T>::operator%(const IOperand &rhs) const
{
    eOperandType return_type = std::max(m_type, rhs.getType());
    T left_side              = Private::convert(*this);
    auto right_side  = rhs.getType() >= FLOAT_INDEX  ? std::stod(rhs.toString()) : std::stoi(rhs.toString());
    std::string result       = std::to_string(std::fmod(left_side, right_side));

    return factory.create(return_type, result);
}

/* Private Implementation */

template <typename T>
  struct Operands<T>::Private
  {
    static void setType(Operands& self)
    {
      if(std::is_same<T, int8_t>::value)
        self.m_type = Int8_t;

      if(std::is_same<T, int16_t>::value)
        self.m_type = Int16_t;

      if(std::is_same<T, int32_t>::value)
        self.m_type = Int32_t;

      if(std::is_same<T, float>::value)
        self.m_type = Float_t;

      if(std::is_same<T, double>::value)
        self.m_type = Double_t;
    }

    static T convert(const Operands &self)
    {
        if (std::is_same<T, float>::value)
            return std::stof(self.m_value);

        if (std::is_same<T, double>::value)
            return std::stod(self.m_value);

        else
            return std::stoi(self.m_value);
    }

  };

/* TESTS */

    TEST_CASE("IOperands: Public methods")
    {
        auto i8  = Operands<int8_t>(2);
        auto i16 = Operands<int16_t>(200);
        auto i32 = Operands<int32_t>(200);
        auto f   = Operands<float>(10.20);
        auto d   = Operands<double>(10.20);

        SUBCASE("toString()")
        {
            CHECK("2 Int8_t"            == i8.toString());
            CHECK("200 Int16_t"         == i16.toString());
            CHECK("200 Int32_t"         == i32.toString());
            CHECK("10.200000 Float_t"   == f.toString());
            CHECK("10.200000 Double_t"  == d.toString());
        }

        SUBCASE("getValue()")
        {
            CHECK("2"                    == i8.toString());
            CHECK("200"                  == i16.toString());
            CHECK("200"                  == i32.toString());
            CHECK("10.20f"               == f.toString());
            CHECK("10.20"                == d.toString());
        }

        SUBCASE("getPrecision() & getType()")
        {
            CHECK(Int8_t              == i8.getType());
            CHECK(Int16_t             == i16.getType());
            CHECK(Int32_t             == i32.getType());
            CHECK(Float_t             == f.getType());
            CHECK(Double_t            == d.getType());
        }
    }

    TEST_CASE("IOperands: Precision")
{
    SUBCASE("same precision: int8_t") {
        auto n1 = Operands<int8_t>(10);
        auto n2 = Operands<int8_t>(30);

        auto *result = n1 + n2;
        CHECK(result->toString() == "40");
        CHECK(result->getPrecision() == Int8_t);
        delete result;

    }

    SUBCASE("same precision: int16_t") {
        Operands<int16_t> n1 = Operands<int16_t>(10);
        Operands<int16_t> n2 = Operands<int16_t>(30);

        auto *result = n1 + n2;
        CHECK(result->toString() == "40");
        CHECK(result->getPrecision() == Int16_t);

        delete result;
    }

    SUBCASE("same precision: int32_t") {
        Operands<int32_t> n2 = Operands<int32_t>(30);
        Operands<int32_t> n1 = Operands<int32_t>(10);

        auto *result = n1 + n2;
        CHECK(result->toString() == "40");
        CHECK(result->getPrecision() == Int32_t);

        delete result;
    }
};

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

TEST_CASE("Operands")
{
    SUBCASE("create very type")
    {
        auto i8 = Operands<int8_t>(10);
        auto i16 = Operands<int16_t>(20);
        auto i32 = Operands<int32_t>(100);
        auto f = Operands<float>(30.20);
        auto d = Operands<double>(40.2020);

        CHECK(i8.toString() == "10");
        CHECK(i16.toString() == "20");
        CHECK(i1.toString() == "20");

    }

    SUBCASE("same type")
    {
        auto i8 = Operands<int8_t>(2);
        auto i8_two = Operands<int8_t>(3);

        auto res = i8 + i8_two;
        CHECK(res->toString() == "5");
        delete res;
    }

}


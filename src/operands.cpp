#include "../include/IOperand.h"

/* Constructor & Destructor */

template <typename T>
  IOperand<T>::IOperand(T value)
  {
    m_value = value;
    Private::setType(*this);
  };

template <typename T>
  IOperand<T>::~IOperand() {};

/* Public Implementation */

template <typename T>
  eOperandType IOperand<T>::getType() const 
  {
     return m_type;
  };

template <typename T>
  int IOperand<T>::getPrecision() const 
  {
     return m_type;
  };

template <typename T>
   T IOperand<T>::getValue() const
  {
     return m_value;
  };

/* Private Implementation */

template <typename T>
  struct IOperand<T>::Private
  {
    static void setType(IOperand& self)
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
  };


/* TESTS */



TEST_CASE("IOperands: Precision")
{
  SUBCASE("same precision: int8_t")
  {
    IOperand<int8_t> n1 = IOperand<int8_t>(10);
    IOperand<int8_t> n2 = IOperand<int8_t>(30);

    auto *result =  n1 + n2;

    CHECK(result->getValue() == 40);
    CHECK(result->getPrecision() == Int8_t);

    delete result;
  }

  SUBCASE("same precision: int16_t")
  {
    IOperand<int16_t> n1 = IOperand<int16_t>(10);
    IOperand<int16_t> n2 = IOperand<int16_t>(30);

    auto *result =  n1 + n2;
    CHECK(result->getValue() == 40);
    CHECK(result->getPrecision() == Int16_t);

    delete result;
  }

  SUBCASE("same precision: int32_t")
  {
    IOperand<int32_t> n1 = IOperand<int32_t>(10);
    IOperand<int32_t> n2 = IOperand<int32_t>(30);

    auto *result =  n1 + n2;
    CHECK(result->getValue() == 40);
    CHECK(result->getPrecision() == Int32_t);

    delete result;
  }

  SUBCASE("same precision: float")
  {
    IOperand<float> n1 = IOperand<float>(10.10);
    IOperand<float> n2 = IOperand<float>(30.10);

    auto *result =  n1 + n2;
    CHECK(result->getValue() == 40.2f);
    CHECK(result->getPrecision() == Float_t);

    delete result;
  }

  SUBCASE("same precision: double")
  {
    IOperand<double> n1 = IOperand<double>(10.222);
    IOperand<double> n2 = IOperand<double>(30.222);

    auto *result =  n1 + n2;
    CHECK(result->getValue() == 40.444);
    CHECK(result->getPrecision() == Double_t);

    delete result;
  }

  SUBCASE("different precisions and size: ints")
  {
    IOperand<int16_t> n1 = IOperand<int16_t>(10);
    IOperand<int32_t> n2 = IOperand<int32_t>(30);

    IOperand<int32_t> *result =  n1 + n2;
    CHECK(result->getValue() == 40);
    CHECK(result->getPrecision() == Int32_t);

    IOperand<int32_t> *result_two = n2 + n1;
    CHECK(result_two->getValue() == 40);
    CHECK(result->getPrecision() == Int32_t);
  
    delete result;
    delete result_two;
   }

  SUBCASE("different precisions and size: int vs floats")
  {
    IOperand<int8_t> n1 = IOperand<int8_t>(10);
    IOperand<float> n2 = IOperand<float>(30.10);

    IOperand<float> *result =  n1 + n2;
    CHECK(result->getValue() == 40.10f);
    CHECK(result->getPrecision() == Float_t);

    IOperand<float> *result_two = n2 + n1;
    CHECK(result_two->getValue() == 40.10f);
    CHECK(result->getPrecision() == Float_t);
  
    delete result;
    delete result_two;
   }

  SUBCASE("different precisions and size: int vs doubles")
  {
    IOperand<int32_t> n1 = IOperand<int32_t>(10);
    IOperand<double> n2 = IOperand<double>(30.10);
    IOperand<double> *result =  n1 + n2;

    CHECK(result->getValue() == 40.10);

    CHECK(result->getPrecision() == Double_t);

    IOperand<double> *result_two = n2 + n1;
    CHECK(result_two->getValue() == 40.10);
    CHECK(result->getPrecision() == Double_t);
  
    delete result;
    delete result_two;
   }
  SUBCASE("different precisions and same size: int vs float")

  {
    IOperand<int32_t> n1 = IOperand<int32_t>(10);
    IOperand<float> n2 = IOperand<float>(30.10);

    IOperand<float> *result =  n1 + n2;
    CHECK(result->getValue() == 40.10f);
    CHECK(result->getPrecision() == Float_t);

    IOperand<float> *result_two = n2 + n1;
    CHECK(result_two->getValue() == 40.10f);
    CHECK(result->getPrecision() == Float_t);
  
    delete result;
    delete result_two;
   }
}

TEST_CASE("IOperands: Operations")
{
  SUBCASE("float <> double")
  {
    IOperand<double> n1 = IOperand<double>(10.20);
    IOperand<float> n2 = IOperand<float>(4.0f);

    auto *sum =  n1 + n2;
    auto *difference =  n1 - n2;
    auto *product =  n1 * n2;
    auto *division =  n1 / n2;
    auto *modulo =  n1 % n2;

    CHECK(sum->getValue() == 14.20);
    CHECK(REQUIRE(doctest::Approx(difference->getValue()).epsilon(0.1) == 6.2));
    CHECK(product->getValue() == 40.80);
    CHECK(division->getValue() == 2.55);
    CHECK(REQUIRE(doctest::Approx(modulo->getValue()).epsilon(0.1) == 2.2));

    delete sum;
    delete difference;
    delete product;
    delete division;
    delete modulo;
  }

  SUBCASE("double <> int")
  {
    IOperand<double> n1 = IOperand<double>(10.20);
    IOperand<int16_t> n2 = IOperand<int16_t>(4);

    auto *sum =  n1 + n2;
    IOperand<double> *difference =  n1 - n2;
    auto *product =  n1 * n2;
    auto *division =  n1 / n2;
    auto *modulo =  n1 % n2;

    CHECK(sum->getValue() == 14.20);
    CHECK(REQUIRE(doctest::Approx(difference->getValue()).epsilon(0.1) == 6.2));
    CHECK(product->getValue() == 40.80);
    CHECK(division->getValue() == 2.55);
    CHECK(REQUIRE(doctest::Approx(modulo->getValue()).epsilon(0.1) == 2.2));

    delete sum;
    delete difference;
    delete product;
    delete division;
    delete modulo;
  }
}



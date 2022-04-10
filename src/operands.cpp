#include "../include/IOperand.h"

const std::array<std::string, 10> TYPES = {"Int8_t", "Int16_t", "Int32_t", "Float_t", "Double_t"};

/* Constructor & Destructor */

template <typename T>
  IOperand<T>::IOperand(T value)
  {
    m_value = value;
    Private::setType(*this);
    Private::setString(*this);
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

template <typename T>
  const std::string& IOperand<T>::toString() const
  {
     return m_string;
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

    static void setString(IOperand& self)
    {
      self.m_string = std::to_string(self.m_value) + " " + TYPES[self.m_type];
    }
  };


/* TESTS */

TEST_CASE("IOperands: Public methods")
{
 auto i8  = IOperand<int8_t>(2);
 auto i16 = IOperand<int16_t>(200);
 auto i32 = IOperand<int32_t>(200);
 auto f   = IOperand<float>(10.20);
 auto d   = IOperand<double>(10.20);

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
    CHECK(2                    == i8.getValue());
    CHECK(200                  == i16.getValue());
    CHECK(200                  == i32.getValue());
    CHECK(10.20f               == f.getValue());
    CHECK(10.20                == d.getValue());
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
  SUBCASE("same precision: int8_t")
  {
    auto n1 = IOperand<int8_t>(10);
    auto n2 = IOperand<int8_t>(30);

    auto *result =  n1 + n2;
    CHECK(result->getValue()     == 40);
    CHECK(result->getPrecision() == Int8_t);
    delete result;

  }

  SUBCASE("same precision: int16_t")
  {
    IOperand<int16_t> n1 = IOperand<int16_t>(10);
    IOperand<int16_t> n2 = IOperand<int16_t>(30);

    auto *result =  n1 + n2;
    CHECK(result->getValue()     == 40);
    CHECK(result->getPrecision() == Int16_t);

    delete result;
  }

  SUBCASE("same precision: int32_t")
  {
    IOperand<int32_t> n2 = IOperand<int32_t>(30);
    IOperand<int32_t> n1 = IOperand<int32_t>(10);

    auto *result =  n1 + n2;
    CHECK(result->getValue()     == 40);
    CHECK(result->getPrecision() == Int32_t);

    delete result;
  }

  SUBCASE("same precision: float")
  {
    IOperand<float> n1 = IOperand<float>(10.10);
    IOperand<float> n2 = IOperand<float>(30.10);

    auto *result =  n1 + n2;
    CHECK(result->getValue()     == 40.2f);
    CHECK(result->getPrecision() == Float_t);

    delete result;
  }

  SUBCASE("same precision: double")
  {
    IOperand<double> n1 = IOperand<double>(10.222);
    IOperand<double> n2 = IOperand<double>(30.222);

    auto *result =  n1 + n2;
    CHECK(result->getValue()     == 40.444);
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
    IOperand<double> n2  = IOperand<double>(30.10);
    IOperand<double> *result =  n1 + n2;

    CHECK(result->getValue()     == 40.10);

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
    CHECK(result->getValue()     == 40.10f);
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

    auto *sum         =  n1 + n2;
    auto *difference  =  n1 - n2;
    auto *product     =  n1 * n2;
    auto *division    =  n1 / n2;
    auto *modulo      =  n1 % n2;

    CHECK(sum->getValue() == 14.20);
    CHECK(REQUIRE(doctest::Approx(difference->getValue()).epsilon(0.1) == 6.2));
    CHECK(division->getValue() == 2.55);
    CHECK(product->getValue()  == 40.80);
    CHECK(REQUIRE(doctest::Approx(modulo->getValue()).epsilon(0.1) == 2.2));

    delete sum;
    delete difference;
    delete product;
    delete division;
    delete modulo;
  }

  SUBCASE("double <> int")
  {
    IOperand<double> n1  = IOperand<double>(10.20);
    IOperand<int16_t> n2 = IOperand<int16_t>(4);

    auto *sum         =  n1 + n2;
    auto *difference  =  n1 - n2;
    auto *product     =  n1 * n2;
    auto *division    =  n1 / n2;
    auto *modulo      =  n1 % n2;

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


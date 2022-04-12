#include "../include/other.h"

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




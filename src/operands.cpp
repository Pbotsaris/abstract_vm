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
  IOperand<T>* IOperand<T>::operator +(const IOperand& rhs) const
  {
    if(rhs.getType() <= m_type)
        return Private::sum(rhs, m_value);

    return Private::sum(*this, rhs.get_value());
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
        self.m_type = Int16_t;

      if(std::is_same<T, float>::value)
        self.m_type = Float_t;

      if(std::is_same<T, double>::value)
        self.m_type = Double_t;
    }

    static IOperand* sum(const IOperand& operand, int8_t value)
    {
       int8_t result = operand.getValue() + value;
       return new IOperand<int8_t>(result);
    }

    static IOperand* sum(const IOperand& operand, int16_t value)
    {
       int16_t result = operand.getValue() + value;
       return new IOperand<int16_t>(result);
    }

   static IOperand* sum(const IOperand& operand, int32_t value)
    {
       int32_t result = operand.getValue() + value;
       return new IOperand<int32_t>(result);
    }

   static IOperand* sum(const IOperand& operand, float value)
    {
       float result = operand.getValue() + value;
       return new IOperand<float>(result);
    }

   static IOperand* sum(const IOperand& operand, double value)
    {
       double result = operand.getValue() + value;
       return new IOperand<double>(result);
    }

  };

    
//template <typename T>
//  class IOperand: public IOperandBase
//  {
//    T m_value;
//    eOperandType m_type;
//
//    public:
//
//    IOperand(T value): m_value {value} { setType(); }
//
//    eOperandType getType() const
//    {
//     return m_type;
//    }
//
//    private:
//
//    void setType()
//    {
//      if(std::is_same<T, int8_t>::value)
//        m_type = Int8_t;
//
//      if(std::is_same<T, int16_t>::value)
//        m_type = Int16_t;
//
//      if(std::is_same<T, int32_t>::value)
//        m_type = Int16_t;
//
//      if(std::is_same<T, float>::value)
//        m_type = Float_t;
//
//      if(std::is_same<T, double>::value)
//        m_type = Double_t;
//
//    }
//
//    ~IOperand(){}
//    
//  };
//



//
//
//};


//class Int8: public IOperand {




#define IO_OPERAD_H
#ifndef IO_OPERAND_H
#include "../include/IOperandBase.h"
#include "doctest.h"

template <typename T>
  class IOperand
  {
     private:
       struct Private;
       T m_value;
       eOperandType m_type;

     public:
       IOperand(T value);
       ~IOperand();

       eOperandType              getType() const;
       T                         getValue() const;
       int                       getPrecision() const;

     
       template<typename U> auto operator+(const IOperand<U>& rhs) const
       {
          /* conditions also handles when comparing int32_t and floats which are the same size */
          using t = typename std::conditional<(
                              !(std::is_same<T, float>::value 
                              && std::is_same<U, int32_t>::value)
                              &&(sizeof(U) >= sizeof(T))),
                              U, T>::type;
 
          t sum = m_value + rhs.getValue();
          return new IOperand<t>(sum);
       }

       template<typename U> auto operator-(const IOperand<U>& rhs) const
       {
          using t = typename std::conditional<(
                              !(std::is_same<T, float>::value 
                              && std::is_same<U, int32_t>::value)
                              &&(sizeof(U) >= sizeof(T))),
                              U, T>::type;
 
          t difference = m_value - rhs.getValue();
          return new IOperand<t>(difference);
       }

        template<typename U> auto operator*(const IOperand<U>& rhs) const
       {
          using t = typename std::conditional<(
                              !(std::is_same<T, float>::value 
                              && std::is_same<U, int32_t>::value)
                              &&(sizeof(U) >= sizeof(T))),
                              U, T>::type;
 
          t product = m_value * rhs.getValue();
          return new IOperand<t>(product);
       }

        template<typename U> auto operator/(const IOperand<U>& rhs) const
       {
          using t = typename std::conditional<(
                              !(std::is_same<T, float>::value 
                              && std::is_same<U, int32_t>::value)
                              &&(sizeof(U) >= sizeof(T))),
                              U, T>::type;
 
          t division = m_value / rhs.getValue();
          return new IOperand<t>(division);
       }


       template<typename U> auto operator%(const IOperand<U>& rhs) const
       {
          using t = typename std::conditional<(
                              !(std::is_same<T, float>::value 
                              && std::is_same<U, int32_t>::value)
                              &&(sizeof(U) >= sizeof(T))),
                              U, T>::type;
 
          t modulo = fmod(m_value, rhs.getValue());
          return new IOperand<t>(modulo);
       }
      
  };
      
#endif


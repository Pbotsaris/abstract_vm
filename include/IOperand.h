#define IO_OPERAD_H
#ifndef IO_OPERAND_H
#include "../include/IOperandBase.h"
#include "doctest.h"

template<typename T, typename U>
  struct return_type
  {
   /* conditions also handles when comparing int32_t and floats which are the same size */
    using type = 
       typename std::conditional
         <
           (
            !( std::is_same<T, float>::value 
               && std::is_same<U, int32_t>::value
             )
            && (sizeof(U) >= sizeof(T))
           ), U, T
         >::type;
  };

template <typename T>
  class IOperand: public IOperandBase
  {
     private:
       struct       Private;
       T            m_value;
       std::string  m_string;
       eOperandType m_type;

     public:
       IOperand(T value);
       ~IOperand();

       eOperandType              getType() const;
       T                         getValue() const;
       int                       getPrecision() const;
       const std::string&        toString() const;

       template<typename U> auto operator+(const IOperand<U>& rhs) const
       {
          using return_t     = typename return_type<T, U>::type;  
          return_t sum       = m_value + rhs.getValue();

          return new IOperand<return_t>(sum);
       }

       template<typename U> auto operator-(const IOperand<U>& rhs) const
       {
          using return_t      = typename return_type<T, U>::type;  
          return_t difference = m_value - rhs.getValue();

          return new IOperand<return_t>(difference);
       }

        template<typename U> auto operator*(const IOperand<U>& rhs) const
       {
          using return_t      = typename return_type<T, U>::type;  
          return_t product    = m_value * rhs.getValue();

          return new IOperand<return_t>(product);
       }

        template<typename U> auto operator/(const IOperand<U>& rhs) const
       {
          using return_t      = typename return_type<T, U>::type;  
          return_t division   = m_value / rhs.getValue();
      
          return new IOperand<return_t>(division);
       }

       template<typename U> auto operator%(const IOperand<U>& rhs) const
       {
          using return_t      = typename return_type<T, U>::type;  
          return_t modulo     = fmod(m_value, rhs.getValue());

          return new IOperand<return_t>(modulo);
       }
  };

#endif


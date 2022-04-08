#define IO_OPERAD_H
#ifndef IO_OPERAND_H
#include "../include/IOperandBase.h"

template <typename T>
  class IOperand
  {
      struct Private;
      eOperandType m_type;
      T m_value;
      public:

      IOperand(T value);
      ~IOperand();

      eOperandType getType() const;
      IOperand*    operator+(const IOperand& rhs) const;
      int          getPrecision() const;
      T            getValue() const;

    };
      


#endif


#define IO_OPERAD_H
#ifndef IO_OPERAND_H
#include "../include/IOperandBase.h"
#include "doctest.h"

typedef IOperand* (*FactoryFunction)(const std::string& value);

template <typename T>

  class Operands: public IOperand
  {
     private:
       struct         Private;
       std::string    m_value;
       T              m_numval;
       eOperandType   m_type;

     public:
       Operands(T value);
       ~Operands();

       eOperandType          getType() const override;
       int                   getPrecision() const override;
       const std::string&    toString() const override;

       IOperand*             operator +(const IOperand &rhs) const override;
       IOperand*             operator -(const IOperand &rhs) const override;
       IOperand*             operator *(const IOperand &rhs) const override;
       IOperand*             operator /(const IOperand &rhs) const override;
       IOperand*             operator %(const IOperand &rhs) const override;
  };


struct Convert;
#endif


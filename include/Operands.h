#define IO_OPERAD_H
#ifndef IO_OPERAND_H
#include "../include/IOperandBase.h"
#include "doctest.h"

template<typename T>
class Operands : public IOperand {
 private:
  struct Private;
  std::string      m_value;
  int              m_precision;
  eOperandType     m_type;

 public:
  explicit Operands (T value);
  ~Operands () override;

  [[nodiscard]]  eOperandType       getType () const override;
  [[nodiscard]]  int                getPrecision () const override;
  [[nodiscard]]  const std::string &toString () const override;

  IOperand *operator+ (const IOperand &rhs) const override;
  IOperand *operator- (const IOperand &rhs) const override;
  IOperand *operator* (const IOperand &rhs) const override;
  IOperand *operator/ (const IOperand &rhs) const override;
  IOperand *operator% (const IOperand &rhs) const override;
};

#endif


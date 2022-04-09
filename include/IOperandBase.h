#define IO_OPERAND_BASE_H
#ifndef IO_OPERAND_BASE
#include <iostream>
#include <type_traits>
#include <typeinfo>
#include <cstdint>
#include <string>
#include <algorithm>
#include <cmath>
enum eOperandType {Int8_t, Int16_t, Int32_t, Float_t, Double_t};


class IOperandBase 
{
  public:
  virtual const std::string& toString() const = 0;

  virtual int           getPrecision() const = 0;
  virtual eOperandType  getType() const = 0;

  virtual IOperandBase* operator +(const IOperandBase &right_hand_side) const = 0;
  virtual IOperandBase* operator -(const IOperandBase &right_hand_side) const = 0;
  virtual IOperandBase* operator *(const IOperandBase &right_hand_side) const = 0;
  virtual IOperandBase* operator /(const IOperandBase &right_hand_side) const = 0;
  virtual IOperandBase* operator %(const IOperandBase &right_hand_side) const = 0;
  virtual ~IOperandBase() {}
};


#endif

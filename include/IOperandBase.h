#ifndef IO_OPERAND_BASE_H
#define IO_OPERAND_BASE_H
#include <iostream>
#include <type_traits>
#include <typeinfo>
#include <cstdint>
#include <algorithm>
#include <string>
#include <cmath>
#include <map>
#include <array>
#include <sstream>
#include <iomanip>

#define INT_PRECISION 0
#define FLOAT_PRECISION 5
#define DOUBLE_PRECISION 14

enum eOperandType {Int8_t, Int16_t, Int32_t, Float_t, Double_t};

class IOperand 
{
  public:
  virtual const std::string& toString() const = 0;

  virtual int           getPrecision() const = 0;
  virtual eOperandType  getType() const = 0;
  
  virtual IOperand* operator +(const IOperand &rhs) const = 0;
  virtual IOperand* operator -(const IOperand &rhs) const = 0;
  virtual IOperand* operator *(const IOperand &rhs) const = 0;
  virtual IOperand* operator /(const IOperand &rhs) const = 0;
  virtual IOperand* operator %(const IOperand &rhs) const = 0;

  virtual ~IOperand() {}

};
#endif

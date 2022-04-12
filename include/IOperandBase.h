#define IO_OPERAND_BASE_H
#ifndef IO_OPERAND_BASE

#include <iostream>
#include <type_traits>
#include <cstdint>
#include <algorithm>
#include <memory>
#include <string>
#include <cmath>
#include <array>

enum eOperandType {Int8_t, Int16_t, Int32_t, Float_t, Double_t};

template<eOperandType> struct Map;

template<> struct Map<Int8_t> {
  using type = int8_t;
};

template<> struct Map<Int16_t> {
  using type = int16_t;
};

template<> struct Map<Int32_t> {
  using type = int32_t;
};

template<> struct Map<Float_t> {
  using type = float;
};

template<> struct Map<Double_t> {
  using type = double;
};

class IOperandBase 
{
  public:

  virtual const std::string& toString() const = 0;
  virtual int                getPrecision() const = 0;
  virtual eOperandType       getType() const = 0;
  
  /* cannot inherit templated methods */
 // virtual IOperandBase* operator +(const IOperandBase &rhs) const = 0;
 // virtual IOperandBase* operator -(const IOperandBase &rhs) const = 0;
 // virtual IOperandBase* operator *(const IOperandBase &rhs) const = 0;
 // virtual IOperandBase* operator /(const IOperandBase &rhs) const = 0;
 // virtual IOperandBase* operator %(const IOperandBase &rhs) const = 0;

  virtual ~IOperandBase() {}
};


#endif

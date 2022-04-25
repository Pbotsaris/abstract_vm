#ifndef CALCULATE_H
#define CALCULATE_H
#include <string>
#include <sstream>
#include "../include/IOperandBase.h"

struct Calculator {
 public:
  template<typename T>
  static std::string sum (const T left, const int left_precision, const IOperand& rhs)
  {
    int precision = std::max(rhs.getPrecision(), left_precision);

    if(rhs.getType() == Double_t)
       return Calculator::toString (left + std::stod(rhs.toString()), precision);

    if(rhs.getType() == Float_t)
      return Calculator::toString (left + std::stof(rhs.toString()), precision);

    else
      return Calculator::toString (left + std::stoi(rhs.toString()), precision);
  }

  template<typename T>
  static std::string subtract (const T left, const int left_precision, const IOperand& rhs)
  {

    int precision = std::max(rhs.getPrecision(), left_precision);

    if(rhs.getType() == Double_t)
      return Calculator::toString(left - std::stod(rhs.toString()), precision);

    if(rhs.getType() == Float_t)
      return Calculator::toString(left - std::stof(rhs.toString()), precision);

    else
      return Calculator::toString(left - std::stoi(rhs.toString()), precision);
  };

  template<typename T>
  static std::string multiply (const T left, const int left_precision, const IOperand& rhs)
  {

    int precision = std::max(rhs.getPrecision(), left_precision);

    if(rhs.getType() == Double_t)
      return Calculator::toString(left * std::stod(rhs.toString()), precision);

    if(rhs.getType() == Float_t)
      return Calculator::toString(left * std::stof(rhs.toString()), precision);

    else
      return Calculator::toString(left * std::stoi(rhs.toString()), precision);
  };

  template<typename T>
  static std::string divide (const T left, const int left_precision, const IOperand& rhs)
  {
    int precision = std::max(rhs.getPrecision(), left_precision);

    if(rhs.getType() == Double_t)
      return Calculator::toString(left / std::stod(rhs.toString()), precision);

    if(rhs.getType() == Float_t)
      return Calculator::toString(left / std::stof(rhs.toString()), precision);

    else
      return Calculator::toString(left / std::stoi(rhs.toString()), precision);
  };

  template<typename T>
  static std::string mod (T left, const int left_precision, const IOperand& rhs)
  {

    int precision = std::max(rhs.getPrecision(), left_precision);

    if(rhs.getType() == Double_t)
      return Calculator::toString(std::fmod(left, std::stod(rhs.toString())), precision);

    if(rhs.getType() == Float_t)
      return Calculator::toString(std::fmod(left, std::stof(rhs.toString())), precision);

    else
      return Calculator::toString(std::fmod(left, std::stoi(rhs.toString())), precision);
  };

  template <typename T>
 static std::string toString(const T value, const int n)
  {
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << value;
    return out.str();
  }

  template <typename T>
  static int getPrecision (T value)
  {
    std::ostringstream ss;
    ss << std::fixed << value;
    std::string s = ss.str ();

    size_t precision = 0;
    bool last        = true;
    bool dot         = false;
    int digits       = 0;

    for (size_t i = s.length () - 1; i >= 0; i--)
      {
        if (last)
          precision = i;

        if (s[i] != '0')
          last = false;

        if (s[i] == '.')
          {
            dot = true;
            continue;
          }

        if (dot)
          digits++;
      }

    return static_cast<int>(precision - digits);
  }

};

#endif

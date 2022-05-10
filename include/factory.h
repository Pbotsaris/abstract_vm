#ifndef FACTORY_H
#define FACTORY_H

#include "Operands.h"
#include "exceptions.h"

#define MAX_INT8 127
#define MAX_INT16 32767


namespace factory
{

typedef IOperand *(*FactoryFunction) (const std::string &value);

struct FactoryFunctions {

public:

  static IOperand *createInt8 (const std::string &value)
  {
    auto val = std::stoi (value);

    if(val > MAX_INT8 || val < (MAX_INT8 * -1)) 
       exceptions::Overflow::throwE<int8_t>(value);

    return new Operands<int8_t> (static_cast<int8_t>(val));
  }

  static IOperand *createInt16 (const std::string &value)
  {
     auto val = std::stoi (value);

     if(val > MAX_INT16 || val < (MAX_INT16 * -1)) 
          exceptions::Overflow::throwE<int16_t>(value);

    return new Operands<int16_t> (static_cast<int16_t>(val));
  }

  static IOperand *createInt32 (const std::string &value)
  {
    try
    {
       auto val = std::stoi(value);
       return new Operands<int32_t> (static_cast<int32_t>(val));
    } 
    catch(std::exception &err)
    {
        exceptions::Overflow::throwE<int32_t>(value);
    }
  }

  static IOperand *createFloat (const std::string &value)
  {

        if(countDigits(value)  > FLOAT_PRECISION)
            std::cout << "WARNING: converting value" << value << " to float produced a loss in precision.\n";

        float val = std::stof(value);
        return new Operands<float> (val);
  }

  static IOperand *createDouble (const std::string &value)
  {
        if(countDigits(value)  > DOUBLE_PRECISION)
            std::cout << "WARNING: converting value" << value << " to double produced a loss in precision.\n";

        double val = std::stod (value);
        return new Operands<double> (val);
  }

private:

  static int countDigits(const std::string &value)
  {
    int count = 0;
    bool was_dot = false;

    for(const char &c : value)
    {
       if(was_dot)
           count++;

        if(c == '.')
           was_dot = true;
    }

    return count;
  }
    
};

    struct Factory {
    
     private:
      std::map<eOperandType, FactoryFunction> factory;
    
      Factory ()
      {
        factory.insert (std::pair<eOperandType, FactoryFunction> (Int8_t, &FactoryFunctions::createInt8));
        factory.insert (std::pair<eOperandType, FactoryFunction> (Int16_t, &FactoryFunctions::createInt16));
        factory.insert (std::pair<eOperandType, FactoryFunction> (Int32_t, &FactoryFunctions::createInt32));
        factory.insert (std::pair<eOperandType, FactoryFunction> (Float_t, &FactoryFunctions::createFloat));
        factory.insert (std::pair<eOperandType, FactoryFunction> (Double_t, &FactoryFunctions::createDouble));
      };
    
        Factory(Factory const&);              //  copy constructor private
    
    public:
        static Factory& getInstance() noexcept
        {
            static Factory instance = Factory();
            return instance;
        };
    
        void operator=(Factory const&) = delete; // don't implement
    
    
      IOperand *create (eOperandType type, const std::string &value) 
      {
        return factory.at (type) (value);
      };
    };
    
    static Factory &factory = Factory::getInstance ();
}

#endif

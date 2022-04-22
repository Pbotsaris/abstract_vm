#ifndef FACTORY_H
#define FACTORY_H
#include "Operands.h"

typedef IOperand* (*FactoryFunction)(const std::string& value);

struct FactoryFunctions
{
    static IOperand* createInt8(const std::string& value)
    {
        auto val = static_cast<int8_t>(std::stoi(value));
        return new Operands<int8_t>(val);
    }

    static IOperand* createInt16(const std::string& value)
    {
        auto val = static_cast<int16_t>(std::stoi(value));
        return new Operands<int16_t>(val);
    }

    static IOperand* createInt32(const std::string& value)
    {
        auto val = static_cast<int32_t>(std::stoi(value));
        return new Operands<int32_t>(val);
    }

    static IOperand* createFloat(const std::string& value)
    {
        float val = std::stof(value);
        return new Operands<float>(val);
    }

    static IOperand* createDouble(const std::string& value)
    {
        double val = std::stod(value);
        return new Operands<double>(val);
    }
};

struct Factory
{
private:
    std::map<eOperandType, FactoryFunction> factory;

    Factory()
    {
        factory.insert(std::pair<eOperandType, FactoryFunction>(Int8_t, &FactoryFunctions::createInt8));
        factory.insert(std::pair<eOperandType, FactoryFunction>(Int16_t, &FactoryFunctions::createInt16));
        factory.insert(std::pair<eOperandType, FactoryFunction>(Int32_t, &FactoryFunctions::createInt32));
        factory.insert(std::pair<eOperandType, FactoryFunction>(Float_t, &FactoryFunctions::createFloat));
        factory.insert(std::pair<eOperandType, FactoryFunction>(Double_t, &FactoryFunctions::createDouble));
    };

    Factory(Factory const&);              //  copy constructor private

public:
    static Factory& getInstance() noexcept
    {
        static Factory instance = Factory();
        return instance;
    };

    void operator=(Factory const&) = delete; // don't implement

    IOperand* create(eOperandType type, const std::string& value)
    {
        return factory.at(type)(value);
    };
};

static Factory &factory = Factory::getInstance ();

#endif

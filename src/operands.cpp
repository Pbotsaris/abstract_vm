#include "../include/Operands.h"

/* Constructor & Destructor */

struct FactoryFunctions 
{

    static IOperand* createInt8(const std::string& value)
     {
         int8_t val = std::stoi(value);
         return new Operands<int8_t>(val);
     }

     static IOperand* createInt16(const std::string& value)
     {
         int16_t val = std::stoi(value);
         return new Operands<int16_t>(val);
     }

     static IOperand* createInt32(const std::string& value)
     {
         int32_t val = std::stoi(value);
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
        factory.insert(std::pair<eOperandType, FactoryFunction>(Float_t, &FactoryFunctions::createDouble));
       };

        Factory(Factory const&);              // Don't Implement
        void operator=(Factory const&);

  public:
       static Factory& getInstance() 
       { 
         static Factory instance = Factory(); 
         return instance;
       };

       IOperand* create(eOperandType type, const std::string& value)
       {
         return factory.at(type)(value);
       };
};


Factory& factory = Factory::getInstance();



template <typename T>
  Operands<T>::Operands(T value)
  {
    m_value = std::to_string(value);
    Private::setType(*this);
  };

template <typename T>
  Operands<T>::~Operands() {};

/* Public Implementation */

template <typename T>
  eOperandType Operands<T>::getType() const 
{
  return m_type;
};

template <typename T>
  int Operands<T>::getPrecision() const 
{
     return m_type;
};

template <typename T>
  const std::string& Operands<T>::toString() const
  {
     return m_value;
  };

template<typename T>
  IOperand* Operands<T>::operator+(const IOperand &rhs) const
{
    eOperandType return_type = std::max(m_type, rhs.getType());
    T left_side              = Private::convert(*this);
    auto right_side          = rhs.getType() >= FLOAT_INDEX  ? std::stod(rhs.toString()) : std::stoi(rhs.toString());
    std::string result       = std::to_string(left_side + right_side);

    return factory.create(return_type, result);
};

template<typename T>
  IOperand* Operands<T>::operator-(const IOperand &rhs) const
{
    eOperandType return_type = std::max(m_type, rhs.getType());
    T left_side              = Private::convert(*this);
    auto right_side          = rhs.getType() >= FLOAT_INDEX  ? std::stod(rhs.toString()) : std::stoi(rhs.toString());
    std::string result       = std::to_string(left_side - right_side);

    return factory.create(return_type, result);
};

template<typename T>
  IOperand* Operands<T>::operator*(const IOperand &rhs) const
{
    eOperandType return_type = std::max(m_type, rhs.getType());
    T left_side              = Private::convert(*this);
    auto right_side          = rhs.getType() >= FLOAT_INDEX  ? std::stod(rhs.toString()) : std::stoi(rhs.toString());
    std::string result       = std::to_string(left_side * right_side);

    return factory.create(return_type, result);
};


template<typename T>
  IOperand* Operands<T>::operator/(const IOperand &rhs) const
{
    eOperandType return_type = std::max(m_type, rhs.getType());
    T left_side              = Private::convert(*this);
    auto right_side          = rhs.getType() >= FLOAT_INDEX  ? std::stod(rhs.toString()) : std::stoi(rhs.toString());
    std::string result       = std::to_string(left_side / right_side);

    return factory.create(return_type, result);
};


template<typename T>
  IOperand* Operands<T>::operator%(const IOperand &rhs) const
{
    eOperandType return_type = std::max(m_type, rhs.getType());
    T left_side              = Private::convert(*this);
    auto right_side          = rhs.getType() >= FLOAT_INDEX  ? std::stod(rhs.toString()) : std::stoi(rhs.toString());
    std::string result       = std::to_string(std::fmod(left_side, right_side));

    return factory.create(return_type, result);
};


/* Private Implementation */

template <typename T>
  struct Operands<T>::Private
  {
    static void setType(Operands& self)
    {
      if(std::is_same<T, int8_t>::value)
        self.m_type = Int8_t;

      if(std::is_same<T, int16_t>::value)
        self.m_type = Int16_t;

      if(std::is_same<T, int32_t>::value)
        self.m_type = Int32_t;

      if(std::is_same<T, float>::value)
        self.m_type = Float_t;

      if(std::is_same<T, double>::value)
        self.m_type = Double_t;
    }

    static const T convert(const Operands& self) 
{
      if(std::is_same<T, float>::value)
          return std::stof(self.m_value);

      if(std::is_same<T, double>::value)
        return std::stod(self.m_value);

      else
       return std::stoi(self.m_value);
 };

  };




/* TESTS */

TEST_CASE("Operands: Public methods")
{
 auto i8  = Operands<int8_t>(2);
 auto i8_two = Operands<int8_t>(3);

 auto res = i8 + i8_two;

 CHECK(res->toString() == "5");

 delete res;

 //auto i16 = Operands<int16_t>(200);
 //auto i32 = Operands<int32_t>(200);
 //auto f   = Operands<float>(10.20);
 //auto d   = Operands<double>(10.20);

}


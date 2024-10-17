#pragma once
#include "34.13.hpp"

class Test : public GOST_34_13::Kuzn {
public:
  using GOST_34_13::Kuzn::Kuzn;
  void setTestData(const std::string& data);
  
  // Crypto algorithms tests
  void checkSimpleEncode(); // 34.12
  void checkGamma();
  void checkGammaRecursive();
  void checkGammaGammaRecursiveCypher();
  void checkRecursiveHook();
  
  void runAllTests();
  
protected:
  bool read(std::ifstream&, Block128& block) const override; //virtual
  void write(std::ofstream&, const Block128& block) const override;
  
  void setIn(const std::string& in);
  std::string getOut() const;
  void clearOut();
  void running(const std::string& name) const;
  void compareData(const std::string& data1, const std::string& data2) const;
  
private:
  std::string m_testData;
  mutable std::string m_in; // instead of ifstream
  mutable std::string m_out; // mutable can be changed by constant methods
};


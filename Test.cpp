#include <iostream>
#include "Test.h"

bool Test::read(std::ifstream&, Block128& block) const {
  std::string data = m_in.substr(0, 16);
  
  if (data.empty()) {
    return false;
  }
  
  m_in = m_in.substr(data.size());
  
  for (int i = 0; i < data.size(); ++i) {
    block(i) = data[i];
  }
  
  for (int i = static_cast<int>(data.size()); i < 16; ++i) {
    block(i) = 0;
  }
  
  return true;
}

void Test::write(std::ofstream&, const Block128& block) const {
  std::string data;
  
  data.resize(16);
  
  for (int i = 15; i >= 0; --i) { //Почему с конца?
    data[i] = block(i);
  }
  
  m_out += data;
}

void Test::setIn(const std::string& in) {
  m_in = in;
}

void Test::setTestData(const std::string& data) {
  m_testData = data;
}

std::string Test::getOut() const {
  return m_out;
}

void Test::clearOut() {
  m_out.clear();
}

void Test::running(const std::string& name) const {
  std::cout << "Running test '" << name << "':" << std::endl;
}
//data2 - выход программы data1 - оригинальные данные
void Test::compareData(const std::string& data1, const std::string& data2) const {
  std::cout << "  Result: ";
  
  if (data2.substr(0, data1.size()) == data1) { // по длинне откр текста из-за мусора в конце
    std::cout << "OK" << std::endl;
  } else {
    std::cout << "FAILED !!!" << std::endl;
    std::cout << "  Input was:" << "'" << data1 << "'" << std::endl;
    std::cout << "  Output is:" << "'" << data2 << "'" << std::endl;
  }
}

void Test::checkSimpleEncode() {
  running("SimpleEncode (34.12)");
  
  setIn(m_testData);
  clearOut();
  
  encode("_void filename_");
  setIn(getOut());
  clearOut();
  decode("_void filename_");
  
  compareData(m_testData, getOut());
}

void Test::checkGamma() {
  running("Gamma");
  
  setIn(m_testData);
  clearOut();
  
  const auto syncro = randomSynchroReg(1)[0][0];
  
  codeGamma("_void filename_", syncro);
  setIn(getOut());
  clearOut();
  codeGamma("_void filename_", syncro);
  
  compareData(m_testData, getOut());
}

void Test::checkGammaRecursive() {
  running("GammaRecursive");
  
  setIn(m_testData);
  clearOut();
  
  const auto reg = randomSynchroReg(3);
  
  codeGammaRecursive("_void filename_", reg);
  setIn(getOut());
  clearOut();
  codeGammaRecursive("_void filename_", reg);
  
  compareData(m_testData, getOut());
}

void Test::checkGammaGammaRecursiveCypher() {
  running("GammaRecursiveCypher");
  
  setIn(m_testData);
  clearOut();
  
  const auto reg = randomSynchroReg(3);
  
  codeGammaRecursiveCypher("_void filename_", reg, true);
  setIn(getOut());
  clearOut();
  codeGammaRecursiveCypher("_void filename_", reg, false);
  
  compareData(m_testData, getOut());
}

void Test::checkRecursiveHook() {
  running("GammaRecursiveHook");
  
  setIn(m_testData);
  clearOut();
  
  const auto reg = randomSynchroReg(3);
  
  encodeRecursiveHook("_void filename_", reg);
  setIn(getOut());
  clearOut();
  decodeRecursiveHook("_void filename_", reg);
  
  compareData(m_testData, getOut());
}

void Test::runAllTests() {
  checkSimpleEncode();
  checkGamma();
  checkGammaRecursive();
  checkGammaGammaRecursiveCypher();
  checkRecursiveHook();
}

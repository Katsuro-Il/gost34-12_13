#pragma once
#include <array>
#include <fstream>
#include <stdio.h>
#include <string>
#include "Block128.hpp"

namespace GOST_34_12
{
class Kuzn
{
public:
  Kuzn(const Block128 &key1, const Block128 &key2);
  void encode(const std::string &path) const;
  void decode(const std::string &path) const;
  
protected:
  void constGen();
  void keyGen();
  
  Block128 Xor(const Block128 &a, const Block128 &b) const;
  Block128 R(const Block128 &state) const;
  Block128 L(const uint8_t &iter) const;
  Block128 L(const Block128 &block) const;
  Block128 S(const Block128 &block) const;
  
  Block128 reverseS(const Block128 &block) const;
  Block128 reverseR(const Block128 &state) const;
  Block128 reverseL(const Block128 &in_data) const;
  
  uint8_t multGalois(uint8_t a, uint8_t b) const;
  std::pair < Block128, Block128 > F(const Block128 &key1, const Block128 &key2, const Block128 &iterConst);
  
  virtual bool read(std::ifstream &f, Block128 &block) const; //могут быть переопределены при наследовании
  virtual void write(std::ofstream &f, const Block128 &block) const;
  
  Block128 encodeBlock(Block128 block) const;
  Block128 decodeBlock(Block128 block) const;
  
private:
  static const Block128 s_lVec;
  static std::array < Block128, 32 > s_constVec;
  static bool s_constGenerated;
  std::array < Block128, 10 > m_keyVec;
  
  static const uint8_t s_Pi[256];
  static const uint8_t s_reverse_Pi[256];
};
}

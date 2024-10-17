#pragma once
#include "34.12.hpp"

namespace GOST_34_13
{
class Kuzn: public GOST_34_12::Kuzn
{
public:
  using GOST_34_12::Kuzn::Kuzn;
  void codeGamma(const std::string &path, const Chunk &synchro) const;
  void codeGammaRecursive(const std::string &path, Register reg) const;
  void codeGammaRecursiveCypher(const std::string &path, Register reg, bool isEncode) const;
  void encodeRecursiveHook(const std::string &path, Register reg) const;
  void decodeRecursiveHook(const std::string &path, Register reg) const;
  
  Register randomSynchroReg(uint8_t lenOfReg) const;
  
  void execute();
};
}

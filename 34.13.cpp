#include <ctime>
#include <iostream>
#include "34.13.hpp"

using namespace GOST_34_13;

Register Kuzn::randomSynchroReg(uint8_t lenOfReg) const {
  Register reg;
  
  std::srand((unsigned)std::time(NULL));
  
  for (uint8_t i{ 0 }; i < lenOfReg; ++i) {
    Block128 block{ (Chunk)rand() * (Chunk)rand(), (Chunk)rand() * (Chunk)rand() };
    
    reg.push_back(block);
  }
  
  return reg;
}

void Kuzn::codeGamma(const std::string &path, const Chunk &synchro) const {
  std::ifstream plainFile(path, std::ios::binary);
  std::ofstream cryptedFile(path + ".txt", std::ios::binary);
  
  Block128 block;
  Chunk index{ 0 };
  
  while (read(plainFile, block)) {
    auto gamma = encodeBlock({ index++, synchro });
    write(cryptedFile, Xor(block, gamma));
  }
  
  plainFile.close();
  cryptedFile.close();
}

void Kuzn::codeGammaRecursive(const std::string &path, Register reg) const {
  std::ifstream plainFile(path, std::ios::binary);
  std::ofstream cryptedFile(path + ".txt", std::ios::binary);
  
  Block128 block;
  
  while (read(plainFile, block)) {
    auto gamma = encodeBlock(reg[0]);
    write(cryptedFile, Xor(block, gamma));
    
    reg.pop_front();
    reg.push_back(gamma);
  }
  
  plainFile.close();
  cryptedFile.close();
}

void Kuzn::codeGammaRecursiveCypher(const std::string &path, Register reg, bool isEncode) const {
  std::ifstream plainFile(path, std::ios::binary);
  std::ofstream cryptedFile(path + ".txt", std::ios::binary);
  
  Block128 block;
  
  while (read(plainFile, block)) {
    auto gamma = encodeBlock(reg[0]);
    const auto cypher = Xor(block, gamma);
    write(cryptedFile, cypher);
    
    reg.pop_front();
    
    if (isEncode) {
      reg.push_back(cypher);
    } else {
      reg.push_back(block);
    }
  }
  
  plainFile.close();
  cryptedFile.close();
}

void Kuzn::encodeRecursiveHook(const std::string &path, Register reg) const {
  std::ifstream plainFile(path, std::ios::binary);
  std::ofstream cryptedFile(path + ".txt", std::ios::binary);
  
  Block128 block;
  
  while (read(plainFile, block)) {
    const auto cypher = encodeBlock(Xor(reg[0], block));
    write(cryptedFile, cypher);
    
    reg.pop_front();
    reg.push_back(cypher);
  }
  
  plainFile.close();
  cryptedFile.close();
}

void Kuzn::decodeRecursiveHook(const std::string &path, Register reg) const {
  std::ifstream plainFile(path, std::ios::binary);
  std::ofstream cryptedFile(path + ".txt", std::ios::binary);
  
  Block128 block;
  
  while (read(plainFile, block)) {
    const auto plain = Xor(decodeBlock(block), reg[0]);
    write(cryptedFile, plain);
    
    reg.pop_front();
    reg.push_back(block);
  }
  
  plainFile.close();
  cryptedFile.close();
}

//##########################################################
void Kuzn::execute() {
  const auto synchro = randomSynchroReg(5);
  std::cout << "##########-Синхропосылка-##########" << std::endl;

  for (uint8_t i{ 0 }; i < synchro.size(); ++i) {
    std::cout << synchro[i];
  }
  
  std::cout << std::endl;
  
  while (true) {
    std::cout << std::endl << "##########-Выберите режим шифрования-##########" << std::endl <<
    "1 - Режим Простой замены, " << "2 - Режим Гаммирования, " << "3 - Режим Гаммирования с обр. свзяью, " << std::endl <<
    "4 - Режим Гаммирования с обр. связью по шифртексту, " << "5 - Режим Простой замены с зацеплением" << std::endl <<
    "USER>>"; // default - DEMO, 0 - exit
    int switchcase;
    std::cin >> switchcase;
    
    if (switchcase == 0) {
      break;
    }
    
    std::cout << std::endl << "##########-Введите путь до файла-##########" << std::endl <<
    "USER>>";
    std::string path;
    std::cin >> path;
    
    std::cout << std::endl << "##########-Что сделать с файлом?-##########" << std::endl <<
    "1 - Зашифровать, " << "2 - Расшифровать" << std::endl << "USER>>";
    int isEncode;
    std::cin >> isEncode;
    
    switch (switchcase) {
      case 1:{
        if (isEncode == 1) {
          encode(path);
        } else {
          decode(path);
        }
        
        continue;
      }
        
      case 2:{
        codeGamma(path, synchro[0](0));
        
        continue;
      }
        
      case 3:{
        codeGammaRecursive(path, synchro);
        
        continue;
      }
        
      case 4:{
        if (isEncode == 1) {
          codeGammaRecursiveCypher(path, synchro, true);
        } else {
          codeGammaRecursiveCypher(path, synchro, false);
        }
        
        continue;
      }
        
      case 5:{
        if (isEncode == 1) {
          encodeRecursiveHook(path, synchro);
        } else {
          decodeRecursiveHook(path, synchro);
        }
        
        continue;
      }
        
      default:{
        break;
      }
    }
  }
}

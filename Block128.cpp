#include "Block128.hpp"

Block128::Block128(const std::string &s) {
  if (s.size() != 32) {
    throw std::runtime_error("Неверная строка: " + s);
  }
  
  for (int i = 0; i < 16; ++i) {
    const auto l = s[31 - i * 2];
    const auto low = l - (l < 65 ? 48 : 55) & 0b11011111;
    
    const auto h = s[30 - i * 2];
    const auto high = h - (h < 65 ? 48 : 55) & 0b11011111;
    
    m_data[i] = (high << 4) + low;
  }
}

Block128::Block128() {
  (*this)[0] = (*this)[1] = 0;
}

Block128::Block128(const Chunk half1, const Chunk half2) {
  (*this)[0] = half1;
  (*this)[1] = half2;
}

Chunk &Block128::operator [](unsigned int i) {
  if (i > 1) {
    throw std::runtime_error("Неверный индекс []");
  }
  
  return *reinterpret_cast<Chunk *>(&m_data[i * 8]);
}

const Chunk &Block128::operator [](unsigned int i) const {
  if (i > 1) {
    throw std::runtime_error("Неверный индекс []");
  }
  
  return *reinterpret_cast<const Chunk *>(&m_data[i * 8]);
}

uint8_t &Block128::operator ()(unsigned int i) {
  if (i > 15) {
    throw std::runtime_error("Неверный индекс ()");
  }
  
  return m_data[i];
}

uint8_t Block128::operator ()(unsigned int i) const {
  if (i > 15) {
    throw std::runtime_error("Неверный индекс ()");
  }
  
  return m_data[i];
}

std::string Block128::str() const {
  std::string result;
  
  for (int i = 15; i >= 0; --i) {
    const auto l = m_data[i] & 0x0f;
    const auto h = m_data[i] >> 4;
    result += h + (h > 9 ? 55 : 48);
    result += l + (l > 9 ? 55 : 48);
  }
  
  return result;
}

void Block128::reverse() {
  for (uint8_t i = 0; i < 8; ++i) {
    std::swap(m_data[i], m_data[15 - i]);
  }
}

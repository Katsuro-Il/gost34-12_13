#pragma once
#include <deque>
#include <string>

using Chunk = unsigned long long;

struct Block128 {
  Block128(const std::string &s); // Создаётся и заполняется данными из hex-строки
  Block128(); // Создаётся пустой, заполненный нулями
  Block128(const Chunk, const Chunk); //
  
  Chunk &operator [](unsigned int i); // Чтение/запись значениями по 64 бита (8 байт)
  const Chunk &operator [](unsigned int i)const; // Только чтение значениями по 64 бита (8 байт)
  uint8_t &operator()(unsigned int i); // Выборка значений по 1 байту (8 бит)
  uint8_t operator()(unsigned int i) const; // Чтение значений по 1 байту (8 бит)
  std::string str() const; // Преобразуется в строку для вывода
  void reverse();
  
private:
  uint8_t m_data[16];
};

template < typename STREAM >
STREAM & operator << (STREAM & stm, const Block128& block)
{
  return stm << block.str();
}

using Register = std::deque < Block128 >;

#include "../src/bitset.h"
#include <iostream>

int main() {
  bitset::Bitset test(50, false);
  test[31] = 1;
  std::cout << test.to_string() << std::endl;
  test <<= 4;
  std::cout << test.to_string() << std::endl;
  test[4] = 1;
  std::cout << test.to_string() << std::endl;  
  test[10] = 1;
  std::cout << test.to_string() << std::endl;  
  test <<= 20;
  std::cout << test.to_string() << std::endl;
  bitset::Bitset test2(50, true);
  std::cout << (test | test2).to_string() << std::endl;
}
#include <iostream>

#include "../src/bitset.h"

int main() {
  bitset::Bitset test(50, false);
  test[31] = 1;
  test[1] = true;
  test[22] = 1;
  test[50] = 1;
  int a = test[31];
  std::cout << test.to_string() << std::endl;
  test <<= 4;
  std::cout << test.to_string() << std::endl;
  test[4] = 1;
  std::cout << test.to_string() << std::endl;  
  test[10] = 1;
  std::cout << test.to_string() << std::endl;  
  test <<= 23;
  std::cout << test.to_string() << std::endl;
  bitset::Bitset test2(50, true);
  test2[3] = 0;
  test2[5] = 0;
  test2[19] = 0;
  std::cout << (test2).to_string() << std::endl;
  bitset::Bitset t3 = test2 << 20;
  std::cout << t3.to_string() << std::endl;
  std::cout << (test & test2).to_string() << std::endl;
}

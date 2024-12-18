#include "unit_test.hpp"
map<string, bool (UNIT_TEST_Sort_Togo::*)()> UNIT_TEST_Sort_Togo::TESTS;
bool charComparator(char &lhs, char &rhs) { return lhs == rhs; }
string vertex2str(char &v) {
  stringstream os;
  os << v;
  return os.str();
}
int intKeyHash(char &key, int capacity) { return key % capacity; }



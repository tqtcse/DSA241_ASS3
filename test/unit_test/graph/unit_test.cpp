#include "unit_test.hpp"
map<string, bool (UNIT_TEST_Graph::*)()> UNIT_TEST_Graph::TESTS;
bool charComparator(char &lhs, char &rhs) { return lhs == rhs; }
string vertex2str(char &v) {
  stringstream os;
  os << v;
  return os.str();
}
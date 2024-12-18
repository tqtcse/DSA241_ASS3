#include "../unit_test.hpp"

bool UNIT_TEST_Sort_Togo::sort_topo02() {
  string name = "sort_topo02";
  stringstream output;
  //! data ------------------------------------
  Stack<char> stack;
  stack.push('A');
  stack.push('B');
  stack.push('C');

  //! expect ----------------------------------
  string expect = "C 0 C D B A A 1";

  //! output ----------------------------------
  output << stack.peek() << " " << stack.empty() << " " << stack.pop() << " ";
  stack.push('D');
  output << stack.pop() << " ";
  output << stack.pop() << " " << stack.peek() << " ";
  output << stack.pop() << " " << stack.empty();

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

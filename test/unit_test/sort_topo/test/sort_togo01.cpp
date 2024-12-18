#include "../unit_test.hpp"

bool UNIT_TEST_Sort_Togo::sort_topo01() {
  string name = "sort_topo01";
  stringstream output;
  //! data ------------------------------------
  Queue<char> queue;
  queue.push('A');
  queue.push('B');
  queue.push('C');

  //! expect ----------------------------------
  string expect = "0 A B C D 1";

  //! output ----------------------------------
  output << queue.empty() << " " << queue.pop() << " ";
  queue.push('D');
  output << queue.pop() << " ";
  output << queue.pop() << " ";
  output << queue.pop() << " " << queue.empty();

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

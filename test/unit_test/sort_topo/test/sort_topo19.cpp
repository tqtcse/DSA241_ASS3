#include "../unit_test.hpp"

bool UNIT_TEST_Sort_Togo::sort_topo19() {
  string name = "sort_topo19";
  //! data ------------------------------------
  DGraphModel<char> model(&charComparator, &vertex2str);

  TopoSorter<char> topoSorter(&model, &intKeyHash);
  DLinkedList<char> result = topoSorter.sort(TopoSorter<char>::DFS);

  //! expect ----------------------------------
  string expect = "DFS Topological Sort: NULL";

  //! output ----------------------------------
  stringstream output;
  output << "DFS Topological Sort: ";
  for (auto it = result.begin(); it != result.end(); it++) {
    output << *it << "->";
  }
  output << "NULL";

  //! remove data -----------------------------
  model.clear();

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

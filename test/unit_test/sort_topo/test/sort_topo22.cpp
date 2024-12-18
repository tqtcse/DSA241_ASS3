#include "../unit_test.hpp"

bool UNIT_TEST_Sort_Togo::sort_topo22() {
  string name = "sort_topo22";
  //! data ------------------------------------
  DGraphModel<char> model(&charComparator, &vertex2str);
  char vertices[] = {'1', '2', '3', '7', '8', '6', '4', '5'};
  for (int idx = 0; idx < 8; idx++) {
    model.add(vertices[idx]);
  }
  TopoSorter<char> topoSorter(&model, &intKeyHash);
  DLinkedList<char> result = topoSorter.sort(TopoSorter<char>::BFS);

  //! expect ----------------------------------
  string expect = "BFS Topological Sort: 1->2->3->4->5->6->7->8->NULL";

  //! output ----------------------------------
  stringstream output;
  output << "BFS Topological Sort: ";
  for (auto it = result.begin(); it != result.end(); it++) {
    output << *it << "->";
  }
  output << "NULL";

  //! remove data -----------------------------
  model.clear();

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

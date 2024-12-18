#include "../unit_test.hpp"

bool UNIT_TEST_Sort_Togo::sort_topo20() {
  string name = "sort_topo20";
  //! data ------------------------------------
  DGraphModel<char> model(&charComparator, &vertex2str);
  char vertices[] = {'1', '2', '3', '4', '5', '6', '7', '8'};
  for (int idx = 0; idx < 8; idx++) {
    model.add(vertices[idx]);
  }
  model.connect('1', '6');
  model.connect('1', '5');
  model.connect('1', '3');
  model.connect('1', '2');
  model.connect('1', '4');
  model.connect('1', '7');
  model.connect('1', '8');
  TopoSorter<char> topoSorter(&model, &intKeyHash);
  DLinkedList<char> result = topoSorter.sort(TopoSorter<char>::DFS);

  //! expect ----------------------------------
  string expect = "DFS Topological Sort: 1->8->7->4->2->3->5->6->NULL";

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

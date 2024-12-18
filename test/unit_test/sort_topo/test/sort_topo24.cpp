#include "../unit_test.hpp"

bool UNIT_TEST_Sort_Togo::sort_topo24() {
  string name = "sort_topo24";
  //! data ------------------------------------
  DGraphModel<char> model(&charComparator, &vertex2str);
  char vertices[] = {'1', '2', '3', '7', '8', '6', '4', '5'};
  for (int idx = 0; idx < 8; idx++) {
    model.add(vertices[idx]);
  }
  model.connect('1', '2');
  model.connect('1', '3');
  model.connect('1', '2');
  model.connect('1', '7');
  model.connect('1', '8');
  model.connect('1', '6');
  model.connect('1', '4');
  model.connect('1', '5');

  TopoSorter<char> topoSorter(&model, &intKeyHash);
  DLinkedList<char> result = topoSorter.sort(TopoSorter<char>::DFS);

  //! expect ----------------------------------
  string expect = "DFS Topological Sort: 1->5->4->6->8->7->3->2->NULL";

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

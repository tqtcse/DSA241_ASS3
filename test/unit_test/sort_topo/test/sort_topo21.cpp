#include "../unit_test.hpp"

bool UNIT_TEST_Sort_Togo::sort_topo21() {
  string name = "sort_topo21";
  //! data ------------------------------------
  DGraphModel<char> model(&charComparator, &vertex2str);
  char vertices[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
  for (int idx = 0; idx < 10; idx++) {
    model.add(vertices[idx]);
  }
  model.connect('0', '1');
  model.connect('0', '5');
  model.connect('1', '7');
  model.connect('3', '2');
  model.connect('3', '4');
  model.connect('3', '7');
  model.connect('3', '8');
  model.connect('4', '8');
  model.connect('6', '0');
  model.connect('6', '1');
  model.connect('6', '2');
  model.connect('8', '2');
  model.connect('8', '7');
  model.connect('9', '4');
  TopoSorter<char> topoSorter(&model, &intKeyHash);
  DLinkedList<char> result = topoSorter.sort(TopoSorter<char>::DFS);

  //! expect ----------------------------------
  string expect = "DFS Topological Sort: 9->6->0->5->1->3->4->8->7->2->NULL";

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

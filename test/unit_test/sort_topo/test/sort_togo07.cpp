#include "../unit_test.hpp"

bool UNIT_TEST_Sort_Togo::sort_topo07() {
  string name = "sort_topo07";
  stringstream output;
  //! data ------------------------------------
  DGraphModel<char> model(&charComparator, &vertex2str);
  char vertices[] = {'A','B','C','D','E'};
  for (int idx = 0; idx < 5; idx++) {
    model.add(vertices[idx]);
  }
  model.connect('A', 'B');
  model.connect('B', 'D');
  model.connect('B', 'C');
  model.connect('B', 'E');

  TopoSorter<char> topoSorter(&model, &intKeyHash);
  DLinkedList<char> result = topoSorter.sort(TopoSorter<char>::BFS);

  //! expect ----------------------------------
  string expect = "BFS Topological Sort: A->B->D->C->E->NULL";
  //! output ----------------------------------
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
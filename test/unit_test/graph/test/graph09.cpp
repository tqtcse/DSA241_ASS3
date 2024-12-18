#include "../unit_test.hpp"

bool UNIT_TEST_Graph::graph09() {
  string name = "graph09";
  stringstream output;
  //! data ------------------------------------
  char vertices[] = {'A', 'B', 'C', 'D'};

  // Định nghĩa các cạnh
  Edge<char> edges[5] = {Edge<char>('A', 'B', 1.5), Edge<char>('A', 'A', 10),
                         Edge<char>('B', 'C', 2.0), Edge<char>('C', 'D', 3.2),
                         Edge<char>('D', 'D', 3.2)};
  DGraphModel<char> *model = DGraphModel<char>::create(
      vertices, 4, edges, 5, &charComparator, &vertex2str);
  model->remove('A');
  model->remove('B');
  DLinkedList<char> in = model->getInwardEdges('D');

  output << "getInwardEdges : D: ";
  for (auto it = in.begin(); it != in.end(); it++) {
    output << *it << "-> ";
  }
  output << "NULL\n";
  //! expect ----------------------------------
  string expect =
      "getInwardEdges : D: C-> D-> NULL\n\
==================================================\n\
Vertices:   \n\
V(C, in: 0, out: 1)\n\
V(D, in: 2, out: 1)\n\
------------------------------\n\
Edges:      \n\
E(C,D,3.2)\n\
E(D,D,3.2)\n\
==================================================\n";

  //! output ----------------------------------
  output << model->toString();

  //! remove data -----------------------------
  model->clear();
  delete model;

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

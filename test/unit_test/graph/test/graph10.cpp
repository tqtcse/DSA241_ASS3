#include "../unit_test.hpp"

bool UNIT_TEST_Graph::graph10() {
  string name = "graph10";
  stringstream output;
  //! data ------------------------------------
  char vertices[] = {'A', 'B', 'C', 'D'};

  // Định nghĩa các cạnh
  Edge<char> edges[5] = {Edge<char>('A', 'B', 1.5), Edge<char>('A', 'A', 10),
                         Edge<char>('B', 'C', 2.0), Edge<char>('C', 'D', 3.2),
                         Edge<char>('D', 'D', 3.2)};
  UGraphModel<char> *model = UGraphModel<char>::create(
      vertices, 4, edges, 5, &charComparator, &vertex2str);
  model->remove('B');
  model->remove('D');
  //! expect ----------------------------------
  string expect =
      "==================================================\n\
Vertices:   \n\
V(A, in: 1, out: 1)\n\
V(C, in: 0, out: 0)\n\
------------------------------\n\
Edges:      \n\
E(A,A,10)\n\
==================================================\n";

  //! output ----------------------------------
  output << model->toString();

  //! remove data -----------------------------
  model->clear();
  delete model;

  //! result ---------------------------------
  return printResult(output.str(), expect, name);
}

#include "../unit_test.hpp"

bool UNIT_TEST_Graph::graph01() {
  string name = "graph01";
  //! data ------------------------------------
  DGraphModel<char> model(&charComparator, &vertex2str);
  char vertices[] = {'A', 'B', 'C', 'D'};
  for (int idx = 0; idx < 4; idx++) {
    model.add(vertices[idx]);
  }
  model.connect('A', 'B');
  model.connect('A', 'B', 5);
  model.connect('B', 'D');
  model.connect('C', 'B');
  model.connect('C', 'D');
  //! expect ----------------------------------
  string expect =
      "==================================================\n\
Vertices:   \n\
V(A, in: 0, out: 1)\n\
V(B, in: 2, out: 1)\n\
V(C, in: 0, out: 2)\n\
V(D, in: 2, out: 0)\n\
------------------------------\n\
Edges:      \n\
E(A,B,5)\n\
E(B,D,0)\n\
E(C,B,0)\n\
E(C,D,0)\n\
==================================================\n";

  //! output ----------------------------------
  stringstream output;

  output << model.toString();

  //! remove data -----------------------------
  model.clear();

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}
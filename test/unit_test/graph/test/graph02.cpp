#include "../unit_test.hpp"

bool UNIT_TEST_Graph::graph02() {
  string name = "graph02";
  //! data ------------------------------------
  UGraphModel<char> model(&charComparator, &vertex2str);
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
V(A, in: 1, out: 1)\n\
V(B, in: 3, out: 3)\n\
V(C, in: 2, out: 2)\n\
V(D, in: 2, out: 2)\n\
------------------------------\n\
Edges:      \n\
E(A,B,5)\n\
E(B,A,5)\n\
E(B,D,0)\n\
E(B,C,0)\n\
E(C,B,0)\n\
E(C,D,0)\n\
E(D,B,0)\n\
E(D,C,0)\n\
==================================================\n";

  //! output ----------------------------------
  stringstream output;

  output << model.toString();

  //! remove data -----------------------------
  model.clear();

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}
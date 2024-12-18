#include "../unit_test.hpp"

bool UNIT_TEST_Graph::graph03() {
  string name = "graph03";
  stringstream output;
  //! data ------------------------------------
  DGraphModel<char> model(&charComparator, &vertex2str);
  char vertices[] = {'A', 'B', 'C', 'D', 'E'};
  for (int idx = 0; idx < 5; idx++) {
    model.add(vertices[idx]);
  }
  model.connect('A', 'B', 8);
  model.connect('B', 'D', 6);
  model.connect('C', 'B', 1);
  model.connect('C', 'D', 2);
  model.connect('E', 'A', 3);
  model.connect('E', 'B', 4);
  model.connect('E', 'C', 5);
  DLinkedList<char> out = model.getOutwardEdges('E');
  DLinkedList<char> in = model.getInwardEdges('B');
  output << "getOutwardEdges : E: ";
  for (auto it = out.begin(); it != out.end(); it++) {
    output << *it << "-> ";
  }
  output << "NULL\n";

  output << "getInwardEdges : B: ";
  for (auto it = in.begin(); it != in.end(); it++) {
    output << *it << "-> ";
  }
  output << "NULL\n";
  //! expect ----------------------------------
  string expect =
      "getOutwardEdges : E: A-> B-> C-> NULL\n\
getInwardEdges : B: A-> C-> E-> NULL\n\
==================================================\n\
Vertices:   \n\
V(A, in: 1, out: 1)\n\
V(B, in: 3, out: 1)\n\
V(C, in: 1, out: 2)\n\
V(D, in: 2, out: 0)\n\
V(E, in: 0, out: 3)\n\
------------------------------\n\
Edges:      \n\
E(A,B,8)\n\
E(B,D,6)\n\
E(C,B,1)\n\
E(C,D,2)\n\
E(E,A,3)\n\
E(E,B,4)\n\
E(E,C,5)\n\
==================================================\n";

  //! output ----------------------------------

  output << model.toString();

  //! remove data -----------------------------
  model.clear();

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}
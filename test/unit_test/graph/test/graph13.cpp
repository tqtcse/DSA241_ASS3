#include "../unit_test.hpp"

bool UNIT_TEST_Graph::graph13() {
  string name = "graph13";
  stringstream output;
  //! data ------------------------------------
  char vertices[] = {'A', 'B', 'C', 'D', 'E', 'F', 'H', 'G'};

  // Định nghĩa các cạnh
  Edge<char> edges[6] = {Edge<char>('A', 'B', 1.5), Edge<char>('A', 'A', 10),
                         Edge<char>('B', 'C', 2.0), Edge<char>('B', 'B', 2.0),
                         Edge<char>('C', 'D', 3.2), Edge<char>('D', 'D', 3.2)};
  DGraphModel<char> *model = DGraphModel<char>::create(
      vertices, 8, edges, 6, &charComparator, &vertex2str);
  output << "Size: " << model->size() << endl;
  output << "vertices: ";
  DLinkedList<char> a = model->vertices();
  for (auto it = a.begin(); it != a.end(); ++it) {
    output << *it << " ";
  }
  output << "\n";
  output << "Indegree H: " << model->inDegree('H') << endl;
  output << "Outdegree C: " << model->outDegree('C') << endl;
  model->remove('F');
  model->remove('B');
  model->remove('H');
  model->remove('G');
  output << "Size: " << model->size() << endl;
  //! expect ----------------------------------
  string expect =
      "Size: 8\n\
vertices: A B C D E F H G \n\
Indegree H: 0\n\
Outdegree C: 1\n\
Size: 4\n\
==================================================\n\
Vertices:   \n\
V(A, in: 1, out: 1)\n\
V(C, in: 0, out: 1)\n\
V(D, in: 2, out: 1)\n\
V(E, in: 0, out: 0)\n\
------------------------------\n\
Edges:      \n\
E(A,A,10)\n\
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

#include "../unit_test.hpp"

bool UNIT_TEST_Graph::graph12() {
  string name = "graph12";
  stringstream output;
  //! data ------------------------------------
  char vertices[] = {'A', 'B', 'C', 'D'};

  // Định nghĩa các cạnh
  Edge<char> edges[5] = {Edge<char>('A', 'B', 1.5), Edge<char>('A', 'A', 10),
                         Edge<char>('B', 'C', 2.0), Edge<char>('C', 'D', 3.2),
                         Edge<char>('D', 'D', 3.2)};
  DGraphModel<char> *model = DGraphModel<char>::create(
      vertices, 4, edges, 5, &charComparator, &vertex2str);
  output << "Size: " << model->size() << endl;
  output << "vertices: ";
  DLinkedList<char> a = model->vertices();
  for (auto it = a.begin(); it != a.end(); ++it) {
    output << *it << " ";
  }
  output << "\n";
  output << "Indegree: " << model->inDegree('A') << endl;
  output << "Outdegree: " << model->outDegree('A') << endl;
  model->remove('A');
  model->remove('B');
  model->remove('C');
  model->remove('D');
  output << "Size: " << model->size() << endl;
  try {
    model->inDegree('F');
  } catch (const VertexNotFoundException &e) {
    output << "Error: " << "F khong ton tai" << endl;
  }
  try {
    model->outDegree('F');
  } catch (const VertexNotFoundException &e) {
    output << "Error: " << "F khong ton tai" << endl;
  }
  //! expect ----------------------------------
  string expect =
      "Size: 4\n\
vertices: A B C D \n\
Indegree: 1\n\
Outdegree: 2\n\
Size: 0\n\
Error: F khong ton tai\n\
Error: F khong ton tai\n\
==================================================\n\
Vertices:   \n\
------------------------------\n\
Edges:      \n\
==================================================\n";

  //! output ----------------------------------
  output << model->toString();

  //! remove data -----------------------------
  model->clear();
  delete model;

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}
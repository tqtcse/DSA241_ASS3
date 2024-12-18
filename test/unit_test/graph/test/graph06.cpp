#include "../unit_test.hpp"

bool UNIT_TEST_Graph::graph06() {
  string name = "graph06";
  stringstream output;
  //! data ------------------------------------
  char vertices[] = {'A', 'B', 'C', 'D'};

  // Định nghĩa các cạnh
  Edge<char> edges[3] = {Edge<char>('A', 'B', 1.5), Edge<char>('B', 'C', 2.0),
                         Edge<char>('C', 'D', 3.2)};
  UGraphModel<char> *model = UGraphModel<char>::create(
      vertices, 4, edges, 3, &charComparator, &vertex2str);

  try {
    // Gọi một phương thức có thể ném ngoại lệ
    DLinkedList<char> out = model->getOutwardEdges('E');
  } catch (const VertexNotFoundException &e) {
    // Xử lý ngoại lệ nếu đỉnh không tìm thấy
    output << "Error: " << "getOutwardEdges :E khong ton tai"
           << endl;  // In ra thông báo lỗi
  }
  DLinkedList<char> in = model->getInwardEdges('B');

  output << "getInwardEdges : B: ";
  for (auto it = in.begin(); it != in.end(); it++) {
    output << *it << "-> ";
  }
  output << "NULL\n";
  //! expect ----------------------------------
  string expect =
      "Error: getOutwardEdges :E khong ton tai\n\
getInwardEdges : B: A-> C-> NULL\n\
==================================================\n\
Vertices:   \n\
V(A, in: 1, out: 1)\n\
V(B, in: 2, out: 2)\n\
V(C, in: 2, out: 2)\n\
V(D, in: 1, out: 1)\n\
------------------------------\n\
Edges:      \n\
E(A,B,1.5)\n\
E(B,A,1.5)\n\
E(B,C,2)\n\
E(C,B,2)\n\
E(C,D,3.2)\n\
E(D,C,3.2)\n\
==================================================\n";

  //! output ----------------------------------
  output << model->toString();

  //! remove data -----------------------------
  model->clear();
  delete model;

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

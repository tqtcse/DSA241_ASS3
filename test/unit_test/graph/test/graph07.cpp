#include "../unit_test.hpp"

bool UNIT_TEST_Graph::graph07() {
  string name = "graph07";
  stringstream output;
  //! data ------------------------------------
  char vertices[] = {'A', 'B', 'C', 'D'};

  // Định nghĩa các cạnh
  Edge<char> edges[4] = {Edge<char>('A', 'B', 1.5), Edge<char>('B', 'C', 2.0),
                         Edge<char>('C', 'D', 3.2), Edge<char>('D', 'D', 3.2)};
  UGraphModel<char> *model = UGraphModel<char>::create(
      vertices, 4, edges, 4, &charComparator, &vertex2str);

  try {
    // Gọi một phương thức có thể ném ngoại lệ
    model->weight('A', 'D');
  } catch (const EdgeNotFoundException &e) {
    // Xử lý ngoại lệ nếu đỉnh không tìm thấy
    output << "Error: " << "AB khong ton tai" << endl;  // In ra thông báo lỗi
  }
  try {
    // Gọi một phương thức có thể ném ngoại lệ
    model->weight('E', 'D');
  } catch (const VertexNotFoundException &e) {
    // Xử lý ngoại lệ nếu đỉnh không tìm thấy
    output << "Error: " << "E khong ton tai" << endl;  // In ra thông báo lỗi
  }

  try {
    // Gọi một phương thức có thể ném ngoại lệ
    model->weight('D', 'F');
  } catch (const VertexNotFoundException &e) {
    // Xử lý ngoại lệ nếu đỉnh không tìm thấy
    output << "Error: " << "F khong ton tai" << endl;  // In ra thông báo lỗi
  }
  output << "AB : " << model->weight('A', 'B') << endl;
  output << "CD : " << model->weight('C', 'D') << endl;

  DLinkedList<char> in = model->getInwardEdges('D');

  output << "getInwardEdges : D: ";
  for (auto it = in.begin(); it != in.end(); it++) {
    output << *it << "-> ";
  }
  output << "NULL\n";
  //! expect ----------------------------------
  string expect =
      "Error: AB khong ton tai\n\
Error: E khong ton tai\n\
Error: F khong ton tai\n\
AB : 1.5\n\
CD : 3.2\n\
getInwardEdges : D: C-> D-> NULL\n\
==================================================\n\
Vertices:   \n\
V(A, in: 1, out: 1)\n\
V(B, in: 2, out: 2)\n\
V(C, in: 2, out: 2)\n\
V(D, in: 2, out: 2)\n\
------------------------------\n\
Edges:      \n\
E(A,B,1.5)\n\
E(B,A,1.5)\n\
E(B,C,2)\n\
E(C,B,2)\n\
E(C,D,3.2)\n\
E(D,C,3.2)\n\
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

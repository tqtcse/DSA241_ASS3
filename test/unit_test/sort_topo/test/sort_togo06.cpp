#include "../unit_test.hpp"
int compare(int& lhs, int& rhs) {
    if (lhs > rhs) return -1; // lhs lớn hơn rhs -> giữ nguyên thứ tự
    else if (lhs < rhs) return 1; // lhs nhỏ hơn rhs -> đảo thứ tự
    else return 0; // Bằng nhau
}
bool UNIT_TEST_Sort_Togo::sort_topo06() {
  string name = "sort_topo06";
  stringstream output;
  //! data ------------------------------------
    DLinkedListSE<int> data;
    data.add(1);
    data.add(2);
    data.add(0);
    data.add(3);
    data.add(3);
    data.add(8);
    data.add(9);
    data.sort(&compare);
  //! expect ----------------------------------
  string expect = "[9, 8, 3, 3, 2, 1, 0]\n\
duyet nguoc : [0, 1, 2, 3, 3, 8, 9]";

  //! output ----------------------------------
  output << data.toString();
  output << "\nduyet nguoc : [";
    for (auto it = data.bbegin(); it != data.bend(); it--) {
       if (it != data.bbegin()) output << ", "; // Thêm dấu phẩy
         output << *it;
    }
    output << "]";

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}

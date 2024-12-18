#include "../unit_test.hpp"

bool UNIT_TEST_Sort_Togo::sort_topo05() {
  string name = "sort_topo05";
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
    data.sort();
  //! expect ----------------------------------
  string expect = "[0, 1, 2, 3, 3, 8, 9]\n\
duyet nguoc : [9, 8, 3, 3, 2, 1, 0]";

  //! output ----------------------------------
  output << data.toString();
 //! output ----------------------------------
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

/*
 * Assignment 3 - Developing List Data Structures and Artificial Neural Networks
 * file : main.cpp
 * Data Structures and Algorithms
 * Author: Võ Tiến
 * Link FB : https://www.facebook.com/Shiba.Vo.Tien
 * Link Group : https://www.facebook.com/groups/khmt.ktmt.cse.bku
 * Date: 05.12.2024

 ! build code graph :   g++ -fsanitize=address -fsanitize=undefined -std=c++17
-o main -Iinclude -Itest main.cpp test/unit_test/sort_topo/unit_test.cpp
test/unit_test/sort_topo/test/*.cpp  -DTEST_SORT_TOPO

  ! build code topo : g++ -fsanitize=address -fsanitize=undefined -std=c++17 -o
main -Iinclude -Itest main.cpp test/unit_test/graph/unit_test.cpp
test/unit_test/graph/test/*.cpp  -DTEST_GRAPH


 * run code
    * terminal unit test array list
    !./main test_unit
    !./main test_unit nameFunctionUnitTest
*/

#include "main.hpp"
#ifdef TEST_GRAPH
#include "unit_test/graph/unit_test.hpp"
const string TEST_CASE = "GRAPH";
#elif TEST_SORT_TOPO
#include "unit_test/sort_topo/unit_test.hpp"
const string TEST_CASE = "SORT_TOPO";
#endif
void printTestCase();

int main(int argc, char *argv[]) {
  if (argc <= 1) {
    printTestCase();
    return 1;
  }

  std::string arg1 = argv[1];
  if (arg1 == "test_unit") {
    std::cout << GREEN << BOLD << "Running unit_test/" << TEST_CASE << RESET
              << "\n";
    handleTestUnit(argc, argv);
  } else {
    printTestCase();
  }
}

#ifdef TEST_GRAPH
void handleTestUnit(int argc, char *argv[]) {
  UNIT_TEST_Graph unitTest;

  if (argc == 2 || (argc == 3 && std::string(argv[2]) == "all")) {
    unitTest.runAllTests();
  } else if (argc == 3) {
    unitTest.runTest(argv[2]);
  } else {
    printTestCase();
  }
}
#elif TEST_SORT_TOPO
void handleTestUnit(int argc, char *argv[]) {
  UNIT_TEST_Sort_Togo unitTest;

  if (argc == 2 || (argc == 3 && std::string(argv[2]) == "all")) {
    unitTest.runAllTests();
  } else if (argc == 3) {
    unitTest.runTest(argv[2]);
  } else {
    printTestCase();
  }
}
#endif

void printTestCase() {
  std::cout << GREEN << BOLD << "terminal unit test" << RESET << std::endl;
  std::cout << RED << "./main test_unit" << RESET << std::endl;
  std::cout << RED << "./main test_unit nameFunctionUnitTest" << RESET
            << std::endl
            << std::endl;
}
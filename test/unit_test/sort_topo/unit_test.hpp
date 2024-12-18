#ifndef UNIT_TEST_Sort_Togo_HPP
#define UNIT_TEST_Sort_Togo_HPP

#include "graph/TopoSorter.h"
#include "library.hpp"
#include "sorting/DLinkedListSE.h"
#include "stacknqueue/Queue.h"
#include "stacknqueue/Stack.h"

bool charComparator(char &lhs, char &rhs);
string vertex2str(char &v);
int intKeyHash(char &key, int capacity);

class UNIT_TEST_Sort_Togo {
 public:
  UNIT_TEST_Sort_Togo() {
    // TODO unit test new
    registerTest("sort_topo01", &UNIT_TEST_Sort_Togo::sort_topo01);
    registerTest("sort_topo02", &UNIT_TEST_Sort_Togo::sort_topo02);
    registerTest("sort_topo03", &UNIT_TEST_Sort_Togo::sort_topo03);
    registerTest("sort_topo04", &UNIT_TEST_Sort_Togo::sort_topo04);
    registerTest("sort_topo05", &UNIT_TEST_Sort_Togo::sort_topo05);
    registerTest("sort_topo06", &UNIT_TEST_Sort_Togo::sort_topo06);
    registerTest("sort_topo07", &UNIT_TEST_Sort_Togo::sort_topo07);
    registerTest("sort_topo08", &UNIT_TEST_Sort_Togo::sort_topo08);
    registerTest("sort_topo09", &UNIT_TEST_Sort_Togo::sort_topo09);
    registerTest("sort_topo10", &UNIT_TEST_Sort_Togo::sort_topo10);
    registerTest("sort_topo11", &UNIT_TEST_Sort_Togo::sort_topo11);
    registerTest("sort_topo12", &UNIT_TEST_Sort_Togo::sort_topo12);
    registerTest("sort_topo13", &UNIT_TEST_Sort_Togo::sort_topo13);
    registerTest("sort_topo14", &UNIT_TEST_Sort_Togo::sort_topo14);
    registerTest("sort_topo15", &UNIT_TEST_Sort_Togo::sort_topo15);
    registerTest("sort_topo16", &UNIT_TEST_Sort_Togo::sort_topo16);
    registerTest("sort_topo17", &UNIT_TEST_Sort_Togo::sort_topo17);
    registerTest("sort_topo18", &UNIT_TEST_Sort_Togo::sort_topo18);
    registerTest("sort_topo19", &UNIT_TEST_Sort_Togo::sort_topo19);
    registerTest("sort_topo20", &UNIT_TEST_Sort_Togo::sort_topo20);
    registerTest("sort_topo21", &UNIT_TEST_Sort_Togo::sort_topo21);
    registerTest("sort_topo22", &UNIT_TEST_Sort_Togo::sort_topo22);
    registerTest("sort_topo23", &UNIT_TEST_Sort_Togo::sort_topo23);
    registerTest("sort_topo24", &UNIT_TEST_Sort_Togo::sort_topo24);
    registerTest("sort_topo25", &UNIT_TEST_Sort_Togo::sort_topo25);
   
  }

 private:
  // TODO unit test new
  bool sort_topo01();
  bool sort_topo02();
  bool sort_topo03();
  bool sort_topo04();
  bool sort_topo05();
  bool sort_topo06();
  bool sort_topo07();
  bool sort_topo08();
  bool sort_topo09();
  bool sort_topo10();
  bool sort_topo11();
  bool sort_topo12();
  bool sort_topo13();
  bool sort_topo14();
  bool sort_topo15();
  bool sort_topo16();
  bool sort_topo17();
  bool sort_topo18();
  bool sort_topo19();
  bool sort_topo20();
  bool sort_topo21();
  bool sort_topo22();
  bool sort_topo23();
  bool sort_topo24();
  bool sort_topo25();
  

 public:
  static map<string, bool (UNIT_TEST_Sort_Togo::*)()> TESTS;
  // ANSI escape codes for colors
  const string green = "\033[32m";
  const string red = "\033[31m";
  const string cyan = "\033[36m";
  const string reset = "\033[0m";  // To reset to default color

  // print result test case
  bool printResult(string output, string expect, string name) {
    if (expect == output) {
      cout << green << "test " + name + " --------------- PASS" << reset
           << "\n";
      return true;
    } else {
      cout << red << "test " + name + " --------------- FAIL" << reset << "\n";
      cout << "\texpect : " << expect << endl;
      cout << "\toutput : " << output << endl;
      return false;
    }
  }
  // run 1 test case
  void runTest(const std::string &name) {
    auto it = TESTS.find(name);
    if (it != TESTS.end()) {
      (this->*(it->second))();
    } else {
      throw std::runtime_error("Test with name '" + name + "' does not exist.");
    }
  }
  // run all test case
  void runAllTests() {
    vector<string> fails;
    for (const auto &test : TESTS) {
      if (!(this->*(test.second))()) {
        fails.push_back(test.first);
      }
    }

    cout << cyan << "\nResult -------------------------" << reset << endl;
    // Print the results
    if (fails.empty()) {
      cout << green << "All tests passed!" << reset << endl;
    } else {
      int totalTests = TESTS.size();
      int failedTests = fails.size();
      int passedTests = totalTests - failedTests;
      double passRate =
          (totalTests > 0)
              ? (static_cast<double>(passedTests) / totalTests) * 100.0
              : 0.0;
      cout << red << "Some tests failed:";
      for (const auto &fail : fails) {
        cout << "  " << fail;
      }
      cout << cyan << "\nPass rate: " << passRate << "%" << reset << endl;
    }
  }
  static void registerTest(string name,
                           bool (UNIT_TEST_Sort_Togo::*function)()) {
    if (TESTS.find(name) != TESTS.end()) {
      throw std::runtime_error("Test with name '" + name + "' already exists.");
    }
    TESTS[name] = function;
  }
};

#endif  // UNIT_TEST_Sort_Togo_HPP
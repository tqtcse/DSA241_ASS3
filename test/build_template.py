import os

template = '''#include "../unit_test.hpp"

bool UNIT_TEST_Graph::graph{index:02}() {{
  string name = "graph{index:02}";
  //! data ------------------------------------

  //! expect ----------------------------------
  string expect = "";

  //! output ----------------------------------
  stringstream output;

  //! remove data -----------------------------

  //! result ----------------------------------
  return printResult(output.str(), expect, name);
}}
'''

# Generate files from graph01.cpp to graph20.cpp
for i in range(1, 21):
    filename = f"unit_test/graph/test/graph{i:02}.cpp"
    if not os.path.exists(filename):
        with open(filename, 'w') as file:
            content = template.format(index=i)
            file.write(content)
        print(f"Created: {filename}")
    else:
        print(f"Skipped (already exists): {filename}")
#include "../unit_test.hpp"

bool UNIT_TEST_Sort_Togo::sort_topo13()
{
    string name = "sort_topo13";
    stringstream output;
    //! data ------------------------------------
    DGraphModel<char> model(&charComparator, &vertex2str);
     char vertices[] = {'F', 'G', 'B', 'C', 'D', 'E', 'A', 'X', 'Y', 'V'};
    for (int idx = 0; idx < 10; idx++)
    {
        model.add(vertices[idx]);
    }
    model.connect('A', 'B');
    model.connect('C', 'G');
    model.connect('G', 'F');
    model.connect('E', 'F');
    model.connect('F', 'Y');
    model.connect('D', 'X');
    model.connect('X', 'Y');
    model.connect('Y', 'V');

    TopoSorter<char> topoSorter(&model, &intKeyHash);
    DLinkedList<char> result = topoSorter.sort(TopoSorter<char>::DFS);

    //! expect ----------------------------------
    string expect = "DFS Topological Sort: E->D->X->C->G->F->Y->V->A->B->NULL";
    //! output ----------------------------------
    output << "DFS Topological Sort: ";
    for (auto it = result.begin(); it != result.end(); it++)
    {
        output << *it << "->";
    }
    output << "NULL";

    //! remove data -----------------------------
    model.clear();

    //! result ----------------------------------
    return printResult(output.str(), expect, name);
}
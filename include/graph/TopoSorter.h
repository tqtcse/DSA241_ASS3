/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TopoSorter.h
 * Author: ltsach
 *
 * Created on July 11, 2021, 10:21 PM
 */

#ifndef TOPOSORTER_H
#define TOPOSORTER_H
#include "stacknqueue/Queue.h"
#include "stacknqueue/Stack.h"
#include "graph/DGraphModel.h"
#include "list/DLinkedList.h"
#include "sorting/DLinkedListSE.h"
#include "hash/xMap.h"
template <class T, class V>
using XHashMap = xMap<T, V>;
template<class T>
class TopoSorter{
public:
    static int DFS;
    static int BFS; 
    
protected:
    DGraphModel<T>* graph;
    int (*hash_code)(T&, int);
    
public:
    TopoSorter(DGraphModel<T>* graph, int (*hash_code)(T&, int)=0){
        this->graph = graph;
        this->hash_code = hash_code;
    }   
    DLinkedList<T> sort(int mode=0, bool sorted=true){
        if(mode == 0){
        	return dfsSort(sorted);
        } else {
        	return bfsSort(sorted);
        }
    }
    DLinkedList<T> bfsSort(bool sorted=true) {
	    DLinkedList<T> result;
	    Queue<T> queue;  // Hàng đợi để lưu các đỉnh có độ vào bằng 0

	    // Khởi tạo map độ vào (in-degree) cho tất cả các đỉnh
	    XHashMap<T, int> inDegree(hash_code);
	    for (T vertex : graph->vertices()) {
	        inDegree.put(vertex, 0); // Ban đầu, độ vào của tất cả các đỉnh là 0
	    }

	    // Tính toán độ vào (in-degree) cho từng đỉnh
	    for (T vertex : graph->vertices()) {
	    	// Lấy các đỉnh kề
	        DLinkedList<T> neighbors = graph->getOutwardEdges(vertex); 
	        for (T neighbor : neighbors) {
	        	// Tăng độ vào của các đỉnh kề
	            inDegree.put(neighbor, inDegree.get(neighbor) + 1); 
	        }
	    }

	    // Thêm các đỉnh có độ vào bằng 0 vào hàng đợi
	    for (T vertex : graph->vertices()) {
	        if (inDegree.get(vertex) == 0) {
	            queue.push(vertex);
	        }
	    }

	    // Duyệt qua đồ thị với BFS
	    while (!queue.empty()) {
	        T vertex = queue.pop();  // Lấy đỉnh ra từ hàng đợi
	        result.add(result.size(), vertex); // Thêm vào kết quả

	        // Duyệt qua các đỉnh kề của vertex
	        DLinkedList<T> neighbors = graph->getOutwardEdges(vertex);
	        for (T neighbor : neighbors) {
	            // Giảm độ vào của các đỉnh kề
	            inDegree.put(neighbor, inDegree.get(neighbor) - 1);

	            // Nếu độ vào của một đỉnh kề trở thành 0, thêm nó vào hàng đợi
	            if (inDegree.get(neighbor) == 0) {
	                queue.push(neighbor);
	            }
	        }
	    }

	    return result;  // Trả về danh sách kết quả theo thứ tự topo
}


    DLinkedList<T> dfsSort(bool sorted=true) {
    Stack<T> dfsStack;
    DLinkedList<T> result;

    XHashMap<T, bool> visited(hash_code);
    for (T vertex : graph->vertices()) {
        visited.put(vertex, false);
    }

    for (T vertex : graph->vertices()) {
        if (!visited.get(vertex)) {
            dfsStack.push(vertex);
            visited.put(vertex, true);

            while (!dfsStack.empty()) {
                T w_ver = dfsStack.peek();  
                DLinkedList<T> n_vers = graph->getOutwardEdges(w_ver);  
                bool hasUnvisitedNeighbor = false;

                for (T n_ver : n_vers) {
                    if (!visited.get(n_ver)) {
                        dfsStack.push(n_ver);  
                        visited.put(n_ver, true); 
                        hasUnvisitedNeighbor = true;
                        break;  
                    }
                }

                if (!hasUnvisitedNeighbor) {
                    result.add(0, dfsStack.pop());
                }
            }
        }
    }

    return result;  
}

protected:

    //Helper functions
    XHashMap<T, int> vertex2inDegree(int (*hash)(T&, int)){
    	XHashMap<T, int> inDegrees(hash);
    	for(T vertex : graph->vertices()){
    		inDegrees.put(vertex, 0);
    	}
    	for(T vertex : graph->vertices()){
    		for (T neighbor : graph->getOutwardEdges(vertex)) {
            inDegrees.put(neighbor, inDegrees.get(neighbor) + 1);
        	}
    	}
    	return inDegrees;
    }
    XHashMap<T, int> vertex2outDegree(int (*hash)(T&, int)){

    }
    void dfsVisit(T vertex, XHashMap<T,bool>& visited, Stack<T>& resultStack){
        // visited.get(vertex) = true;
        visited.put(vertex, true);

        
        for (T neighbor : graph->getOutwardEdges(vertex)) {
            if (!visited.get(neighbor)) {
                dfsVisit(neighbor, visited, resultStack);
            }
        }
        
        resultStack.push(vertex);
    }
    DLinkedList<T> listOfZeroInDegrees(){
    	DLinkedList<T> zeroInDegreeList;
	    XHashMap<T, int> inDegrees = vertex2inDegree(hash_code);  // Get in-degrees
	    for (T vertex : graph->vertices()) {
	        if (inDegrees.get(vertex) == 0) {
	            zeroInDegreeList.add(vertex);
	        }
	    }
	    return zeroInDegreeList;
    }

}; //TopoSorter
template<class T>
int TopoSorter<T>::DFS = 0;
template<class T>
int TopoSorter<T>::BFS = 1;

/////////////////////////////End of TopoSorter//////////////////////////////////


#endif /* TOPOSORTER_H */


/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   UGraphModel.h
 * Author: LTSACH
 *
 * Created on 24 August 2020, 15:16
 */

#ifndef UGRAPHMODEL_H
#define UGRAPHMODEL_H

#include "graph/AbstractGraph.h"
// #include "stacknqueue/Queue.h"
// #include "stacknqueue/Stack.h"
// #include "hash/xMap.h"
// #include "sorting/DLinkedListSE.h"
// template <class T, class V>
// using XHashMap = xMap<T, V>;

//////////////////////////////////////////////////////////////////////
///////////// UGraphModel: Undirected Graph Model ////////////////////
//////////////////////////////////////////////////////////////////////

template <class T>
class UGraphModel : public AbstractGraph<T>
{
private:
public:
    // class UGraphAlgorithm;
    // friend class UGraphAlgorithm;

    UGraphModel(
        bool (*vertexEQ)(T &, T &),
        string (*vertex2str)(T &)) : AbstractGraph<T>(vertexEQ, vertex2str)
    {
    }

    void connect(T from, T to, float weight = 0)
    {
        typename AbstractGraph<T>::VertexNode* fromNode = this->getVertexNode(from);
        typename AbstractGraph<T>::VertexNode* toNode = this->getVertexNode(to);

        if (!fromNode) {
            throw VertexNotFoundException("vertex2str(*from)");
        }
        if (!toNode) {
            throw VertexNotFoundException("vertex2str(*to)");
        }
        typename AbstractGraph<T>::Edge* edge = fromNode->getEdge(toNode);
     
        if(edge){
            fromNode->removeTo(toNode);
            toNode->removeTo(fromNode);
        }
        if (from == to){
            fromNode->connect(toNode, weight);
        } else {
            fromNode->connect(toNode, weight);
            toNode->connect(fromNode, weight);
        }

    }
    void disconnect(T from, T to)
    {
        typename AbstractGraph<T>::VertexNode* fromNode = this->getVertexNode(from);
        typename AbstractGraph<T>::VertexNode* toNode = this->getVertexNode(to);
        if (!fromNode) {
            throw VertexNotFoundException("vertex2str(*from)");
        }
        if (!toNode) {
            throw VertexNotFoundException("vertex2str(*to)");
        }
        typename AbstractGraph<T>::Edge* edge = fromNode->getEdge(toNode);
        if (!edge) {
            throw EdgeNotFoundException("edge2Str(*edge)");
        }
        if (from == to){
            fromNode->removeTo(toNode);
        } else {
            fromNode->removeTo(toNode);
            toNode->removeTo(fromNode);
        }

    }
    void remove(T vertex)
    {
        typename AbstractGraph<T>::VertexNode* deleteNode = this->getVertexNode(vertex);

        if(!deleteNode){
            throw VertexNotFoundException("vertex2str(*vertex)");
        }

        typename DLinkedList<typename AbstractGraph<T>::VertexNode*>::Iterator it = this->nodeList.begin();
        while(it != this->nodeList.end()){
            typename AbstractGraph<T>::VertexNode* currentNode =  *it;
            typename AbstractGraph<T>::Edge* edge = currentNode->getEdge(deleteNode);
            if(edge){
                currentNode->removeTo(deleteNode);
                deleteNode->removeTo(currentNode);
            }
            ++it;
        }
        if(this->nodeList.removeItem(deleteNode)){
            delete deleteNode;
        }

    }
    static UGraphModel<T> *create(
        T *vertices, int nvertices, Edge<T> *edges, int nedges,
        bool (*vertexEQ)(T &, T &),
        string (*vertex2str)(T &))
    {
         UGraphModel<T>* graph = new UGraphModel<T>(vertexEQ, vertex2str);
         for (int i = 0; i < nvertices; ++i) {
            graph->add(vertices[i]);
         }

         for(int i = 0; i < nedges; i++){
            graph->connect(edges[i].from, edges[i].to, edges[i].weight);
         }
         return graph;
    }
};

#endif /* UGRAPHMODEL_H */
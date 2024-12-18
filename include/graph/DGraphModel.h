/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DGraphModel.h
 * Author: LTSACH
 *
 * Created on 23 August 2020, 19:36
 */

#ifndef DGRAPHMODEL_H
#define DGRAPHMODEL_H
#include "graph/AbstractGraph.h"
#include "stacknqueue/Queue.h"
#include "stacknqueue/Stack.h"
#include "hash/xMap.h"
#include "sorting/DLinkedListSE.h"
template <class T, class V>
using XHashMap = xMap<T, V>;

//////////////////////////////////////////////////////////////////////
///////////// GraphModel: Directed Graph Model    ////////////////////
//////////////////////////////////////////////////////////////////////


template<class T>
class DGraphModel: public AbstractGraph<T>{
private:
public:
    DGraphModel(
            bool (*vertexEQ)(T&, T&), 
            string (*vertex2str)(T&) ): 
        AbstractGraph<T>(vertexEQ, vertex2str){
    }
    
    void connect(T from, T to, float weight=0){
        typename AbstractGraph<T>::VertexNode* fromNode = this->getVertexNode(from);
        typename AbstractGraph<T>::VertexNode* toNode = this->getVertexNode(to);

        if(!toNode){
            // throw VertexNotFoundException(VertexNode(from, null, vertex2str).toString());
            throw VertexNotFoundException("vertex2str(*to)");
        }
        if(!fromNode){
            // throw VertexNotFoundException(VertexNode(null, to, vertex2str).toString());
            throw VertexNotFoundException("vertex2str(*from)");
        }
        typename AbstractGraph<T>::Edge* edge = fromNode->getEdge(toNode);
        if(edge){
            fromNode->removeTo(toNode);
        }

        fromNode->connect(toNode, weight);
    }
    void disconnect(T from, T to){
        typename AbstractGraph<T>::VertexNode* fromNode = this->getVertexNode(from);
        typename AbstractGraph<T>::VertexNode* toNode = this->getVertexNode(to);

        if(!toNode){
            // throw VertexNotFoundException(VertexNode(from, null, vertex2str).toString());
            throw VertexNotFoundException("vertex2str(*to)");
        }
        if(!fromNode){
            // throw VertexNotFoundException(VertexNode(null, to, vertex2str).toString());
            throw VertexNotFoundException("vertex2str(*from)");
        }

        typename AbstractGraph<T>::Edge* edge = fromNode->getEdge(toNode);
        if(!edge){
             throw EdgeNotFoundException("edge2Str(*edge)");
        }
        fromNode->removeTo(toNode);
        

    }
    void remove(T vertex){
        typename AbstractGraph<T>::VertexNode* deleteNode = this->getVertexNode(vertex);
        if(!deleteNode){
            throw VertexNotFoundException("vertex2str(*vertex)");
        }
        typename DLinkedList<typename AbstractGraph<T>::VertexNode*>::Iterator it = this->nodeList.begin();
        //xoa cac canh lien quan den nut
        while(it != this->nodeList.end()){
            typename AbstractGraph<T>::VertexNode* currentNode = *it;
            typename AbstractGraph<T>::Edge* edge = currentNode->getEdge(deleteNode);
            if(edge){
                currentNode->removeTo(deleteNode);

            }
            typename AbstractGraph<T>::Edge* edge2 = deleteNode->getEdge(currentNode);
            if(edge2){
                deleteNode->removeTo(currentNode);
            }
            ++it;
        }
 
        if(this->nodeList.removeItem(deleteNode)){
            delete deleteNode;
        }

    }
    
    static DGraphModel<T>* create(
            T* vertices, int nvertices, Edge<T>* edges, int nedges,
            bool (*vertexEQ)(T&, T&),
            string (*vertex2str)(T&)){
        DGraphModel<T>* graph = new DGraphModel<T>(vertexEQ, vertex2str);
        for(int i = 0; i < nvertices; i++){
            graph->add(vertices[i]);
        }
        for(int i = 0; i < nedges; i++){
            graph->connect(edges[i].from, edges[i].to, edges[i].weight);
        }
        return graph;
    }
};

#endif /* DGRAPHMODEL_H */

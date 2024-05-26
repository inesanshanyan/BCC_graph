#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

#include <algorithm>
#include <list>
#include <vector>
#include <stack>

#define NIL -1
extern int count;

class Edge {
public:
	int u, v;
	Edge(int u, int v) {
	    this->u = u;
	    this->v = v;
    }
};

class Graph {
public:
    Graph(int); 
    ~Graph();

	void addEdge(int, int);

    void insertGraph(const std::string&);
    void drawGraph(const std::string&);
    void generateGraph(const std::string&);

    void print();
    void printBlocks();

    void BCCUtil(int, int[], int[], std::list<Edge>*, int[]);
    void BCC();
    void removeDuplicates(std::vector<int>&);

    void drawBlocks(const std::string&);
    

private:
    int V = 0; 
	int E = 0; 
	std::list<int>* adj;
    std::vector<int> edges;
    std::vector<std::vector<int>> blocks;
    std::vector<int> currentBlock;
    
};




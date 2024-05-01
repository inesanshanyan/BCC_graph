#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

class Graph {
public:
    Graph(int);
    void inputGraph();
    void drawGraph(const std::string&, const std::vector<std::vector<int>>&);
    void generateGraph(const std::string&);
    void findBlocks();
private:
    int vertices;
    std::vector<std::vector<int>> adjMatrix;
    std::vector<std::vector<int>> blockAdjMatrix;
};


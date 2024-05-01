#include "../include/graph.hpp"

Graph::Graph(int vertices_):vertices(vertices_){
    adjMatrix.resize(vertices, std::vector<int>(vertices, 0));
}

void Graph::inputGraph(){
    std::cout << "Enter matrix elements:" << std::endl;
    for (int i = 0; i < adjMatrix.size(); ++i) {
        for (int j = 0; j < adjMatrix[0].size(); ++j) {
            std::cout << "(" << i << ", " << j << "): ";
            std::cin >> adjMatrix[i][j];
            if(adjMatrix[i][j] != 0 && adjMatrix[i][j] != 1){
                std::cout << "Enter 0 or 1";
                --j;
            } 
        }
    }
    drawGraph("inputGraph.dot", adjMatrix);
}

void Graph::drawGraph(const std::string& filename, const std::vector<std::vector<int>>& matrix){
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    outfile << "graph G {" <<std:: endl;
    for (int i = 0; i < vertices; ++i) {
        for (int j = i + 1; j < vertices; ++j) {
            if (adjMatrix[i][j] == 1) {
                outfile << i << " -- " << j << ";" << std::endl;
            }
        }
    }
    outfile << "}" << std::endl;
    outfile.close();
    std::cout << "DOT file generated: " << filename << std::endl;

    generateGraph(filename);
}

void Graph::generateGraph(const std::string& filename){
    std::string command = "dot -Tpng " + filename + " -o " + filename + ".png";
        int status = std::system(command.c_str());
        if (status != 0) {
            std::cerr << "Error generating graph PNG image." << std::endl;
        } else {
            std::cout << "Graph PNG image generated: " << filename << ".png" << std::endl;
        }
}
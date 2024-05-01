#include <iostream>
#include "../include/graph.hpp"

int main(){
    int vertexNumber;
    std::cout<<"Enter the number of vertices: ";
    std::cin>>vertexNumber;
    Graph graph(vertexNumber);
    graph.inputGraph();
    return 0;
}
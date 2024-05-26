#include "./include/graph.hpp"

int main(){
    Graph g(7);
    g.insertGraph("graph.txt");
    //g.print();
    g.BCC();
    g.printBlocks();
}
#include "./include/graph.hpp"

int main(){
    Graph g(21);
    g.insertGraph("graph.txt");
    g.print();
    g.BCC();
    //g.printBlocks();
}
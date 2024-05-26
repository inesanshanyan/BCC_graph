#include "../include/graph.hpp"

int count = 0;

Graph::Graph(int v) : V(v), E(0) {
    adj = new std::list<int>[V];
}

Graph::~Graph() {
    delete[] adj;
}

void Graph::addEdge(int v, int u) {
    
    adj[v].push_back(u);
    adj[u].push_back(v);
    edges.push_back(v);
    edges.push_back(u);
    E += 2;
}

void Graph::insertGraph(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return;
    }

    std::string line;
    int u, v;
    std::cout << "\nInsert graph: \n";
    while (getline(file, line)) {
        std::istringstream iss(line);
        if (iss >> u >> v) {
            std::cout << "Adding edge: " << u << " " << v << std::endl;
            addEdge(u, v);
        } else {
            std::cerr << "Failed to parse line: " << line << std::endl;
        }
    }

    file.close();
    this->drawGraph("inputGraph.dot");
}

void Graph::drawGraph(const std::string& filename) {
    if (adj == nullptr) {
        std::cerr << "Adjacency list is empty. Nothing to draw" << std::endl;
        return;
    }

    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    outfile << "graph G {" << std::endl;
    for (auto i = 0; i < edges.size() - 1; i += 2) {
        outfile << edges[i] << " -- " << edges[i + 1] << ";" << std::endl;
    }
    outfile << "}\n";
    outfile.close();
    std::cout << "DOT file generated: " << filename << std::endl;

    generateGraph(filename);
}

void Graph::generateGraph(const std::string& filename) {
    std::string output_filename = filename + ".png";
    std::string command = "dot -Tpng " + filename + " -o " + output_filename;
    int status = std::system(command.c_str());
    if (status != 0) {
        std::cerr << "Error generating graph PNG image." << std::endl;
    } else {
        std::cout << "Graph PNG image generated: " << output_filename << std::endl;
    }
}

void Graph::print() {
    std::cout << "Printing graph:" << std::endl;
    if (adj != nullptr) {
        for (int v = 0; v < V; v++) {
            std::cout << "Adjacency list of vertex " << v << ": ";
            for (const auto& element : adj[v]) {
                std::cout << element << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "Edges: ";
        for (int el : edges) {
            std::cout << el << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Adjacency list is empty." << std::endl;
    }
}


void Graph::BCCUtil(int u, int disc[], int low[], std::list<Edge>* st, int parent[])
{
	static int time = 0;
	disc[u] = ++time;
    low[u] = ++time;
	int children = 0;

	std::list<int>::iterator i;
	for (i = adj[u].begin(); i != adj[u].end(); ++i) {
		int v = *i; 
		if (disc[v] == -1) {
			children++;
			parent[v] = u;
			
            st->push_back(Edge(u, v));
			BCCUtil(v, disc, low, st, parent);

			low[u] = std::min(low[u], low[v]);

			if ((disc[u] == 1 && children > 1) || (disc[u] > 1 && low[v] >= disc[u])) {
				while (st->back().u != u || st->back().v != v) {
					//std::cout << st->back().u << "--" << st->back().v << " ";
                    currentBlock.push_back(st->back().u);
                    currentBlock.push_back(st->back().v);
					st->pop_back();
				}
				//std::cout << st->back().u << "--" << st->back().v;
                currentBlock.push_back(st->back().u);
                currentBlock.push_back(st->back().v);
				st->pop_back();
                removeDuplicates(currentBlock);
                blocks.push_back(currentBlock);
                currentBlock.clear();
				std::cout << std::endl;
				count++;
			}
		}

		else if (v != parent[u]) {
			low[u] = std::min(low[u], disc[v]);
			if (disc[v] < disc[u]) {
				st->push_back(Edge(u, v));
			}
		}
	}
}

void Graph::BCC()
{
	int* disc = new int[V];
	int* low = new int[V];
	int* parent = new int[V];
	std::list<Edge>* st = new std::list<Edge>[E];
    
	for (int i = 0; i < V; i++) {
		disc[i] = NIL;
		low[i] = NIL;
		parent[i] = NIL;
	}

	for (int i = 0; i < V; i++) {
		if (disc[i] == NIL)
			BCCUtil(i, disc, low, st, parent);

		int j = 0;
		while (st->size() > 0) {
			j = 1;
			//std::cout << st->back().u << "--" << st->back().v << " ";
            currentBlock.push_back(st->back().u);
            currentBlock.push_back(st->back().v);
			st->pop_back();
		}
		if (j == 1) {
            removeDuplicates(currentBlock);
            blocks.push_back(currentBlock);
            currentBlock.clear();
			std::cout << std::endl;
			count++;
		}
	}
    drawBlocks("blockGraph.dot");
}

void Graph::printBlocks(){
    std::cout<<"\nBlocks";
    for(const auto& row : blocks){
        for(const auto& col : row){
            std::cout<<col<<" ";
        }
        std::cout<<std::endl;
    }
}

void Graph::removeDuplicates(std::vector<int>& vec) {
    std::sort(vec.begin(), vec.end());
    auto last = std::unique(vec.begin(), vec.end());
    vec.erase(last, vec.end());
}

void Graph::drawBlocks(const std::string& filename){
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    outfile << "graph G {" << std::endl;
    for(auto row = blocks.begin(); row != blocks.end(); ++row) {
        for(const auto& col : *row) {
            for(auto row2 = row + 1; row2 != blocks.end(); ++row2) {
                auto it = std::find(row2->begin(), row2->end(), col);
                if (it != row2->end()) {
                    for (const auto& element : *row) {
                        outfile << element;
                    }
                    outfile << " -- ";
                    for (const auto& element : *row2) {
                        outfile << element;
                    }
                    outfile << std::endl;
                }
            }
        }
    }


    outfile << "}\n";
    outfile.close();
    std::cout << "Block Dot file generated: " << filename << std::endl;

    generateGraph(filename);
}
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

//Author: Zeynep Taskin 33851
//Date: 31.12.2024 
//Purpose: This program cheks if graphs are bipartate then find the max matching number in bipartite graphs.

struct node {//structure to hold the vertices
	string name;//name of thertex
	node* connectedVertices;//vertices connected to the vertex
	node(string n = "", node* cV = nullptr) :name(n), connectedVertices(cV) {};
};

bool isBipartite(vector<bool>& bipartite1, vector<bool>& bipartite2, vector<node*> graph) {// function to check if a graph is bipartite
	bool bipartite = true;//bool to determine bipartite

	for (int i = 0; i < graph.size(); i++) {//get every vertex
		if (graph[i] != nullptr) {//if vertex exists
			if (!bipartite1[i]) {
				if (!bipartite2[i]) {
					//if vertex is not in any side
					bipartite1[i] = true;//add the vertex to the left side
					node* temp = graph[i]->connectedVertices;//get the vetices connected
					while (temp != nullptr) {
						if (!bipartite1[stoi(temp->name)]) {
							if (!bipartite2[stoi(temp->name)]) {
								//if vertex is not in any side
								bipartite2[stoi(temp->name)] = true;// add it to the right side
							}
						}
						else {//if it is in the same side 
							bipartite = false;//the graph is not bipartite
							return bipartite;
						}
						temp = temp->connectedVertices;//get the next vertex connected
					}
				}
				else {
					//the vertex is in the right side
					node* temp = graph[i]->connectedVertices;//get the connected vertices
					while (temp != nullptr) {
						if (!bipartite2[stoi(temp->name)]) {
							if (!bipartite1[stoi(temp->name)]) {
								//if vertex is not in any side
								bipartite1[stoi(temp->name)] = true;// add it to the left side

							}
						}
						else {//if it is in the same side 
							bipartite = false;//the graph is not bipartite
							return bipartite;
						}
						temp = temp->connectedVertices;//get the next vertex connected
					}
				}
			}
			else {
				//the vertex is in the left side
				node* temp = graph[i]->connectedVertices;//get the connected vertices
				while (temp != nullptr) {
					if (!bipartite1[stoi(temp->name)]) {
						if (!bipartite2[stoi(temp->name)]) {
							//if vertex is not in any side
							bipartite2[stoi(temp->name)] = true;// add it to the right side
						}
					}
					else {//if it is in the same side 
						bipartite = false;//the graph is not bipartite
						return bipartite;
					}
					temp = temp->connectedVertices;//get the next vertex connected
				}
			}
		}
	}
	return bipartite;
}

int maxMatching(vector<node*> g, vector<bool>& bipartite1) {//function to find the max matching in a bipartite graph
	int maxMatch = 0;//integer to hold the max match
	vector<int> path(g.size(), -1);//vector to hold the path of matched vertices
	for (int i = 1; i < g.size(); i++) {
		if (bipartite1[i] && g[i] != nullptr) {//check the vertices in the left side
			node* t = g[i]->connectedVertices;//get the connected vertex
			while (t != nullptr && path[stoi(t->name)] != -1) {//if there is a connected vertex and it is matched
				t = t->connectedVertices;//go to the next connected vertex
			}
			if (t != nullptr) {//if vertex exists and is not matched
				path[stoi(t->name)] = stoi(g[i]->name);//match the vertices
				maxMatch++;//increase the max matching
			}
			else {//if there is no available match
				vector<bool> visit(g.size(), false);//create a visit vector to not visit a vertex more than once
				vector<int> stack;//stack to hold the vertices that can be unmatched
				stack.push_back(i);//push the vertex

				while (!stack.empty()) {//if there is vertex to match
					int current = stack.back();//get the current unmatched vertex from the stack
					stack.pop_back();//remove from the stack
					if (!visit[current]) {//if the vertex is not visited
						visit[current] = true;//make the vertex match
						node* temp = g[current]->connectedVertices;//get the connected vertex
						while (temp != nullptr) {
							int v = stoi(temp->name);
							if (path[v] == -1) {//if the vertex is not matched
								path[v] = current;//match it to the unmatched vertex
								maxMatch++;//increase the max match
								stack.clear();//clear the stack
								break;//go to the next node
							}
							else {//if the vertex is matched
								if (!visit[path[v]]) {
									stack.push_back(path[v]);//push the vertex to the stack
								}
							}
							temp = temp->connectedVertices;//go to the next connected vertex
						}
					}
				}
			}
		}
	}
	return maxMatch;//return the max match
}



int main() {

	string graphName;//input graph name
	string read;//string to get the numbers in txt file
	string nextNode;//string to hold the connected vertex name
	cout << "Enter the graph name (e.g., 'graph1' or 'exit' to terminate): ";
	cin >> graphName;//get the input file
	while (graphName != "exit") {//until the exit is inputted
		ifstream graphFile;
		graphName = graphName + ".txt";//create the graphs name
		graphFile.open(graphName);//open the file
		graphFile >> read;//read the number of vertices
		vector<node*> graph(stoi(read), nullptr);//create the vector to hold the graph as adjacency list
		graphFile >> read;//read the number of edges
		int edgeCount = stoi(read);
		string vertexName;//string to hold the vertex's name

		for (int i = 0; i < edgeCount; i++) {//read each edge
			graphFile >> read;//get the vertex
			graphFile >> nextNode;//get the connected vertex
			node* nextN = new node(nextNode);//connected vertex node
			if (graph[stoi(read)] != nullptr && graph[stoi(read)]->name == read) {//if the vertex already in the graph
				node* temp = graph[stoi(read)];
				while (temp->connectedVertices != nullptr) {//go to the end of the adjacency list of the vertex
					temp = temp->connectedVertices;
				}
				temp->connectedVertices = nextN;//add the connected vertex to the list of the main vertex
			}
			else {//if the vertex is npt in  the graph
				vertexName = read;
				node* vertex = new node(vertexName, nextN);
				graph[stoi(read)] = vertex;//add it to the vertex
			}

		}
		graphFile.close();//close the file
		vector<bool> bipartite1(graph.size(), false);//left side of the bipartite graph
		vector <bool>bipartite2(graph.size(), false);//right side of the bipartite graph

		bool bipartite = isBipartite(bipartite1, bipartite2, graph);//check if the graph is bipartite
		if (!bipartite) {
			cout << "The graph is not bipartite." << endl;
		}
		else {//if it is bipartite
			cout << "The graph is bipartite." << endl;
			for (int i = 0; i < graph.size(); i++) {//add the right side to the graph as well
				if (bipartite1[i]) {//find left side vertices
					node* temp = graph[i];
					if (temp != nullptr) {
						node* temp2 = graph[i]->connectedVertices;//get the right side vertex
						while (temp2 != nullptr) {
							if (graph[stoi(temp2->name)] == nullptr) {//if the vertex is not in the graph
								graph[stoi(temp2->name)] = new node;//create a node
								graph[stoi(temp2->name)]->connectedVertices = new node(temp->name);//add the left side as a connected vertex
								graph[stoi(temp2->name)]->name = temp2->name;//assign the name of the right side vertex to the graph position
								temp2 = temp2->connectedVertices;//go to the next vertex
							}
							else {//if vertex is already in the graph
								node* t = graph[stoi(temp2->name)]->connectedVertices;//get the connected vertex
								while (t->connectedVertices != nullptr) {//go to the end of the adjacency list
									t = t->connectedVertices;
								}
								t->connectedVertices = new node(temp->name);//add to the end of the list
								temp2 = temp2->connectedVertices;// go to the next vertex

							}

						}
					}
				}
			}
			int maxMatchNo = maxMatching(graph, bipartite1);//find the max matching
			cout << "Maximum matching size: " << maxMatchNo << endl;
		}
		for (int i = 0; i < graph.size();i++) {
			//deallocate the dynamically allocated memory in graph
			delete graph[i];
		}
		
		cout << "Enter the graph name (e.g., 'graph1' or 'exit' to terminate): ";
		cin >> graphName;//get the next graph
	}
	
	return 0;
}
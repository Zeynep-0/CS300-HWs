#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>
#include <iostream>
using namespace std;

//Author: Zeynep Taskin 33851
//Date: 17.11.2024
//Header file of the quadtree class

struct QuadNode {// structure to hold the quadtree nodes
	QuadNode* NW;// pointer to the north-west node of the node
	QuadNode* NE;// pointer to the north-east node of the node
	QuadNode* SW;// pointer to the south-west node of the node
	QuadNode* SE;// pointer to the south-east node of the node
	int xCoord;// x coordinate of the node
	int yCoord;// y coordinate of the node
	string name;// name of the node
	QuadNode() {// constructor of the quad node
		name = "";
		NW = nullptr;
		NE = nullptr;
		SE = nullptr;
		SW = nullptr;
		xCoord = 0;
		yCoord = 0;
	}
};

class QuadTree {
	
private:
	QuadNode* root;// pointer to the root node of the tree
	QuadNode* getSon(QuadNode* P, string I);// function to get the specific quadrant node of a node
	void insertSon(QuadNode*& P, QuadNode*& father, string quadrant);// function to insert a node to the specific quadrant of a node
public:
	QuadTree();// constructor
	~QuadTree();// destructor
	void deleteSubtree(QuadNode* P);// function to delete a subtree
	QuadNode* get_root();// function to get the root of the quad tree
	void pretty_print(QuadNode* root);// function to recursively print the tree
	string pt_Compare(QuadNode* P, QuadNode* root);// function to compare two quadnodes based on their coordinates
	void pt_Insert(QuadNode P);// function to insert a quadnode to the tree
	double distanceBetween(int x, int y, QuadNode* P);// function to calculate the distance between the given coordinates and a quadnode
	/* function to calculate which quadrants should be checked for the 
	given nodes position in relation to given coordinates and radius*/
	vector<string> whichQuadrants(int x, int y, int r, QuadNode* P);
	vector<string> citiesInTheArea(string quadrant, int x, int y, int r, QuadNode* P, vector<string>& searchPath, vector<string>& foundCities);// function to recursively check if a node is in the searched area

};

#endif
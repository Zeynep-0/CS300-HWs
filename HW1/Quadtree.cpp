#include "Quadtree.h"

//Author: Zeynep Taskin 33851
//Date: 17.11.2024
//Implementation file of the quadtree class

QuadNode* QuadTree::getSon(QuadNode* P, string I) {// function to get the specific quadrant node of a node
	if (I == "NW") {// check which quadrant is wanted
		return P->NW;// return wanted quadrant's node
	}
	else if (I == "NE") {
		return P->NE;
	}
	else if (I == "SW") {
		return P->SW;
	}
	else if (I == "SE") {
		return P->SE;
	}
}
void QuadTree::insertSon(QuadNode*& P, QuadNode*& father, string quadrant) {// function to insert a node to the specific quadrant of another node
	if (quadrant == "SE") {// check which quadrant is wanted
		father->SE = P;// insert the node into that quadrant of the given node (father)
	}
	else if (quadrant == "SW") {
		father->SW = P;
	}
	else if (quadrant == "NE") {
		father->NE = P;
	}
	else if (quadrant == "NW") {
		father->NW = P;
	}
}
QuadTree::QuadTree() {// constructor
	root = nullptr;
}
QuadTree::~QuadTree() {// destructor
	deleteSubtree(root);
}
void QuadTree::deleteSubtree(QuadNode* P) {// function to delete a subtree
	if (P == nullptr) {//if node is not null
		return;
	}
	deleteSubtree(P->SE);//recursively get the subtrees
	deleteSubtree(P->SW);
	deleteSubtree(P->NE);
	deleteSubtree(P->NW);
	delete P;//delete the node
}
QuadNode* QuadTree::get_root() {// function to get the root of the quad tree
	return root;
}
void QuadTree::pretty_print(QuadNode* root) {// function to recursively print the tree
	if (root != NULL) {
		cout << root->name << endl;// print the name of the city
		pretty_print(root->SE);// go to the all subtree of the node
		pretty_print(root->SW);
		pretty_print(root->NE);
		pretty_print(root->NW);
	}
}
string QuadTree::pt_Compare(QuadNode* P, QuadNode* root) {// function to compare two quadnodes based on their coordinates
	if (root->xCoord <= P->xCoord && root->yCoord > P->yCoord) {//compare the x and y coordinates and determine which quadrant P node belong relative to root node
		return "SE";
	}
	else if (root->xCoord > P->xCoord && root->yCoord > P->yCoord) {
		return "SW";
	}
	else if (root->xCoord <= P->xCoord && root->yCoord <= P->yCoord) {
		return "NE";
	}
	else if (root->xCoord > P->xCoord && root->yCoord <= P->yCoord) {
		return "NW";
	}
}
void QuadTree::pt_Insert(QuadNode P) {// function to insert a quadnode to the tree
	QuadNode* T = new QuadNode;// create a temporary node pointer
	T->name = P.name;// assign node's values to temporary node
	T->xCoord = P.xCoord;
	T->yCoord = P.yCoord;
	if (root == nullptr) {// if there is no node in the tree
		root = T;// make the root the node
	}
	else {// if there are nodes in the tree
		QuadNode* temp = root;
		QuadNode* father;
		string quadrant;
		while (temp != nullptr) {// until there is no node in the found position
			father = temp;
			quadrant = pt_Compare(T, temp);// compare the nodes and get the quadrant new node belong to
			temp = getSon(temp, quadrant);// check if there is a node in the found quadrant
		}
		if (temp == nullptr) {// if the found position is empty
			insertSon(T, father, quadrant);// insert the node to the position
		}
	}
}
double QuadTree::distanceBetween(int x, int y, QuadNode* P) {// function to calculate the distance between the given coordinates and a quadnode
	double distance = sqrt(pow(x - P->xCoord, 2) + pow(y - P->yCoord, 2));// calculate the distance using the coordinates
	return distance;
}
/* function to calculate which quadrants should be checked for the 
qiven nodes position in relation to given coordinates and radius */
vector<string> QuadTree::whichQuadrants(int x, int y, int r, QuadNode* P) {
	vector<string> quadrants;// create a vector to hold quadrants that will be searched
	//cases in figure 2.17
	if (x - r > P->xCoord && y + r < P->yCoord) {// if it is the 1st case 
		quadrants.push_back("SE");
	}
	else if (x + r > P->xCoord && x - r < P->xCoord && y + r < P->yCoord) {// if it is the 2nd case
		quadrants.push_back("SE");
		quadrants.push_back("SW");
	}
	else if (x + r < P->xCoord && y + r < P->yCoord) {// if it is the 3rd case
		quadrants.push_back("SW");
	}
	else if (x - r > P->xCoord && y - r < P->yCoord && y + r > P->yCoord) {// if it is the 4th case
		quadrants.push_back("SE");
		quadrants.push_back("NE");
	}
	else if (x + r < P->xCoord && y - r < P->yCoord && y + r > P->yCoord) {// if it is the 5th case
		quadrants.push_back("SW");
		quadrants.push_back("NW");
	}
	else if (x - r > P->xCoord && y - r > P->yCoord) {// if it is the 6th case
		quadrants.push_back("NE");
	}
	else if (x + r > P->xCoord && x - r < P->xCoord && y - r > P->yCoord) {// if it is the 7th case
		quadrants.push_back("NE");
		quadrants.push_back("NW");
	}
	else if (x + r < P->xCoord && y - r > P->yCoord) {// if it is the 8th case
		quadrants.push_back("NW");
	}
	else if (distanceBetween(x, y, P) > r && x > P->xCoord && y < P->yCoord) {// if it is the 9th case
		quadrants.push_back("SE");
		quadrants.push_back("SW");
		quadrants.push_back("NE");
	}
	else if (distanceBetween(x, y, P) > r && x < P->xCoord && y < P->yCoord) {// if it is the 10th case
		quadrants.push_back("SE");
		quadrants.push_back("SW");
		quadrants.push_back("NW");
	}
	else if (distanceBetween(x, y, P) > r && x > P->xCoord && y > P->yCoord) {// if it is the 11th case
		quadrants.push_back("SE");
		quadrants.push_back("NE");
		quadrants.push_back("NW");
	}
	else if (distanceBetween(x, y, P) > r && x < P->xCoord && y > P->yCoord) {// if it is the 12th case
		quadrants.push_back("SW");
		quadrants.push_back("NE");
		quadrants.push_back("NW");
	}
	else if (distanceBetween(x, y, P) <= r) {// if it is the 13th case
		quadrants.push_back("SE");
		quadrants.push_back("SW");
		quadrants.push_back("NE");
		quadrants.push_back("NW");
	}
	//edge cases
	else if (x > P->xCoord && x - r < P->xCoord && y + r == P->yCoord) {// case A
		quadrants.push_back("SE");
		quadrants.push_back("SW");
		quadrants.push_back("NE");
	}
	else if (x < P->xCoord && x + r > P->xCoord && y + r == P->yCoord) {// case B
		quadrants.push_back("SE");
		quadrants.push_back("SW");
		quadrants.push_back("NW");
	}
	else if (y < P->yCoord && y + r > P->yCoord && x + r == P->xCoord) {//case C
		quadrants.push_back("SE");
		quadrants.push_back("SW");
		quadrants.push_back("NW");
	}
	else if (y > P->yCoord && y - r < P->yCoord && x + r == P->xCoord) {//case D
		quadrants.push_back("SW");
		quadrants.push_back("NE");
		quadrants.push_back("NW");
	}
	else if (x < P->xCoord && x + r > P->xCoord && y - r == P->yCoord) {//case E
		quadrants.push_back("NE");
		quadrants.push_back("NW");
	}
	else if (x > P->xCoord && x - r < P->xCoord && y - r == P->yCoord) {//case F
		quadrants.push_back("NE");
		quadrants.push_back("NW");
	}
	else if (y > P->yCoord && y - r < P->yCoord && x - r == P->xCoord) {//case G
		quadrants.push_back("SE");
		quadrants.push_back("NE");
	}
	else if (y < P->yCoord && y + r > P->yCoord && x - r == P->xCoord) {//case I
		quadrants.push_back("SE");
		quadrants.push_back("NE");
	}
	else if (x + r < P->xCoord && y + r == P->yCoord) {//case P
		quadrants.push_back("SW");
		quadrants.push_back("NW");
	}
	else if (x + r < P->xCoord && y - r == P->yCoord) {//case R
		quadrants.push_back("NW");
	}
	else if (x + r == P->xCoord && y - r > P->yCoord) {//case J
		quadrants.push_back("NE");
		quadrants.push_back("NW");
	}
	else if (x - r == P->xCoord && y - r > P->yCoord) {//case K
		quadrants.push_back("NE");
	}
	else if (x - r > P->xCoord && y - r == P->yCoord) {//case L
		quadrants.push_back("NE");
	}
	else if (x - r > P->xCoord && y + r == P->yCoord) {//case M
		quadrants.push_back("SE");
		quadrants.push_back("NE");
	}
	else if (x - r == P->xCoord && y + r < P->yCoord) {//case N
		quadrants.push_back("SE");
	}
	else if (x + r == P->xCoord && y + r < P->yCoord) {//case O
		quadrants.push_back("SE");
		quadrants.push_back("SW");
	}
	else if (x - r == P->xCoord && y + r == P->yCoord) {//case X
		quadrants.push_back("SE");
		quadrants.push_back("NE");
	}
	else if (x + r == P->xCoord && y + r == P->yCoord) {//case Y
		quadrants.push_back("SE");
		quadrants.push_back("SW");
		quadrants.push_back("NW");
	}
	else if (x + r == P->xCoord && y - r == P->yCoord) {//case Z
		quadrants.push_back("NE");
		quadrants.push_back("NW");
	}
	else if (x - r == P->xCoord && y - r == P->yCoord) {//case W
		quadrants.push_back("NE");
	}
	return quadrants;
}
vector<string> QuadTree::citiesInTheArea(string quadrant, int x, int y, int r, QuadNode* P, vector<string>& searchPath, vector<string>& foundCities) {// function to recursively check if a node is in the searched area

	vector < string> temp;// temporary string to hold quadrants
	if (quadrant == "SE") {// if the quadrant to be searched is south east
		if (P->SE != nullptr) {// if there is a node in the south east quadrant of the node
			P = P->SE;// get the SE quadrant node
			if (distanceBetween(x, y, P) <= r) {// check if the node is in the searched area
				foundCities.push_back(P->name);// add to the found cities list
			}
			searchPath.push_back(P->name);// add the node to the searched cities list

			temp = whichQuadrants(x, y, r, P);// get the quadrants of the node to be searched
			for (int i = 0; i < temp.size(); i++) {// go through each found quadrant recursively
				citiesInTheArea(temp[i], x, y, r, P, searchPath, foundCities); 
			}
		}
	}
	else if (quadrant == "SW") {// if the quadrant to be searched is south west do the same things as the south east quadrant
		if (P->SW != nullptr) {
			P = P->SW;
			if (P != nullptr) {
				if (distanceBetween(x, y, P) <= r) {
					foundCities.push_back(P->name);
				}
				searchPath.push_back(P->name);

				temp = whichQuadrants(x, y, r, P);
				for (int i = 0; i < temp.size(); i++) {
					citiesInTheArea(temp[i], x, y, r, P, searchPath, foundCities);
				}
			}
		}
	}
	else if (quadrant == "NE") {// if the quadrant to be searched is north east do the same things as the south east quadrant
		if (P->NE != nullptr) {
			P = P->NE;
			if (distanceBetween(x, y, P) <= r) {
				foundCities.push_back(P->name);
			}
			searchPath.push_back(P->name);

			temp = whichQuadrants(x, y, r, P);
			for (int i = 0; i < temp.size(); i++) {
				citiesInTheArea(temp[i], x, y, r, P, searchPath, foundCities);
			}
		}
	}
	else if (quadrant == "NW") {// if the quadrant to be searched is north west do the same things as the south east quadrant
		if (P->NW != nullptr) {
			P = P->NW;
			if (distanceBetween(x, y, P) <= r) {
				foundCities.push_back(P->name);
			}
			searchPath.push_back(P->name);

			temp = whichQuadrants(x, y, r, P);
			for (int i = 0; i < temp.size(); i++) {
				citiesInTheArea(temp[i], x, y, r, P, searchPath, foundCities);
			}
		}
	}
	return searchPath;
}

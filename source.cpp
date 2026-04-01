#include <iostream>
#include <fstream>
#include <string>
#include "Quadtree.h"
using namespace std;

//Author: Zeynep Taskin 33851
//Date: 17.11.2024 
//Purpose: This program creates a quadtree with given cities and finds the cities in a given radius.

int main() { 

	QuadTree quadTree;// quadtree to hold the cities
	fstream cityFile;// city file
	cityFile.open("cities0.txt");// open the file that holds the cities names
	string readFile;
	cityFile >> readFile;// read the x coordinate of the upper right corner of the space
	cityFile >> readFile;// read the y coordinate of the upper right corner of the space

	QuadNode* temp;// create a temporary quadnode to add cities to the quadtree
	while (cityFile >> readFile) {//read the city's name until the end of the file
		temp=new QuadNode;
		temp->name = readFile;// assign the name to the temp node
		cityFile >> readFile;// read the city's x coordinate
		temp->xCoord = stoi(readFile);// assign the x coordinate to temp node
		cityFile >> readFile;// read the city's y coordinate
		temp->yCoord = stoi(readFile);// assign the y coordinate to temp node
		quadTree.pt_Insert(*temp);// insert the node to the quadtree
	}
	quadTree.pretty_print(quadTree.get_root());// print the quadtree

	fstream queryFile;// query file
	string queries;
	queryFile.open("queries0.txt");	//open the file that holds the queries

	while (queryFile >> queries) {// read the queries
		cout << endl;
		vector<string> quadrants;//vector of quadrants to be searched
		vector<string> searchPath;// list of the cities that have been searched
		vector<string> coutSearchPath;// vector to print the search list
		vector<string> foundCities;// cities in the searched area

		queries = queries.substr(0, queries.length() - 1);// get the x coordinate of the search point without the comma
		int x = stoi(queries);// assign the x coordinate
		queryFile >> queries;
		queries = queries.substr(0, queries.length() - 1);// get the y coordinate of the search point without the comma
		int y = stoi(queries);// assign the y coordinate
		queryFile >> queries;// get the radius for the search point
		int r = stoi(queries);// assign the radius

		if (quadTree.distanceBetween(x, y, quadTree.get_root()) <= r) {// check if the root is within the searched area
			foundCities.push_back(quadTree.get_root()->name);// if the root is in the area, add it to the list
		}
		searchPath.push_back(quadTree.get_root()->name);// add the root to the searched cities list

		quadrants=quadTree.whichQuadrants(x, y, r,quadTree.get_root());// get the quadrants to be searched
		for (int i = 0; i < quadrants.size(); i++) {// loop through the quadrants
			coutSearchPath = quadTree.citiesInTheArea(quadrants[i], x, y, r, quadTree.get_root(),searchPath,foundCities);// update the found cities and get the searched cities list
		}
		if (foundCities.size() > 0) {// if any city is within the radius to be searched
			for (int i = 0; i < foundCities.size() - 1; i++) {
				cout << foundCities[i] << ", ";// print the cities

			}
			cout << foundCities[foundCities.size() - 1];
			cout << endl;
		}
		else {
			cout << "<None>"<<endl;
		}
		for (int i = 0; i < coutSearchPath.size()-1; i++) {// print the searched cities one by one
			cout << coutSearchPath[i] << ", ";
		}
		cout << coutSearchPath[coutSearchPath.size()-1];
		if (!queryFile.eof()){
			cout << endl;
		}
	}
	return 0; 
}
#include <iostream>
#include "stack.h"
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//Author: Zeynep Taskin 33851
//Date: 28.10.2024 
//Purpose: This program solves the N-queens problem and creates a file to hold the found solutions.

struct BoardNodes { // struct to hold the state of the board during backtracking
	int rowNum;
	vector<int> queenPositions; // vector to hold queens colummn positions

};

bool isSafe(int** matrix,int rowNo, int colNo) { // function to check if a position is safe
	if (matrix[rowNo][colNo] == 0) { // if the position is 0, it's safe
		return true;
	}return false;
}

void putQueen(int** & matrix, int rowNo, int colNo,int N) { // function to update the safe matrix and add a queen
	if (isSafe(matrix, rowNo, colNo)) { // check if the position is safe
		for (int i = 0; i < N; i++) {
			matrix[rowNo][i] += 1; // increment the entire row
		}
		for (int i = 1; i < N; i++) {
			matrix[i][colNo] += 1; // increment the entire column
		}
		for (int i = 1; i < N; i++) { // increment the four diagonals
			if (-1< rowNo - i && -1 < colNo-i) {
				matrix[rowNo - i][colNo - i] += 1; // upper-left diagonal
			}
			if (rowNo + i < N && colNo + i < N) {
				matrix[rowNo + i][colNo + i] += 1; // lower-right diagonal
			}
			if (-1 < rowNo - i && N> colNo + i) {
				matrix[rowNo - i][colNo + i] += 1; // upper-right diagonal
			}
			if (rowNo + i < N && colNo - i > -1) {
				matrix[rowNo + i][colNo - i] += 1; // lower-left diagonal
			}
		}
		
	}
}

void removeQueen(int**& matrix, int rowNo, int colNo, int N) { // function to update the safe matrix and remove a queen
	if (isSafe(matrix, rowNo, colNo)==0) {
		for (int i = 0; i < N; i++) {
			matrix[rowNo][i] -= 1; // decrement the entire row
		}
		for (int i = 1; i < N; i++) {
			matrix[i][colNo] -= 1; // decrement the entire column
		}
		for (int i = 1; i < N; i++) { // decrement the four diagonals
			if (-1 < rowNo - i && -1 < colNo - i) { 
				matrix[rowNo - i][colNo - i] -= 1; // upper-left diagonal
			}
			if (rowNo + i < N && colNo + i < N) {
				matrix[rowNo + i][colNo + i] -= 1; // lower-right diagonal
			}
			if (-1 < rowNo - i && N > colNo + i) {
				matrix[rowNo - i][colNo + i] -= 1; // upper-right diagonal
			}
			if (rowNo + i < N && colNo - i > -1) {
				matrix[rowNo + i][colNo - i] -= 1; // lower-left diagonal
			}
		}
	}
}

int popLast(vector<int>& queenPos) { // function to update an integer vector and get its last added integer
	int lastPos=queenPos[queenPos.size()-1]; // get the last position of a queen
	queenPos.pop_back(); // remove the position
	return lastPos; // return the column number
}

// function to backtrack
void backTrack(int& i, int& j, int N, int**& board, BoardNodes& newState, Stack<BoardNodes>& boardStack) {
	BoardNodes backtrack = boardStack.pop(); // pop the last state
	i = backtrack.rowNum; // update the row 
	j = popLast(backtrack.queenPositions); // update the column to the column of the queen
	newState.queenPositions = backtrack.queenPositions; // update the state
	removeQueen(board, i, j, N); // remove the queen from the board
}
int main() {
	int N;
	cout << "Enter the value of N for the N-Queens problem: "; // get input
	cin >> N;
	if (N < 1) { // if input is invalid give appropriate message
		cout << "Invalid input. Please enter a positive integer";
	}
	else {
		// create the board as a safe matrix
		// with all positions being 0
		int** board = new int* [N];
		for (int i = 0; i < N; i++) {
			board[i] = new int [N];
			for (int j = 0; j < N; j++) {
				board[i][j] = 0;
			}
		} 

		Stack<BoardNodes> boardStack; // create a stack for backtracking
		vector<vector<int>> solutions; // create a vector to hold solutions
		BoardNodes initialState; // node for the initial state of the board
		BoardNodes newState; // node for new states of the board
		initialState.rowNum = 0;
		initialState.queenPositions = {};
		boardStack.push(initialState); // push the initial state to the stack

		while (boardStack.isEmpty() == 0) { // while stack is not empty
			for (int rowNo = 0; rowNo < N; rowNo++) {
				for (int columnNo = 0; columnNo < N; columnNo++) {
					// check each position
					if (isSafe(board, rowNo, columnNo)) {
						putQueen(board, rowNo, columnNo, N); // put the queen
						// update the state
						newState.rowNum = rowNo; // update the row number
						newState.queenPositions.push_back(columnNo); // add the queen's column position
						boardStack.push(newState); // push the state
						// check if there are more rows
						if (newState.rowNum != N - 1) {
							rowNo++; // move to the next row
							columnNo = -1; // start from the first position of that row
						}
						else {
							solutions.push_back(newState.queenPositions); // add the solution
							backTrack(rowNo, columnNo, N, board, newState, boardStack); // backtrack
							if (columnNo == N - 1 && rowNo != 0) { // if there is no more column left in the row
								backTrack(rowNo, columnNo, N, board, newState, boardStack);
							}
						}
					}
					else if (columnNo == N - 1) { // if there is no safe positions in the row
						backTrack(rowNo, columnNo, N, board, newState, boardStack); // backtrack
						if (columnNo == N - 1 && rowNo != 0) { // if there is no more column left in the row
							backTrack(rowNo, columnNo, N, board, newState, boardStack);
						}
					}

					/* if backtracked into the last
					column of the first row there
					are no other solutions left */
					if (rowNo == 0 && columnNo == N - 1) {
						boardStack.pop(); // pop the initial state
						// break the for loops
						rowNo = N;
						columnNo = rowNo;
					}
				}
			}
		}

		string filename = to_string(N) + "queens_solutions.txt"; // create the file name
		ofstream file(filename); // create the file
		int solutionNumber = solutions.size();
		file << "Total solutions for N=" << N << ": " << solutionNumber;
		file << endl << endl;
		for (int i = 0; i < solutionNumber; i++) { // write the solutions to the file one by one
			file << "Solution " << i + 1 << ": ";
			file << "[";
			for (int j = 0; j < N - 1; j++) {
				file << solutions[i][j] << ", ";
			}
			file << solutions[i][N - 1];

			file << "]" << endl;
		}
		cout << "Solutions have been saved to \'" << N << "queens_solutions.txt\'";
		file.close(); // close the file
		for (int i = 0; i < N; i++) {
			delete[] board[i];
		}
		delete board;
	}
	return 0;
}
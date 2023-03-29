//C++ standard library
#include <vector>
#include <iostream> 
#include <algorithm> 
//This project
#include "treeNode.h"

std::vector<std::vector<treeNode*>> ConstructTree(int numBottomRow, std::vector<int> treeValues)
{
	//input: 
	//numBottomRow: How large the bottom row of the tree is
	//treeValues: Are the values of the tree, starting from the bottom left, moving towards the right
	//when a row is completed, the values jump up to the next row starting at the left again

	int currentRow{0}; //a counter that tells us the current row of the tree we are on, with 0 being bottom
	int positionInTree{0}; //a counter that tells us our position in the tree

	//A vector we will return with the tree, and a temporary vector for the current row
	std::vector<std::vector<treeNode*>> returnVal;
	std::vector<treeNode*> tempTreeRow;

	for (int numEntriesInRow = numBottomRow; numEntriesInRow > 0; --numEntriesInRow) //count up from the bottom row to the top
	{
		for (int positionInRow = 0; positionInRow < numEntriesInRow; ++positionInRow) //count over from the left of the row to the right
		{
			int value = treeValues[positionInTree]; //Get the value of the current node
			treeNode* leftConnection{nullptr};
			treeNode* bottomLeftConnection{nullptr};
			treeNode* bottomRightConnection{nullptr};

			//Set the left connection
			if (positionInRow != 0) //a node on the left of the row has nothing to the left of it
			{
				leftConnection = tempTreeRow[positionInRow-1]; //If not on the left of the row, point to the next node over
			}

			//Set the bottom left and right connections
			if (numEntriesInRow != numBottomRow) //a node on the bottom row has nothing below it
			{
				bottomLeftConnection = ((returnVal[currentRow-1])[positionInRow]);
				bottomRightConnection = ((returnVal[currentRow-1])[positionInRow+1]);
			}

			
			//Push back a node on the current row
			tempTreeRow.push_back(new treeNode(value, leftConnection, bottomLeftConnection, bottomRightConnection));

			// std::cout << std::endl <<"Current value: " << value << std::endl;
			// if (leftConnection) {std::cout << "Left Connection: " << leftConnection->_value << std::endl;}
			// if (bottomLeftConnection) {std::cout << "Bottom Left Connection: " << bottomLeftConnection->_value << std::endl;}
			// if (bottomRightConnection) {std::cout << "Bottom Right Connection: " << bottomRightConnection->_value << std::endl;}

			++positionInTree;
		}

		//push back the current row onto the tree
		returnVal.push_back(tempTreeRow);
		tempTreeRow.erase(tempTreeRow.begin(), tempTreeRow.end()); //clear the current temp row
		++currentRow;
	}

	return returnVal;
}

std::vector<std::vector<treeNode*>> ConstructMaximumBelowTree(std::vector<std::vector<treeNode*>> pathTree)
{

	int currentRow{0}; //a counter that tells us the current row of the tree we are on, with 0 being bottom
	int positionInTree{0}; //a counter that tells us our position in the tree

	//A vector we will return with the tree, and a temporary vector for the current row
	std::vector<std::vector<treeNode*>> returnVal;
	std::vector<treeNode*> tempTreeRow;

	for (int numEntriesInRow = pathTree[0].size(); numEntriesInRow > 0; --numEntriesInRow) //count up from the bottom row to the top
	{
		for (int positionInRow = 0; positionInRow < numEntriesInRow; ++positionInRow) //count over from the left of the row to the right
		{
			int value{pathTree[currentRow][positionInRow]->_value}; //Get the value of the current node
			treeNode* leftConnection{nullptr};
			treeNode* bottomLeftConnection{nullptr};
			treeNode* bottomRightConnection{nullptr};

			if (currentRow != 0) //if current row is zero there is nothing below to sum
			{
				//Look at the two values to the bottom left and bottom right
				//Sum which ever of the two is largest
				value += std::max(((returnVal[currentRow-1])[positionInRow])->_value, ((returnVal[currentRow-1])[positionInRow+1])->_value);
			}

			//Set the left connection
			if (positionInRow != 0) //a node on the left of the row has nothing to the left of it
			{
				leftConnection = tempTreeRow[positionInRow-1]; //If not on the left of the row, point to the next node over
			}

			//Set the bottom left and right connections
			if (currentRow != 0) //a node on the bottom row has nothing below it
			{
				bottomLeftConnection = ((returnVal[currentRow-1])[positionInRow]);
				bottomRightConnection = ((returnVal[currentRow-1])[positionInRow+1]);
			}

			//Push back a node on the current row
			tempTreeRow.push_back(new treeNode(value, leftConnection, bottomLeftConnection, bottomRightConnection));

			// std::cout << std::endl <<"Current value: " << value << std::endl;
			// if (leftConnection) {std::cout << "Left Connection: " << leftConnection->_value << std::endl;}
			// if (bottomLeftConnection) {std::cout << "Bottom Left Connection: " << bottomLeftConnection->_value << std::endl;}
			// if (bottomRightConnection) {std::cout << "Bottom Right Connection: " << bottomRightConnection->_value << std::endl;}

			++positionInTree;
		}

		//push back the current row onto the tree
		returnVal.push_back(tempTreeRow);
		tempTreeRow.erase(tempTreeRow.begin(), tempTreeRow.end()); //clear the current temp row
		++currentRow;
	}

	return returnVal;
}

void PrintOptimalPath(std::vector<std::vector<treeNode*>> pathTree, std::vector<std::vector<treeNode*>> maximumBelowTree)
{

	treeNode* lastOptimalNode{nullptr};
	treeNode* matchingNodeInPathTree{nullptr};

	for (int currentRow = pathTree.size(); currentRow > 0; --currentRow) //count from top row to the bottom
	{
		if (currentRow != pathTree.size())
		{
			//Take the left path
			if (lastOptimalNode->_pBottomLeftConnection->_value >= lastOptimalNode->_pBottomRightConnection->_value)
			{
				lastOptimalNode = lastOptimalNode->_pBottomLeftConnection;
				matchingNodeInPathTree = matchingNodeInPathTree->_pBottomLeftConnection;
				std::cout << matchingNodeInPathTree->_value << " --> ";
			}
			else //take the right path
			{
				lastOptimalNode = lastOptimalNode->_pBottomRightConnection;
				matchingNodeInPathTree = matchingNodeInPathTree->_pBottomRightConnection;
				std::cout << matchingNodeInPathTree->_value << " --> ";
			}
		}
		else //so for the first row there is only one value to grab
		{
			lastOptimalNode = maximumBelowTree[currentRow-1][0];
			matchingNodeInPathTree = pathTree[currentRow-1][0];
			std::cout << "Value of maximal path: " << maximumBelowTree[currentRow-1][0]->_value << std::endl;
			std::cout << "Path: " << matchingNodeInPathTree->_value << " --> ";
		}
	}

	std::cout << "end of tree." << std::endl;
}

int main()
{
	std::cout << "Small tree:" << std::endl;
	std::vector<int> treeRaw {8, 5, 9, 3, 2, 4, 6, 7, 4, 3};
	auto tree = ConstructTree(4, treeRaw);
	auto maximumBelowTree = ConstructMaximumBelowTree(tree);
	PrintOptimalPath(tree, maximumBelowTree);

	std::cout << std::endl << "Big tree:" << std::endl;
	std::vector<int> bigTreeRaw {4,62,98,27,23,9,70,98,73,93,38,53,60,4,23,63,66,4,68,89,53,67,30,73,16,69,87,40,31,91,71,52,38,17,14,91,43,58,50,27,29,48,70,11,33,28,77,73,17,78,39,68,17,57,53,71,44,65,25,43,91,52,97,51,14,41,48,72,33,47,32,37,16,94,29,41,41,26,56,83,40,80,70,33,99,65,4,28,6,16,70,92,88,2,77,73,7,63,67,19,1,23,75,3,34,20,4,82,47,65,18,35,87,10,17,47,82,95,64,75};
	auto bigTree = ConstructTree(15, bigTreeRaw);
	auto maximumBelowBigTree = ConstructMaximumBelowTree(bigTree);
	PrintOptimalPath(bigTree, maximumBelowBigTree);
}


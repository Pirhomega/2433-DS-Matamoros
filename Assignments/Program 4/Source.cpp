/*
Corbin Matamoros
Discrete Structures and Analysis, CMPS 2433
Dr. Stringfellow
Program 4 - 11/16/2018
Will receive a simple undirected graph (i.e. an adjacency matrix) as input and
determine if it has an Euler Circuit. If so, the program will find it (or
a subcircuit using Fleury's algorithm.
*/

#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

/*struct to form linked list. 
Holds the vertex number and a pointer to the next node*/
struct pathFinder
{
	int data;
	pathFinder* next;

	pathFinder()
	{
		data = 0;
		next = NULL;
	}
	pathFinder(int value)
	{
		data = value;
		next = NULL;
	}
};

/*
Class:				path
Variables:			front and traverser
Member functions:	path, push, and printList
Purpose:			to create an object to track the path traversed through
					the input adjacency matrix. It is a bit overkill, but I
					did it to practice knowledge of classes.
*/
class path
{
private:
	pathFinder *front, *traverser;
public:

	//default constructor
	path()
	{
		front = traverser = NULL;
	}

	/*
	Function:	push
	Params:		vertex
	Purpose:	pushes a vertex to the linked list to simulate the path that
				connects through the vertex
	Returns:	void
	*/
	void push(int vertex)
	{	
		pathFinder *temp = new pathFinder(vertex);
		
		//begin list if list is empty
		if (front == NULL)
		{
			front = traverser = temp;
		}

		//add node to list and connect previous node to new node
		else
		{
			traverser->next = temp;
			traverser = temp;
		}
	}

	/*
	Function:	printList
	Params:		none
	Purpose:	completely prints the contents of the linked list and deletes
				nodes as they are printed
	Returns:	void
	*/
	void printList(ofstream &outfile, int *numEdges)
	{
		pathFinder *temp = front;
		if (temp == NULL)
		{
			cout << "ERROR: cannot print from a NULL pointer!\n";
		}
		else
		{
			outfile << "0 ";
			while (temp != NULL)
			{
				outfile << front->data << ' ';
				front = front->next;
				delete temp;
				temp = front;
			}
			if (*numEdges == 0)
				outfile << "\nEuler circuit constructed\n\n";
			else
				outfile << "\nEuler subcircuit constructed\n\n";
		}
	}
};

//here's some room for prototypes
void openFiles(ifstream &infile, ofstream &outfile);
bool checkEdges(ifstream &infile, vector<vector<int>> &vectorArray, int *numEdges);
void fleuryAlgo(vector<vector<int>> &graphVector, int *numEdges, path &finalPath);
void closeProgram(ifstream &infile, ofstream &outfile, int *numEdges);

int main()
{
	//declarations
	int i = 0, numCases = 0, *numEdges;
	/*numEdges will be passed around between functions with the number of
	edges in each adjacency matrix. It will prevent the Fleury algorithm
	from checking for more edges if numEdges is zero.*/

	path finalPath;
	bool isCircuit;
	char finished = 'N';
	vector<vector<int>> graphVector(3, vector<int>(3, 0));
	ifstream infile;
	ofstream outfile;

	//function to open input and output files
	openFiles(infile, outfile);

	infile >> numCases;
	outfile << "Corbin Matamoros - Program 4\n" << "There will be " << numCases
		<< " graphs to analyze\n\n";

	//declaring one 'int' of memory for numEdges, having it point to zero.
	numEdges = new int [1];
	while (i < numCases)
	{
		*numEdges = 0;

		outfile << "GRAPH " << i + 1 << '\n';

		//function to check if graph has vertices all of even degree
		isCircuit = checkEdges(infile, graphVector, numEdges);

		if (isCircuit)
		{
			//function to activate Fleury's algorithm
			fleuryAlgo(graphVector, numEdges, finalPath);

			//function to print the Euler circuit
			finalPath.printList(outfile, numEdges);
		}
		else
			outfile << "No Euler Circuit found\n\n";

		i++;
	}
	//function to close input/output files and delete pointers
	closeProgram(infile, outfile, numEdges);

	return 0;
}

/*
Function:	openFiles
Params:		infile and outfile
Purpose:	prompt user for input and output files to be used and open them
Returns:	void
*/
void openFiles(ifstream &infile, ofstream &outfile)
{
	char input[40], output[40];

	cout << "Input desired files\n" << "Input (.dat): ";
	cin >> input;
	cout << "\nOutput (.txt): ";
	cin >> output;

	infile.open(input);
	outfile.open(output);
}

/*
Function:	checkEdges
Params:		infile, 2D vector "graphVector," numEdges
Purpose:	read in the size of the array-representation of a graph,
			cycle through each element per row and count the number of 1's,
			and continue until the last row has been counted. The cycling
			will stop early if a row contains an odd number of 1's. Early
			exits return a false flag; otherwise, true.
Returns:	true or false
*/
bool checkEdges(ifstream &infile, vector<vector<int>> &graphVector, int *numEdges)
{
	int numVertices, colCount, rowCount = 0, element, sumOfRow = 0;
	bool evenORodd = true; //help determine if a vertex had even or odd degree
	infile >> numVertices; //read in size of array

	cout << numVertices << " is the number of vertices in this matrix\n";

	//resize 2D vector to fit current array
	graphVector.resize(numVertices);
	for (colCount = 0; colCount < numVertices; colCount++)
	{
		graphVector[colCount].resize(numVertices);
	}

	/*loop through all elements in adjacency matrix until the entire matrix
	has been copied to the 2D vector or the sum of 1's in a row was not even*/
	while (rowCount != numVertices)
	{
		sumOfRow = 0;

		/*loop through each column in row, read in each value from input file,
		and copy to corresponding element in vector array*/
		for (colCount = 0; colCount < numVertices; colCount++)
		{
			infile >> element;
			graphVector[rowCount][colCount] = element;
			sumOfRow += element;
		}
		*numEdges += sumOfRow;
		if ((sumOfRow & 1) == 1)
			evenORodd = false;
		rowCount++;//move on to the next row
	}
	return evenORodd;
}

/*
Function:	fleuryAlgo
Params:		graphVector, *numEdges, numCases
Purpose:	create an Euler circuit or subcircuit from the input adjacency
			matrix by Fleury's algorithm (starting at a vertex, find an edge
			from it and delete it. Repeat until there are no edges left or
			a circuit has been formed).
Returns:	void
*/
void fleuryAlgo(vector<vector<int>> &graphVector, int *numEdges, path &finalPath)
{
	int traveler = graphVector[0][0], i = 0, j = 0;

	//while loop traverses each column for the first vertex
	while (traveler != 1)
	{
		traveler = graphVector[++i][j];
	}
	graphVector[i][j] = graphVector[j][i] = 0;
	
	/*the first node of the linked list will not be vertex 0, it will be 
	whatever vertex 0 links to first (found by the algorithm).
	Vertex 0 will be assumed to preceed the node of vertex 1.*/
	finalPath.push(i);

	*numEdges -= 2;

	/*do-while loop initially iterates (one column at a time) through 
	elements below the major diagonal. If no edges were found below that,
	the iterator resets and traverses through the elements above the major
	diagonal.*/
	do {
		/*move to column that corresponds to vertex connected to previous 
		vertex*/
		j = i;
		traveler = 0;

		//traverse column for next edge
		while (traveler != 1)
		{
			/*if traveler reaches last row of adjacency matrix, start iterating
			from the very top*/
			if (i == (graphVector.size() - 1))
				i = -1;

			traveler = graphVector[++i][j];
		}

		cout << "Found edge between vertices " << j << " and " << i << '\n';

		graphVector[i][j] = graphVector[j][i] = 0;
		finalPath.push(i);
		*numEdges -= 2;

	} while (*numEdges != 0 && i != 0);
}

/*
Function:	closeProgram
Params:		infile, outfile, numEdges
Purpose:	close input and output files and delete all pointers
Returns:	void
*/
void closeProgram(ifstream &infile, ofstream &outfile, int *numEdges)
{
	delete numEdges;
	infile.close();
	outfile.close();
}

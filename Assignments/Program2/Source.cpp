/*
Matamoros, Corbin
2433-102 Discrete Structures, Fall '18, Catherine Stringfellow
Program 2 - 9/28/2018
This program will compute the number of possible squares in an n-by-n size grid
with three different methods - iterative, recursive, and closed form. The 
equation to calculate the number of possible squares is 

# of squares = (n)^2 + (n - 1)^2 + (n - 2)^2 + . . . (n - (n - 1))^2

*/

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

//prototypes for the three functions called
int iterative(int n);
int recursive(int n, int result);
int closedForm(int n);

int main()
{
	int n = 0, itRes = 0, recRes = 0, cloRes = 0;

	char input[40], output[40], flag; 
			/* flag will display a Y if all three functions returned the same 
			   value for number of possible squares in an n-by-n grid. 
			   N otherwise.*/
	
	ifstream infile;
	ofstream outfile;

	cout << "Please declare the input and output files (.txt): ";
	cin >> input >> output;
	infile.open(input);
	outfile.open(output);
	
	/*using "setw" functions to seperate the columns in the output file. Each 
	column will be 15 characters wide except the "N" and "Equal?" column*/
	outfile << "Corbin Matamoros\n\n" << setw(3) << "N" << setw(15) 
		<< "iterative" << setw(15) << "recursive" << setw(15) 
		<< "closedForm" << setw(10) << "Equal?\n";
	
	while (infile >> n)
	{
		//catches squares with n = 0 or anything less than zero
		if (n <= 0)
			cout << "Detected invalid value for n (n = " << n << ")." 
			<< " Not included in output file.\n";
		else
		{
			itRes = iterative(n);
			recRes = recursive(n, 1);
			cloRes = closedForm(n);

			if (itRes == recRes && recRes == cloRes && itRes == cloRes)
				flag = 'Y';
			else
				flag = 'N';
			outfile << setw(3) << n << setw(15) << itRes << setw(15) << recRes 
				<< setw(15) << cloRes << setw(9) << flag << '\n';
		}
	}
	
	infile.close();
	outfile.close();

	return 0;
}

/*
FunctionName:	iterative
Description:	Calculates number of possible squares by iterating from 1 to n
Params:			n
Returns:		result
*/
int iterative(int n)
{
	int result = 1; /*initializing result to 1 eliminates one loop, since
					the loop will calculate (n - (n - 1))^2. That equals 1, and
					1 will always be added to the result regardless of n.*/

	for (int i = 2; i <= n; i++)
	{
		result += i * i; /*accumulating calculation.
						 result = result + (i * i), where i = 2, 3, ... n*/
	}

	return result;
}

/*
FunctionName:	recursive
Description:	Calculates number of possible squares utilizing tail recursion
				See commented-out section at bottom of program for a non-tail
				recursive version of this same function
Params:			n, result
Returns:		result
*/
int recursive(int n, int result)
{
	//once again, result is initialized to 1. See function 
	//"iterative" for explanation
	if (n <= 1)
		return result;
		
	/*calling the same function again, decreasing n by 1. 
		Result holds the accumulating calculation, which is the same one used 
		in the function "iterative"*/
	return recursive(n - 1, result + (n * n));
}

int closedForm(int n)
{
	return (n * (n + 1) * (2*n + 1)) / 6;
}

/******************************************************
//OTHER RECURSION TECHNIQUE

this version will use more memory, making it less favorable

int recursive(int n)
{
	if (n == 1)
		return 1;
	else
		return ((n * n) + recursive(n - 1)); 
} 

*******************************************************/

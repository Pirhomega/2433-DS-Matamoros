/*
Matamoros, Corbin
2433-102 Discrete Structures, Fall '18, Catherine Stringfellow
Program 1 - 9/7/2018
This program will convert gray code to binary and\or decimal, and vice versa
*/

#include<iostream>
#include<fstream>
#include<iomanip>

using namespace std;

//prototypes of functions after int main()
int computeGrayInteger(int k);
int computeGrayPosition(int grayCode, int* grayArray, int counter);
int computePower(int counter);

int main()
{
	int k = 0, n = 0, grayCode = 0, g = 0, iterations = 0, grayInt = 0,
		temp = 0, counter = 0;
	int *grayArray;
	char option = ' ';

	ifstream infile;
	ofstream outfile;
	infile.open("graycodes.dat");
	outfile.open("Output.txt");

	outfile << "Corbin Matamoros\n";

	infile >> iterations; //read in how many values the program will run

	//while loop to read in each gray code, n, and/or k value
	while (infile >> option)
	{
		//checks if we will run the gray integer or gray position function
		if (option == 'A')
		{
			//reads in number of bits and decimal value of those bits
			infile >> n >> k;

			//calls function that will transmit a copy of k to it
			grayInt = computeGrayInteger(k);
			outfile << setw(3) << grayInt
				<< " is the gray code integer equivalent " << "to a " << n
				<< "-bit number of decimal value " << k << '\n';
		}
		else if (option == 'B')//runs when "option" is no longer "A"
		{
			infile >> grayCode;
			temp = grayCode;

			if (grayCode == 0)//backup if grayCode == 0 (i.e. log(0)=NaN)
				counter = 1;
			else
				/*counts how many bits are in the gray code to create an
				equivalently sized array*/
				counter = (int)log10(grayCode) + 1;

			//dynamically declares an array of size "counter"
			grayArray = new int[counter];

			g = computeGrayPosition(grayCode, grayArray, counter);
			outfile << setw(3) << g << " is the decimal value of gray code "
				<< grayCode << '\n';
		}
	}
	infile.close();
	outfile.close();
	return 0;
}

/*
	FunctionName:	computeGrayInteger
	Description:	Translates decimal value "k" to gray code in "n" number of
					bits
	Params:			k
	Returns:		result
*/
int computeGrayInteger(int k)
{
	/* (k >> 1) is a bitwise function that shifts all bit values to the right
	by 1 (e.g. 100110 >> 010011)*/
	return (k >> 1) ^ k; //performs exclusive-or function
}

/*
	FunctionName:	computeGrayPosition
	Description:	computes the decimal value of a gray code number
	Params:			grayCode, grayArray, counter
	Returns:		g
*/
int computeGrayPosition(int grayCode, int* grayArray, int counter)
{
	int value = 0, temp;

	//created "temp" to avoid permanent changes to argument "counter"
	temp = counter;

	//draws each bit value from gray code and inputs each to an element 
	//in grayArray
	while (temp > 0)
	{
		//we will array from largest index to smallest
		grayArray[temp - 1] = grayCode % 10;
		grayCode /= 10;
		temp--;
	}

	//computes decimal value of element in first index of array
	if (grayArray[0] == 1)
		value = computePower(counter - 1);

	//converts from gray code to binary using exclusive or function
	for (int i = 1; i < counter; i++)
	{
		grayArray[i] = grayArray[i - 1] ^ grayArray[i];
		if (grayArray[i] == 1)
			value += computePower(counter - 1 - i);
	}
	return value;
}

/*
	FunctionName:	computePower
	Description:	recursive function to compute the power of an integer
	Params:			binary, counter
	Returns:		binary
*/
int computePower(int counter)
{
	if (counter == 0)
		return 1;
	else
		return 2 * computePower(counter - 1);
}


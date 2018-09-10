/*
Matamoros, Corbin
2433 Discrete Structures
Catherine Stringfellow
Program 1 - 9/7/2018
This program will convert gray code to decimal and vice versa. This version is untested and unfinished.
*/

#include<iostream>
#include<fstream>
#include<cmath>

using namespace std;

/*	
	FunctionName:	computeGrayInteger
	Description:	translates decimal value "k" to gray code in "n" number of bits
	Params:			k
	Returns:		result
*/
int computeGrayInteger(int k)
{
	int result = 0;
	result = k >> 1; //bitwise function that shifts all bit values to the left by 1 (e.g. 0110 > 0011)
	return result = result ^ k; //performs exclusive-or function
}

/*
	FunctionName:	computeGrayPosition
	Description:	computes the decimal value of a gray code number
	Params:			grayCode, grayArray, counter
	Returns:		g
*/
int computeGrayPosition(int grayCode, int* grayArray, int counter)
{
	int i = 0, g = 0;
	while (i < counter) //draws each bit value from gray code and inputs each to an element in array
	{
		grayArray[i] = grayCode % 10;
		grayCode /= 10;
		i++;
	}
	i = counter - 1;
	while (i > 0) //translates gray code to binary
	{
		grayArray[i - 1] = grayArray[i] ^ grayArray[i - 1];
		i--;
	}
	i = 0;
	while (i < counter) //computes decimal value of binary code
	{
		g += (grayArray[i] * pow(2.0, i)); //"pow" computes the i-th power of 2.0
	}
	return g;
}

int main()
{
	int k = 0, n = 0, grayCode = 0, iterations = 0, grayInt = 0, g = 0, temp = 0, counter = 0;
	int *grayArray;
	char option = ' ';

	ifstream infile;
	ofstream outfile;
	infile.open("Input.txt");
	outfile.open("Output.txt");

	outfile << "Corbin Matamoros\n";

	infile >> iterations; //read in how many values the program will run
	cout << "We're going to run this program for " << " values!\n";

	while (infile >> option) //while loop to read in each gray code, n, and/or k value
	{
		if (option == 'A') //checks if we will run the gray integer or gray position function
		{
			infile >> n >> k; //reads in number of bits and decimal value of those bits
			grayInt = computeGrayInteger(k); //calls function that will transmit a copy of k to it
			outfile << grayInt << '\n';
		}
		else //runs when "option" is no longer "A"
		{
			infile >> grayCode;
			temp = grayCode;
			while (temp != 0) //counts how many bits are in the gray code to create an equivalently sized array
			{
				temp = temp / 10;
				counter++;
			}
			grayArray = new int[counter]; //dynamically declares an array of size "counter"
			g = computeGrayPosition(grayCode, grayArray, counter);
			outfile << g;
		}
	}
	return 0;
}

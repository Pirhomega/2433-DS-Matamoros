/*
Matamoros, Corbin
2433 Discrete Structures
Catherine Stringfellow
Program 1 - 9/7/2018
This program will convert gray code to binary and\or decimal, and vice versa
*/

#include<iostream>
#include<fstream>
#include<cmath>

using namespace std;

/*	
	FunctionName:	computeGrayInteger
	Description:	Translates decimal value "k" to gray code in "n" number of
	bits
	Params:			k
	Returns:		result
*/
int computeGrayInteger(int k)
{
	int result = 0;
	result = k >> 1; //bitwise function that shifts all bit values to the left 
					//by 1 (e.g. 0110 > 0011)
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
	int g = 0, temp;
	
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
	//"pow" computes the counter - 1-nth power of 2
	g = (grayArray[0] * pow(2, counter - 1));
	
	//converts from gray code to binary using exclusive or function
	for (int i = 1; i < counter; i++)
	{
		grayArray[i] = grayArray[i - 1] ^ grayArray[i];
		g += (grayArray[i] * pow(2, (counter - 1) - i));
	}
	g += grayArray[counter - 1];
	return g;
}

int main()
{
	int k = 0, n = 0, grayCode = 0, g = 0, iterations = 0, grayInt = 0, 
		temp = 0, counter = 0;
	int *grayArray;
	char option = ' ';

	ifstream infile;
	ofstream outfile;
	infile.open("Input.txt");
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
			outfile << grayInt << " is the gray code integer equivalent " <<
				"to a " << n << "-bit number of decimal value " << k << '\n';
		}
		if (option == 'B')//runs when "option" is no longer "A"
		{
			infile >> grayCode;
			temp = grayCode;

			//counts how many bits are in the gray code to create an 
			//equivalently sized array
			while (temp != 0)
			{
				temp = temp / 10;
				counter++;
			}

			//dynamically declares an array of size "counter"
			grayArray = new int[counter]; 
			g = computeGrayPosition(grayCode, grayArray, counter);
			outfile << g << " is the decimal value of gray code " 
				<< grayCode << '\n';
		}
	}
	infile.close();
	outfile.close();
	return 0;
}
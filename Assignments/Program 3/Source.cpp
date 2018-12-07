/*
Matamoros, Corbin
2433-102 Discrete Structures, Fall '18, Catherine Stringfellow
Program 3 - 10/23/2018

This program will, given a set of integers, compute the maximum greatest common
divisor and the minimum least common multiple of every possible pair of the 
integers.
*/

#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>

using namespace std;

int parsing(string inputer, int numbers[]);
void keeper(int numbers[], int counter);
int gcd(int value1, int value2);
int lcm(int value1, int value2, int gcdValue);

int main()
{
	char input[40], output[40];
	string inputer;
	int numbers[100] = { 0 }, counter = 0;

	/*
		NOTE:	the numbers array is size 100 since each line of input may 
				be up to 100 elements long. After completing the program's
				purposes with the first line of input, the next line will
				overwrite the previous in the numbers array. Counter will
				prevent reading data from a previous line (say if the previous
				had 10 elements and the subsequent had 8. Counter will limit
				processing to the 8 elements, leaving the last two alone).
	*/
	
	ifstream infile;
	ofstream outfile;

	cout << "What input (.dat) and output (.txt) file to use?\n";
	cin >> input >> output;

	infile.open(input);
	outfile.open(output);

	/*	getline grabs input from a "infile" one line at a time, placing the
		string into "inputer". Converting (parsing) the string input into
		integers will be conducted in a function*/
	getline(infile, inputer);

	outfile << "Corbin Matamoros\n" << "Max GCD and Min LCM Program\n"
		<< "There will be " << inputer << " test cases!\n\n"
		<< setw(10) << "maxGCD" << setw(10) << "minLCM" << '\n';

	//while loop to run the parser and keeper function
	while (getline(infile, inputer))
	{
		counter = parsing(inputer, numbers);
		keeper(numbers, counter);
		outfile << setw(10) << numbers[0] << setw(10) << numbers[1] << '\n';
	}
	
	outfile << '\n';
	infile.close();
	outfile.close();

	return 0;
}

/*  
	Function:	parsing
	Params:		inputer and numbers[]
	Purpose:	receive each line of input file in the form of a string.
				It will loop through string and convert all digits to
				integers and put them into the numbers array. It uses the
				following algorithm: 
				1) read in element of string as data type char
				2) convert digit to int and add to accumulator, reader
				3) set corresponding numbers array element to value of reader
				4) proceed to next element
					a) if digit, multiply reader by 10 and repeat from step 1
					b) if space, reset reader to 0 and repeat from step 1
	Returns:	counter
*/
int parsing(string inputer, int numbers[])
{
	int reader = 0, i = 0, counter = 0;
	/*First while loop cycles through string until reaching end.
	  In theory, it doesn't need an end condition since inner
	  loop will always terminate the function*/
	while (i < (int)size(inputer))
	{
		/*Second loop cycles through string until it reaches a space,
		  at which point, terminates.*/
		while (inputer[i] != ' ')
		{	
			/*by subtracting a digit still in character data type by the 
			char '0',converts the char to an int of the same digit*/
			numbers[counter] = reader + inputer[i] - '0';
			reader = numbers[counter] * 10;
			i++;

			//once loop hits the end of the string, terminate the function
			if (i == (int)size(inputer))
			{
				return counter;
			}
		}
		i++;
		counter++;
		reader = 0;
	}
	return counter;
}

/*
	Function:	keeper
	Params:		numbers[] and counter
	Purpose:	numbers array will be read from the first element to counter
				(see NOTE at beginning of program for purpose of counter) and
				send every possible pair of the elements of numbers[] to get
				the GCD and LCM. After receiving them, it will track the max
				and min of the GCD and LCM results, respectively. At the end of
				the function, it will set the first two elements of the numbers
				array to the max GCD and min LCM, respectively
	Returns:	none
*/
void keeper(int numbers[], int counter)
{
	int max = 0, tempMax = 0, min = 2147483647, tempMin = 0;

	/*
		nested for loops will ensure all possible pairs of the values in
		numbers[] are selected and sent to the gcd and lcm functions.
		Outer loop will select an element as the first, and the second loop
		will pair it with each of the remaining elements. After all pairs with
		that element are made, the outer loop moves to the next element. 
		Process	repeats. 
	*/

	for (int i = 0; i <= counter; i++)
	{
		for (int j = i + 1; j <= counter; j++)
		{
			tempMax = gcd(numbers[i], numbers[j]);
			tempMin = lcm(numbers[i], numbers[j], tempMax);

			/*max was initialized to 0, so for the first iteration tempMax
			will be greater than max*/
			if (tempMax > max)
				max = tempMax;
			
			/*for this to work for the first iteration, min MUST be greater
			than tempMin. Therefore, min was not initialized to 0, but to
			the largest possible int value*/
			if (tempMin < min)
				min = tempMin;
		}
	}
	numbers[0] = max;
	numbers[1] = min;
}

/*
	Function:	gcd
	Params:		value1 and value2
	Purpose:	tail recursively compute the greatest common demonenator of
				value1 and value2. Greatest common denomenator will be held
				in value2 after function completion
	Returns:	internally, gcd(); externally, value2
*/
int gcd(int value1, int value2)
{
	if ((value1 % value2) == 0)
		return value2;
	return gcd(value2, (value1 % value2));
}

/*
	Function:	lcm
	Params:		value1, value2, and gcdValue
	Purpose:	gcd and lcm are related in the following way:
					
			value1 * value2 = gcd(value1 and value2) * lcm(value1 and value2)

				In light of this, 

			lcm(value1 and value2) = (value1 * value2) / gcm(value1 and value2)
	
	Returns:	result of above calculation
*/
int lcm(int value1, int value2, int gcdValue)
{
	return ((value1 * value2) / gcdValue);
}

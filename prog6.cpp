// Assignment 6: Katelyn Stamas-Nickandros
// read in, sort, and perform other statistical actions on a set of
// student IDs and their corresponding IQ scores
// read in all data from a file, write all output to a file
#include <iostream>
#include <fstream>
using namespace std;
ifstream infile("prog6input2.txt");
ofstream outfile("pro6output2.txt");
void readdata (int[], int[], int&);
void printarrs (int[], int[], int);
void lsort (int[], int[], int);
void bsort (int[], int[], int);
double mean (int[], int);
void findlimits (int[], int&, int&, int);
int search (int[], int, int);
double median (int[], int);
int mode (int[], int);
int main()
{
	int studentID[15], IQscore[15], n, max, min, IQsearch;
	int pos, medianIQ, modeIQ;
	double averageIQ;

	readdata (studentID, IQscore, n);
	outfile << "List of Student IDs and IQ Scores" << endl;
	printarrs (studentID, IQscore, n);
	lsort (studentID, IQscore, n);
	outfile << "Sorted by ID in Ascending Order" << endl;
	printarrs (studentID, IQscore, n);
	bsort (studentID, IQscore, n);
	outfile << "Sorted by IQ score in Descending Order" << endl;
	printarrs (studentID, IQscore, n);
	averageIQ = mean (IQscore, n);
	outfile << "The average IQ score is " << averageIQ << endl;
	findlimits (IQscore, max, min, n);
	outfile << "The highest IQ score is " << max << endl;
	outfile << "The lowest IQ score is " << min << endl << endl;
	infile >> IQsearch;
	while (infile){
		pos = search (IQscore, n, IQsearch);
		if (pos == -1)
			outfile << IQsearch << " not found" << endl;
		else
			outfile << IQsearch << " found in ID number " << studentID[pos] << endl;
		infile >> IQsearch;
	}
	medianIQ = median (IQscore, n);
	outfile << "The median IQ score is " << medianIQ << endl;
	modeIQ = mode (IQscore, n);
	outfile << "The mode IQ score is " << IQscore[modeIQ] << endl;
	infile.close();
	outfile.close();
	return 0;
}

// Input: receives two arrays and one integer as a referece parameter
// Process: reads in n number groups of data from a file, for each group
// one ID number and one IQ score is read in
// Output: data stored in arrays, n stored as reference parameter
void readdata (int studentID[], int IQscore[], int &n){
	infile >> n;
	for (int i=0; i<n; i++){
		infile >> studentID[i];
		infile >> IQscore[i];
	}
	return;
}

// Input: receives two arrays and one integer as parameters
// Process: loops through array data that was read in from readdata
// Output: sends a table of array data with headings to a file
void printarrs (int studentID[], int IQscore[], int n){
	outfile << "Student ID\t\t" << "IQ Score" << endl;
	for (int i=0; i<n; i++){
		outfile << "   " << studentID[i] << "\t\t\t   ";
		outfile << IQscore[i] << endl;

	}
	outfile << endl << endl;
	return;
}

// Input: receives two arrays and one integer as parameters
// Process: sorts student ID # in ascending order with corresponding IQ
// Output: student ID # array sorted with corresponding IQ scores
void lsort (int studentID[], int IQscore[], int n){
	int tempID, tempIQ;

	for (int pass=0; pass<n-1; pass++)
		for (int cand=pass+1; cand<n; cand++)	
			if (studentID[pass] > studentID[cand]){
				tempID = studentID[pass];
				studentID[pass] = studentID[cand];
				studentID[cand] = tempID;
				tempIQ = IQscore[pass];
				IQscore[pass] = IQscore[cand];
				IQscore[cand] = tempIQ;
			}
	return;
}

// Input: receives two arrays and one integer as parameters
// Process: sorts IQ scores in ascending order with corresponding student ID #
// Output: IQ scores array sorted with corresponding IQ scores
void bsort (int studentID[], int IQscore[], int n){
	int tempID, tempIQ;
	bool swap;

	do{
		swap = false;
		for (int i=0; i<n-1; i++)
			if (IQscore[i] < IQscore[i+1]){
				tempIQ = IQscore[i];
				IQscore[i] = IQscore[i+1];
				IQscore[i+1] = tempIQ;
				tempID = studentID[i];
				studentID[i] = studentID[i+1];
				studentID[i+1] = tempID;
				swap = true;
			}
	} while (swap);
	return;
}

// Input: receives array of IQ scores and n as parameters
// Process: computes the average of all IQ scores in the array
// Output: returns the average to the main function
double mean (int IQscore[], int n){
	int sum = 0;
	double average;

	for (int i=0; i<n; i++)
		sum += IQscore[i];
	average = (double)sum / n;
	return average;
}

// Input: receive the IQ score array, n, and two reference parameters
// Process: find the highest and lowest IQ scores
// Output: return highest (max) and lowest (min) to main program through
// reference parameters
void findlimits (int IQscore[], int &max, int &min, int n){
	max = IQscore[0];
	min = IQscore[n-1];
}

// Input: receive the IQ array, n, and an IQ score as parameters
// Process: find if the specified IQ score is in the IQ array
// Output: return the position of the found specified IQ score in the array
// or return -1 to signal the value is not in the array
int search (int IQscore[], int n, int IQsearch){
	int low = 0, high = n - 1, mid = (low + high) / 2;

	while (low <= high)
		if (IQscore[mid] == IQsearch)
			return mid;
		else if (IQscore[mid] > IQsearch){
			low = mid + 1;
			mid = (low + high) / 2;
		}
			else{
				high = mid - 1;
				mid = (low + high) / 2;
			}
	return -1;
}

// Input: receive the IQ array and n as parameters
// Process: find the median value in the sorted IQ array data
// Output: return the median value to the main program
double median (int IQscore[], int n){
	if (n % 2 != 0)
		return IQscore[(n - 1)/2];
	else
		return (IQscore[(n / 2)] + IQscore[(n / 2 - 1)]) / 2;
}

// Input: receives the IQ array and n as parameters
// Process: find the mode value in the IQ array
// Output: return the mode value back to main program
int mode (int IQscore [], int n){
	int countIQ[20], largestsofar = 0, match;
	
	for (int i=0; i<n; i++)
		countIQ[i] = 0;
	for (int i=0; i<n; i++){
		match = IQscore[i];
		for (int i=0; i<n; i++)
			if (IQscore[i] == match)
				countIQ[i] ++;
	}
	for (int i=0; i<n; i++)
		if (countIQ[i] > largestsofar)
			largestsofar = i;
	return largestsofar;
}
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <string>
 
using namespace std;



const int INSERTION = 0;
const int QUICK = 1;
const int MERGE = 2;
const int SHELL = 3;


template <class T>
T* readFile(string infile, int & n);
template <class T>
bool sorted(T arr[], int n);
template <class T>
bool contains(T arr1[], T arr2[], int n);
template <class T>
bool search(T arr[], int n, T target);
template <class T>
void sortTestResult(T arr[], int n, int sort);
void isTest();
void qsTest();
void msTest();
void shsTest();



// Sorts array in an ascending order using insertionsort algorithm
// PARAM: T data type of array, n = size of the array
// PRE: unsorted/sorted array
// POST: returns barometer comparisons in integer, sorts array
template <class T>
int insertionsort(T arr[], int n)
{
	int comparison = 0;
	for(int i =1; i<n; i++){
		T temp = arr[i]; 
		int pos = i; //marks position
		while(pos > 0 && arr[pos-1] > temp){
			comparison++;
			arr[pos] = arr[pos-1];
			pos--; //decreases position until reaches -1 then while loop stops
		}
		//Insert the current item
		arr[pos] = temp; 
	}
	return comparison;
}


// partitions the array
// PARAM: T data type of array, integer of lowest and highest index, address of comparison counter
// PRE: unsorted/sorted array
// POST: partitioned array
template <class T>
int partition(T arr[], int low, int high, int &comparison)
{
	//Marks pivot with high as index
	T pivot = arr[high];

	while(low<high){
		comparison++;
		while(arr[low] < pivot){ //Increments low if the lowest is less than the marked pivot
			low++;
			comparison++;
			comparison++;
		}
		while(arr[high] > pivot){ //decrements the high if the highest is greater than the marked pivot
			high--;
			comparison++;
			comparison++;
		}
		if(low==high){ //The incremeted low and decremented high reaches a certain point where its same
			low++;
		}

		else if(low<high) //Otherwise
		{
			//Swaps, to sort the array
			T temp = arr[low];
			arr[low] = arr[high];
			arr[high] = temp;
		}
	}
	return high; //Returns the high to set pivot index at the right place after partition
}

// Inputs variables onto quick_sort function, separate function to track comparison and output it as an integer
// PARAM: T data type of array, n = size of array
// PRE: an array
// POST: returns barometer comparison
template <class T>
int quicksort(T arr[], int n){
	int comparison = 0;
	int low = 0;
	int high = n-1;
	quick_sort(arr, low, high, comparison);
	return comparison;
}


// Sorts array in an ascending order using recursive function to call itself repeatedly
// PARAM: T data type of array, n = size of array, address of comparison
// PRE: an array
// POST: sorted array
template <class T>
void quick_sort(T arr[], int low, int high, int &comparison){
	if(low < high){
		int pivot = partition(arr, low, high, comparison);
		quick_sort(arr, low, pivot-1, comparison); //left comparison sort
		quick_sort(arr, pivot+1, high, comparison); //right comparison sort
	}
}

//www.sourcetricks.com/2011/06/merge-sort.html#.U6kBRfldUwA
//Used above source for merge
// Sorts array in an ascending order using mergesort algorithm, separates array, conquers it, merges the array
// PARAM: T data type of array, first, mid, last integers of indexes, address of comparison
// PRE: divided array
// POST: merged array
template <class T>
void merge(T arr[], int low, int mid, int high, int &comparison)
{
	int i;
	int j;
	int k;
	T *c = new T[high+1];
	i= low;
	k=  low;
	j= mid+1;


	while (i <= mid && j <= high)
    {
		comparison++;
        if (arr[i] < arr[j])
        {
            c[k] = arr[i];
            k++;
            i++;
        }
        else
        {
            c[k] = arr[j];
            k++;
            j++;
        }
    }
	//Merge sorts the first half
    while (i <= mid)
    {
        c[k] = arr[i];
        k++;
        i++;
		comparison++;
    }
	//Merge sorts the second half
    while (j <= high)
    {
        c[k] = arr[j];
        k++;
        j++;
		comparison++;
    }

    for (i = low; i < k; i++)
    {
        arr[i] = c[i];
		comparison++;
    }
}

// Separate function to output as an integer
// PARAM: T data type of array, n = size of array
// PRE: an array with size
// POST: returns barometer comparison
template <class T>
int mergesort(T arr[], int n){
	int comparison = 0;
	int first = 0;
	int last = n-1;
	merge_sort(arr, first, last, comparison);
	return comparison;
}

// Using recursion it sorts the array (divides, sorts, merge)
// PARAM: T data type of array, first and last both integers of indexes, address of comparison
// PRE: an array with size
// POST: sorted array
template <class T>
void merge_sort(T arr[], int first,int last, int &comparison){
	if(first < last){
		int mid = (first+last)/2; //Sets mid
		merge_sort(arr, first, mid, comparison); //recursively sorts left from mid to first
		merge_sort(arr, mid+1, last, comparison); //recursively sorts right from mid+1 to last
		merge(arr, first, mid, last, comparison); //Merges array
	}
}



//www.cplusplus.com/forum/general/123961/
//Used above source
// Sorts data type T in an ascending order using shellsort algorithm
// PARAM: T data type of array, n = size of array
// PRE: unsorted/sorted array
// POST: returns barometer comparison in integer
template <class T>
int shellsort(T arr[],int n)
{
	int comparison = 0;
	int j;
	int i;
	int m;
	T mid;

	for(m = n/2;m>0;m/=2)
	{
		comparison++;
		for(j = m;j< n;j++)
		{
			comparison++;
			for(i=j-m;i>=0;i-=m)
			{
				comparison++;
				if(arr[i+m]>=arr[i]){
					break;
				}
				else
				{
					//Swaps
					mid = arr[i];
					arr[i] = arr[i+m];
					arr[i+m] = mid;
				}
			}
		}
	}
	return comparison;
}






// Tests the insertionsort function
void isTest()
{
  try{
         cout << "INSERTION SORT" << endl << "--------------" << endl;
         int n = 0;
         int* arr1 = readFile<int>("test1.txt", n);
         sortTestResult(arr1, n, INSERTION);
         float* arr2 = readFile<float>("test2.txt", n);
         sortTestResult(arr2, n, INSERTION);
         string* arr3 = readFile<string>("test4.txt", n);
         sortTestResult(arr3, n, INSERTION);
         int* arr4 = readFile<int>("test5.txt", n);
         sortTestResult(arr4, n, INSERTION);
         cout << endl;
  }catch(exception e){
         cout << e.what() << endl;
  }
}


// Tests the quicksort function
void qsTest()
{
  try{
         cout << "QUICKSORT" << endl << "---------" << endl;
         int n = 0;
         int* arr1 = readFile<int>("test1.txt", n);
         sortTestResult(arr1, n, QUICK);
         float* arr2 = readFile<float>("test2.txt", n);
         sortTestResult(arr2, n, QUICK);
         string* arr3 = readFile<string>("test3.txt", n);
         sortTestResult(arr3, n, QUICK);
         int* arr4 = readFile<int>("test5.txt", n);
         sortTestResult(arr4, n, QUICK);
         cout << endl;
  }catch(exception e){
         cout << e.what() << endl;
  }
}

// Tests the mergesort function
void msTest()
{
  try{
         cout << "MERGESORT" << endl << "---------" << endl;
         int n = 0;
         int* arr1 = readFile<int>("test1.txt", n);
         sortTestResult(arr1, n, MERGE);
         float* arr2 = readFile<float>("test2.txt", n);
         sortTestResult(arr2, n, MERGE);
         string* arr3 = readFile<string>("test3.txt", n);
         sortTestResult(arr3, n, MERGE);
         int* arr4 = readFile<int>("test5.txt", n);
         sortTestResult(arr4, n, MERGE);
         cout << endl;
  }catch(exception e){
         cout << e.what() << endl;
  }
}
 
// Tests the shellsort function
void shsTest()
{
  try{
         cout << "SHELL SORT" << endl << "---------" << endl;
         int n = 0;
         int* arr1 = readFile<int>("test1.txt", n);
         sortTestResult(arr1, n, SHELL);
         float* arr2 = readFile<float>("test2.txt", n);
         sortTestResult(arr2, n, SHELL);
         string* arr3 = readFile<string>("test3.txt", n);
         sortTestResult(arr3, n, SHELL);
         int* arr4 = readFile<int>("test5.txt", n);
         sortTestResult(arr4, n, SHELL);
         cout << endl;
  }catch(exception e){
         cout << e.what() << endl;
  }
}


// Tests that array is correctly sorted
template <class T>
void sortTestResult(T arr[], int n, int sort)
{
  T* arrcopy = new T[n];
  for(int i=0; i < n; i++){
         arrcopy[i] = arr[i];
  }
 
  cout << "n = " << n;
  
  if(sort == INSERTION){
         cout << ", comparisons = " << insertionsort(arr, n);
  }else if (sort == QUICK){
         cout << ", comparisons = " << quicksort(arr, n);
  }else if (sort == MERGE){
         cout << ", comparisons = " << mergesort(arr, n);
  }else if (sort == SHELL){
         cout << ", comparisons = " << shellsort(arr, n);
  }
  
  
  cout <<", values = " << contains(arr, arrcopy, n);
  cout <<", sorted = " << sorted(arr, n) << endl;
 
  delete[] arr;
  delete[] arrcopy;
}
 
// Opens a file and reads the contents into an array
// PARAM: infile = name of the file to be opened
//        n = the size of the result array
// PRE: the file contains values separated by white space
// POST: returns an array containing the contents of infile
template <class T>
T* readFile(string infile, int & n)
{
  T* result;
  T next;
  n = 0;
 
  ifstream ist(infile.c_str()); // open file
  // Check if file opened correctly
  if(ist.fail())
         throw runtime_error(infile + " not found");
    
  // Find file size
  while(ist >> next){
         n++;
  }
 
  // Read file into array
  ist.close();
  ist.open(infile.c_str());
  result = new T[n];
  for(int i=0; i < n; ++i){
         ist >> result[i];
  }
 
  ist.close();
 
  return result;
}
 
// Checks to see if the input array is in ascending order
// PARAM: arr = name of the array
//        n = size of arr
// PRE:
// POST: returns true iff arr is in ascending order
template <class T>
bool sorted(T arr[], int n)
{
  // Check to see each element i <= element i+1
  for(int i=0; i < n-1; ++i){
         if(arr[i] > arr[i+1]){
                 return false;
         }
  }
  return true;
}
 
// Checks to see if the two arrays contain the same values
// PARAM: arr1, arr2 = name of the arrays
//        n = size of both arrays
// PRE: arr1 and arr2 are the same size, arr1 is sorted
// POST: returns true iff arr1 contains all values in arr2
template <class T>
bool contains(T arr1[], T arr2[], int n)
{
  // Check to see each element of arr2 is in arr1
  for(int i=0; i < n; ++i){
         if(!search(arr1, n, arr2[i])){
                 return false;
         }
  }
  return true;
}
 
// Checks to see if target value is in array
// PARAM: arr = array to be searched
//        n = size of array
//        target =  value to be searched for
// PRE: arr is sorted
// POST: returns true iff target is in arr
template <class T>
bool search(T arr[], int n, T target)
{
  int low = 0;
  int high = n-1;
  int mid = 0;
 
  while(low <= high){
         mid = (low + high) / 2;
         if(arr[mid] == target){
                 return true;
         }else if(target < arr[mid]){
                 high = mid - 1;
         }else{
                 low = mid + 1;
         }
  }
  return false;
}



int main(){

	//isTest();
	//qsTest();
	//msTest();
	//shsTest();
	
	return 0;
}

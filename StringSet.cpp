#include <iostream> //for cout
#include "StringSet.h"

using namespace std;

//Constructor
//Populates an array of maxsize 4; currentsize 0
//Initializes an object
StringSet::StringSet()
{
	maxsize = 4;
	darray = new string[maxsize];
	currentsize = 0;
}

//Deep copy of constructor
//PARAM: const variable, class Stringset, address of s
StringSet::StringSet(const StringSet &s)
{
	maxsize = s.maxsize;
	darray = new string[maxsize];

	for(int i=0; i<s.currentsize;i++){
		darray[i] = s.darray[i];
	}
	currentsize = s.currentsize;
}


//Destructor
//Frees dynamic memory of the array's pointer
StringSet::~StringSet()
{
	delete[] darray;
}

//Inserts string type to the array
//PARAM: String type s
bool StringSet::insert(string s)
{
	//If same string, returns false
	for(int i=0; i<maxsize; i++){
		if(darray[i] == s){
			return false;	
		}
	}
	//First string inserted
	if(currentsize==0){
		darray[0] = s;
		currentsize++;
		return true;
	}
	//Second string and above inserted
	//Insert will be allowed until currentsize is greater than maxsize
	if(currentsize>0 && maxsize>currentsize){
		darray[currentsize] = s;
		currentsize++;
		return true;
	}
	//If currentsize is greater than maxsize, doubles the maxsize
	//Creates a temporary dynamic array and copies the old array
	//Deletes the old array and the new array's address is assigned to object's array pointer
	//Inserts parameter, increments currentsize, returns true
	if(maxsize<=currentsize){
		maxsize = maxsize*2;
		string *temp = new string[maxsize+1];
		for(int k=0; k<currentsize; k++){
			temp[k] = darray[k];
		}
		delete[] darray;
		darray = temp;
		darray[currentsize] = s;
		currentsize++;
		return true;
	}
	//If everything fails
	return false;
}

//returns false unless returned true
//PARAM: String type s
//If the parameter is within the array, it swaps the matching string with the last string in the array of the currentsize
//Decrements currentsize and returns true if met with criteria

bool StringSet::remove(string s){

	for(int i=0; i<maxsize; i++){
		if(darray[i] == s){
			darray[i] = darray[currentsize-1];
			currentsize--;
			return true;
		}
	}
	return false;	
}

//If found returns 1, if not returns -1
//PARAM: String type s, function is const
int StringSet::find(string s) const
{
	for(int i=0; i<currentsize; i++){
		if(darray[i] == s){
			return 1;
		}
	}
	return -1;
}


//Results in two sets that are in union
//Insert takes out duplicates therefore already in union when inserted to StringSet result
//PARAM: const variable, class StringsSet, addressed of set, const function
StringSet StringSet::unions(const StringSet& set) const
{
	StringSet result;

	for(int i= 0; i<currentsize; i++){
		result.insert(darray[i]);
	}
	for(int j=0; j<set.currentsize; j++){
		result.insert(set.darray[j]);
	}
	return result;
}

//Looking at both index, if there is a duplicate, then it is inserted to StringSet result
//StringSet result outputs the intersection of both arrays
//PARAM: const variable, class StringSet, addressed of set, const function
StringSet StringSet::intersection(const StringSet& set) const
{
	StringSet result;
	for(int i= 0; i<currentsize; i++){
		string temp = darray[i];
		for(int j=0; j<set.currentsize; j++){
			string temp1 = set.darray[j];
			if(temp==temp1){
				result.insert(temp);
			}
		}
	}
	 
    return result;
}

//Object's array is added to result, then another forloop checks the result to the parameter if there is any duplicates
//The duplicates are removed and results the difference of set A and B
//PARAM: const variable, class StringSet, addressed of set, const function
StringSet StringSet::difference(const StringSet & set) const
{
	StringSet result;
	for(int i= 0; i<currentsize; i++){
		result.insert(darray[i]);
	}
	for(int j=0; j<result.currentsize; j++){
		for(int k=0; k<set.currentsize; k++){
			if(result.darray[j] == set.darray[k]){
				result.remove(result.darray[j]);
			}
		}
	}
	return result;
}

//Returns currentsize
int StringSet::size()
{
	return currentsize;
}



/*

void arrayClassTest();

int main(){
	arrayClassTest();
	return 0;

}

void arrayClassTest(){

	StringSet ac1;
	StringSet ac3;

	ac1.insert("hello");
	ac1.insert("hello1");
	ac1.insert("hello2");
	ac1.insert("hello3");
	ac1.insert("hello4");
	ac1.insert("hello5");
	ac1.insert("hello6");
	ac1.insert("hello7");
	ac1.insert("hello8");
	ac1.insert("hello9");
	ac1.remove("hello5");
	ac1.find("hello9");

	ac3.insert("hello");
	ac3.insert("hello1");
	ac3.insert("hello2");
	ac3.insert("hello10");
	ac3.insert("hello10");

	ac1.unions(ac3);
	ac1.intersection(ac3);
	ac1.difference(ac3);
	
	StringSet ac2(ac1);

}
*/
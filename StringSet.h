#include <string>

using namespace std;


class StringSet
{

//Headers
public:
	
	StringSet();

	StringSet(const StringSet& s);

	~StringSet();

	//Constructor need to be initialized before using the methods below
	bool insert(string s);

	bool remove(string s);

	int find(string s) const;

	int size();

	StringSet unions(const StringSet & set) const;

	StringSet intersection(const StringSet &set) const;

	StringSet difference(const StringSet &set) const;

private:
	string* darray; //Dynamic Array
	int maxsize;
	int currentsize;
};
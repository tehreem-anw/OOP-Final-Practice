#include<iostream>
#include<string>
#include<fstream>
using namespace std;
int main(){
	ifstream infile("story.txt");
	if(infile.is_open()){
		infile.seekg(0, ios::end);
		streampos pos = infile.tellg();
		cout<<"File size: "<<pos<<endl;
		infile.seekg(0, ios::beg);
		string line;
		getline(infile, line);
		cout<<"First line: "<<endl;
		cout<<line<<endl;
	}
	else{
		cerr<<"Unable to open file."<<endl;
	}
	return 0;
}

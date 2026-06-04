#include<iostream>
#include<string>
#include<fstream>
using namespace std;
int main(){
	fstream myfile("log.txt", ios::in | ios::out);
	char ch;
	streampos targetpos = -1;
	if(myfile.is_open()){
		while(myfile.get(ch)){
			if(ch == 'O'){
				streampos currentpos = myfile.tellg();
				currentpos -= 1;
				char nextch;
				if(myfile.get(nextch) && nextch == 'K'){
					targetpos = currentpos;
				}
			}
		}
		myfile.clear();
		if(targetpos != -1){
			myfile.seekp(targetpos, ios::beg);
			myfile<<"ER";
			cout<<"Last OK modified to ER."<<endl;
		}
		else{
			cout<<"Last OK not found."<<endl;
		}
	}
	else{
		cerr<<"Unable to open file."<<endl;
	}
	return 0;
}

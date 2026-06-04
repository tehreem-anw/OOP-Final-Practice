#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int main(){
	ifstream infile("story.txt");
	string line;
	int lcount = 0;
	int ccount = 0;
	if(infile.is_open()){
		while(getline(infile, line)){
			lcount++;
			for(char ch : line){
				if(ch != ' ' && ch != '\n' && ch != '\t' && ch != '\r'){
					ccount++;
				}
			}
		}
		cout<<"Line count: "<<lcount<<endl;
		cout<<"Char count: "<<ccount<<endl;
	}
	else{
		cout<<"Error: Unable to open file."<<endl;
	}
	return 0;
}

#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int main(){
	string name;
	int score;
	ofstream outfile("highscore.txt", ios :: app);
	if(outfile.is_open()){
		cout<<"Enter name: ";
		cin>>name;
		cout<<"Enter score: ";
		cin>>score;
		outfile<<"Name: "<<name<<" | Score: "<<score<<endl;
		outfile.close();
	}
	else{
		cout<<"Error: Unable to open file."<<endl;
	}
	ifstream infile("highscore.txt");
	string line;
	if(infile.is_open()){
		cout<<"---Highscore Leaderboard---"<<endl;
		while(getline(infile, line)){
			cout<<line<<endl;
		}
		infile.close();
	}
	else{
		cout<<"Error: Unable to open file"<<endl;
	}
	return 0;
}

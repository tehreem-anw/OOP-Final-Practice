#include<iostream>
#include<string>
using namespace std;

class Sport{
	string current_champ; 
	int start_year; 
	string headquarter_location;
	public:
		Sport(): current_champ("N/A"), start_year(0), headquarter_location("N/A"){}
		Sport(string c, int s, string h): current_champ(c), start_year(s), headquarter_location(h){}
		string getheadquarter(){return headquarter_location;}
		int getyear(){return start_year;}
};

class Tournament { 
	protected:
	Sport * sport; 
	public:
		Tournament(){
			sport = new Sport();
		}
		Tournament(string c, int s, string h) {
			sport = new Sport(c, s, h);
		}
		virtual void Begin_Tournament(Sport s){
			if(s.getheadquarter() == "Karachi" || s.getheadquarter() == "Toronto"){
				cout<<"Tournament Begins."<<endl;
			}
			else{
				cout<<"Tournament allowed in only Karachi and Toronto."<<endl;
			}
		}
		virtual ~Tournament(){
			delete sport;
		}
}; 

class WorldCup: public Tournament{
	public:
		void Begin_Tournament(Sport s) override {
			if(s.getyear() > 1950 && s.getheadquarter() != "Karachi" && s.getheadquarter() != "Toronto"){
				cout<<"World Cup Begins."<<endl;
			}
			else{
				cout<<"World Cup not Begins."<<endl;
			}
		}
};

template <typename T>
void PrintIt(T attribute){
	cout<<attribute<<endl;
}

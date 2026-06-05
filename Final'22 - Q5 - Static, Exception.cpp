#include<iostream>
#include<string>
using namespace std;

class Castle{
	public:
		int count;
		Castle(): count(0){}
		void enter(){
			if(count < 10){
				count++;
			}
			else{
				throw 76;
			}
		}
		void exit(){
			if(count > 0){
				count--;
			}
			else{
				throw 67;
			}
		}
};

int main(){
	Castle c;
	while(1){
		int choice;
		cout<<"---Jumpy Castle Menu---"<<endl;
		cout<<"Current People on Jumpy Castle: "<<c.count<<endl;
		cout<<"1. Enter"<<endl;
		cout<<"2. Exit"<<endl;
		cout<<"3. Destroy"<<endl;
		cout<<"Enter your choice: ";
		cin>>choice;
		switch(choice){
			case 1:
				try{
					c.enter();
				}
				catch(int i){
					cout<<"Error: Count Overflow!"<<endl;
				}
				break;
			case 2:
				try{
					c.exit();
				}
				catch (int x){
					cout<<"Error: Count Underflow!"<<endl;
				}
				break;
			case 3:
				cout<<"Destroying Jumpy Castle..."<<endl;
				return 0;
			default:
				cout<<"Inavalid choice entered."<<endl;
				break;
		}
	}
	return 0;
}

//string name;
	//		int mode;
	//		cout<<"Enter file name: ";
	//		cin>>name;
	//		cout<<"Select mode: Write(1) Read(2)."<<endl;
	//		cin>>mode;
	//		if(mode == 1){
	//			ofstream out()

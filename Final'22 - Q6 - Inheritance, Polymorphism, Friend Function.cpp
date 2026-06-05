#include<iostream>
#include<string>
using namespace std;

class File{
	protected:
		int size;
		string location;
		string created_date;
		string modified_date;
	public:
		File(int s, string l, string c, string m): size(s), location(l), created_date(c), modified_date(m){}
		virtual void open() = 0;
		virtual void print(){}
		virtual ~File(){}
		friend bool operator * (const File& f1, const File& f2);
};

class PDF: public File{
	public:
		PDF(int s, string l, string c, string m): File(s, l, c, m){}
		virtual void open() override {
			cout<<"PDF File opened."<<endl;
		}
		virtual void print() override{
			cout<<"PDF File printed."<<endl;
		}
};

class ASCII: public File{
	public:
		ASCII(int s, string l, string c, string m): File(s, l, c, m){}
		virtual void open() override {
			cout<<"ASCII file opened."<<endl;
		}
		virtual void print() override{
			cout<<"ASCII File printed."<<endl;
		}
};

class PS: public File{
	public:
		PS(int s, string l, string c, string m): File(s, l, c, m){}
		virtual void open() override {
			cout<<"PS File opened."<<endl;
		}
		virtual void print() override{
			cout<<"PS File printed."<<endl;
		}
};

bool operator * (const File& f1, const File& f2){
	if(f1.size == f2.size && f1.location == f2.location){
		return true;
	}
	else{
		return false;
	}
}

int main(){
	File *f1 = new PDF(67, "meow", "07/01/2007", "67/01/2067");
	File *f2 = new ASCII(67, "hehe", "24/09/2005", "05/08/2020");
	File *f3 = new PS(67, "meow", "22/10/2009", "11/09/2076");
	f1->print();
	f2->print();
	f3->print();
	cout<<endl;
	if(*f1 * *f2){
		cout<<"F1 and F2 are the same."<<endl;
	}
	else{
		cout<<"F1 and F2 are not the same."<<endl;
	}
	if(*f1 * *f3){
		cout<<"F1 and F3 are the same."<<endl;
	}
	else{
		cout<<"F1 and F3 are not the same."<<endl;
	}
	cout << "--- Cleaning Up Heap Memory ---" << endl;
    delete f1;
    delete f2;
    delete f3;
	return 0;
}

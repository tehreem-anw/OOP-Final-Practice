#include<iostream>
#include<fstream>
#include<string>
using namespace std;
class Test {
int ID;
string name;
static int genID;
public:
Test(){
	ID = ++genID;
	name = "000" + to_string(genID);
}

void operator + (string filename) {
ofstream fout(filename, ios :: app); 
fout << "ID = " << this->ID << ", Name = " << this->name << endl;
}
};
int Test :: genID = 0;

int main() {
Test t1, t2;

t1 + "outfile.txt";
t2 + "outfile.txt";

}


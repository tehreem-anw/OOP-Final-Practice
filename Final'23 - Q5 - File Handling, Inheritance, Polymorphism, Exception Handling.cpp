#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

class ChatBox;

class User{
	string username;
	string country;
	string interest;
	int age;
	public:
		User(string u, string c, string i, int a): username(u), country(c), interest(i), age(a){}
		void Ask(string query, ChatBox& medBot, ChatBox& legalBot, ChatBox& techBot, ChatBox& genBot);
		string getUserName() {return username;}
};

class ChatBox{
	protected:
		static int boxCount;
	public:
		ChatBox() {boxCount++;}
		virtual string generate_response(string query, User u) = 0;
		virtual int getCount() = 0;
		virtual ~ChatBox() {}
};

int ChatBox::boxCount = 0;

class MedicalChatBox: public ChatBox{
	static int medCount;
	int interactionCount;
	string latestUser;
	public:
		MedicalChatBox(): ChatBox(), interactionCount(0) {medCount++;}
		string generate_response(string query, User u) override {
			interactionCount++;
			latestUser = u.getUserName();
			string response = "Hi there! This is your Medical Chat Box. How can I help you?";
			return response;
		}
		int getCount() override {return interactionCount;}
		string getLatestUser() {return latestUser;}
		static int getMedCount() {return medCount;}
};
int MedicalChatBox::medCount = 0;

class LegalChatBox: public ChatBox{
	static int legCount;
	int interactionCount;
	string latestUser;
	public:
		LegalChatBox(): ChatBox(), interactionCount(0) {legCount++;}
		string generate_response(string query, User u) override {
			interactionCount++;
			latestUser = u.getUserName();
			string response = "Hi there! This is your Legal Chat Box. How can I help you?";
			return response;
		}
		int getCount() override {return interactionCount;}
		string getLatestUser() {return latestUser;}
		static int getLegCount() {return legCount;}
};
int LegalChatBox::legCount = 0;

class TechnologyChatBox: public ChatBox{
	static int tecCount;
	int interactionCount;
	string latestUser;
	public:
		TechnologyChatBox(): ChatBox(), interactionCount(0) {tecCount++;}
		string generate_response(string query, User u) override {
			interactionCount++;
			latestUser = u.getUserName();
			string response = "Hi there! This is your Technology Chat Box. How can I help you?";
			return response;
		}
		int getCount() override {return interactionCount;}
		string getLatestUser() {return latestUser;}
		static int getTecCount() {return tecCount;}
};
int TechnologyChatBox::tecCount = 0;

class GeneralChatBox: public ChatBox{
	static int genCount;
	int interactionCount;
	string latestUser;
	public:
		GeneralChatBox(): ChatBox(), interactionCount(0) {genCount++;}
		string generate_response(string query, User u) override {
			interactionCount++;
			latestUser = u.getUserName();
			string response = "Hi there! This is your General Chat Box. How can I help you?";
			return response;
		}
		int getCount() override {return interactionCount;}
		string getLatestUser() {return latestUser;}
		static int getGenCount() {return genCount;}
};
int GeneralChatBox::genCount = 0;

class Bot_Exception {
    string message;
	public:
	    Bot_Exception(string msg) : message(msg) {}
	    string getMessage() {return message;}
};

void User::Ask(string query, ChatBox& medBot, ChatBox& legalBot, ChatBox& techBot, ChatBox& genBot) {
    string prefix;
    stringstream ss(query);
    ss >> prefix;
    if (prefix == "doc") {
        medBot.generate_response(query, *this);
    }
    else if (prefix == "attorney") {
        legalBot.generate_response(query, *this);
    }
    else if (prefix == "guru") {
        techBot.generate_response(query, *this);
    }
    else if (prefix == "special") {
        if (interest == "medical")      { medBot.generate_response(query, *this); }
        else if (interest == "legal")   { legalBot.generate_response(query, *this); }
        else if (interest == "technology") { techBot.generate_response(query, *this); }
        else if (interest == "general") { genBot.generate_response(query, *this); }
    }
    else {
        throw Bot_Exception("Invalid query prefix entered!");
    }
}

void Analysis() {
    ifstream inFile("error_log.txt");
    if (!inFile.is_open()) {
        cout << "No error log file found." << endl;
        return;
    }

    string line;
    // Simple parallel tracking arrays
    string usernames[100];
    int exceptionCounts[100] = {0};
    int totalUniqueUsers = 0;

    while (getline(inFile, line)) {
        if (line.empty()) continue;

        // Find our delimiter ':'
        size_t colonPos = line.find(':');
        if (colonPos == string::npos) continue;

        string name = line.substr(0, colonPos);
        string query = line.substr(colonPos + 1);

        // --- 1. Track the Username for Max Calculation ---
        bool found = false;
        for (int i = 0; i < totalUniqueUsers; i++) {
            if (usernames[i] == name) {
                exceptionCounts[i]++;
                found = true;
                break;
            }
        }
        if (!found && totalUniqueUsers < 100) {
            usernames[totalUniqueUsers] = name;
            exceptionCounts[totalUniqueUsers] = 1;
            totalUniqueUsers++;
        }

        // --- 2. Calculate Word Count for This Query ---
        stringstream wordCheck(query);
        string singleWord;
        int wordCount = 0;
        while (wordCheck >> singleWord) {
            wordCount++;
        }
        cout << "Query: \"" << query << "\" -> Word Count: " << wordCount << endl;
    }
    inFile.close();

    // --- 3. Determine the Maximum Violator ---
    if (totalUniqueUsers > 0) {
        int maxIndex = 0;
        for (int i = 1; i < totalUniqueUsers; i++) {
            if (exceptionCounts[i] > exceptionCounts[maxIndex]) {
                maxIndex = i;
            }
        }
        cout << "\nUser with maximum exceptions: " << usernames[maxIndex] 
             << " (" << exceptionCounts[maxIndex] << " exceptions)" << endl;
    }
}

int main(){
	MedicalChatBox med;
	LegalChatBox leg;
	TechnologyChatBox tec;
	GeneralChatBox gen;
	
	User u1("Treem", "Paxtan", "general", 19);
	
	string ztoopidquery = "skibidi toilet";
	try{
		u1.Ask(ztoopidquery, med, leg, tec, gen);
	}
	catch(Bot_Exception& b){
		cout<<"Error: "<<b.getMessage()<<endl;
		ofstream out("error_log.txt", ios::app);
		if(out.is_open()){
			out<<u1.getUserName()<<":"<<ztoopidquery<<endl;
			out.close();
		}
		else{cerr<<"Error: Unable to open file."<<endl;}
	}
	
	cout << "\n--- Run Analysis System ---" << endl;
    Analysis();
	
	return 0;
}

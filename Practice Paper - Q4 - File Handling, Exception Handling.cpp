#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class SystemAlert{
	int alertLevel;
	string errorMessage;
	public:
		SystemAlert(int a, string e): alertLevel(a), errorMessage(e){}
		string getError() const {
			return errorMessage;
		}
		int getLevel() const {
			return alertLevel;
		}
};

void runDiagnostic(string componentName, int stressTestLoad){
	if(stressTestLoad < 0){
		throw SystemAlert(1, "Invalid Load Metric");
	}
	else if(stressTestLoad > 100){
		throw SystemAlert(3, "Thermal Threshold Breached");
	}
	else{
		ofstream out("security_audit.log", ios::app);
		if(out.is_open()){
			out<<"[SAFE] Component: "<<componentName<<" | Load: "<<stressTestLoad<<endl;
			out.close();
			cout<<"Diagnostic logged successfully for "<<componentName<<endl;
		}
		else{
			cerr<<"Error: Unable to open file."<<endl;
		}
	}
}

void executeLogAnalysis(){
	ifstream in("security_audit.log");
	if(in.is_open()){
		string line;
		int totalEntries = 0;
		int safeEntries = 0;
		while(getline(in, line)){
			totalEntries++;
			if (line.find("[SAFE]") != string::npos) {
                safeEntries++;
            }
		}
		in.close();
		cout << "=== Security Audit Log Analysis ===\n";
        cout << "Total Log Entries Processed: " << totalEntries << "\n";
        cout << "Total Safely Recorded Entry Count: " << safeEntries << "\n";
	}
	else{
		cerr<<"Error: Unable to open file."<<endl;
	}
}

int main() {
    // Test Case 1: Trigger Lower Exception Boundary
    try {
        runDiagnostic("Processor_Core_0", -15);
    }
    catch (const SystemAlert& s) { // Fixed catch location (outside try braces)
        cout << "Caught Exception [Level " << s.getLevel() << "]: " << s.getError() << "\n";
    }

    // Test Case 2: Safe Condition Logging
    try {
        runDiagnostic("Graphics_Engine_1", 45);
        runDiagnostic("Memory_Controller", 72);
    }
    catch (const SystemAlert& s) {
        cout << "Caught Exception: " << s.getError() << "\n";
    }

    // Test Case 3: Trigger Upper Exception Boundary
    try {
        runDiagnostic("Power_Supply_Unit", 120);
    }
    catch (const SystemAlert& s) {
        cout << "Caught Exception [Level " << s.getLevel() << "]: " << s.getError() << "\n";
    }

    // Run the final file analysis reporting module
    cout << "\nRunning system file analysis metrics...\n";
    executeLogAnalysis();

    return 0;
}

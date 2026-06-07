#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class SensorFault{
	int sensorID;
	string faultType;
	public:
		SensorFault(int s, string f): sensorID(s), faultType(f){}
		int getID() const{
			return sensorID;
		}
		string getFault() const{
			return faultType;
		}
};

void monitorTelemetry(string segmentName, double internalPressure){
	if(internalPressure < 0.0){
		throw SensorFault(101, "Vacuum Pressure Collapse");
	}
	else if(internalPressure > 550.5){
		throw SensorFault(505, "Overpressure Danger Threshold");
	}
	else{
		ofstream out("telemetry_stream.log", ios::app);
		if(out.is_open()){
			out<<"[OPERATIONAL] Segment: "<<segmentName<<" | Pressure: "<<internalPressure<<endl;
			out.close();
		}
		else{
			cerr<<"Error: Unable to open file."<<endl;
		}
	}
}

void runSystemAudit(){
	ifstream in("telemetry_stream.log");
	if(in.is_open()){
		string line;
		int totalentries = 0;
		int operationalentries = 0;
		double sum = 0;
		double average;
		while(getline(in, line)){
			totalentries++;
			if(line.find("[OPERATIONAL]") != string::npos){
				string target = "Pressure: ";
				size_t pos = line.find(target);
				if(pos != string::npos){
					string value_string = line.substr(pos + target.length());
					sum += stod(value_string);
					operationalentries++;
				}
			}
		}
		average = sum / operationalentries;
		cout<<"---System Audit---"<<endl;
		cout<<"Total Entries: "<<totalentries<<" | Operational Entries: "<<operationalentries<<endl;
		cout<<"Average Operational Pressure: "<<average<<endl;
		in.close();
	}
	else{
		cerr<<"Error: Unable to open file."<<endl;
	}
}

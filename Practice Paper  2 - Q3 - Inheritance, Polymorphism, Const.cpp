#include<iostream>
#include<string>
using namespace std;

class VehicleSpace{
	protected:
		static int count;
		int spaceID = 0;
		string bayCode;
		double baseHourlyRate;
	public:
		VehicleSpace(string b, double r): bayCode(b), baseHourlyRate(r){
			count++;
			spaceID += count;
		}
		virtual bool validateVehicleAccess(double vehicleWeight) const = 0;
		virtual double calculateParkingFee(int totalHours) const{
			return totalHours * baseHourlyRate;
		}
		virtual ~VehicleSpace(){}
};
int VehicleSpace::count = 0;

class StandardSpace: public VehicleSpace{
	public:
		StandardSpace(string b, double r): VehicleSpace(b, r){}
		bool validateVehicleAccess(double vehicleWeight) const override{
			if(vehicleWeight > 3500.0){
				return false;
			}
			else{
				return true;
			}
		}
};

class ChargingSpace: public VehicleSpace{
	int kwOutputRating;
	bool hasFastCharger;
	public:
		ChargingSpace(string b, double r, int k, bool h): VehicleSpace(b, r), kwOutputRating(k), hasFastCharger(h){}
		bool validateVehicleAccess(double vehicleWeight) const override{
			if(vehicleWeight > 2200.0){
				return false;
			}
			else{
				return true;
			}
		}
		double calculateParkingFee(int totalHours) const override{
			if(hasFastCharger){
				return VehicleSpace::calculateParkingFee(totalHours) + VehicleSpace::calculateParkingFee(totalHours) * 0.25;
			}
			else{
				return VehicleSpace::calculateParkingFee(totalHours);
			}
		}
};

#include<iostream>
#include<string>
using namespace std;

class Item{
	protected:
		static int counter;
		int ID = 0;
		string SKU;
		double weight;
		double baseStorageCost;
	public:
		Item(string s, double w, double b): SKU(s), weight(w), baseStorageCost(b){ 
			counter++;
			ID += counter;
		}
		virtual bool verifyStorageConditions() const = 0;
		virtual double computeFinalTariff() const {
			return weight * baseStorageCost;
		}
		virtual ~Item(){}
};

int Item::counter = 0;

class PerishableGoods: public Item{
	int daysToExpiration;
	double requiredTemperature;
	public:
		PerishableGoods(string s, double w, double b, int d, double r): Item(s, w, b), daysToExpiration(d), requiredTemperature(r){}
		bool verifyStorageConditions() const override{
			if(daysToExpiration > 2 && requiredTemperature < 4.0){
				return true;
			}
			else{
				return false;
			}
		}
		double computeFinalTariff() const override{
			double tariff = Item::computeFinalTariff();
			if(daysToExpiration < 5){
				return tariff + tariff * 0.2;
			}
			else{
				return tariff;
			}
		}
};


class Electronics: public Item{
	int wattageRating;
	bool isFragile;
	public:
		Electronics(string s, double w, double b, int r, bool f): Item(s, w, b), wattageRating(r), isFragile(f){}
		bool verifyStorageConditions() const override{
			if(isFragile && weight>25.0){
				return false;
			}
			else{
				return true;
			}
		}
};


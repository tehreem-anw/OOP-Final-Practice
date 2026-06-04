#include <iostream>
#include <string>
using namespace std;

// ==========================================
// 1. STOCK CLASSES
// ==========================================

class Stock {
private:
    string symbol;
    string companyName;
    double price;
    int availableQuantity;
    int maxQuantityPerInvestor;
    int stockCategoryQuantity;

public:
    // Parameterized Constructor
    Stock(string sym, string name, double prc, int availQty, int maxQty, int catQty)
        : symbol(sym), companyName(name), price(prc), availableQuantity(availQty), 
          maxQuantityPerInvestor(maxQty), stockCategoryQuantity(catQty) {}

    // Getters for all attributes
    string getSymbol() const { return symbol; }
    string getCompanyName() const { return companyName; }
    double getPrice() const { return price; }
    int getAvailableQuantity() const { return availableQuantity; }
    int getMaxQuantityPerInvestor() const { return maxQuantityPerInvestor; }
    int getStockCategoryQuantity() const { return stockCategoryQuantity; }

    // Virtual function
    virtual bool isEligibleToBuy(int purchaseQuantity);

    // Defined function as per requirement
    void displayInfo() const {
        cout << "Symbol: " << symbol 
                  << ", Company Name: " << companyName 
                  << ", Price: " << price 
                  << ", Available Quantity: " << availableQuantity 
                  << ", Max Quantity Per Investor: " << maxQuantityPerInvestor 
                  << ", Category Quantity: " << stockCategoryQuantity << endl;
    }

	// Operator Overloading (!=)
	bool operator != (const Stock& s){
		return (this->companyName != s.companyName || this->symbol != s.symbol);
	}

    virtual ~Stock() {}
};

class PharmaStock : public Stock {
public:
    // Constructor calling parent constructor
    PharmaStock(string sym, string name, double prc, int availQty, int maxQty, int catQty)
        : Stock(sym, name, prc, availQty, maxQty, catQty) {}

    bool isEligibleToBuy(int purchaseQuantity) override;
};

class TechStock : public Stock {
public:
    // Constructor calling parent constructor
    TechStock(string sym, string name, double prc, int availQty, int maxQty, int catQty)
        : Stock(sym, name, prc, availQty, maxQty, catQty) {}

    bool isEligibleToBuy(int purchaseQuantity) override;
};

// ==========================================
// 2. INVESTOR CLASSES
// ==========================================

class Investor {
private:
    string name;
    string CNIC;
    string email;
    int availableFunds;
    bool hasLoan;

public:
    // Parameterized Constructor
    Investor(string nm, string cnic, string em, int funds, bool loan)
        : name(nm), CNIC(cnic), email(em), availableFunds(funds), hasLoan(loan) {}

    // Getters for all attributes
    string getName() const { return name; }
    string getCNIC() const { return CNIC; }
    string getEmail() const { return email; }
    int getAvailableFunds() const { return availableFunds; }
    bool getHasLoan() const { return hasLoan; }

    // Pure Virtual Function
    virtual bool canBuyStock(Stock& stock, int purchaseQuantity) = 0;

    virtual ~Investor() {}
};

class DayTrader : public Investor {
public:
    // Constructor calling parent constructor
    DayTrader(string nm, string cnic, string em, int funds, bool loan)
        : Investor(nm, cnic, em, funds, loan) {}

    bool canBuyStock(Stock& stock, int purchaseQuantity) override;
};

class LongTermInvestor : public Investor {
public:
    // Constructor calling parent constructor
    LongTermInvestor(string nm, string cnic, string em, int funds, bool loan)
        : Investor(nm, cnic, em, funds, loan) {}

    bool canBuyStock(Stock& stock, int purchaseQuantity) override;
};

// ==========================================
// 3. MARKET CLASS
// ==========================================

class Market {
private:
    Stock** stock; // Dynamic array representing composition/aggregation list of Stock pointers
    int numStocks;

public:
    // Parameterized Constructor
    Market(int capacity = 100) {
        stock = new Stock*[capacity];
        numStocks = 0;
    }

    // Getters for attributes
    Stock** getStock() const { return stock; }
    
    // Defined function as per requirement
    int getNumStocks() const {
        return numStocks;
    }

    // Signatures for skeleton
    void addStock(Stock* s) {
        // Skeleton implementation
    }

    void tradeStocks() {
        // Skeleton implementation
    }

    ~Market() {
        delete[] stock;
    }
};

bool Stock::isEligibleToBuy(int purchaseQuantity){
	if(purchaseQuantity > 0){
		if(purchaseQuantity < maxQuantityPerInvestor && purchaseQuantity < availableQuantity){
			return true;
		}
		else{
			return false;
		}
	}
	else{
		cout<<"Error: Invalid purchase quantity entered."<<endl;
		return false;
	}
}
bool TechStock::isEligibleToBuy(int purchaseQuantity){
	if(Stock::isEligibleToBuy(purchaseQuantity)){
		if(purchaseQuantity == 100 || purchaseQuantity < 100)
			if(purchaseQuantity % 10 == 0){
				return true;
			}
			else{
				cout<<"Error: Purchase Quantity not a multiple of 10."<<endl;
				return false;
			}
		else{
			cout<<"Error: Max purchase quantity of TechStock is 100."<<endl;
			return false;
		}
	}
	else{
		cout<<"Error: Basic conditions not fulfilled."<<endl;
		return false;
	}
}
bool PharmaStock::isEligibleToBuy(int purchaseQuantity){
	if(Stock::isEligibleToBuy(purchaseQuantity)){
		if(purchaseQuantity == 50 || purchaseQuantity > 50)
			if(purchaseQuantity % 5 == 0){
				return true;
			}
			else{
				cout<<"Error: Purchase Quantity not a multiple of 5."<<endl;
				return false;
			}
		else{
			cout<<"Error: Min purchase quantity of PharmaStock is 50."<<endl;
			return false;
		}
	}
	else{
		cout<<"Error: Basic conditions not fulfilled."<<endl;
		return false;
	}
}
bool DayTrader::canBuyStock(Stock& stock, int purchaseQuantity){
	if(!gethasLoan()){
		double total = purchaseQuantity * stock.getPrice();
		if(total < getAvailableFunds()){
			if(stock.isEligibleToBuy(purchaseQuantity)){
				return true;
			}
			else{
				cout<<"Error: Not eligible to buy."<<endl;
				return false;
			}
		}
		else{
			cout<<"Error: Total price exceeds available funds."<<endl;
			return false;
		}
	}
	else{
		cout<<"Error: Trader has availed a loan."<<endl;
		return false;
	}
}
bool LongTermInvestor::canBuyStock(Stock& stock, int purchaseQuantity){
	if(!getHasLoan() && getAvailableFunds() > 50000){
		if(purchaseQuantity < stock.getMaxQuantityPerInvestor()){
			if(stock.isEligibleToBuy(purchaseQuantity)){
				return true;
			}
			else{
				cout<<"Error: Not eligible to buy."<<endl;
				return false;
			}
		}
		else{
			cout<<"Error: Purchase quantity exceeds max quantity per investor limit."<<endl;
			return false;
		}
	}
	else{
		cout<<"Error: Trader has availed a loan and has available funds less than 50000."<<endl;
		return false;
	}
}

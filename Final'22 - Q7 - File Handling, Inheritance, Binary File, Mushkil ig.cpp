#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// ==========================================
// 1. CLASS DEFINITIONS WITH INHERITANCE
// ==========================================
class Laptops {
protected:
    int id;
    float price;
    int hdd;
    int ram;
public:
    Laptops() : id(0), price(0.0f), hdd(0), ram(0) {}
    Laptops(int i, float p, int h, int r) : id(i), price(p), hdd(h), ram(r) {}

    float getPrice() const { return price; }

    virtual void printDetails() const {
        cout << "ID: " << id << " | Price: " << price 
             << " | HDD: " << hdd << "GB | RAM: " << ram << "GB";
    }
    virtual ~Laptops() {}
};

class HP : public Laptops {
    int portsCount;
public:
    HP() : Laptops(), portsCount(0) {}
    HP(int i, float p, int h, int r, int pc) : Laptops(i, p, h, r), portsCount(pc) {}

    void printDetails() const override {
        cout << "[HP] ";
        Laptops::printDetails();
        cout << " | Ports: " << portsCount << endl;
    }
};

class Asus : public Laptops {
    int graphicsCardSize;
public:
    Asus() : Laptops(), graphicsCardSize(0) {}
    Asus(int i, float p, int h, int r, int gs) : Laptops(i, p, h, r), graphicsCardSize(gs) {}

    void printDetails() const override {
        cout << "[ASUS] ";
        Laptops::printDetails();
        cout << " | Graphics: " << graphicsCardSize << "GB" << endl;
    }
};

class Dell : public Laptops {
    float screenSize;
public:
    Dell() : Laptops(), screenSize(0.0f) {}
    Dell(int i, float p, int h, int r, float ss) : Laptops(i, p, h, r), screenSize(ss) {}

    void printDetails() const override {
        cout << "[DELL] ";
        Laptops::printDetails();
        cout << " | Screen Size: " << screenSize << " inches" << endl;
    }
};

// ==========================================
// MAIN FUNCTION (FILE HANDLING LOGIC)
// ==========================================
int main() {
    // Accumulators for Part (b)
    float total_hp = 0.0f;
    float total_asus = 0.0f;
    float total_dell = 0.0f;

    // Open binary file for reading
    ifstream inFile("datafile.bin", ios::in | ios::binary);
    if (!inFile) {
        cerr << "Error: Could not open datafile.bin!" << endl;
        return 1;
    }

    cout << "--- Part (a): Extracting and Printing Objects ---" << endl;

    // Temporary object containers for reading
    HP hp_obj;
    Asus asus_obj;
    Dell dell_obj;

    // Reading loop using the exact sequence pattern: HP -> Asus -> Dell
    while (true) {
        // 1. Read HP using simplified C-style cast
        inFile.read((char*)&hp_obj, sizeof(hp_obj));
        if (inFile.eof()) break; // Stop looping if end of file is reached
        hp_obj.printDetails();
        total_hp += hp_obj.getPrice();

        // 2. Read Asus using simplified C-style cast
        inFile.read((char*)&asus_obj, sizeof(asus_obj));
        if (inFile.eof()) break;
        asus_obj.printDetails();
        total_asus += asus_obj.getPrice();

        // 3. Read Dell using simplified C-style cast
        inFile.read((char*)&dell_obj, sizeof(dell_obj));
        if (inFile.eof()) break;
        dell_obj.printDetails();
        total_dell += dell_obj.getPrice();
    }
    inFile.close();

    // Calculate absolute total sum
    float grand_total = total_hp + total_asus + total_dell;

    // ==========================================
    // Part (b): Writing to report.txt
    // ==========================================
    ofstream outFile("report.txt", ios::out);
    if (!outFile) {
        cerr << "Error: Could not create report.txt!" << endl;
        return 1;
    }

    // Matching the exact string output format shown in the question diagram
    outFile << "ELECTRONICS SHOP:\n";
    outFile << "-----------------\n";
    outFile << "HP: " << total_hp << " PKR\n";
    outFile << "DELL: " << total_dell << " PKR\n";
    outFile << "ASUS: " << total_asus << " PKR\n\n";
    outFile << "Total: " << grand_total << " PKR\n";

    outFile.close();
    cout << "\n--- Part (b): report.txt generated successfully! ---" << endl;

    return 0;
}


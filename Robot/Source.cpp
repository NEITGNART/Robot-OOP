#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>


using namespace std;

class Alpha;
class Beta;
class Omega;

class MotherShip {
public:

	virtual int Waste_Enery() = 0;
	virtual int Waste_Tine() = 0;
	virtual int Waste_Gold() { return 0; }
	virtual int Waste_Iron() { return 0; }

};

class Alpha : virtual public MotherShip {
	int joule;
	int weightGold;
	int weightIron;
	int wasteTime;
public:
	Alpha() {
		joule = 5000;
		weightGold = 4;
		weightIron = 2;
		wasteTime = 2;
	}
	int Waste_Enery() override {
		return joule;
	}
	int Waste_Tine() override {
		return wasteTime;
	}
	int Waste_Gold() override {
		return weightGold;
	}
	int Waste_Iron() override {
		return weightIron;
	}
};

class Beta : public virtual MotherShip {

protected:
	int watPerHour;
	int joulePerHour;
	int transport;
	int weightGold;
	int wasteTime;
public:
	Beta() {
		joulePerHour = 4000;
		transport = 50;
		wasteTime = 3;
		watPerHour = 200;
		weightGold = 6;
	}
	int Waste_Enery() override {
		return joulePerHour;
	}
	int Waste_Tine() override {
		return wasteTime;
	}
	int Waste_Gold() override {
		return weightGold;
	}
};

class Omega : public virtual MotherShip{
	int watPerHour;
	int joulePerHour;
	int weightIron;
	int wasteTime;
public:
	Omega(){
		watPerHour = 300;
		joulePerHour = 6000;
		weightIron = 10;
		wasteTime = 15;
	}
	int Waste_Enery() override {
		return joulePerHour;
	}
	int Waste_Tine() override {
		return wasteTime;
	}
	int Waste_Iron() override {
		return weightIron;
	}
};

class Manage {
	vector<MotherShip*> mother;
public:

	void add(MotherShip* p) {
		mother.push_back(p);
	}

	void ReadFile() {
		int n;
		cin >> n;
		cin.ignore();

		string str;
		while (n--) {
			cin >> str;
			if (str == "Beta") {
				Beta* p = new Beta;
				mother.push_back(p);
			}
			else if (str == "Omega") {
				Omega* p = new Omega;
				mother.push_back(p);
			}
			else if (str == "Alpha") {
				Alpha* p = new Alpha;
				mother.push_back(p);
			}
		}
	}
	void Analyst() {
		int cntBeta = 0, cntOmega = 0, cntAlpha = 0;
		for (auto x : mother) {
			if (dynamic_cast<Beta*>(x) != nullptr) {
				++cntBeta;
			}
			else if (dynamic_cast<Omega*>(x) != nullptr) {
				++cntOmega;
			}
			else if (dynamic_cast<Alpha*>(x) != nullptr) {
				++cntAlpha;
			}
		}
		cout << "Alpha: " << cntAlpha << "\n" << "Beta: " << cntBeta << "\n" << "Omega: " << cntOmega << "\n";
	}
	void AnalystEnergyAndTime() {
		int cntEnergy = 0;
		int cntTime = 0;
		for (auto x : mother) {
			cntEnergy += x->Waste_Enery();
			cntTime += x->Waste_Tine();
		}
		cout << "Total Energy to create a whole Robot: " << cntEnergy << " Joule \n" << "Total Number of Time to create a whole Robot: " << cntTime << " Hours\n";
	}
	void AnalystResource() {
		int numberOfGold = 0;
		int numberOfIron = 0;
		for (auto x : mother) {
			if (dynamic_cast<Alpha*>(x) != nullptr) {
				numberOfGold += x->Waste_Gold();
				numberOfIron += x->Waste_Iron();
			}
			else if (dynamic_cast<Beta*>(x) != nullptr) {
				numberOfGold += x->Waste_Gold();
			}
			else if (dynamic_cast<Omega*>(x) != nullptr) {
				numberOfIron += x->Waste_Iron();
			}
		}
		cout << "Total Resource had been used " << "\nGold: " << numberOfGold << "\n" << "Iron: " << numberOfIron << " \n";
	}
};

int main(void) {
	Manage a;
	a.ReadFile();
	cout << "Number of robot had been created: \n";
	a.Analyst();
	a.AnalystEnergyAndTime();
	a.AnalystResource();
	return 0;
}
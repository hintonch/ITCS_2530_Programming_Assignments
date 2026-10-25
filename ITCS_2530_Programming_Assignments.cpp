#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

int main()
{
	// Variables to track production costs and customer pricing
	string garmentType;
	int orderQuantity;
	double materialCost = 0.0;
	double retailPrice = 0.0;
	double grossRevenue = 0.0;
	double totalProductionCost = 0.0;
	double netProfit = 0.0;

	// Introdution Banner
	cout << "-------------------------------------------------" << endl;
	cout << "       EMBROIDERY APPAREL ECOMMERCE SYSTEM       " << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "Calculate Production Costs and Customer Pricing for Embroidery Apparel" << endl;

	// Prompt user for garment type
	cout << "Enter the garment type (e.g., T-shirt, Hoodie, Jacket): ";
	cin >> garmentType;

	// Prompt user for order quantity
	cout << "Enter the order quantity: ";
	cin >> orderQuantity;

	// Input validation restore stream state and clear input buffer
	bool qtyFailed = cin.fail() || orderQuantity <= 0;
	qtyFailed ? cout << "Invalid input. Please enter a positive integer for order quantity." << endl : cout << "Order quantity accepted: " << orderQuantity << endl;

	// Prompt user for material cost
	cout << "Enter the material cost per garment: $";
	cin >> materialCost;

	// Input validation restore stream state and clear input buffer
	bool costFailed = cin.fail() || materialCost <= 0.0;
	costFailed ? (
		cin.clear(),
		cin.ignore(numeric_limits<streamsize>::max(), '\n'),
		cout << "Invalid input. Please enter a positive number for material cost." << endl
	) : cout << "Material cost accepted: $" << fixed << setprecision(2) << materialCost << endl;

	// Prompt user for retail price
	cout << "Enter the retail price per garment: $";
	cin >> retailPrice;

	// Input validation restore stream state and clear input buffer
	bool priceFailed = cin.fail() || retailPrice <= 0.0;
	priceFailed ? cout << "Invalid input. Please enter a positive number for retail price." << endl : cout << "Retail price accepted: $" << fixed << setprecision(2) << retailPrice << endl;

	// Input validation restore stream state and clear input buffer
	//cin.clear();
	//cin.ignore(numeric_limits<streamsize>::max(), '\n');

	// << "\nline 45:Entered garment type: " << garmentType << endl;
	//cout << "line 46:Entered order quantity: " << orderQuantity << endl;
	//cout << "line 47:Entered material cost: $" << fixed << setprecision(2) << materialCost << endl;
	//cout << "line 48:Entered retail price: $" << fixed << setprecision(2) << retailPrice << endl;
	
	//cin >> garmentType >> orderQuantity >> materialCost >> retailPrice;
	//cout << endl;

	// Data calculations
	grossRevenue = retailPrice * orderQuantity;
	totalProductionCost = materialCost * orderQuantity;
	netProfit = grossRevenue - totalProductionCost;

	// Output results
	cout << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << "               COMMERCIAL INVOICE REPORT             " << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << left << setw(30) << "Garment Type: " << right << garmentType << endl;
	cout << left << setw(30) << "Order Quantity: " << right << orderQuantity << " units" << endl;
	cout << left << setw(30) << "Material Cost: " << right << "$" << fixed << setprecision(2) << materialCost << endl;
	cout << left << setw(30) << "Retail Price: " << right << "$" << fixed << setprecision(2) << retailPrice << endl;
	cout << "-----------------------------------------------------" << endl;
	cout << left << setw(30) << "Gross Revenue: " << right << "$" << fixed << setprecision(2) << grossRevenue << endl;
	cout << left << setw(30) << "Total Production Cost: " << right << "$" << fixed << setprecision(2) << totalProductionCost << endl;
	cout << left << setw(30) << "Net Profit: " << right << "$" << fixed << setprecision(2) << netProfit << endl;
	cout << "-----------------------------------------------------" << endl;

	// Save results to a file
	ofstream outFile("report.txt");

	// Check if the file was opened successfully
	if (!outFile) {
		cout << "Error opening file for writing." << endl;
		return 1;
	}

	// Write results to the file
	outFile << "-----------------------------------------------------" << endl;
	outFile << "               COMMERCIAL INVOICE REPORT             " << endl;
	outFile << left << setw(30) << "Garment Type: " << right << garmentType << endl;
	outFile << left << setw(30) << "Order Quantity: " << right << orderQuantity << " units" << endl;
	outFile << left << setw(30) << "Material Cost: " << right << "$" << fixed << setprecision(2) << materialCost << endl;
	outFile << left << setw(30) << "Retail Price: " << right << "$" << fixed << setprecision(2) << retailPrice << endl;
	outFile << "-----------------------------------------------------" << endl;
	outFile << left << setw(30) << "Gross Revenue: " << right << "$" << fixed << setprecision(2) << grossRevenue << endl;
	outFile << left << setw(30) << "Total Production Cost: " << right << "$" << fixed << setprecision(2) << totalProductionCost << endl;
	outFile << left << setw(30) << "Net Profit: " << right << "$" << fixed << setprecision(2) << netProfit << endl;
	outFile << "-----------------------------------------------------" << endl;

	// Close the file
	outFile.close();
	cout << "Report saved to report.txt" << endl;

	return 0;
}



#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <limits> 

using namespace std;

int main()
{
	// Variables to track production costs and customer pricing
	string garmentType;
	int orderQuantity = 0;
	double materialCost = 0.0;
	double retailPrice = 0.0;
	int menuChoice = 0;
	double grossRevenue = 0.0;
	double totalProductionCost = 0.0;
	double netProfit = 0.0;
	double discount = 0.0;
	double discountAmount = 0.0; // Track actual dollar discount for the output report
	string shippingTier = "Standard";

	// Introdution Banner
	cout << "-------------------------------------------------" << endl;
	cout << "       EMBROIDERY APPAREL ECOMMERCE SYSTEM       " << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "1. Calculate Production Costs and Customer Pricing for Embroidery Apparel" << endl;
	cout << "2. Exit Program" << endl;
	cout << "Enter your choice (1 or 2): ";
	cin >> menuChoice;

	// Input validation for menu choice 
	switch (menuChoice) {
	case 1:
		cout << "You selected option 1: Calculate Production Costs and Customer Pricing for Embroidery Apparel" << endl;
		// Clear the input buffer newline so getline works correctly next
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		break;
	case 2:
		cout << "You selected option 2: Exit Program" << endl;
		return 0; // Exit the program
	default:
		cout << "Invalid choice. Please enter 1 or 2." << endl;
		return 1; // Exit the program with an error code
	}

	// Prompt user for garment type 
	cout << "Enter the garment type (e.g., T-shirt, Hoodie, Jacket, Tech Fleece Set): ";
	getline(cin, garmentType);

	// Prompt user for order quantity
	cout << "Enter the order quantity: ";
	cin >> orderQuantity;

	// Input validation restore stream state and clear input buffer
	if (cin.fail() || orderQuantity <= 0) {
		cout << "Invalid input. Please enter a positive integer for order quantity." << endl;
		return 1;
	}
	else {
		cout << "Order quantity accepted: " << orderQuantity << endl;
	}

	// Prompt user for material cost
	cout << "Enter the material cost per garment: $";
	cin >> materialCost;

	// Input validation restore stream state and clear input buffer
	if (cin.fail() || materialCost <= 0.0) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input. Please enter a positive number for material cost." << endl;
		return 1;
	}
	else {
		cout << "Material cost accepted: $" << fixed << setprecision(2) << materialCost << endl;
	}

	// Prompt user for retail price
	cout << "Enter the retail price per garment: $";
	cin >> retailPrice;

	// Input validation restore stream state and clear input buffer
	if (cin.fail() || retailPrice <= 0.0) {
		cout << "Invalid input. Please enter a positive number for retail price." << endl;
		return 1;
	}
	else {
		cout << "Retail price accepted: $" << fixed << setprecision(2) << retailPrice << endl;
	}

	// Data calculations
	grossRevenue = retailPrice * orderQuantity;
	totalProductionCost = materialCost * orderQuantity;
	netProfit = grossRevenue - totalProductionCost;

	// Apply discount based on order quantity
	if (orderQuantity >= 100) {
		discount = 0.10; 
		discountAmount = netProfit * discount;
		netProfit -= discountAmount;
	}
	else if (orderQuantity >= 50) {
		discount = 0.05; 
		discountAmount = netProfit * discount;
		netProfit -= discountAmount;
	}
	else {
		discount = 0.0; 
		discountAmount = 0.0;
	}

	// Shipping tiers based on quantity and production cost
	if (orderQuantity >= 100 && totalProductionCost >= 2000.0) {
		shippingTier = "Express Priority Bulk";
	}
	else if (orderQuantity < 100 && totalProductionCost > 500.0) {
		shippingTier = "Standard Premium Handling";
	}
	else {
		shippingTier = "Basic Economy Ground";
	}

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
	cout << left << setw(30) << "Bulk Discount: " << right << "-$" << fixed << setprecision(2) << discountAmount << endl;
	cout << left << setw(30) << "Total Production Cost: " << right << "$" << fixed << setprecision(2) << totalProductionCost << endl;
	cout << left << setw(30) << "Net Profit: " << right << "$" << fixed << setprecision(2) << netProfit << endl;
	cout << left << setw(30) << "Assigned Shipping Tier: " << right << shippingTier << endl;
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
	outFile << left << setw(30) << "Bulk Discount: " << right << "-$" << fixed << setprecision(2) << discountAmount << endl;
	outFile << left << setw(30) << "Total Production Cost: " << right << "$" << fixed << setprecision(2) << totalProductionCost << endl;
	outFile << left << setw(30) << "Net Profit: " << right << "$" << fixed << setprecision(2) << netProfit << endl;
	outFile << left << setw(30) << "Assigned Shipping Tier: " << right << shippingTier << endl;
	outFile << "-----------------------------------------------------" << endl;

	// Close the file
	outFile.close();
	cout << "Report saved to report.txt" << endl;

	return 0;
}

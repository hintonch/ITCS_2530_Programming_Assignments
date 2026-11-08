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
	bool hasOrderData = false; // Track if user has entered order details yet

	// Repeat the menu until the user chooses to exit
	do {
		// Introdution Banner
		cout << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "       EMBROIDERY APPAREL ECOMMERCE SYSTEM       " << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "1. Enter Order Details and Calculate Costs" << endl;
		cout << "2. View Commercial Invoice Report" << endl;
		cout << "3. View Assigned Shipping Tier & Discount Summary" << endl;
		cout << "4. Exit Program" << endl;
		cout << "Enter your choice (1-4): ";
		cin >> menuChoice;

		// Check if menu input failed
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			menuChoice = 0;
		}

		// Handle menu selection
		switch (menuChoice) {
		case 1:
			cout << "You selected option 1: Enter Order Details and Calculate Costs" << endl;
			// Clear the input buffer newline so getline works correctly next
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			// Prompt user for garment type 
			cout << "Enter the garment type (e.g., T-shirt, Hoodie, Jacket, Tech Fleece Set): ";
			getline(cin, garmentType);

			// Prompt user for order quantity and validate with while loop
			cout << "Enter the order quantity: ";
			cin >> orderQuantity;

			while (cin.fail() || orderQuantity <= 0) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input. Please enter a positive integer for order quantity: ";
				cin >> orderQuantity;
			}
			cout << "Order quantity accepted: " << orderQuantity << endl;

			// Prompt user for material cost and validate with while loop
			cout << "Enter the material cost per garment: $";
			cin >> materialCost;

			while (cin.fail() || materialCost <= 0.0) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input. Please enter a positive number for material cost: $";
				cin >> materialCost;
			}
			cout << "Material cost accepted: $" << fixed << setprecision(2) << materialCost << endl;

			// Prompt user for retail price and validate with while loop
			cout << "Enter the retail price per garment: $";
			cin >> retailPrice;

			while (cin.fail() || retailPrice <= 0.0) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input. Please enter a positive number for retail price: $";
				cin >> retailPrice;
			}
			cout << "Retail price accepted: $" << fixed << setprecision(2) << retailPrice << endl;

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

			hasOrderData = true;
			cout << "\nOrder calculations complete! Select Option 2 or 3 from the menu to view reports." << endl;
			break;

		case 2:
			if (!hasOrderData) {
				cout << "\nNo order data found. Please select Option 1 first to enter order details." << endl;
			}
			else {
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

				// Show 3-month recurring profit projection 
				cout << "-----------------------------------------------------" << endl;
				cout << "           3-MONTH RECURRING ORDER PROJECTION        " << endl;
				cout << "-----------------------------------------------------" << endl;
				for (int month = 1; month <= 3; month++) {
					cout << left << setw(25) << "Projected Profit Month " << month << ": "
						<< right << "$" << fixed << setprecision(2) << (netProfit * month) << endl;
				}
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
				outFile << "-----------------------------------------------------" << endl;
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
				outFile << "           3-MONTH RECURRING ORDER PROJECTION        " << endl;
				outFile << "-----------------------------------------------------" << endl;
				for (int month = 1; month <= 3; month++) {
					outFile << left << setw(25) << "Projected Profit Month " << month << ": "
						<< right << "$" << fixed << setprecision(2) << (netProfit * month) << endl;
				}
				outFile << "-----------------------------------------------------" << endl;

				// Close the file
				outFile.close();
				cout << "Report saved to report.txt" << endl;
			}
			break;

		case 3:
			if (!hasOrderData) {
				cout << "\nNo order data found. Please select Option 1 first to enter order details." << endl;
			}
			else {
				cout << endl;
				cout << "-----------------------------------------------------" << endl;
				cout << "        SHIPPING TIER & BULK DISCOUNT SUMMARY        " << endl;
				cout << "-----------------------------------------------------" << endl;
				cout << left << setw(30) << "Garment Type: " << right << garmentType << endl;
				cout << left << setw(30) << "Order Quantity: " << right << orderQuantity << " units" << endl;
				cout << left << setw(30) << "Total Production Cost: " << right << "$" << fixed << setprecision(2) << totalProductionCost << endl;
				cout << left << setw(30) << "Applied Bulk Discount: " << right << fixed << setprecision(0) << (discount * 100) << "%" << endl;
				cout << left << setw(30) << "Assigned Shipping Tier: " << right << shippingTier << endl;
				cout << "-----------------------------------------------------" << endl;
			}
			break;

		case 4:
			cout << "You selected option 4: Exit Program" << endl;
			break;

		default:
			cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
			break;
		}

	} while (menuChoice != 4);

	return 0;
}

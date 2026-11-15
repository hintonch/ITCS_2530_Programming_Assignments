#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <windows.h>

using namespace std;

// Function prototypes
void setColor(int color);
void displayBanner();
void displayMenu();
string getValidGarment();
int getValidQuantity();
double getValidDollarAmount(string promptText);
void collectOrderInput(string& garmentType, int& orderQuantity, double& materialCost, double& retailPrice);
void calculateTotals(int orderQuantity, double materialCost, double retailPrice,
    double& grossRevenue, double& totalProductionCost,
    double& discount, double& discountAmount,
    double& netProfit, string& shippingTier);
void printInvoiceReport(string garmentType, int orderQuantity, double materialCost,
    double retailPrice, double grossRevenue, double discountAmount,
    double totalProductionCost, double netProfit, string shippingTier);
void printShippingSummary(string garmentType, int orderQuantity, double totalProductionCost,
    double discount, string shippingTier);
void saveReportFile(string garmentType, int orderQuantity, double materialCost,
    double retailPrice, double grossRevenue, double discountAmount,
    double totalProductionCost, double netProfit, string shippingTier);

int main()
{
    // Variables to track production costs and customer pricing
    string garmentType = "";
    int orderQuantity = 0;
    double materialCost = 0.0;
    double retailPrice = 0.0;
    int menuChoice = 0;

    double grossRevenue = 0.0;
    double totalProductionCost = 0.0;
    double netProfit = 0.0;
    double discount = 0.0;
    double discountAmount = 0.0;
    string shippingTier = "Standard";
    bool orderEntered = false;

    displayBanner();

    // Keep showing the menu until the user selects 4 to exit
    do {
        displayMenu();
        cin >> menuChoice;

        // Check if user typed letters instead of a number
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            menuChoice = 0;
        }
        else {
            cin.ignore(1000, '\n');
        }

        switch (menuChoice) {
        case 1:
            setColor(11);
            cout << "\nYou selected Option 1: Enter Order Details and Calculate Costs" << endl;
            setColor(7);

            collectOrderInput(garmentType, orderQuantity, materialCost, retailPrice);

            calculateTotals(orderQuantity, materialCost, retailPrice,
                grossRevenue, totalProductionCost,
                discount, discountAmount, netProfit, shippingTier);

            orderEntered = true;
            setColor(10);
            cout << "\nOrder calculations complete! Select Option 2 or 3 from the menu to view reports." << endl;
            setColor(7);
            break;

        case 2:
            if (!orderEntered) {
                setColor(14);
                cout << "\nNo order data found. Please select Option 1 first to enter order details." << endl;
                setColor(7);
            }
            else {
                printInvoiceReport(garmentType, orderQuantity, materialCost,
                    retailPrice, grossRevenue, discountAmount,
                    totalProductionCost, netProfit, shippingTier);

                saveReportFile(garmentType, orderQuantity, materialCost,
                    retailPrice, grossRevenue, discountAmount,
                    totalProductionCost, netProfit, shippingTier);
            }
            break;

        case 3:
            if (!orderEntered) {
                setColor(14);
                cout << "\nNo order data found. Please select Option 1 first to enter order details." << endl;
                setColor(7);
            }
            else {
                printShippingSummary(garmentType, orderQuantity, totalProductionCost,
                    discount, shippingTier);
            }
            break;

        case 4:
            setColor(11);
            cout << "\nThank you for using the Embroidery Apparel Ecommerce System. Goodbye!" << endl;
            setColor(7);
            break;

        default:
            setColor(12);
            cout << "\nInvalid choice. Please enter a number between 1 and 4." << endl;
            setColor(7);
            break;
        }

    } while (menuChoice != 4);

    return 0;
}

// Changes console text color on Windows (7 = white, 10 = green, 11 = cyan, 12 = red, 14 = yellow)
void setColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Displays welcome banner
void displayBanner()
{
    setColor(11);
    cout << "=====================================================" << endl;
    cout << "                EMBROIDERY APPAREL SYSTEM            " << endl;
    cout << "    Custom Production, Pricing & Profit Estimator    " << endl;
    cout << "=====================================================" << endl;
    setColor(7);
}

// Displays the main menu
void displayMenu()
{
    setColor(11);
    cout << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "                      MAIN MENU                      " << endl;
    cout << "-----------------------------------------------------" << endl;
    setColor(7);
    cout << "1. Enter Order Details and Calculate Costs" << endl;
    cout << "2. View Commercial Invoice Report & Save File" << endl;
    cout << "3. View Assigned Shipping Tier & Discount Summary" << endl;
    cout << "4. Exit Program" << endl;
    setColor(14);
    cout << "Enter your choice (1-4): ";
    setColor(7);
}

// Gets and validates a non-empty garment name
string getValidGarment()
{
    string garment = "";
    cout << "Enter the garment type (e.g., T-shirt, Hoodie, Tech Fleece Set): ";
    getline(cin, garment);

    while (garment == "") {
        setColor(12);
        cout << "Invalid input. Garment type cannot be blank. Please enter again: ";
        setColor(7);
        getline(cin, garment);
    }

    return garment;
}

// Gets and validates a positive whole number for quantity
int getValidQuantity()
{
    int qty = 0;
    cout << "Enter the order quantity: ";
    cin >> qty;

    while (cin.fail() || qty <= 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        setColor(12);
        cout << "Invalid input. Please enter a positive whole number: ";
        setColor(7);
        cin >> qty;
    }

    cin.ignore(1000, '\n');
    return qty;
}

// Gets and validates a positive dollar amount
double getValidDollarAmount(string promptText)
{
    double amount = 0.0;
    cout << promptText;
    cin >> amount;

    while (cin.fail() || amount <= 0.0) {
        cin.clear();
        cin.ignore(1000, '\n');
        setColor(12);
        cout << "Invalid input. Please enter a positive dollar amount: $";
        setColor(7);
        cin >> amount;
    }

    cin.ignore(1000, '\n');
    return amount;
}

// Collects all inputs from the user
void collectOrderInput(string& garmentType, int& orderQuantity, double& materialCost, double& retailPrice)
{
    garmentType = getValidGarment();

    orderQuantity = getValidQuantity();
    setColor(10);
    cout << "Order quantity accepted: " << orderQuantity << endl;
    setColor(7);

    materialCost = getValidDollarAmount("Enter the material cost per garment: $");
    setColor(10);
    cout << "Material cost accepted: $" << fixed << setprecision(2) << materialCost << endl;
    setColor(7);

    retailPrice = getValidDollarAmount("Enter the retail price per garment: $");
    setColor(10);
    cout << "Retail price accepted: $" << fixed << setprecision(2) << retailPrice << endl;
    setColor(7);
}

// Calculates revenue, bulk discount, net profit, and shipping tier
void calculateTotals(int orderQuantity, double materialCost, double retailPrice,
    double& grossRevenue, double& totalProductionCost,
    double& discount, double& discountAmount,
    double& netProfit, string& shippingTier)
{
    grossRevenue = retailPrice * orderQuantity;
    totalProductionCost = materialCost * orderQuantity;
    netProfit = grossRevenue - totalProductionCost;

    // Bulk discount rules
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

    // Shipping tier rules using compound boolean conditions
    if (orderQuantity >= 100 && totalProductionCost >= 2000.0) {
        shippingTier = "Express Priority Bulk";
    }
    else if (orderQuantity < 100 && totalProductionCost > 500.0) {
        shippingTier = "Standard Premium Handling";
    }
    else {
        shippingTier = "Basic Economy Ground";
    }
}

// Displays the full invoice report and 3-month projection
void printInvoiceReport(string garmentType, int orderQuantity, double materialCost,
    double retailPrice, double grossRevenue, double discountAmount,
    double totalProductionCost, double netProfit, string shippingTier)
{
    setColor(11);
    cout << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "               COMMERCIAL INVOICE REPORT             " << endl;
    cout << "-----------------------------------------------------" << endl;
    setColor(7);

    cout << left << setw(30) << "Garment Type: " << right << garmentType << endl;
    cout << left << setw(30) << "Order Quantity: " << right << orderQuantity << " units" << endl;
    cout << left << setw(30) << "Material Cost: " << right << "$" << fixed << setprecision(2) << materialCost << endl;
    cout << left << setw(30) << "Retail Price: " << right << "$" << fixed << setprecision(2) << retailPrice << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << left << setw(30) << "Gross Revenue: " << right << "$" << fixed << setprecision(2) << grossRevenue << endl;
    cout << left << setw(30) << "Bulk Discount: " << right << "-$" << fixed << setprecision(2) << discountAmount << endl;
    cout << left << setw(30) << "Total Production Cost: " << right << "$" << fixed << setprecision(2) << totalProductionCost << endl;
    setColor(10);
    cout << left << setw(30) << "Net Profit: " << right << "$" << fixed << setprecision(2) << netProfit << endl;
    setColor(7);
    cout << left << setw(30) << "Assigned Shipping Tier: " << right << shippingTier << endl;
    setColor(11);
    cout << "-----------------------------------------------------" << endl;
    cout << "           3-MONTH RECURRING ORDER PROJECTION        " << endl;
    cout << "-----------------------------------------------------" << endl;
    setColor(7);
    for (int month = 1; month <= 3; month++) {
	    cout << left << setw(25) << "Projected Profit Month " << month << ": "
		    << right << "$" << fixed << setprecision(2) << (netProfit * month) << endl;
    }
    cout << "-----------------------------------------------------" << endl;
    }
    // Displays shipping tier and discount breakdown
    void printShippingSummary(string garmentType, int orderQuantity, double totalProductionCost,
	    double discount, string shippingTier)
    {
	    setColor(11);
	    cout << endl;
	    cout << "-----------------------------------------------------" << endl;
	    cout << "        SHIPPING TIER & BULK DISCOUNT SUMMARY        " << endl;
	    cout << "-----------------------------------------------------" << endl;
	    setColor(7);
	    cout << left << setw(30) << "Garment Type: " << right << garmentType << endl;
	    cout << left << setw(30) << "Order Quantity: " << right << orderQuantity << " units" << endl;
	    cout << left << setw(30) << "Total Production Cost: " << right << "$" << fixed << setprecision(2) << totalProductionCost << endl;
	    cout << left << setw(30) << "Applied Bulk Discount: " << right << fixed << setprecision(0) << (discount * 100) << "%" << endl;
	    cout << left << setw(30) << "Assigned Shipping Tier: " << right << shippingTier << endl;
	    cout << "-----------------------------------------------------" << endl;
    }
    // Saves the invoice report to report.txt
    void saveReportFile(string garmentType, int orderQuantity, double materialCost,
	    double retailPrice, double grossRevenue, double discountAmount,
	    double totalProductionCost, double netProfit, string shippingTier)
    {
	    ofstream outFile("report.txt");
	    if (!outFile) {
		    setColor(12);
		    cout << "Error opening report.txt for writing." << endl;
		    setColor(7);
		    return;
	    }
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
	    outFile.close();
	    setColor(10);
	    cout << "Report successfully saved to report.txt" << endl;
	    setColor(7);
    }
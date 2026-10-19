#include <iostream>
#include <string>

using namespace std;

int main()
{
    // Variables for user information and calculations
    string garmentType;
    int itemQuantity;
    string customDetails;
    double garmentPrice;
    double embroideryFee;
    double shippingCost;
    double totalCost;

    cout << "Welcome to the Custom Embroidery Ordering System!" << endl;
    cout << "------------------------------------------------" << endl;

    // 1. Gather garment information
    cout << "What type of garments do you like embroidered? (hoodies, tech fleece sets, joggers): ";
    getline(cin, garmentType);

    // Prompt user for the corresponding base price to allow calculations without if-statements
    cout << "Enter the price for your selection (hoodies=$50, tech fleece=$100, joggers=$30): $";
    cin >> garmentPrice;

    cout << "How many items would you like?: ";
    cin >> itemQuantity;
    cin.ignore(); // Clears the newline character so getline works next

    // 2. Gather custom design details
    cout << "Is there any custom embroidery you would like to add?: ";
    getline(cin, customDetails);

    cout << "Enter the embroidery fee (Enter 50 for custom embroidery, 0 for none): $";
    cin >> embroideryFee;
    cin.ignore();

    // 3. Gather shipping preferences
    string shippingSpeed;
    cout << "How fast do you want your items shipped? (next day, 2 day, standard 5-7 days): ";
    getline(cin, shippingSpeed);

    cout << "Enter matching shipping cost (next day=$40, 2 day=$25, standard=$12): $";
    cin >> shippingCost;

    // 4. Calculate total order balance
    totalCost = (garmentPrice * itemQuantity) + embroideryFee + shippingCost;

    // 5. Display the final summary paragraph
    cout << endl;
    cout << "Thank you for your order! You selected custom embroidered " << garmentType << " and requested " << itemQuantity << " item(s)." << endl;
    cout << "For your design, you added: \"" << customDetails << "\"." << endl;
    cout << "Your order will be sent via " << shippingSpeed << " shipping." << endl;
    cout << "Based on your selections, your total calculated order balance comes out to: $" << totalCost << "." << endl;
    cout << "We will begin stitching your custom items soon!" << endl;

    return 0;
}
// Forgot to add commit message displayed on assignment
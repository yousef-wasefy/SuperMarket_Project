#include <iostream> 
using namespace std;
int main() {
    string order;
    
    cout << "Enter your order: ";
    getline(cin, order);
    
    cout << "Your current order is: " << order << endl;
    
    cout << "Would you like to modify your order? (Y/N): ";
    char choice;
    cin >> choice;
    
    if (choice == 'Y' || choice == 'y') {
        cin.ignore(); // Clear input buffer
        cout << "Enter your new order: ";
        getline(cin, order);
        cout << "Your updated order is: " << order << endl;
    } else {
        cout << "Thank you for your order!" << endl;
    }
    
    return 0;
}



#include<iostream>
#include<string>
#include<vector>
#include<chrono> //used for the time
#include<ctime>  //used for the time
#include<iomanip> //used for the time
#include<fstream>

using namespace std;
#define max 50 
int currentCustomerIndex = -1;//to save the index
char answer;//to use it in log out 

//ofstream outFile("superMarket.txt", ios::app); // file to save the data
//ifstream inFile("superMarket.txt"); // file to read the data

struct Product
{
    string Code;
    string Name;
    string Category;
    string ProductionDate;
    string ExpiredDate;
    double Price = 0.0;
    int ProductCount = 0; //the quantity of one order (not relatable to the product but to the order)
};

const int NUMBER_OF_PRODUCTS = max;
struct Order
{
    int CustomerID = 0;
    Product list_Of_Products[NUMBER_OF_PRODUCTS]; // that the customer will take
    int OrderCount = 0;  //(عدد المنتجات في الطلب الفعلي (ككل
    double TotalPrice = 0;
} customerOrder[max]; //every client has only one order

struct Customer
{
    int ID = 0;
    string Name;
    string PhoneNumber;
    string Location;
    string Password;
    string userRank;
};

Customer customers[max];
int customerCount = 0;
bool is_logged_in = false; //to check if he has logged in before any access he can do
bool is_logged_out = true; //to check if he has logged out before sign up when he logged in
bool is_admin = false;

const int CATEGORY_COUNT = 5;// at least 5
string productCategories[CATEGORY_COUNT] = { "Dairy", "Beverages", "Bakery", "Snacks", "Frozen Food" };

const int MAX_PRODUCTS = 3; // 3 products per category

//All the products are in the array of products
Product Products[CATEGORY_COUNT][MAX_PRODUCTS] = {
    { // Dairy
        {"D001", "Milk", "Dairy", "2025-03-01", "2025-03-10", 1.50},
        {"D002", "Cheese", "Dairy", "2025-02-25", "2025-03-20", 4.00},
        {"D003", "Butter", "Dairy", "2025-02-28", "2025-04-15", 2.50}
    },
    { // Beverages
        {"B001", "Orange Juice", "Beverages", "2025-03-05", "2025-06-05", 2.00},
        {"B002", "Coca-Cola", "Beverages", "2025-02-15", "2025-08-15", 1.25},
        {"B003", "Green Tea", "Beverages", "2025-01-30", "2025-07-30", 1.75}
    },
    { // Bakery
        {"BK001", "White Bread", "Bakery", "2025-03-08", "2025-03-12", 1.20},
        {"BK002", "Croissant", "Bakery", "2025-03-07", "2025-03-10", 0.99},
        {"BK003", "Chocolate Muffin", "Bakery", "2025-03-06", "2025-03-11", 1.50}
    },
    { // Snacks
        {"S001", "Potato Chips", "Snacks", "2025-02-20", "2025-08-20", 1.75},
        {"S002", "Chocolate Bar", "Snacks", "2025-03-01", "2025-09-01", 1.25},
        {"S003", "Peanuts", "Snacks", "2025-02-18", "2025-12-18", 2.30}
    },
    { // Frozen Food
        {"F001", "Frozen Pizza", "Frozen Food", "2025-02-10", "2026-02-10", 5.50},
        {"F002", "Ice Cream (Vanilla)", "Frozen Food", "2025-02-28", "2026-02-28", 3.99},
        {"F003", "Chicken Nuggets", "Frozen Food", "2025-03-01", "2026-03-01", 6.75}
    }
};

void sign_up(); //Sa3eed
bool log_in(string name, string password, int ID); //Sa3eed
void edit_customer_information(); //nour
void edit_products_information(); //nour
void view_products_menu(); //Doha
void view_the_information_of_the_item_that_the_customer_has_chosen(); //Doha
void word_check(string &name); //Doha
void the_customer_selects_the_goods_he_wants_to_add_to_his_order(); //Mostafa
void Review_his_order(int ID); //Youssef hagras
void the_customer_is_able_to_modify_his_order(int ID); //Mohra
void view_total_price(int ID); //Youssef Ahmed
void log_out(); //Sa3eed
int menu();

int main()
{
    //pull first !!!!
    int choice;
    string name, password;
    int targetID = 0;

    do
    {
        choice = menu();
        switch (choice) //add your case.
        {
        case 1:
            if (is_logged_out) {
                sign_up();
            }
            else {
                cout << "========================================" << endl;
                cout << "#### You Must Logged Out First. ####" << endl;
                answer = 'y';
                cout << "========================================" << endl;
                continue;
            }
            break;
        case 2:
            if (is_logged_out) {
                cout << "========================================" << endl;
                cout << "Enter Your Name:\t\t";
                cin >> name;
                cout << "Enter Your Password:\t\t";
                cin >> password;
                cout << "Enter your ID:\t\t";
                cin >> targetID;
                if (log_in(name, password, targetID))
                {
                    cout << "#### Log In Successfully. ####" << endl;
                }
                else
                {
                    cout << "#### Your Name Or Password Or ID Is Incorrect. Please Try Again ####" << endl;
                    cout << "Sign up if you don't have an account" << endl;
                    answer = 'y';
                    continue;
                }
                cout << "========================================" << endl;
            }
            else {
                cout << "========================================" << endl;
                cout << "#### You Are Already Logged In! You Must Logged Out First. ####" << endl;
                answer = 'y';
                cout << "========================================" << endl;
                continue;
            }
            break;
        case 3:
            view_products_menu();
            break;
        case 4:
            view_the_information_of_the_item_that_the_customer_has_chosen();
            break;
        case 5:
            the_customer_selects_the_goods_he_wants_to_add_to_his_order();
            break;
        case 6:
            Review_his_order(targetID);
            break;
        case 7:
            the_customer_is_able_to_modify_his_order(targetID);
            break;
        case 8:
            view_total_price(targetID);
            break;
        case 9:
            edit_customer_information();
            break;
        case 10:
            if (is_admin)
            {
                edit_products_information();
                break;
            }
        case 11:
            cout << "========================================" << endl;
            char confirm;
            cout << "#### Are You Sure You Want To Log Out?(Y/N) ####" << endl;
            cin >> confirm;
            if (confirm == 'Y' || confirm == 'y') {
                log_out();
                continue;
            }
            else {
                cout << "#### Log Out Cancelled.\n";
            }
            break;
        default:
            cout << "Invalid choice!\nPlease re-enter the correct one\n";
            answer = 'y';
            continue;
        }
        cout << "\nAnother operation? (Y/N)";
        cin >> answer;
    } while (answer == 'Y' || answer == 'y');

    return 0; //pull first !!!!
}

int menu()
{
    int choice;
    cout << "\t\tWelcome to Super Market Online Shopping" << endl;
    cout << "\t\t***************************************" << endl;
    cout << "========================================" << endl;
    cout << "Press\n1. to sign up\n";
    cout << "2. to log in\n";
    cout << "3. to view products menu\n";
    cout << "4. to view the information of the item.\n";
    cout << "5. to add to the order\n";
    cout << "6. to review your order\n";
    cout << "7. to modify your order\n";
    cout << "8. to view the total price\n";
    cout << "9. to edit your informations\n";
    if (is_admin)
    {
        cout << "10. to edit information of product\n";
        cout << "11. to log out\n";
        cout << "========================================" << endl;
    }
    else
    {
        cout << "10. to log out\n";
        cout << "========================================" << endl;
    }
    cin >> choice;
    if (choice != 1 && choice != 2 && choice != 3 && choice != 4)
    {
        if (is_logged_in)
        {
            if (!is_admin && choice == 11) return choice = -1; //any value just to go to the default case
            return choice;
        }
        else
        {
            cout << "Please log in first" << endl;
            return choice = 2;
        }
    }
    return choice;
}

// <<--sign_up-->>
void sign_up() {
    cout << "========================================" << endl;
    Customer NewCustomer;
    cout << "Please choose the rank: admin or customer ?"; cin >> NewCustomer.userRank;
    
    NewCustomer.ID = customerCount + 1;
    cout << "Enter Your Name:\t\t";
    cin >> NewCustomer.Name;
    cout << "Enter Your Phone Number:\t";
    cin >> NewCustomer.PhoneNumber;
    cout << "Enter Your Location:\t\t";
    cin >> NewCustomer.Location;
    cout << "Enter Your Password:\t\t";
    cin >> NewCustomer.Password;
    customers[customerCount] = NewCustomer;
    customerOrder[customerCount].CustomerID = customers[customerCount].ID;
    customerCount++;
    cout << "#### Sign Up Successfully. Your ID(" << NewCustomer.ID << ") ####" << endl;
    cout << "========================================" << endl;
}
//<<--log_in-->>
bool log_in(string name, string password, int ID) {
    for (int i = 0;i <= customerCount;i++) {
        if (customers[i].Name == name && customers[i].Password == password && customers[i].ID == ID)
        {
            currentCustomerIndex = i;
            is_logged_in = true;
            is_logged_out = false;
            if (customers[currentCustomerIndex].userRank[0] == 'a' || customers[currentCustomerIndex].userRank[0] == 'A')
                is_admin = true;
            else
                is_admin = false;
            return true;
        }
    } return false;
}
// <<-- view product menu -->>
void view_products_menu() {
    cout << endl << "\t\t-------------------------------------" << endl;
    cout << "\t\t\tMenu of the products" << endl;
    cout << "\t\t-------------------------------------\n\n";

    for (int cat = 0; cat < CATEGORY_COUNT; cat++) {
        cout << "#" << productCategories[cat] << "\n\n";
        for (int i = 0; i < MAX_PRODUCTS; i++) {
            cout << "  Code  : " << Products[cat][i].Code << endl;
            cout << "  Name  : " << Products[cat][i].Name << endl;
            cout << "  Price : $" << Products[cat][i].Price << endl;
            cout << "-------------------------------------\n";
        }
        cout << endl;
    }
}
// <<-- view_the_information_of_the_item_that_the_customer_has_chosen -->>
void view_the_information_of_the_item_that_the_customer_has_chosen() {
    string name;
    bool found = false;
    cout << "Enter the product name: ";
    cin.ignore();
    getline(cin, name);
    word_check(name);
    for (int cat = 0; cat < CATEGORY_COUNT; cat++) {
        for (int i = 0; i < MAX_PRODUCTS; i++) {
            if (Products[cat][i].Name == name) {
                cout << "\nProduct [ " << Products[cat][i].Code << " ] Information:\n";
                cout << "-------------------------\n";
                cout << "Category      : " << Products[cat][i].Category << endl;
                cout << "Production    : " << Products[cat][i].ProductionDate << endl;
                cout << "Expiration    : " << Products[cat][i].ExpiredDate << endl;
                cout << "Price         : " << Products[cat][i].Price << endl;
                cout << "-------------------------\n\n";
                found = true;
                break;
            }
        }
    }
    if (!found) {
        cout << "\nProduct not found! Please check the code and try again.\n\n";
    }
}
// <<-- word check -->>
void word_check(string &name) {
    char* pOfUserInput = &name[1];
    name[0] = toupper(name[0]);
    while (*pOfUserInput != '\0') {
        *pOfUserInput = tolower(*pOfUserInput);
        ++pOfUserInput;
    }
}
// <<-- Review_his_order -->>
void Review_his_order(int ID)
{
    if (customerOrder[currentCustomerIndex].OrderCount == 0)
    {
        cout << "Your order is empty.\n";
        return;
    }

    double totalPrice = 0;
    cout << "Current Products in your order:\n";
    for (int i = 0; i < customerCount; i++)
    {
        if (customerOrder[i].CustomerID == ID)
        {
            for (int j = 0; j < customerOrder[i].OrderCount; j++) {
                cout << j + 1 << ". " << customerOrder[i].list_Of_Products[j].Name
                << " (Quantity: " << customerOrder[i].list_Of_Products[j].ProductCount
                << ", Price: $" << customerOrder[i].list_Of_Products[j].Price * customerOrder[i].list_Of_Products[j].ProductCount << ")\n";
            }
        }
    }
}
// <<-- view_total_price -->>
void view_total_price(int ID)
{
    if (customerOrder[currentCustomerIndex].OrderCount == 0)
    {
        cout << "Your order is empty.\n";
        return;
    }

    for (int i = 0; i < customerCount; i++)
    {
        if (customerOrder[i].CustomerID == ID)
        {
            double totalPrice = 0;
            cout << "Total Price : ";
            for (int j = 0; j < customerOrder[i].OrderCount; j++)
            {
                totalPrice += customerOrder[i].list_Of_Products[j].Price * customerOrder[i].list_Of_Products[j].ProductCount;
            }
            cout << totalPrice << endl;
        }
    }
}
// <<-- edit_information -->>
void edit_products_information()
{
    int categoryChoice, productChoice, fieldChoice;

    cout << "Select product category to edit:\n";
    cout << "1. Dairy\n2. Beverages\n3. Bakery\n4. Snacks\n5. Frozen Food\n";
    cout << "Enter your choice (1-5): ";
    cin >> categoryChoice;
    categoryChoice = categoryChoice - 1;

    cout << "\nCategory: " << productCategories[categoryChoice] << endl;
    for (int j = 0;j < MAX_PRODUCTS;j++)
    {
        cout << (j + 1) << ".Code: " << Products[categoryChoice][j].Code << "   ";
        cout << "Name: " << Products[categoryChoice][j].Name << endl;
    }

    cout << "\n Select product number to edit (1-3): ";
    cin >> productChoice;
    productChoice = productChoice - 1;

    cout << "\nWhich data do you want to edit?\n";
    cout << "1. Code\n";
    cout << "2. Name\n";
    cout << "3. Category\n";
    cout << "4. Production Date\n";
    cout << "5. Expired Date\n";
    cout << "6. Price\n";
    cout << "Enter your choice (1-6): ";
    cin >> fieldChoice;

    switch (fieldChoice)
    {
    case 1:
        cout << "Enter new code: ";
        cin >> Products[categoryChoice][productChoice].Code;
        break;
    case 2:
        cout << "Enter new Name: ";
        cin.ignore();
        getline(cin,Products[categoryChoice][productChoice].Name);
        break;
    case 3:
        cout << "Enter new Category: ";
        cin >> Products[categoryChoice][productChoice].Category;
        break;
    case 4:
        cout << "Enter new Production Date (YYYY-MM-DD): ";
        cin >> Products[categoryChoice][productChoice].ProductionDate;
        break;
    case 5:
        cout << "Enter new Expired Date (YYYY-MM-DD): ";
        cin >> Products[categoryChoice][productChoice].ExpiredDate;
        break;
    case 6:
        cout << "Enter new Price: ";
        cin >> Products[categoryChoice][productChoice].Price;
        break;
    default:
        cout << "Invalid field choice.\n";
        return;

    }
}
// <<-- the_customer_is_able_to_modify_his_order -->>
void the_customer_is_able_to_modify_his_order(int ID)
{
    int choice;
    if (customerOrder[currentCustomerIndex].OrderCount == 0)
    {
        cout << "Your order is empty.\n";
        return;
    }

    do {
        cout << "\n========== Modify Your Order ==========\n";
        Review_his_order(ID);

        cout << "\nWhat would you like to do?\n";
        cout << "1. Remove an item\n";
        cout << "2. Change quantity of an item\n";
        cout << "3. Add a new product to the order\n";
        cout << "4. Exit modification\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int removeIndex;
            cout << "Enter the number of the product you want to remove: ";
            cin >> removeIndex;
            removeIndex--;

            if (removeIndex >= 0 && removeIndex < customerOrder[currentCustomerIndex].OrderCount)
            {
                for (int i = removeIndex; i < customerOrder[currentCustomerIndex].OrderCount - 1; i++)
                {
                    customerOrder[currentCustomerIndex].list_Of_Products[i] = customerOrder[currentCustomerIndex].list_Of_Products[i + 1]; //shifting                   
                }
                customerOrder[currentCustomerIndex].OrderCount--;
                cout << "Item removed successfully!\n";

                if (customerOrder[currentCustomerIndex].OrderCount == 0)
                {
                    cout << "Your order is empty now.\n";
                    return;
                }
            }
            else {
                cout << "Invalid product number.\n";
            }
            break;
        }

        case 2: {
            int index, newQuantity;
            cout << "Enter the product number you want to change quantity for: ";
            cin >> index;
            index--;

            if (index >= 0 && index < customerOrder[currentCustomerIndex].OrderCount) {
                cout << "Enter the new quantity: ";
                cin >> newQuantity;
                customerOrder[currentCustomerIndex].list_Of_Products[index].ProductCount = newQuantity;
                cout << "Quantity updated successfully!\n";
            }
            else {
                cout << "Invalid product number.\n";
            }
            break;
        }

        case 3: {
            the_customer_selects_the_goods_he_wants_to_add_to_his_order();
            break;
        }

        case 4:
            cout << "Exiting modification...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 4);
}
// <<-- the_customer_selects_the_goods_he_wants_to_add_to_his_order -->>
void the_customer_selects_the_goods_he_wants_to_add_to_his_order()
{
    string name;
    int qnt;
    bool found = false;
    char ans;
    do
    {
        cout << "Enter the product name: ";
        cin.ignore();
        getline(cin, name);
            for (int i = 0; i < CATEGORY_COUNT; i++)
            {
                found = false;
                for (int j = 0; j < MAX_PRODUCTS; j++)
                {
                    for (int n = 0; n < customerOrder[currentCustomerIndex].OrderCount; n++) //عدي على كل الطلبات بتاعته
                    {
                        if (customerOrder[currentCustomerIndex].list_Of_Products[n].Name == name) {
                            found = true;
                            cout << "Enter the quantity: ";
                            cin >> qnt;
                            customerOrder[currentCustomerIndex].list_Of_Products[n].ProductCount += qnt;
                            break;
                        }
                    }
                    if (found) break;
                    if (Products[i][j].Name == name) {
                        found = true;
                        cout << "Enter the quantity: ";
                        cin >> Products[i][j].ProductCount;
                        customerOrder[currentCustomerIndex].list_Of_Products[customerOrder[currentCustomerIndex].OrderCount++] = Products[i][j];
                        cout << "Product added to your order.\n";
                        break;
                    }
                }
                if (found) break;
            }
        if(!found) {
            cout << "Product not found!, please try again" << endl;
            ans = 'y';
            continue;
        }
        cout << "Want to add another product?(Y/N): ";
        cin >> ans;
    } while (ans == 'y' || ans == 'Y');
}
// <<-- edit_customer_information -->>
void edit_customer_information() {
    int choice;
    cout << "Which information would you like to edit?\n";
    cout << "1. Name\n2. Phone Number\n3. Location\n4.Password\nEnter choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
        cout << "Enter new name: ";
        cin >> customers[currentCustomerIndex].Name;
        cout << "Name updated successfully.\n";
        break;
    case 2:
        cout << "Enter new phone number: ";
        cin >> customers[currentCustomerIndex].PhoneNumber;
        cout << "Phone number updated successfully.\n";
        break;
    case 3:
        cout << "Enter new location: ";
        cin >> customers[currentCustomerIndex].Location;
        cout << "Location updated successfully.\n";
        break;
    case 4:
        cout << "Enter new password: ";
        cin >> customers[currentCustomerIndex].Password;
        cout << "Password updated.\n";
        break;
    default:
        cout << "Invalid choice.\n";
    }
	cout << "Your information has been updated successfully.\n";
	cout << "Name: " << customers[currentCustomerIndex].Name << endl;
	cout << "Phone Number: " << customers[currentCustomerIndex].PhoneNumber << endl;
	cout << "Location: " << customers[currentCustomerIndex].Location << endl;
	cout << "Password: " << customers[currentCustomerIndex].Password << endl;

	cout << "========================================" << endl;
}
// <<-- log_out -->>
void log_out() {
    cout << "========================================" << endl;
    is_logged_in = false;
    is_logged_out = true;
    is_admin = false;
    currentCustomerIndex = -1;
    cout << "#### You Have Been Succsessfully Logged Out. ####" << endl;
    cout << "#### Thank You For Using Our Online Supermarket!" << endl;
    answer = 'y';
    cout << "========================================" << endl;
}
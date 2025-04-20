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
//ازاي تربط الطلب بعميله؟؟
struct Customer
{
    int ID = 0;
    string Name;
    string PhoneNumber;
    string Location;
    string Password;
};

Customer customers[max];
int customerCount = 0;
bool is_logged_in = false; //to check if he has logged in before any access he can do

const int CATEGORY_COUNT = 5;// at least 5
string productCategories[CATEGORY_COUNT] = { "Dairy", "Beverages", "Bakery", "Snacks", "Frozen Food" };

const int MAX_PRODUCTS = 3; // 3 products per category

//Product dairyProducts[MAX_PRODUCTS] = {
//     {"D001", "Milk", "Dairy", "2025-03-01", "2025-03-10", 1.50},
//     {"D002", "Cheese", "Dairy", "2025-02-25", "2025-03-20", 4.00},
//     {"D003", "Butter", "Dairy", "2025-02-28", "2025-04-15", 2.50} };
//
//Product beveragesProducts[MAX_PRODUCTS] = {
//    {"B001", "Orange Juice", "Beverages", "2025-03-05", "2025-06-05", 2.00},
//    {"B002", "Coca-Cola", "Beverages", "2025-02-15", "2025-08-15", 1.25},
//    {"B003", "Green Tea", "Beverages", "2025-01-30", "2025-07-30", 1.75} };
//
//Product bakeryProducts[MAX_PRODUCTS] = {
//    {"BK001", "White Bread", "Bakery", "2025-03-08", "2025-03-12", 1.20},
//    {"BK002", "Croissant", "Bakery", "2025-03-07", "2025-03-10", 0.99},
//    {"BK003", "Chocolate Muffin", "Bakery", "2025-03-06", "2025-03-11", 1.50} };
//
//Product snacksProducts[MAX_PRODUCTS] = {
//    {"S001", "Potato Chips", "Snacks", "2025-02-20", "2025-08-20", 1.75},
//    {"S002", "Chocolate Bar", "Snacks", "2025-03-01", "2025-09-01", 1.25},
//    {"S003", "Peanuts", "Snacks", "2025-02-18", "2025-12-18", 2.30} };
//
//Product frozenFoodProducts[MAX_PRODUCTS] = {
//    {"F001", "Frozen Pizza", "Frozen Food", "2025-02-10", "2026-02-10", 5.50},
//    {"F002", "Ice Cream (Vanilla)", "Frozen Food", "2025-02-28", "2026-02-28", 3.99},
//    {"F003", "Chicken Nuggets", "Frozen Food", "2025-03-01", "2026-03-01", 6.75} };

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

/*              -->> NOTES <<--
- Don't modify,add or use any new structs or arrays before you tell us and we approve.
- Don't forget to -->["pull"]<-- before you start working , and before you push your work.
- We will finish from the required functions before the midterm,
when we finish we may add new functions and it may take week or more.
- Don't use GPT !!, just make him helps you.
- بالنسبة لموضوع الفايل : انت الاول هتخلص الفانكشن بتاعتك عادي بعدين تبدا تظبط موضوع الفايل بحيث تقرا وتكتب منه
- ممكن تستعين ب gpt في موضوع الفايل بس كون فاهم اللي بيتعمل
- كل واحد مسؤول عن كوده (اكيد هنساعد بعض )
- اتاكد ان الفانكشن بتاعتك بتأدي دورها بشكل كامل مع عدم وجود اي اخطاء في اي مكان في البروجكت
*/

// ظبط الفانكشن بتاعتك من حيث الاسم والنوع والبراميترز اللي هتاخدها
// حاولوا بقدر الامكان تنوعوا في النوع والبراميترز
void sign_up(); //Sa3eed
bool log_in(string name, string password); //Sa3eed
void edit_information(); //nour
void view_products_menu(); //Doha
void view_the_information_of_the_item_that_the_customer_has_chosen(); //Doha
void the_customer_selects_the_goods_he_wants_to_add_to_his_order(); //Mostafa
void Review_his_order(); //Youssef hagras
void the_customer_is_able_to_modify_his_order(); //Mohra
void view_total_price(); //Youssef Ahmed
void log_out(); //Sa3eed
void belong_orders();
int menu();

/*before you start working and before you push your work, please do the following:
git add superMarket.cpp
git commit -m "your message"
git pull
git push
*/

int main()
{
    //pull first !!!!
    int choice;
    char answer;
    string name, password;

    customerOrder[0].OrderCount = 2; // Assuming there are 2 products in that order for testing
    customerOrder[0].list_Of_Products[0] = Products[0][0]; // Adding a product for testing
    customerOrder[0].list_Of_Products[1] = Products[1][1]; // Adding another product for testing
    // Assuming the customer ID is set

    customerOrder[1].CustomerID = customers[customerCount].ID; // Assuming the customer ID is set
    customerOrder[1].OrderCount = 2; // Assuming there is 2 products in that order for testing
    customerOrder[1].list_Of_Products[0] = Products[2][0]; // Adding a product for testing
    customerOrder[1].list_Of_Products[1] = Products[3][1]; // Adding another product for testing

    customerOrder[2].CustomerID = customers[customerCount].ID; // Assuming the customer ID is set
    customerOrder[2].OrderCount = 3; // Assuming there is 3 products in that order for testing
    customerOrder[2].list_Of_Products[0] = Products[4][0]; // Adding a product for testing
    customerOrder[2].list_Of_Products[1] = Products[0][1]; // Adding another product for testing

    do
    {
        choice = menu();
        switch (choice) //add your case.
        {
        case 1:
            sign_up();
            break;
        case 2:
            cout << "========================================" << endl;
            cout << "Enter Your Name:\t\t";
            cin >> name;
            cout << "Enter Your Password:\t\t";
            cin >> password;
            if (log_in(name, password))
            {
                cout << "#### Log In Successfully. ####" << endl;
            }
            else
            {
                cout << "#### Your Name Or Password Is Incorrect. Please Try Again ####" << endl;
                cout << "Sign up if you don't have an account" << endl;
                answer = 'y';
                continue;
            }
            belong_orders();
            cout << "========================================" << endl;
            break;
        case 3:
            view_products_menu();
            break;
        case 4:
            view_the_information_of_the_item_that_the_customer_has_chosen();
            break;
        case 7:
            the_customer_is_able_to_modify_his_order();
            break;
        case 8:
            view_total_price();
            break;
        case 9:
            edit_information();
            break;
        case 10:
            char confirm;
            cout << "#### Are You Sure You Want To Log Out?(Y/N) ####" << endl;
            cin >> confirm;
            if (confirm == 'Y' || confirm == 'y') {
                log_out();
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
    cout << "9. to edit information\n";
    cout << "10. to log out\n";
    cout << "========================================" << endl;
    cin >> choice;
    if (choice != 1 && choice != 2)
    {
        if (is_logged_in) return choice;
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
    customerCount++;
    cout << "#### Sign Up Successfully. Your ID(" << NewCustomer.ID << ") ####" << endl;
    cout << "========================================" << endl;
}
//<<--log_in-->>
bool log_in(string name, string password) {
    for (int i = 0;i <= customerCount;i++) {
        if (customers[i].Name == name && customers[i].Password == password)
        {
            currentCustomerIndex = i;
            is_logged_in = true; //when he log out make it false
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

void view_total_price()
{
    double totalPrice = 0;

    // customerOrder[0].list_Of_Products[0] = dairyProducts[0];
    // customerOrder[0].ProductCount = 2;
    // customerOrder[0].orderTime = getCurrentTimeString();
    // customerOrder[1].list_Of_Products[1] = dairyProducts[1];
    // customerOrder[1].ProductCount = 3;
    // customerOrder[1].orderTime = getCurrentTimeString();

    cout << "Item\t\tquantity\ttotal price" << endl;
    for (int i = 0; i < 3; i++)
    {
        totalPrice = 0;
        cout << "Order number ." << (i + 1) << endl;
        for (int j = 0; j < 3; j++)
        {
            cout << customerOrder[i].list_Of_Products[j].Name;
            cout << "\t\t" << customerOrder[i].list_Of_Products[j].ProductCount;
            cout << "\t\t" << customerOrder[i].list_Of_Products[j].Price * customerOrder[i].list_Of_Products[j].ProductCount;
            cout << endl;
        }
        cout << "Total Price : ";
        for (int j = 0; j < 3; j++)
        {
            totalPrice += customerOrder[i].list_Of_Products[j].Price * customerOrder[i].list_Of_Products[j].ProductCount;
        }
        cout << totalPrice << endl;
        cout << "=========================" << endl;
    }
}

void edit_information()
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

    /*switch (categoryChoice) {
    case 1:
        cout << "\nDairy Products:\n";
        for (int i = 0;i < MAX_PRODUCTS;i++)
        {
            cout << "1. Code: " << dairyProducts[i].Code << "   Name: " << dairyProducts[i].Name << "\n";
        }
            break;
    case 2:
        cout << "\nBeverages Products:\n";
        for (int i = 0;i < MAX_PRODUCTS;i++)
        {
            cout << "1. Code: " << beveragesProducts[i].Code << "   Name: " << beveragesProducts[i].Name << "\n";
        }
            break;
    case 3:
        cout << "\nBakery Products:\n";
        for (int i = 0;i < MAX_PRODUCTS;i++)
        {
            cout << "1. Code: " << bakeryProducts[i].Code << "   Name: " << bakeryProducts[i].Name << "\n";
        }
            break;
    case 4:
        cout << "\nSnacks Products:\n";
        for (int i = 0;i < MAX_PRODUCTS;i++)
        {
            cout << "1. Code: " << snacksProducts[i].Code << "   Name: " << snacksProducts[i].Name << "\n";
        }
            break;
    case 5:
        cout << "\nFrozen Food Products:\n";
        for (int i = 0;i < MAX_PRODUCTS;i++)
        {
            cout << "1. Code: " << frozenFoodProducts[i].Code << "   Name: " << frozenFoodProducts[i].Name << "\n";
        }
            break;
    default:
        cout << "Invalid category choice.\n";
        return;
    }*/

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
    }
    /*switch (categoryChoice) {
    case 1:
        switch (fieldChoice) {
        case 1:
            cout << "Enter new Code: ";
            cin >> dairyProducts[productChoice].Code;
            break;
        case 2:
            cout << "Enter new Name: ";
            cin >> dairyProducts[productChoice].Name;
            break;
        case 3:
            cout << "Enter new Category: ";
            cin >> dairyProducts[productChoice].Category;
            break;
        case 4:
            cout << "Enter new Production Date (YYYY-MM-DD): ";
            cin >> dairyProducts[productChoice].ProductionDate;
            break;
        case 5:
            cout << "Enter new Expired Date (YYYY-MM-DD): ";
            cin >> dairyProducts[productChoice].ExpiredDate;
            break;
        case 6:
            cout << "Enter new Price: ";
            cin >> dairyProducts[productChoice].Price;
            break;
        default:
            cout << "Invalid field choice.\n";
            return;
        }
        break;
    case 2:
        switch (fieldChoice) {
        case 1:
            cout << "Enter new Code: ";
            cin >> beveragesProducts[productChoice].Code;
            break;
        case 2:
            cout << "Enter new Name: ";
            cin >> beveragesProducts[productChoice].Name;
            break;
        case 3:
            cout << "Enter new Category: ";
            cin >> beveragesProducts[productChoice].Category;
            break;
        case 4:
            cout << "Enter new Production Date (YYYY-MM-DD): ";
            cin >> beveragesProducts[productChoice].ProductionDate;
            break;
        case 5:
            cout << "Enter new Expired Date (YYYY-MM-DD): ";
            cin >> beveragesProducts[productChoice].ExpiredDate;
            break;
        case 6:
            cout << "Enter new Price: ";
            cin >> beveragesProducts[productChoice].Price;
            break;
        default:
            cout << "Invalid field choice.\n";
            return;
        }
        break;
    case 3:
        switch (fieldChoice) {
        case 1:
            cout << "Enter new Code: ";
            cin >> bakeryProducts[productChoice].Code;
            break;
        case 2:
            cout << "Enter new Name: ";
            cin >> bakeryProducts[productChoice].Name;
            break;
        case 3:
            cout << "Enter new Category: ";
            cin >> bakeryProducts[productChoice].Category;
            break;
        case 4:
            cout << "Enter new Production Date (YYYY-MM-DD): ";
            cin >> bakeryProducts[productChoice].ProductionDate;
            break;
        case 5:
            cout << "Enter new Expired Date (YYYY-MM-DD): ";
            cin >> bakeryProducts[productChoice].ExpiredDate;
            break;
        case 6:
            cout << "Enter new Price: ";
            cin >> bakeryProducts[productChoice].Price;
            break;
        default:
            cout << "Invalid field choice.\n";
            return;
        }
        break;
    case 4:
        switch (fieldChoice) {
        case 1:
            cout << "Enter new Code: ";
            cin >> snacksProducts[productChoice].Code;
            break;
        case 2:
            cout << "Enter new Name: ";
            cin >> snacksProducts[productChoice].Name;
            break;
        case 3:
            cout << "Enter new Category: ";
            cin >> snacksProducts[productChoice].Category;
            break;
        case 4:
            cout << "Enter new Production Date (YYYY-MM-DD): ";
            cin >> snacksProducts[productChoice].ProductionDate;
            break;
        case 5:
            cout << "Enter new Expired Date (YYYY-MM-DD): ";
            cin >> snacksProducts[productChoice].ExpiredDate;
            break;
        case 6:
            cout << "Enter new Price: ";
            cin >> snacksProducts[productChoice].Price;
            break;
        default:
            cout << "Invalid field choice.\n";
            return;
        }
        break;
    case 5:
        switch (fieldChoice) {
        case 1:
            cout << "Enter new Code: ";
            cin >> frozenFoodProducts[productChoice].Code;
            break;
        case 2:
            cout << "Enter new Name: ";
            cin >> frozenFoodProducts[productChoice].Name;
            break;
        case 3:
            cout << "Enter new Category: ";
            cin >> frozenFoodProducts[productChoice].Category;
            break;
        case 4:
            cout << "Enter new Production Date (YYYY-MM-DD): ";
            cin >> frozenFoodProducts[productChoice].ProductionDate;
            break;
        case 5:
            cout << "Enter new Expired Date (YYYY-MM-DD): ";
            cin >> frozenFoodProducts[productChoice].ExpiredDate;
            break;
        case 6:
            cout << "Enter new Price: ";
            cin >> frozenFoodProducts[productChoice].Price;
            break;
        default:
            cout << "Invalid field choice.\n";
            return;
        }
        break;
    default:
        cout << "Invalid category choice.\n";
        return;
    }

    cout << "\nProduct information updated successfully.\n";*/
}

void the_customer_is_able_to_modify_his_order()
{
    int choice;
    int orderNumber;

    do {
        cout << "\n========== Modify Your Order ==========\n";
        cout << "Current Products in your order:\n";
        for (int i = 0; i < 3; i++)
        {
            cout << "Order number: " << (i + 1) << endl;
            for (int j = 0; j < customerOrder[i].OrderCount; j++) {
                cout << j + 1 << ". " << customerOrder[i].list_Of_Products[j].Name
                    << " (Quantity: " << customerOrder[i].list_Of_Products[j].ProductCount
                    << ", Price: $" << customerOrder[i].list_Of_Products[j].Price * customerOrder[i].list_Of_Products[j].ProductCount << ")\n";
            }
        }

        cout << "Enter the order number (or press 0 to exit):";
        cin >> orderNumber;
        if (orderNumber == 0) {
            cout << "Exiting...\n";
            return;
        }
        orderNumber--;

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

            if (removeIndex >= 0 && removeIndex < customerOrder[orderNumber].OrderCount)
            {
                for (int i = removeIndex; i < customerOrder[orderNumber].OrderCount - 1; i++)
                {
                    customerOrder[orderNumber].list_Of_Products[i] = customerOrder[orderNumber].list_Of_Products[i + 1]; //shifting                   
                }
                customerOrder[orderNumber].OrderCount--;

                if (customerOrder[orderNumber].OrderCount == 0)
                {
                    for (int n = orderNumber; n < 3; n++) //shifting
                    {
                        customerOrder[n] = customerOrder[n + 1];
                    }
                }
                cout << "Item removed successfully!\n";
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

            if (index >= 0 && index < customerOrder[orderNumber].OrderCount) {
                cout << "Enter the new quantity: ";
                cin >> newQuantity;
                customerOrder[orderNumber].list_Of_Products[index].ProductCount = newQuantity;
                cout << "Quantity updated successfully!\n";
            }
            else {
                cout << "Invalid product number.\n";
            }
            break;
        }

        case 3: {
            string code;
            bool found = false;
            cout << "Enter the product code to add: ";
            cin >> code;

            for (int cat = 0; cat < CATEGORY_COUNT && !found; cat++) {
                for (int i = 0; i < MAX_PRODUCTS; i++) {
                    if (Products[cat][i].Code == code) {
                        customerOrder[orderNumber].list_Of_Products[customerOrder[orderNumber].OrderCount++] = Products[cat][i];
                        found = true;
                        cout << "Product added to your order.\n";
                        break;
                    }
                }
            }
            if (!found)
                cout << "Product not found!\n";
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
//<<---log_out--->>
void log_out() {
    cout << "========================================" << endl;
    /*if (currentCustomerIndex >= 0 && currentCustomerIndex < customerCount) {
        customers[currentCustomerIndex].ID = 0;
        customers[currentCustomerIndex].Location = "";
        customers[currentCustomerIndex].Name = "";
        customers[currentCustomerIndex].Password = "";
        customers[currentCustomerIndex].PhoneNumber = "";
    }*/
    is_logged_in = false;
    currentCustomerIndex = -1;
    cout << "#### You Have Been Succsessfully Logged Out. ####" << endl;
    cout << "#### Thank You For Using Our Online Supermarket!" << endl;
    cout << "========================================" << endl;
}

void belong_orders()
{
    customerOrder[0].CustomerID = customers[--customerCount].ID;
    int targetID = customers[0].ID; // مثلًا عايز أجيب طلبات العميل رقم 1

    for (int i = 0; i < 1; i++) {
        if (customerOrder[i].CustomerID == targetID) {
            cout << "Order #" << i << " belongs to customer: " << customers[0].Name << endl;
            for (int j = 0; j < customerOrder[i].OrderCount; j++) {
                cout << "- " << customerOrder[i].list_Of_Products[j].Name << endl;
            }
        }
    }
}
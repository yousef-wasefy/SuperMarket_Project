#include<iostream>
#include<string>
#include<vector>
#include<chrono> //used for the time
#include<ctime>  //used for the time
#include<iomanip> //used for the time
#include<fstream>

using namespace std;
#define max=50;//added by sa3ed 

//ofstream outFile("superMarket.txt", ios::app); // file to save the data
//ifstream inFile("superMarket.txt"); // file to read the data

struct Customer
{
    int ID = 0;
    string Name;
    string PhoneNumber;
    string Location;
    string Password;
};

struct Product
{
    string Code;
    string Name;
    string Category;
    string ProductionDate;
    string ExpiredDate;
    double Price = 0.0;
    string info;
};

const int NUMBER_OF_PRODUCTS = 50;
struct Order
{
    int CustomerID = 0;
    Product list_Of_Products[NUMBER_OF_PRODUCTS]; // that the customer will take
    int ProductCount = 0;  //عدد المنتجات في الطلب الفعلي
    double TotalPrice = 0;
    string orderTime;
} customerOrder[50];

// string getCurrentTimeString() // only testing rightnow
// {
//     auto now = std::chrono::system_clock::now();
//     std::time_t now_time = std::chrono::system_clock::to_time_t(now);
//     std::tm local_time = *std::localtime(&now_time); // تحويل الوقت إلى `tm`

//     std::ostringstream oss;
//     oss << std::put_time(&local_time, "%Y-%m-%d %H:%M"); // تحويل إلى نص
//     return oss.str();
// }

const int CATEGORY_COUNT = 5;// at least 5
string productCategories[CATEGORY_COUNT] = { "Dairy", "Beverages", "Bakery", "Snacks", "Frozen Food" };

const int MAX_PRODUCTS = 3; // 3 products per category
Product dairyProducts[MAX_PRODUCTS] = {
     {"D001", "Milk", "Dairy", "2025-03-01", "2025-03-10", 1.50},
     {"D002", "Cheese", "Dairy", "2025-02-25", "2025-03-20", 4.00},
     {"D003", "Butter", "Dairy", "2025-02-28", "2025-04-15", 2.50} };

Product beveragesProducts[MAX_PRODUCTS] = {
    {"B001", "Orange Juice", "Beverages", "2025-03-05", "2025-06-05", 2.00},
    {"B002", "Coca-Cola", "Beverages", "2025-02-15", "2025-08-15", 1.25},
    {"B003", "Green Tea", "Beverages", "2025-01-30", "2025-07-30", 1.75} };

Product bakeryProducts[MAX_PRODUCTS] = {
    {"BK001", "White Bread", "Bakery", "2025-03-08", "2025-03-12", 1.20},
    {"BK002", "Croissant", "Bakery", "2025-03-07", "2025-03-10", 0.99},
    {"BK003", "Chocolate Muffin", "Bakery", "2025-03-06", "2025-03-11", 1.50} };

Product snacksProducts[MAX_PRODUCTS] = {
    {"S001", "Potato Chips", "Snacks", "2025-02-20", "2025-08-20", 1.75},
    {"S002", "Chocolate Bar", "Snacks", "2025-03-01", "2025-09-01", 1.25},
    {"S003", "Peanuts", "Snacks", "2025-02-18", "2025-12-18", 2.30} };

Product frozenFoodProducts[MAX_PRODUCTS] = {
    {"F001", "Frozen Pizza", "Frozen Food", "2025-02-10", "2026-02-10", 5.50},
    {"F002", "Ice Cream (Vanilla)", "Frozen Food", "2025-02-28", "2026-02-28", 3.99},
    {"F003", "Chicken Nuggets", "Frozen Food", "2025-03-01", "2026-03-01", 6.75} };

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
void log_in(); //Sa3eed
void edit_information(); //nour
void view_products_menu(); //Doha
void view_the_information_of_the_item_that_the_customer_has_chosen(); //Doha
void the_customer_selects_the_goods_he_wants_to_add_to_his_order(); //Mostafa
void Review_his_order(); //Youssef hagras
void the_customer_is_able_to_modify_his_order(); //Mohra
void view_total_price(); //Youssef Ahmed
void log_out(); //Sa3eed
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
    do
    {
        choice = menu();
        switch(choice) //add your case.
        {
        case 1:
            sign_up();
            break;
        case 3:
            view_products_menu();
            break;
        case 4:
            view_the_information_of_the_item_that_the_customer_has_chosen();
            break;
        case 8:
            view_total_price();
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
    cin >> choice;
    return choice;
}
//<<--sgin_up-->>
Customer customers[max]
int customerCount=0
void sgin_up() {
    Customer NewCustomer;
    NewCustomer.id = customerCount + 1;
    cout << "Enter Your Name:\t\t";
    cin >> NewCustomer.Name;
    cout << "Enter Your Phone Number:\t\t";
    cin >> NewCustomer.phoneNumber;
    cout << "Enter Your Location:\t\t";
    cin >> NewCustomer.Location;
    cout << "Enter Your Password:\t\t";
    cin >> NewCustomer.Password;
    customers[customerCount] = NewCustomer;
    customerCount++;
    cout << "<<----Sgin Up Successfully. Your ID\t" << NewCustomer.id << "---->>";
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

    cout << "Item\t\tquantity\ttotal price\tOrder Date & Time" << endl;
    for (int j = 0; j < 2; j++)
    {
        cout << customerOrder[j].list_Of_Products[j].Name;
        cout << "\t\t" << customerOrder[j].ProductCount;
        cout << "\t\t" << customerOrder[j].list_Of_Products[j].Price * customerOrder[j].ProductCount;
        cout << "\t\t" << customerOrder[j].orderTime;
        cout << endl;
    }

    cout << "Total Price : ";
    for (int i = 0; i < NUMBER_OF_PRODUCTS; i++)
    {
        totalPrice += customerOrder[i].list_Of_Products[i].Price * customerOrder[i].ProductCount;
    }
    cout << totalPrice << endl;
}
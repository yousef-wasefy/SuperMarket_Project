#include<iostream>
#include<string>
#include<vector>

using namespace std;

struct Customer
{
    int ID;
    string Name;
    string PhoneNumber;
    string Location;
};

struct Product
{
    string Code;
    string Name;
    string Category;
    string ProductionDate;
    string ExpiredDate;
    double Price;
};

struct Order
{
    int CustomerID;
    Product list_Of_Products[50];
    int ProductCount;  // عدد المنتجات في الطلب الفعلي
    double TotalPrice;
};

const int CATEGORY_COUNT = 5; // at least 5
string productCategories[CATEGORY_COUNT] = {};

//هنهمشها دلوقت ونرجعهم اما نشوف ايه الكاتجوريز اللي هنضيفها
// const int MAX_PRODUCTS = 100; // الحد الأقصى للمنتجات في كل فئة

// Product واسم الكاتجوري[MAX_PRODUCTS];
// Product [MAX_PRODUCTS];
// Product [MAX_PRODUCTS];
// Product [MAX_PRODUCTS];
// Product [MAX_PRODUCTS];

/*NOTES 
- Don't modify,add or use any new structs or arrays before you tell us and we approve.
- Don't forget to -->["pull"]<-- before you start working , and before you push your work.
- We will finish from the required functions before the midterm, 
when we finish we will add new functions and it may take week or more.
- Don't use GPT !!, just make him helps you.
- بالنسبة لموضوع الفايل : انت الاول هتخلص الفانكشن بتاعتك عادي بعدين تبدا تظبط موضوع الفايل بحيث تقرا وتكتب منه
- ممكن تستعين ب gpt في موضوع الفايل بس كون فاهم اللي بيتعمل
- كل واحد مسؤول عن كوده
*/

// ظبط الفانكشن بتاعتك من حيث الاسم والنوع والبراميترز اللي هتاخدها
void sign_up();
void log_in();
void edit_information();
void view_products_menu();
void view_the_information_of_the_item_that_the_customer_has_chosen();
void the_customer_selects_the_goods_he_wants_to_add_to_his_order();
void Review_his_order();
void the_customer_is_able_to_modify_his_order();
void view_total_price();
void log_out();
int menu();

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

            default:
                cout << "Invalid choice!\nPlease re-enter the correct one\n";
                answer = 'y';
                continue;
        }
        cout << "Another operation? (Y/N)";
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
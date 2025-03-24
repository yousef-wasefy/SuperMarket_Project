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
- We will finish from the required functions at  ... 
when we finish we will add new functions and it may takes week or more.
- Don't use GPT !!, just make him helps you.
*/

int main()
{
    //pull first !!!!!

    return 0; //pull first !!!!!
}
#ifndef KHO_H
#define KHO_H
#include <iostream>
#include <sstream>
#include <cstring>
#include <fstream>
#include "Manager.h"
#include "Entity.h"
#include "Product.h"
#include <map>
using namespace std;
class Kho : public Entity {
    string date;
    Manager *qli= nullptr;
    Product *sp=nullptr;
public:
    void Nhap();
    void Xuat();
    void docFile(ifstream &f, multimap<string, Product*>& products, multimap<string, Manager*>& managers);
    void addProduct(Product *prod);
};
void Kho::Nhap() {
    Entity::Nhap();
    cout << "Nhap ngay nhap hang: "; 
    getline(cin >> ws, date);  
}
void Kho::Xuat() {
    Entity::Xuat();
    if (sp) cout<< "   ID sp: "<<sp->getID()<<"   SP:  "<<sp->getName()<<"\tSo Luong: "<<sp->getSL()<<"   Don gia: "<<sp->getDonGia()<<"\tThanh tien: "<<sp->TinhthanhTien()<<"   Ngay nhap: " << date;
    else cout<<endl;
    if (qli) cout<< "   ID quan li: "<<qli->getID()<<endl;
    else cout<<endl;
}
void Kho::docFile(ifstream &file, multimap<string, Product*>& products, multimap<string, Manager*>& managers){
    string line, productID, managerID;
    if (file.tellg() == 0)
        getline(file, line);
    if (getline(file, line)){
        stringstream ss(line);
        getline(ss, ID, '|');
        getline(ss, name, '|');
        getline(ss, date, '|');
        // string str;
        // ss>>maxsize; Sai ở đây, vì chưa đọc hết kí tự | sau maxsize
        // getline(ss, str, '|');
        // maxsize=stoi(str);
        getline(ss, productID, '|');
        getline(ss, managerID, '|');
        auto productRange = products.equal_range(productID);
        for (auto it = productRange.first; it != productRange.second; ++it) {
            addProduct(it->second); // add each matching product
        }

        // Assign a manager pointer if managerID exists in `managers`
        auto managerRange = managers.equal_range(managerID);
        if (managerRange.first != managerRange.second) {
            qli = managerRange.first->second; // Assigns the first found manager
        }
}}
void Kho::addProduct(Product *pro){
    sp=pro;
}
#endif
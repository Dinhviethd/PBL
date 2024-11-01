#ifndef KHO_H
#define KHO_H
#include <iostream>
#include <sstream>
#include <cstring>
#include <fstream>
#include "Manager.h"
#include "Entity.h"
#include "Product.h"
#include <unordered_map>
using namespace std;
class Kho : public Entity {
    string date;
    Manager *qli= nullptr;
    Product *sp=nullptr;
public:
    void Nhap();
    void Xuat();
    void docFile(ifstream &f, unordered_map<string, Product*>& products, unordered_map<string, Manager*>& managers);
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
void Kho::docFile(ifstream &file, unordered_map<string, Product*>& products, unordered_map<string, Manager*>& managers){
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
        if (products.find(productID) != products.end())
        sp = products[productID];
        if (managers.find(managerID) != managers.end())
        qli = managers[managerID];
}
}
#endif
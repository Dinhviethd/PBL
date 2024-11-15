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
    int capacity, current_size = 0;
    Manager *qli= nullptr;
public:
    void Nhap();
    void Xuat();
    void docFile(ifstream &f,multimap<string, Manager*>& managers);
    void addManager(Manager *qly);
    int getCurrentSize();
    void setCurrentSize(int size);
    int getCapacity();
    void chinhSuaThongTin();
};
void Kho::Nhap() {
    Entity::Nhap();
    cout<<"Nhap suc chua cua kho: ";
    cin>>capacity;
}
void Kho::Xuat() {
    Entity::Xuat();

    cout << " | " << setw(11) << left << capacity
         << " | " << setw(14) << left << current_size;
    if (qli) cout<< " | " << setw(13) << left << qli->getID() << " | " << setw(19) << left << qli->getName()<< " |\n";
             
    else cout << " | " << setw(11) << left << "Chua co quan li!";
}
void Kho::docFile(ifstream &file, multimap<string, Manager*>& managers){
    string line, managerID;
    if (file.tellg() == 0)
        getline(file, line);
    if (getline(file, line)){
        stringstream ss(line);
        string capacityStr;
        getline(ss, ID, '|');
        getline(ss, name, '|');
        getline(ss, capacityStr, '|');
        capacity = stoi(capacityStr);
        getline(ss, managerID, '|');
        auto managerRange = managers.equal_range(managerID);
        if (managerRange.first != managerRange.second) {
            qli = managerRange.first->second;
        }
}}
void Kho::addManager(Manager *qly){
    qli=qly;
}
int Kho::getCapacity(){
    return capacity;
}
int Kho::getCurrentSize(){
    return current_size;
}
void Kho::setCurrentSize(int size) {
    current_size = size;
}
void Kho::chinhSuaThongTin() {
    int choice;
    cout << "Chon thong tin ban muon sua:" << endl;
    cout << "1. ID" << endl;
    cout << "2. Ten kho" << endl;
    cout << "3. Suc chua" << endl;
    cout << "Lua chon cua ban: ";
    cin >> choice;
    cin.ignore();

    switch (choice) {
        case 1:
            cout << "Nhap ID moi (hien tai: " << ID << "): ";
            getline(cin, ID); 
            break;
        case 2:
            cout << "Nhap ten kho moi (hien tai: " << name << "): ";
            getline(cin, name); 
            break;
        case 3:
            cout << "Nhap suc chua moi (hien tai: " << capacity << "): ";
            cin >> capacity;
            cin.ignore();
            break;
        
        default:
            cout << "Lua chon khong hop le." << endl;
            break;
    }
}

#endif
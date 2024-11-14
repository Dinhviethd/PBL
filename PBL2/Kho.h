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
};
void Kho::Nhap() {
    Entity::Nhap();
    cout<<"Nhap suc chua cua kho: ";
    cin>>capacity;
}
void Kho::Xuat() {
    Entity::Xuat();
    cout << "   Suc chua: " << capacity;
    cout << "   Suc chua hien tai" << current_size;
    if (qli) 
    cout << "   ID quan li: " << qli->getID() << " Ten quan li: " << qli->getName()<<endl;
    else cout << "   Chua co quan li."<<endl;
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
#endif
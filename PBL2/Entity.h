#ifndef ENTITY_H
#define ENTITY_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>

using namespace std;
class Entity {
protected:
    string ID;
    string name;
public:
    virtual void Nhap();
    virtual void Xuat()=0;
    virtual string getName() const;
    virtual string getID() const;
  
};
void Entity::Nhap() {
    cout << "Nhap ID: "; 
    getline(cin >> ws, ID);  
    cout << "Nhap ten: "; 
    getline(cin >> ws, name);  
}
void Entity::Xuat() {
    cout << "ID: " << ID << "\tTen: " << name;
}
string Entity::getName() const {
    return name;
}
string Entity::getID() const {
    return ID;
}
#endif
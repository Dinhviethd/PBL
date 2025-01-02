#ifndef ENTITY_H
#define ENTITY_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;
int cnt = 0;
int month = 0;
class Entity {
protected:
    string ID;
    string name;
public:
    Entity();
    Entity(string ID, string name);
    virtual ~Entity();
    virtual void Nhap();
    virtual void Xuat()=0;
    virtual string getID() const = 0;  
    virtual string getName() const = 0;
    virtual void setID();
    virtual void chinhSuaThongTin();
};
Entity::Entity(){
    ID = "";
    name = "";
}
Entity::Entity(string ID, string name) : ID (ID), name(name){

}
Entity::~Entity(){

}
void Entity::Nhap() {
    cout << "Nhap ten: "; 
    getline(cin >> ws, name);  
}
void Entity::Xuat() {
    cout << "| " << setw(3) << left << ++cnt
        << "| " << setw(12) << left << ID
         << " | " << setw(29) << left << name;
}
// string Entity::getName() const {
//     return name;
// }
// string Entity::getID() const {
//     return ID;
// }
void Entity::chinhSuaThongTin(){
}
void Entity::setID(){
    cout << "Nhap ID: "; 
    getline(cin >> ws, ID);  
}
bool checkDate(int day, int month){
    if (day<=0) return 0;
    switch(month){
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
        if (day>31) return 0;
        case 4:
        case 6:
        case 9:
        case 11:
        if (day>30) return 0;
        case 2: if (day>29) return 0;
        
    }
    return 1;
}
#endif
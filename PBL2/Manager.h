#ifndef MANAGER_H
#define MANAGER_H
#include <iostream>
#include <cstring>
#include <sstream>
#include <fstream>
#include "Entity.h"
using namespace std;
class Manager : public Entity {
    string mAdr;
    string gender;
    int birth;
public:
    void Nhap();
    void Xuat();
    void docFile(ifstream &file);
};

void Manager::docFile(ifstream &file){
    string line;
    if (file.tellg() == 0)
        getline(file, line);
    if (getline(file, line)){
        stringstream ss(line);
        getline(ss, ID, '|');
        getline(ss, name, '|');
        getline(ss, gender, '|');
        getline(ss, mAdr, '|');
        ss>>birth;
    }
}
void Manager::Nhap() {
    Entity::Nhap();
    cout << "Nhap gioi tinh: "; 
    cin>>gender; 
    cout << "Nhap nam sinh: "; cin >> birth;
    cout << "Nhap dia chi quan li: "; 
    getline(cin >> ws, mAdr);  
}
void Manager::Xuat() {
    Entity::Xuat();
    cout << "\tGioi tinh: " << gender << "\tNam sinh: " << birth << "\tDia chi: " << mAdr << endl;
}
#endif
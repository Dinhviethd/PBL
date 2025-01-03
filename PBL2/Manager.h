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
    Manager();
    Manager(const string &id, const string &name, const string &gender, int birth, const string &mAdr);
    void Nhap();
    void Xuat();
    string getID() const override { return ID; }
    string getName() const override { return name; }
    void docFile(ifstream &file);
    void xuatFile(ofstream &file);
    void chinhSuaThongTin();
};

Manager::Manager() : Entity() {
    mAdr = "";
    gender = "";
    birth = 0;
}

Manager::Manager(const string &id, const string &name, const string &gender, int birth, const string &mAdr)
    : Entity(id, name), gender(gender), birth(birth), mAdr(mAdr) {}

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
void Manager::xuatFile(ofstream &file){
    //ID|name|gender|address|birth
    if (file.is_open()) {
        file << ID << "|" << name << "|" << gender << "|" << mAdr << "|" << birth << endl;
    } 
    else {
        cerr << "Error: Could not open file for writing." << endl;
    }
}
void Manager::Nhap() {
    Entity::Nhap();
    cout << "Nhap gioi tinh: "; 
    getline(cin>>ws,gender);
    cout << "Nhap nam sinh: "; cin >> birth;
    cout << "Nhap dia chi quan li: "; 
    getline(cin >> ws, mAdr);  
}
void Manager::Xuat() {
    Entity::Xuat();
    cout << " | " << setw(11) << left << gender
         << " | " << setw(9) << left << birth
         << " | " << setw(15) << left << mAdr << " |\n";
}
void Manager::chinhSuaThongTin() {
    int choice;
    cout << "Chon thong tin ban muon sua:" << endl;
    cout << "1. ID" << endl;
    cout << "2. Ten" << endl;
    cout << "3. Gioi tinh" << endl;
    cout << "4. Nam sinh" << endl;
    cout << "5. Dia chi" << endl;
    cout << "Lua chon cua ban: ";
    cin >> choice;
    cin.ignore();

    switch (choice) {
        case 1:
            cout << "Nhap ID moi (hien tai: " << ID << "): ";
            getline(cin, ID); 
            break;
        case 2:
            cout << "Nhap ten moi (hien tai: " << name << "): ";
            getline(cin, name); 
            break;
        case 3:
            cout << "Nhap gioi tinh moi (hien tai: " << gender << "): ";
            getline(cin, gender); 
            break;
        case 4:
            cout << "Nhap nam sinh moi (hien tai: " << birth << "): ";
            cin >> birth; 
            cin.ignore();
            break;
        case 5:
            cout << "Nhap dia chi moi (hien tai: " << mAdr << "): ";
            getline(cin, mAdr); 
            break;
        default:
            cout << "Lua chon khong hop le." << endl;
            break;
    }
}

#endif
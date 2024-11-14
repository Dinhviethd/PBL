#ifndef PRODUCT_H
#define PRODUCT_H
#include <iostream>
#include <sstream>
#include <fstream>
#include "Entity.h"
#include "Kho.h"
#include "LinkList.h"
#include <cstring>
#include <map>
using namespace std;
class Product : public Entity {
protected:
    string loai, donVi;
    int sl;
    double donGia, thanhTien;
    Kho *kho= nullptr;
public:
    void Nhap();
    void Xuat();
    void docFile(ifstream &file, multimap<string, Kho*>& _kho);
    double TinhthanhTien();
    string getLoai();
    double getThanhTien();
    int getSL();
    double getDonGia();
    void themSPVaoKho(Kho *k);
};
void Product::Nhap() {
    Entity::Nhap();
    cout << "Nhap loai hang: "; cin >> loai;
    cout << "Nhap so luong sp: "; cin >> sl;
    cout << "Nhap don gia san pham: "; cin >> donGia;
    cout << "Nhap don vi: "; 
    getline(cin >> ws, donVi);  
}
void Product::Xuat() {
    Entity::Xuat();
    cout << " | " << setw(14) << left << loai
         << " | " << setw(14) << left << donVi
         << " | " << setw(6) << left << sl
         << " | " << setw(10) << left << fixed << setprecision(2) << donGia
         << " | " << setw(11) << left << thanhTien;

    if (kho) {
        cout << " | " << setw(11) << left << kho->getName()
             << " | " << setw(11) << left << kho->getID() << " |" << endl;
    } else {
        cout << " | " << setw(11) << left << "N/A"
             << " | " << setw(11) << left << "N/A" << " |" << endl;
    }
}
void Product::docFile(ifstream &file, multimap<string, Kho*>& _kho) {
    string line, khoID;
    if (file.tellg() == 0)
        getline(file, line);
    if (getline(file, line)) {
        stringstream ss(line);
        string slStr, donGiaStr;
        getline(ss, ID, '|');
        getline(ss, name, '|');
        getline(ss, loai, '|');
        getline(ss, donVi, '|');
        getline(ss, slStr, '|');
        sl = stoi(slStr);
        getline(ss, donGiaStr, '|');
        donGia = stof(donGiaStr);
        getline(ss, khoID, '|');
        auto range = _kho.equal_range(khoID);
        if (range.first != range.second) {
            kho = range.first->second; 
        }
        kho->setCurrentSize(kho->getCurrentSize()+sl);
        thanhTien =TinhthanhTien();
    }
}
string Product::getLoai(){
    return loai;
}
double Product::getThanhTien(){
    return thanhTien;
}
double Product::TinhthanhTien(){
    float thanhTien=0;
    if (sl>200)
        thanhTien= sl*donGia*1.15;
    else if (sl>100 && sl<=200){
        thanhTien= sl*donGia*1.1;
    }
    else if (sl<=100){
        thanhTien=sl*donGia;
    }
    return thanhTien;
}
int Product::getSL(){
    return sl;
}
void Product::themSPVaoKho(Kho *k) {
    if (k->getCurrentSize() + sl <= k->getCapacity()) {  
        kho = k;
        k->setCurrentSize(k->getCurrentSize() + sl);  
        cout << "San pham da duoc them vao kho: " << k->getName() << endl;
    } else {
        cout << "Kho '" << k->getName() << "' khong du suc chua de them san pham nay!" << endl;
    }
}
double Product::getDonGia(){
    return donGia;
}

#endif
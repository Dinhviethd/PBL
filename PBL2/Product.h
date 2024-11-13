#ifndef PRODUCT_H
#define PRODUCT_H
#include <iostream>
#include <sstream>
#include <fstream>
#include "Entity.h"
#include "Kho.h"
#include <cstring>
#include <map>
using namespace std;
class Product : public Entity {
protected:
    string loai, donVi;
    int sl;
    float donGia;
    Kho *kho= nullptr;
public:
    void Nhap();
    void Xuat();
    void docFile(ifstream &file, multimap<string, Kho*>& _kho);
    float TinhthanhTien();
    int getSL();
    float getDonGia();
    void themSPVaoKho(Kho *k);
};
void Product::Nhap() {
    Entity::Nhap();
    cout << "Nhap so luong sp: "; cin >> sl;
    cout << "Nhap don gia san pham: "; cin >> donGia;
    cout << "Nhap don vi: "; 
    getline(cin >> ws, donVi);  
}
void Product::Xuat() {
    Entity::Xuat();
    cout << "\tSo Luong: " << sl << "\tDon vi: " << donVi << "\tDon gia: " << donGia << "\tID Kho: "<<kho->getID()<<endl;
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
    }
}
float Product::TinhthanhTien(){
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
void Product::themSPVaoKho(Kho *k){
    kho=k;
}
float Product::getDonGia(){
    return donGia;
}
#endif
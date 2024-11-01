#ifndef PRODUCT_H
#define PRODUCT_H
#include <iostream>
#include <sstream>
#include <fstream>
#include "Entity.h"
#include <cstring>
using namespace std;
class Product : public Entity {
protected:
    string donVi;
    int sl;
    float donGia;
public:
    void Nhap();
    void Xuat();
    void docFile(ifstream &file);
    float TinhthanhTien();
    int getSL();
    float getDonGia();
    void themSPVaoKho();
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
    cout << "\tSo Luong: " << sl << "\tDon vi: " << donVi << "\tDon gia: " << donGia << endl;
}
void Product::docFile(ifstream &file){
  string line;
  if (file.tellg() == 0)
  getline(file, line);
  if (getline(file, line)) { 
    stringstream ss(line);  
    getline(ss, ID, '|');
   getline(ss, name, '|');
        getline(ss, donVi, '|');
        ss >> sl;
        ss.ignore(); 
        ss >> donGia;
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
float Product::getDonGia(){
    return donGia;
}
#endif
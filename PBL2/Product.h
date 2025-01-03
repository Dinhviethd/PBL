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
    int ngayNhap;
    int sl;
    double donGia, thanhTien;
    Kho *kho= nullptr;
public:
    Product();
    void Nhap();
    void Xuat();
    void docFile(ifstream &file, multimap<string, Kho*>& _kho);
    void xuatFile(ofstream &file);
    double TinhthanhTien();
    string getLoai();
    string getID() const override { return ID; }
    string getName() const override { return name; }
    double getThanhTien();
    int getSL();
    double getDonGia();
    void themSPVaoKho(Kho *k);
    void chinhSuaThongTin();
    void themSL(int add);
    int getNgayNhap();
    void setThanhTien();
    Kho *getKho();
};
Product::Product(): Entity() {
    loai = donVi = "";
    sl = 0;
    donGia = 0;
    thanhTien = 0;
}
void Product::Nhap() {
    Entity::Nhap();
    cout << "Nhap loai hang: "; getline(std::cin, loai);
    cout << "Nhap don vi: "; 
    getline(std::cin >> ws, donVi);  
    cout << "Nhap so luong sp: "; std::cin >> sl; std::cin.ignore(); 
    cout << "Nhap don gia san pham: "; std::cin >> donGia;
    while (1){
    cout << "Nhap ngay nhap: "; std::cin >> ngayNhap;   
    if (checkDate(ngayNhap,month)) break;
    else cout << "Ngay nhap khong hop le! Vui long nhap lai...\n";
    }
}
void Product::Xuat() {
    Entity::Xuat();
    cout << " | " << setw(14) << left << loai
         << " | " << setw(14) << left << donVi
         << " | " << setw(6) << left << sl
         << " | " << setw(10) << left << fixed << setprecision(2) << donGia
         << " | " << setw(11) << left << thanhTien
         << " | " << setw(8) << left << ngayNhap;

    if (kho) {
        cout << " | " << setw(11) << left << kho->getName()
             << " | " << setw(11) << left << kho->getID() << "|" << endl;
    } else {
        cout << " | " << setw(11) << left << "N/A"
             << " | " << setw(11) << left << "N/A" << "|" << endl;
    }
}
void Product::docFile(ifstream &file, multimap<string, Kho*>& _kho) {
    string line, khoID;
    if (file.tellg() == 0)
        getline(file, line);
    if (getline(file, line)) {
        stringstream ss(line);
        string slStr, donGiaStr,ngayNhapStr;
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
        getline(ss, ngayNhapStr, '|');
        ngayNhap = stoi(ngayNhapStr);
    }
}
void Product::xuatFile(ofstream &file) {
    
    if (file.is_open()) {
        file << ID << "|" << name << "|" << loai << "|" << donVi << "|"
             << sl << "|"  << donGia << "|";
        if (kho) {
            file << kho->getID();
        } else {
            file << "N/A";  
        }
        file  << "|" << ngayNhap;
        file << endl;
    } else {
        cerr << "Error: Could not open file for writing." << endl;
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
    if (k->getLoaiKho() != loai) {
        cout << "San pham khong phu hop voi loai kho!" << endl;
        return;
    }
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
void Product::chinhSuaThongTin() {
    int choice;
    cout << "Chon thong tin ban muon sua:" << endl;
    cout << "1. ID" << endl;
    cout << "2. Ten" << endl;
    cout << "3. Loai hang" << endl;
    cout << "4. Don vi tinh (DVT)" << endl;
    cout << "5. So luong" << endl;
    cout << "6. Don gia" << endl;
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
            cout << "Nhap loai hang moi (hien tai: " << loai << "): ";
            getline(cin, loai); 
            break;
        case 4:
            cout << "Nhap don vi tinh moi (hien tai: " << donVi << "): ";
            getline(cin, donVi); 
            break;
        case 5:
            cout << "Nhap so luong moi (hien tai: " << sl << "): ";
            cin >> sl; 
            cin.ignore(); 
            break;
        case 6:
            cout << "Nhap don gia moi (hien tai: " << donGia << "): ";
            cin >> donGia;
            cin.ignore(); 
            break;
        
        default:
            cout << "Lua chon khong hop le." << endl;
            break;
    }
}
void Product::themSL(int add) {
    if (add > 0) {
        sl += add;
        thanhTien = TinhthanhTien(); 
        cout << "So luong san pham da duoc cap nhat thanh: " << sl << endl;
    } else {
        cout << "So luong cap nhat phai lon hon 0!" << endl;
    }
}
int Product::getNgayNhap() {
        return ngayNhap;
}
void Product::setThanhTien(){
    thanhTien=TinhthanhTien();
}
Kho *Product::getKho() {
    return kho; 
}
#endif
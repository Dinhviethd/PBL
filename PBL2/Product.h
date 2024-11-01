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
  string line; //biến này dùng để lưu nội dung 1 hàng
  if (file.tellg() == 0)
  getline(file, line);
  if (getline(file, line)) { //Đọc 1 dòng trong file r lưu vào biến line
    stringstream ss(line);  /*Lấy dữ liệu biến line để tạo biến ss
Kiểu stringstream giúp ta đọc/ghi dữ liệu từ chuỗi truyền vào
Tức là dòng stringstream ss(line) dùng để lấy dữ liệu từ chuỗi line rồi từ đó
đọc/ghi trên  nội dung của line đó
*/
    getline(ss, ID, '|'); //Như ở đây, ta đọc dữ liệu từ ss r lưu vào biến ID
//Câu lệnh này có nghĩa là đọc dl từ ss đến khi gặp kí tự |, rồi lưu vào biến ID
/*Chú ý, getline đọc dl xong trả về kiểu string. Nên với dl dạng số, ta nên
đọc bằng >> (chính là cin ấy), hoặc đọc = getline rồi chuyển kiểu */
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
#include <iostream>
#include <cstring>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include "Product.h"
#include "Entity.h"
#include "LinkList.h"
#include "Kho.h"
#include <conio.h>
#include <windows.h>

void print(int tl);
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;  // Tọa độ X
    coord.Y = y;  // Tọa độ Y
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void textcolor(int textColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, textColor);
}
void xuatThongTin(LinkList &l1, LinkList &l2, LinkList &l3, int tl)
{
    print(tl);
    if (tl == 0)
        return;
    else if (tl == 1)
    {
        l1.output();
    }
    else if (tl == 2)
    {
        l2.output();
    }
    else if (tl == 3)
    {
        l3.output();
    }
    else
        cout << "Sai loai thong tin. Vui long nhap lai" << endl;
}
void xoaThongTin(LinkList &l1, LinkList &l2, LinkList &l3, int tl)
{
    int tl1;
    string ID, name;
    if (tl == 0)
        return;
    cout << "Chon loai du lieu can xoa (1: ID, 2: Ten): ";
    cin >> tl1;
    if (tl1 == 1)
    {
        cout << "Nhap ID can xoa: ";
        cin >> ID;
        if (tl == 1)
            l1.deleteNode(ID, "ID");
        else if (tl == 2)
            l2.deleteNode(ID, "ID");
        else if (tl == 3)
            l3.deleteNode(ID, "ID");
    }
    else if (tl1 == 2)
    {
        cout << "Nhap ten can xoa: ";
        getline(cin >> ws, name);
        if (tl == 1)
            l1.deleteNode(name, "name");
        else if (tl == 2)
            l2.deleteNode(name, "name");
        else if (tl == 3)
            l3.deleteNode(name, "name");
    }
}
void docFile(LinkList &l1, LinkList &l2, LinkList &l3,
             multimap<string, Product *> &products,
             multimap<string, Kho *> &khoMap,
             multimap<string, Manager *> &managers)
{
    ifstream fileKho("kho.txt");
    ifstream fileProduct("product.txt");
    ifstream fileManager("manager.txt");
    while (!fileManager.eof())
    {
        Manager *m = new Manager;
        m->docFile(fileManager);
        managers.insert({m->getID(), m});
        l3.insertNode(m);
    }
    while (!fileKho.eof())
    {
        Kho *k = new Kho;
        k->docFile(fileKho, managers);
        khoMap.insert({k->getID(), k});
        l2.insertNode(k);
    }
    while (!fileProduct.eof())
    {
        Product *p = new Product;
        p->docFile(fileProduct, khoMap);
        if (!p->getID().empty())
        {
            products.insert({p->getID(), p});
            l1.insertNode(p);
        }
        else
        {
            delete p;
        }
    }
}
void xuatFile(LinkList &l1, LinkList &l2, LinkList &l3,
             multimap<string, Product *> &products,
             multimap<string, Kho *> &khoMap,
             multimap<string, Manager *> &managers)
{
    ofstream fileProduct("producttest.txt");
    ofstream fileManager("managertest.txt");
    ofstream fileKho("managertest.txt");
    // for (const auto &node : l1) {
    //     dynamic_cast<Product *>(node)->xuatFile(fileProduct);
    // }
    fileProduct << "ID|Name|loai|DVT|SL|DonGia|IDKho|NgayNhap" << endl;
    Node *c1 = l1.getHeader(); 
    auto *p1 = dynamic_cast<Product *>(c1->data);

    while (c1 != nullptr) {
       
        p1->xuatFile(fileProduct);
        c1 = c1->next;
    }
    Node *current = l3.getHeader(); 
    auto *p = dynamic_cast<Manager *>(current->data);

    while (current != nullptr) {
       
         p->xuatFile(fileManager);
        current = current->next;
    }
}
Kho *chonKho(LinkList &l2, int sl, string loai)
{
    string info;
    while (true)
    {
        cout << "Nhap ID kho chua san pham: ";
        cin >> info;
        Node *foundNode = nullptr;
        if (l2.search(info, "ID", foundNode))
        {
            Kho *selectedKho = (Kho *)foundNode->data;
            if (selectedKho->getLoaiKho() != loai)
            {
                cout << "Loi: Loai kho khong phu hop voi loai san pham!" << endl;
                continue;
            }
            if (selectedKho->getCurrentSize() + sl <= selectedKho->getCapacity())
            {
                cout << "Da chon kho: " << selectedKho->getName() << endl;
                return selectedKho;
            }
            else
            {
                cout << "Kho '" << selectedKho->getName() << "' khong du suc chua. Vui long chon kho khac." << endl;
            }
        }
        else
        {
            cout << "Khong tim thay kho voi ID nay. Vui long nhap lai!" << endl;
        }
    }
}
Kho *chonKhoDeQuanLy(LinkList &l2)
{
    string info;
    while (true)
    {
        cout << "Nhap ID kho muon gan quan ly: ";
        cin >> info;
        Node *foundNode = nullptr;
        if (l2.search(info, "ID", foundNode))
        {
            Kho *selectedKho = (Kho *)foundNode->data;
            cout << "Da chon kho: " << selectedKho->getName() << " (ID: " << selectedKho->getID() << ")" << endl;
            return selectedKho;
        }
        else
        {
            cout << "Khong tim thay kho voi ID nay. Vui long nhap lai!" << endl;
        }
    }
}
void nhapBanPhim(LinkList &l1, LinkList &l2, LinkList &l3, int tl, Entity *list)
{
    if (tl == 0)
        return;
    if (tl == 1)
    {
        list = new Product;
        list->setID();
        if (l1.checkDuplicate(list))
        {
            cout << "Phan tu voi ID '" << list->getID() << "' da ton tai trong danh sach." << endl;
            cout << "Ban co muon cap nhat them so luong khong? (1. Co  2. Khong): ";
            int choice;
            cin >> choice;
            if (choice == 1)
            {
                Node *foundNode = NULL;
                l1.search(list->getID(), "ID", foundNode);
                if (foundNode)
                {
                    Product *existingProduct = (Product *)foundNode->data;
                    cout << "Nhap so luong can them: ";
                    cin >> choice;
                    existingProduct->themSL(choice);
                    existingProduct->setThanhTien();
                    return;
                }
            }
            else
            {
                cout << "San pham bi trung, giu nguyen thong tin cu." << endl;
                delete list;
                return;
            }
        }
        list->Nhap();
        l1.insertNode(list);
        Product *newProduct = (Product *)list;
        newProduct->setThanhTien();
        xuatThongTin(l1, l2, l3, 2);
        Kho *selectedKho = chonKho(l2, newProduct->getSL(), newProduct->getLoai()); // Chọn kho và kiểm tra sức chứa
        if (selectedKho)
        {
            newProduct->themSPVaoKho(selectedKho);
        }
        else
        {
            cout << "Lua chon khong hop le!! Vui long nhap lai." << endl;
        }
    }
    else if (tl == 2)
    {
        list = new Kho;
        do
        {
            list->setID();
        } while (!l2.checkDuplicate(list));
        list->Nhap();
        l2.insertNode(list);
    }
    else if (tl == 3)
    {
        list = new Manager;
        do
        {
            list->setID();
        } while (l3.checkDuplicate(list));
        list->Nhap(); // Nhập thông tin quản lý
        l3.insertNode(list);
        Manager *newManager = (Manager *)list;
        print(tl);
        l2.output();
        Kho *selectedKho = chonKhoDeQuanLy(l2); // Chọn kho để quản lý
        if (selectedKho)
        {
            selectedKho->addManager(newManager); // Gán quản lý cho kho
        }
        else
        {
            cout << "Lua chon khong hop le!! Vui long nhap lai." << endl;
        }
    }
}
int selectOption()
{
    int tl;
    cout << "Chon du lieu ban muon truy van: " << endl;
    cout << "1. Hang hoa" << endl;
    cout << "2. Kho" << endl;
    cout << "3. Nguoi quan ly" << endl;
    cout << "0. Thoat" << endl;
    cin >> tl;
    return tl;
}
void print(int tl)
{
    switch (tl)
    {
    case 1:
        cout << "+--------------+-------------------------------+----------------+----------------+--------+------------+-------------+----------+-------------+------------+\n";
        cout << "| Ma hang      | Ten hang                      | Loai           | DVT            | SL     | Don gia    | Thanh tien  | Ngay Nhap| Thuoc Kho   |ID Kho      |\n";
        cout << "+--------------+-------------------------------+----------------+----------------+--------+------------+-------------+----------+-------------+------------+\n";
        break;
    case 2:
        cout << "+--------------+-------------------------------+-------------+------------+----------------+---------------+---------------------+\n";
        cout << "| Ma kho       | Ten kho                       | Suc chua    |Loai Kho    | SL hien tai    | ID quan li    | Ten quan li         |\n";
        cout << "+--------------+-------------------------------+-------------+------------+----------------+---------------+---------------------+\n";
        break;
    case 3:
        cout << "+--------------+-------------------------------+-------------+-----------+-----------------+\n";
        cout << "| ID quan li   | Ten Quan Li                   | Gioi tinh   | Nam sinh  | Dia chi         |\n";
        cout << "+--------------+-------------------------------+-------------+-----------+-----------------+\n";
        break;
    }
}
void printStatistics(LinkList &list)
{
    double totalPrice = 0;
    int totalAmount = 0;
    struct TypeStats
    {
        char loaiVatTu[100];
        int soLuong;
        double thanhTien;
    };

    TypeStats stats[100];
    int typeCount = 0;

    Node *temp = list.getHeader();
    ;
    while (temp != NULL)
    {
        Product *product = dynamic_cast<Product *>(temp->data);
        if (product)
        { // Check if the cast was successful
            totalPrice += product->getThanhTien();
            totalAmount += product->getSL();

            bool found = false;
            for (int i = 0; i < typeCount; i++)
            {
                if (strcmp(stats[i].loaiVatTu, product->getLoai().c_str()) == 0)
                {
                    stats[i].soLuong += product->getSL();
                    stats[i].thanhTien += product->getThanhTien();
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                strcpy(stats[typeCount].loaiVatTu, product->getLoai().c_str());
                stats[typeCount].soLuong = product->getSL();
                stats[typeCount].thanhTien = product->getThanhTien();
                typeCount++;
            }
        }
        temp = temp->next;
    }

    cout << "+---------------------+------------+-------------+\n";
    cout << "| Loai hang           | So Luong   | Thanh Tien  |\n";
    cout << "+---------------------+------------+-------------+\n";
    for (int i = 0; i < typeCount; i++)
    {
        cout << "| " << setw(20) << left << stats[i].loaiVatTu
             << "|  " << setw(10) << stats[i].soLuong
             << "| " << setw(12) << fixed << setprecision(2) << stats[i].thanhTien
             << "|\n";
    }
    cout << "+---------------------+------------+-------------+\n";

    // Display the totals
    cout << "| Tong cong           |  " << setw(10) << totalAmount
         << "|  " << setw(11) << fixed << setprecision(2) << totalPrice
         << "|\n";
    cout << "+---------------------+------------+-------------+\n";
}
void printStatisticsByDate(LinkList &list)
{
    map<int, int> quantityByDate;
    map<int, double> valueByDate;
    Node *temp = list.getHeader();
    while (temp != NULL)
    {
        Product *product = (Product *)temp->data;
        if (product)
        {
            int ngay = product->getNgayNhap();
            quantityByDate[ngay] += product->getSL();
            valueByDate[ngay] += product->getThanhTien();
        }
        temp = temp->next;
    }

    cout << "+-----------+-----------+------------+\n";
    cout << "| Ngay nhap | So luong  |Tong gia tri|\n";
    cout << "+-----------+-----------+------------+\n";
    for (const auto &entry : quantityByDate)
    {
        cout << "| " << setw(10) << left << entry.first
             << "| " << setw(10) << entry.second
             << "| " << setw(11) << fixed << setprecision(2) << valueByDate[entry.first]
             << "|\n";
    }
    cout << "+-----------+-----------+------------+\n";
}
#include <iostream>
#include <cstring>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include "Product.h"
#include "Entity.h"
#include "LinkList.h"
#include "Kho.h"
using namespace std;
void xuatThongTin(LinkList l1, LinkList l2, LinkList l3, int tl){
    if (tl==0) return;
    else if (tl==1) {l1.output();system("pause");}
    else if (tl==2) {l2.output(); system("pause");}
    else if (tl==3) {l3.output(); system("pause");}
    else cout<<"Sai loai thong tin. Vui long nhap lai"<<endl;
}
void xoaThongTin(LinkList &l1, LinkList &l2, LinkList &l3, int tl){
    int tl1;
    string ID, name;
    if (tl==0) return;
    cout<<"Chon loai du lieu can xoa (1: ID, 2: Ten): ";
    cin>>tl1;
    if (tl1==1){
        cout<<"Nhap ID can xoa: "; 
        cin>>ID;
        if (tl==1) l1.deleteNode(ID, "ID");
        else if (tl==2) l2.deleteNode(ID, "ID");
        else if (tl==3) l3.deleteNode(ID, "ID");}
    else if (tl1==2){
        cout<<"Nhap ten can xoa: ";
        getline(cin >> ws, name);
        if (tl==1) l1.deleteNode(name, "name");
        else if (tl==2) l2.deleteNode(name, "name");
        else if (tl==3) l3.deleteNode(name, "name");
}
}
void docFile(LinkList &l1, LinkList &l2, LinkList &l3,
             multimap<string, Product*>& products,
             multimap<string, Manager*>& managers){
    ifstream fileProduct("product.txt");
    ifstream fileKho("kho.txt");
    ifstream fileManager("manager.txt");
    while (!fileProduct.eof()) {
        Product *p = new Product;
        p->docFile(fileProduct);
        products.insert({p->getID(), p});
        l1.insertNode(p);
    }
    while (!fileManager.eof()) {
        Manager *m = new Manager;
        m->docFile(fileManager);
        managers.insert({m->getID(), m});
        l3.insertNode(m);
    }
    while (!fileKho.eof()) {
        Kho *k = new Kho;
        k->docFile(fileKho, products, managers);
        l2.insertNode(k);
    }
}
void nhapBanPhim(LinkList &l1, LinkList &l2, LinkList &l3, int tl, Entity *list) {
    string info;
    if (tl == 0) return;
    if (tl == 1) {
        list = new Product;
    } else if (tl == 2) {
        list = new Kho;
    } else if (tl == 3) {
        list = new Manager;
    } else {
        cout << "Lua chon khong hop le!! Vui long nhap lai" << endl;
        return;
    }
    list->Nhap();
    if (tl == 1) {
        l1.insertNode(list);
        Product *newProduct= (Product*)list;
        xuatThongTin(l1, l2, l3, 2);
        cout << "Vui long nhap ID kho chua san pham: ";
        cin >> info; 
        Node *foundNode = nullptr;
        if (l2.search(info, "ID", foundNode)) {
            Kho *selectedKho = (Kho*)foundNode->data;  
            if (selectedKho) {
                selectedKho->addProduct(newProduct);  
                cout << "Da them san pham vao kho: " << selectedKho->getName() << endl;
            } else {
                cout << "Khong tim thay kho phu hop!" << endl;
            }
        } else {
            cout << "Khong tim thay kho phu hop!" << endl;
        }
    } else if (tl == 2) {
        l2.insertNode(list);
    } else if (tl == 3) {
        l3.insertNode(list);
    }
}

int selectOption(){
    int tl;
    cout << "1. Hang hoa" << endl;
    cout << "2. Kho" << endl;
    cout << "3. Nguoi quan ly" << endl;
    cout << "0. Thoat"<<endl;
    cin >> tl;
    return tl;
}
int main(){
    LinkList l1,l2,l3;
    Entity *list;
    int tl, tl6;
    multimap<string, Product*> products;
    multimap<string, Manager*> managers;
    docFile(l1,l2,l3, products, managers);
	string username, password;
    int choice;
    login:
    while (1) {
    	loginUI:
    	system("cls");
        cout << "Go exit de thoat" << endl;
        cout << "Username: ";
        cin >> username;
        if (username == "exit") break; 
        cout << "Password: ";
        cin >> password;
        if (username == "admin" && password == "12345" ) {
        cout << "Chao mung " << username << endl;
		while (1){
          cout << "===== MENU  =====\n";
          cout << "1. Them thong tin\n";
          cout << "2. Xem thong tin\n";
          cout << "3. Xoa thong tin\n";
          cout << "4. Khoi phuc thong tin vua xoa\n";
          cout << "5. Tim kiem thong tin (theo ID/Ten)\n";
          cout << "6. Sap xep theo ID/Ten\n";
          cout<< "7. Thong ke thong tin vat tu\n";
          cout << "0. Dang Xuat\n";
          cout << "========================\n";
          cout << "Chon: ";
          cin >> choice;
          switch (choice){
          	case 0: goto loginUI;
          	case 1:
            cout << "Chon kieu thong tin muon nhap: ";
          		cout << "Moi ban nhap thong tin can them: " << endl;
                tl=selectOption();
                nhapBanPhim(l1, l2, l3, tl, list);
                break;
          	case 2:
			  	cout << "Moi ban nhap thong tin can xem: " << endl;
                tl=selectOption();
                if (tl==0) break;
                else if (tl==1) {l1.output();system("pause");}
                else if (tl==2) {l2.output(); system("pause");}
                else if (tl==3) {l3.output(); system("pause");}
                else cout<<"Sai loai thong tin. Vui long nhap lai"<<endl;
                break;
			case 3: 
                cout<<"Moi ban nhap thong tin can xoa: "<<endl;
                tl=selectOption();
                if (tl==0) break;
                else if (tl==1) {l1.output();}
                else if (tl==2) {l2.output();}
                else if (tl==3) {l3.output();}
                else {cout<<"Sai loai thong tin. Vui long nhap lai"<<endl; break;}
                xoaThongTin(l1,l2,l3, tl);	
				break;
			case 4: 
                tl=selectOption();
                if (tl==0) break;
                else if (tl==1) l1.undoDelete();
                else if (tl==2) l2.undoDelete();
                else if (tl==3) l3.undoDelete();
                cout<<"Khoi phuc thong tin thanh cong!!";
				break;	
            case 6:
            	tl=selectOption();
				if (tl==0) break;
				cout<<"\nChon loai du lieu can sap xep theo alphabet (1: ID, 2: Ten): ";
                cin>>tl6;
            	switch (tl6){
            		case 1:
            			switch (tl){
            				case 1: l1.sort("ID"); break;
            				case 2: l2.sort("ID"); break;
            				case 3: l3.sort("ID"); break;
						}
						break;
            		case 2:	
            			switch (tl){
            				case 1: l1.sort("name"); break;
            				case 2: l2.sort("name"); break;
            				case 3: l3.sort("name"); break;
						}
						break;
				}
            	break;
            case 5:
                tl=selectOption();
                int tl1;
                string ID, name;
                if (tl==0) break;
                cout<<"\nChon loai du lieu can tim kiem (1: ID, 2: Ten): ";
                cin>>tl1;
                bool found=false;
                Node *foundNode= NULL;
                if (tl1==1){
                    cout<<"Nhap ID can tim kiem: "; 
                    cin>>ID;
                    if (tl==1) found=l1.search(ID, "ID", foundNode);
                    else if (tl==2) found=l2.search(ID, "ID", foundNode);
                    else if (tl==3) found=l3.search(ID, "ID", foundNode);}
                    else if (tl1==2){
                        cout<<"Nhap ten can tim kiem: ";
                        getline(cin >> ws, name);
                        if (tl==1) found=l1.search(name, "name",foundNode);
                        else if (tl==2) found=l2.search(name, "name",foundNode);
                        else if (tl==3) found=l3.search(name, "name",foundNode);}
                    else cout<<"Kieu du lieu can tim kiem khong hop le"<<endl;
                    if (found) {
                        cout << "Tim thay phan tu can tim:\n";
                        foundNode->data->Xuat();
                        system("pause");
                    } else cout << "Khong tim thay gia tri can tim\n";
                break;	
            // case 7: (cha biet sao nhap xuong duoi nay thi code k chay duoc nen t tam de option len ke cuoi, tam thoi bo qua cai nay)
            //     tl=selectOption();
            //     int tl1;
            //     if (tl==1){
            //         cout<<"Chon kieu du lieu can thong ke: ";
            //         cin>>tl1;
            //     }

	}
        }
        }
     else {
	cout << "Dang nhap that bai!" << endl;
	system("pause");
	}
}
	return 0;
}

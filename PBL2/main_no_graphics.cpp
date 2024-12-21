#include "System.cpp"
using namespace std;

int main()
{
    LinkList l1, l2, l3;
    Entity *list;
    int tl, tl6;
    multimap<string, Product *> products;
    multimap<string, Manager *> managers;
    multimap<string, Kho *> kho;
    docFile(l1, l2, l3, products, kho, managers);
    string username, password;
    int choice;
login:
    while (1)
    {
    loginUI:
    system("cls");
    cout << "Username:";
    cin >> username;
    if (username == "exit") {
        system("cls");
        cout << "Ban da thoat chuong trinh!";
        return 0;
    }
     cout << "Password:";
    cin >> password;
        if (username == "admin" && password == "12345")
        {

            while (1)
            {
                system("cls");
                cout << "=======   MENU  ==========\n";
                cout << "1. Them thong tin\n";
                cout << "2. Xem thong tin\n";
                cout << "3. Xoa thong tin\n";
                cout << "4. Khoi phuc thong tin vua xoa\n";
                cout << "5. Tim kiem thong tin (theo ID/Ten)\n";
                cout << "6. Sap xep theo ID/Ten\n";
                cout << "7. Thong ke thong tin hang\n";
                cout << "8. Chinh sua thong tin\n";
                cout << "0. Dang Xuat\n";
                cout << "========================\n";
                cout << "Chon: ";
                cin >> choice;
                switch (choice)
                {
                case 0:
                    cout << "Ban co muon luu file truoc khi dang xuat khong? \nBam Y de dong y, bam N de thoat.";
                    if (getch()=='y'||(getch()=='Y')) {
                    xuatFile(l1, l2, l3, products, kho, managers);
                    cout << "Luu file thanh cong!" << endl;
                    system("pause");
                    }
                    goto loginUI;
                case 1:
                    cout << "Moi ban nhap thong tin can them: " << endl;
                    tl = selectOption();
                    nhapBanPhim(l1, l2, l3, tl, list);
                    system("pause");
                    break;
                case 2:
                    cout << "Moi ban nhap thong tin can xem: " << endl;
                    tl = selectOption();
                    print(tl);
                    if (tl == 0)
                        break;
                    else if (tl == 1)
                    {
                        l1.output();
                        system("pause");
                    }
                    else if (tl == 2)
                    {
                        l2.output();
                        system("pause");
                    }
                    else if (tl == 3)
                    {
                        l3.output();
                        system("pause");
                    }
                    else
                        cout << "Sai loai thong tin. Vui long nhap lai" << endl;
                    break;
                case 3:
                    cout << "Moi ban nhap thong tin can xoa: " << endl;
                    tl = selectOption();
                    if (tl)
                        print(tl);
                    if (tl == 0)
                        break;
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
                    {
                        cout << "Sai loai thong tin. Vui long nhap lai" << endl;
                        break;
                    }
                    xoaThongTin(l1, l2, l3, tl);
                    cout << "Xoa thong tin thanh cong!\n";
                    system("pause");
                    break;
                case 4:
                    tl = selectOption();
                    if (tl == 0)
                        break;
                    else if (tl == 1)
                        l1.undoDelete();
                    else if (tl == 2)
                        l2.undoDelete();
                    else if (tl == 3)
                        l3.undoDelete();
                    cout << "Khoi phuc thong tin thanh cong!!\n";
                    system("pause");
                    break;
                case 6:
                    tl = selectOption();
                    if (tl == 0)
                        break;
                    cout << "\nChon loai du lieu can sap xep theo alphabet (1: ID, 2: Ten): ";
                    cin >> tl6;
                    switch (tl6)
                    {
                    case 1:
                        switch (tl)
                        {
                        case 1:
                            l1.sort("ID");
                            break;
                        case 2:
                            l2.sort("ID");
                            break;
                        case 3:
                            l3.sort("ID");
                            break;
                        }
                        break;
                    case 2:
                        switch (tl)
                        {
                        case 1:
                            l1.sort("name");
                            break;
                        case 2:
                            l2.sort("name");
                            break;
                        case 3:
                            l3.sort("name");
                            break;
                        }
                        break;
                    }
                    break;

                case 7:
                    cout << "Thong ke theo (1: Loai hang, 2: Ngay nhap): ";
                    int type;
                    cin >> type;
                    if (type == 1)
                    {
                        printStatistics(l1);
                    }
                    else if (type == 2)
                    {
                        printStatisticsByDate(l1);
                    }
                    system("pause");
                    break;
                case 8:
                    int index;
                    tl = selectOption();
                    print(tl);
                    if (tl == 0)
                        break;
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
                    cout << "Chon chi so (STT) cua thong tin cua de chinh sua: ";
                    cin >> index;
                    index--;
                    switch (tl)
                    {
                    case 1:
                        l1[index]->chinhSuaThongTin();
                        break;
                    case 2:
                        l2[index]->chinhSuaThongTin();
                        break;
                    case 3:
                        l3[index]->chinhSuaThongTin();
                        break;
                    }
                    cout << "Da sua thong tin theo yeu cau!\n";
                    system("pause");
                    break;
                case 5:
                    tl = selectOption();
                    int tl1;
                    string ID, name;
                    if (tl == 0)
                        break;
                    cout << "\nChon loai du lieu can tim kiem (1: ID, 2: Ten): ";
                    cin >> tl1;
                    bool found = false;
                    Node *foundNode = NULL;
                    if (tl1 == 1)
                    {
                        cout << "Nhap ID can tim kiem: ";
                        cin >> ID;
                        if (tl == 1)
                            found = l1.search(ID, "ID", foundNode);
                        else if (tl == 2)
                            found = l2.search(ID, "ID", foundNode);
                        else if (tl == 3)
                            found = l3.search(ID, "ID", foundNode);
                    }
                    else if (tl1 == 2)
                    {
                        cout << "Nhap ten can tim kiem: ";
                        getline(cin >> ws, name);
                        if (tl == 1)
                            found = l1.search(name, "name", foundNode);
                        else if (tl == 2)
                            found = l2.search(name, "name", foundNode);
                        else if (tl == 3)
                            found = l3.search(name, "name", foundNode);
                    }
                    else
                        cout << "Kieu du lieu can tim kiem khong hop le" << endl;
                    if (found)
                    {
                        cout << "Tim thay phan tu can tim:\n";
                        print(tl);
                        foundNode->data->Xuat();
                        system("pause");
                    }
                    else
                        cout << "Khong tim thay gia tri can tim\n";
                    system("pause");
                    break;
                }
            }
        }
        else
        {
            cout << "Dang nhap that bai!" << endl;
            system("pause");
        }
    }
    return 0;
}

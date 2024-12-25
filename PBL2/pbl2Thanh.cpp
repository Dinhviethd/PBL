#include "System.cpp"
using namespace std;

int main()
{
    LinkList l1, l2, l3;
    Entity *list;
    char tl, tl6;
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
    textcolor(14);
    cout << "┌───────────────────────────────────────────────┐" << endl;
    cout << "│                                               │" << endl;
    cout << "│           PBL 2: DO AN CO SO LAP TRINH        │" << endl;
    cout << "│           QUAN LY HANG NHAP TRONG 1 THANG     │" << endl;
    cout << "│                                               │" << endl;
    cout << "│        Created by: NGUYEN CHI THANH           │" << endl;
    cout << "│                    NGUYEN TA DINH VIET        │" << endl;
    cout << "│                                               │" << endl;
    cout << "│        Username:                              │" << endl;
    cout << "│                                               │" << endl;
    cout << "│        Password:                              │" << endl;
    cout << "│                                               │" << endl;
    cout << "│                                               │" << endl;
    cout << "│ Nhap exit muc username de thoat CT...         │" << endl;
    cout << "└───────────────────────────────────────────────┘" << endl;
    cout << endl;
    gotoxy(18, 8); 
    cin >> username;
    if (username == "exit") {
        system("cls");
        textcolor(2);
        cout << "Ban da thoat chuong trinh!";
        return 0;
    }
    gotoxy(18, 10); 
    cin >> password;
        if (username == "admin" && password == "12345")
        {
        gotoxy(5, 15); 
        textcolor(2);
        cout << "Dang nhap thanh cong, se vao menu trong 3s...";
        Sleep(3000); 
            while (1)
            {
                textcolor(7);
                system("cls");
                showMenu();
                gotoxy(38, 17);
                cin >> choice;
                system("cls");
                switch (choice)
                {
                case 0:
                    cout << "Ban co muon luu file truoc khi dang xuat khong? \nBam Y de dong y, bam N de thoat.";
                    tl = getch();
                    if (tl=='y'||tl=='Y') {
                    xuatFile(l1, l2, l3, products, kho, managers);
                    textcolor(2);
                    cout << "\nLuu file thanh cong!" << endl;
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

                    }
                    else if (tl == 2)
                    {
                        l2.output();
                    }
                    else if (tl == 3)
                    {
                        l3.output();
                    }
                    else{
                        cout << "Sai loai thong tin. Vui long nhap lai" << endl;
                        getch();
                    }
                    printLine(tl);
                    system("pause");
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
                    printLine(tl);
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
                    cout << "Da sap xep theo yeu cau cua nguoi dung theo yeu cau" << endl;
                    system("pause");
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
                    printLine(tl);
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
             gotoxy(5, 15); 
            textcolor(4);
            cout << "Dang nhap that bai!" << endl;
            system("pause");
        }
    }
    return 0;
}

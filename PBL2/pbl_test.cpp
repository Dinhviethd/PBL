#include <iostream>
#include <cstring>
using namespace std;
class Entity{
    protected:
        string ID;
        string name;
    public:
        virtual void Nhap();
        virtual void Xuat();
        // virtual void sapXep();
        virtual string getName() const;
        virtual string getID() const;
};
void Entity::Nhap(){
    cout<<"Nhap ID: "; getline(cin>>ws, ID);
    cout<<"Nhap ten: "; getline(cin>>ws, name);
}
void Entity::Xuat(){
    cout<<"ID: "<<ID<<"\tTen: "<<name;
}
string Entity::getName() const{
    return name;
}
string Entity::getID() const{
    return ID;
}
class Product:public Entity{
protected:
    string donVi;
    int sl;
    float donGia;
    public: 
        void Nhap();
        void Xuat();
};
void Product::Nhap(){
    Entity::Nhap();
    cout<<"Nhap so luong sp: "; cin>>sl;
    cout<<"Nhap don gia san pham: "; cin>>donGia;
    cout<<"Nhap don vi: "; cin>>donVi;
}
void Product::Xuat(){
    Entity::Xuat();
    cout<<"\tSo Luong: "<<sl<<"\tDon vi: "<<donVi<<"\tDon gia: "<<donGia;
}
class Manager:public Entity{
    string mAdr;
    string gender;
    int birth;
    public:
        void Nhap();
        void Xuat();
};
void Manager::Nhap(){
    Entity::Nhap();
    cout<<"Nhap gioi tinh: "; cin>>gender;
    cout<<"Nhap nam sinh: "; cin>>birth;
    cout<<"Nhap dia chi quan li: "; getline(cin>>ws, mAdr);
}
void Manager::Xuat(){
    Entity::Xuat();
    cout<<"\tGioi tinh: "<<gender<<"\tNam sinh: "<<birth<<"\tDia chi: "<<mAdr;
}
class DaiLy:public Entity{
    string dAdr;
    string sdt;
    public:
        void Nhap();
        void Xuat();
};
void DaiLy::Nhap(){
    Entity::Nhap();
    cout<<"Nhap dia chi dai ly: "; getline(cin>>ws, dAdr);
    cout<<"Nhap SDT: "; cin>>sdt;
}
void DaiLy::Xuat(){
    Entity::Xuat();
    cout<<"\tDia chi: "<<dAdr<<"\tSDT: "<<sdt<<"\tID sp: "<<Product::getID;
}
class Kho:public Entity{
    string date;
    int maxsize;
    public:
        void Nhap();
        void Xuat();
};
void Kho::Nhap(){
    Entity::Nhap();
    cout<<"Nhap ngay nhap hang: "; cin>>date;
    cout<<"Nhap suc chua cua kho: "; cin>>maxsize;
}
void Kho::Xuat(){
    Entity::Xuat();
    cout<<"\tSuc chua: "<<maxsize<<"\tNgay nhap hang: "<<date
    <<"\tID quan ly: "<<Manager::getID;
}
class GiaoDich: public Product{
    public:
        void Xuat();
        float thanhTien();
};
void GiaoDich::Xuat(){
    cout<<"ID: "<<Product::getID()<< "\tName: "<<Product::getName()<<"\tThanh Tien: "<<thanhTien();
}
float GiaoDich::thanhTien(){
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
class LinkList{
    struct Node{
        Entity *data;
        Node *next;
        Node *prev;
    };
    Node *header;
    Node *deleted;
    public:
        LinkList();
        ~LinkList();
        void insertNode(Entity *data);
        void deleteNode(int vitri);
        void deleteNode(string info, string _type);
        void undoDelete();
        void search(string info);
        void output();
};
LinkList::LinkList() {
    header=NULL;
    deleted= NULL;
}
void LinkList::insertNode(Entity *data){
    Node *newNode= new Node();
    newNode->data= data;
    newNode->next= header;
    newNode->prev= NULL;
    if (header !=NULL) header->prev= newNode;
    header= newNode;
}
void LinkList::deleteNode(string info, string _type){
    if (header==NULL) return;
    Node *temp= header;
    if (_type=="ID" &&header->data->getID()== info|| _type=="name" && header->data->getName()==info){
        deleted= header;
        header= temp->next;
        if (header==NULL){
            header->prev= NULL;
        }        
        return;
    }
    while (temp!=NULL){
        if (_type=="ID" &&temp->data->getID()== info|| _type=="name" && temp->data->getName()==info){
        deleted= temp;
        temp->prev->next= temp->next;
            if (temp->next != NULL){
                temp->next->prev= temp->prev;
        }
        return;}
        temp=temp->next;
    }
    cout<<"Khong co gia tri can tim!!!";
}
void LinkList::undoDelete() {
    if (deleted == NULL) {
        cout << "Khong co node nao da bi xoa!" << endl;
        return;
    }
    // Nếu là node đầu tiên
    if (deleted->prev == NULL) {
        deleted->next->prev = deleted;
        header = deleted;
    } else if (deleted->next == NULL) {
        // Nếu là node cuối cùng
        deleted->prev->next = deleted;
    } else {
        // Nếu là node giữa
        deleted->prev->next = deleted;
        deleted->next->prev = deleted;
    }
    deleted = NULL;  // Đặt lại con trỏ để tránh undo lại nhiều lần
}
void LinkList::output(){
    if (header==NULL) return; 
    Node *temp=header;
    while (temp!=NULL){
        temp->data->Xuat();
        temp=temp->next;
    }
}
void xuatThongTin(LinkList l1, LinkList l2, LinkList l3, LinkList l4, LinkList l5){
    cout << "Chon loai thong tin can xuat (1: Product, 2: Kho, 3: Manager, 4: Dai ly, 5: Phie Giao Dich 0: Thoat)" << endl;
    int tl;
    cin>>tl;
    if (tl==1) l1.output();
    else if (tl==2) l2.output();
    else if (tl=3) l3.output();
    else if (tl=4) l4.output();
    else if (tl=5) l5.output();
    else cout<<"Sai loai thong tin. Vui long nhap lai"<<endl;
}
LinkList xoaThongTin(LinkList l1, LinkList l2, LinkList l3, LinkList l4, LinkList l5){
    cout << "Chon thong tin can xoa (1: Product, 2: Kho, 3: Manager, 4: Dai ly, 5: Phie Giao Dich 0: Thoat)" << endl;
    int tl,tl1;
    string ID, name;
    cin>>tl;
    cout<<"Chon loai thong tin can xoa (1: ID, 2: Ten)";
    cin>>tl1;
    if (tl1==1){
        cout<<"Nhap ID can xoa: "; 
        cin>>ID;
        if (tl==1) {
            l1.deleteNode(ID, "ID");
            return l1;}
        else if (tl==2) {
            l2.deleteNode(ID, "ID");
            return l2;}
        else if (tl==3) {
            l3.deleteNode(ID, "ID");
            return l3;}
        else if (tl==4) {
            l4.deleteNode(ID, "ID");
            return l4;}
        else if (tl==5) {
            l5.deleteNode(ID, "ID");
            return l5;}
    else if (tl1==2){
        cout<<"Nhap ten can xoa: ";
        getline(cin >> ws, name);
        if (tl==1) {
            l1.deleteNode(name, "name");
            return l1;}
        else if (tl==2) {
            l2.deleteNode(name, "name");
            return l2;}
        else if (tl==3) {
            l3.deleteNode(name, "name");
            return l3;}
        else if (tl==4) {
            l4.deleteNode(name, "name");
            return l4;}
        else if (tl==5) {
            l5.deleteNode(name, "name");
            return l5;}
    }
}
}
int main(){
    LinkList l1,l2,l3,l4,l5;
    Entity *list[150];
    int n=0;
    int tl;
    do {
        cout << "Chon kieu thong tin muon nhap (1: Product, 2: Kho, 3: Manager, 4: Dai Ly, 5: Phieu Giao Dich 0: Thoat): ";
        cin >> tl;
        if (tl == 1){
            list[n] = new Product;
            l1.insertNode(list[n]);}
        else if (tl == 2){
            list[n] = new Kho;
            l2.insertNode(list[n]);}
        else if (tl == 3){
            list[n] = new Manager;
            l3.insertNode(list[n]);}
        else if (tl==4){
            list[n]= new DaiLy;
            l4.insertNode(list[n]);
        }
        else if (tl==5){
            list[n]= new GiaoDich;
            l5.insertNode(list[n]);
        }
        else break;
        list[n++]->Nhap();
    } while (n < 150);
    xuatThongTin(l1,l2,l3,l4,l5);
    xoaThongTin(l1,l2,l3,l4,l5);
    return 0;    
}
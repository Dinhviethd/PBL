#ifndef LINKLIST_H
#define LINKLIST_H
#include <iostream>
#include "Entity.h"
#include <cstring>
using namespace std;
struct Node {
        Entity *data;
        Node *next;
        Node *prev;
};
class LinkList {
    Node *header;
    Node *deleted;
public:
    LinkList();
    ~LinkList();
    void insertNode(Entity *data);
    void insertNode1(Entity *data, int viTri);
    void deleteNode(string info, string _type);
    void undoDelete();
    bool search(string info,string _type, Node *&foundNode);
    void output();
};
LinkList::LinkList() {
    header = NULL;
    deleted = NULL;
}
LinkList::~LinkList() {
    Node *temp = header;
    while (temp != NULL) {
        Node *next = temp->next;
        delete temp->data;
        delete temp;
        temp = next;
    }
}
bool LinkList::search(string info, string _type, Node *&foundNode){
    foundNode=NULL;
    if (header==NULL) return false;
    Node  *temp=header;
    while (temp != NULL) {
        if ((_type == "ID" && temp->data->getID() == info) || 
            (_type == "name" && temp->data->getName() == info)) {
            foundNode= temp;
            return true;
        }
        temp = temp->next;
    }
    return false;
}
void LinkList::insertNode(Entity *data) {
    Node* foundNode = NULL;
    if (search(data->getID(), "ID", foundNode)) {
        cout << "Phan tu voi ID '" << data->getID() << "' da ton tai trong danh sach. Khong them moi.\n";
        getchar();
        return;  
    }
    Node *newNode = new Node();
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    if (header == NULL) header= newNode;
    else { 
        Node *temp= header;
        while (temp->next !=NULL){
            temp=temp->next;
        }
        temp->next= newNode;
        newNode->prev= temp;
    }
}
int count(Node *head){
        int cnt=0;
    while (head!=NULL){
        cnt++;
        head=head->next;
    }
    return cnt;
}
void LinkList::insertNode1(Entity *data, int position){
    int cnt= count(header);
    Node *newNode = new Node();
    newNode->data=data;
    newNode->next = NULL;
    newNode->prev = NULL;
    if (position == 1) {
        newNode->next = header;
        if (header != nullptr) {
            header->prev = newNode;
        }
        header = newNode;
        return;
    }
    Node *temp = header;
    for (int i = 1; i < position - 1; i++) {
        temp = temp->next;
    }
    newNode->next = temp->next;
    newNode->prev = temp;
    if (temp->next != NULL) {
        temp->next->prev = newNode;
    }
    temp->next = newNode;
}
void LinkList::deleteNode(string info, string _type) {
    if (header == NULL) {
        cout << "Danh sach rong!" << endl;
        return;
    }
    Node *temp = header;
    while (temp != NULL) {
        if ((_type == "ID" && temp->data->getID() == info) || 
            (_type == "name" && temp->data->getName() == info)) {
            deleted = temp;    
            if (temp == header) {
                header = temp->next;
                if (header != NULL) header->prev = NULL;
            } else {
                if (temp->prev != NULL) temp->prev->next = temp->next;
                if (temp->next != NULL) temp->next->prev = temp->prev;
            }
            return;
        }
        temp = temp->next;
    }
    cout << "Khong tim thay gia tri can xoa!" << endl;
}
void LinkList::undoDelete() {
    if (deleted == NULL) {
        cout << "Khong co node nao da bi xoa!" << endl;
        return;
    }
    if (deleted->prev == NULL) {
        deleted->next->prev = deleted;
        header = deleted;
    } else if (deleted->next == NULL) {
        deleted->prev->next = deleted;
    } else {
        deleted->prev->next = deleted;
        deleted->next->prev = deleted;
    }
    deleted = NULL;
}
void LinkList::output() {
    if (header == NULL) {
        cout << "Danh sach rong!" << endl;
        return;
    }
    Node *temp = header;
    while (temp != NULL) {
        temp->data->Xuat();
        temp = temp->next;
    }
}

#endif
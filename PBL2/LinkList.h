#ifndef LINKLIST_H
#define LINKLIST_H
#include <iostream>
#include "Entity.h"
#include <cstring>
using namespace std;
class LinkList {
    struct Node {
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
    void deleteNode(string info, string _type);
    void undoDelete();
    void search(string info,string _type);
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
void LinkList::insertNode(Entity *data) {
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
void LinkList::search(string info, string _type){
    if (header==NULL) return;
    Node  *temp=header;
    while (temp != NULL) {
        if ((_type == "ID" && temp->data->getID() == info) || 
            (_type == "name" && temp->data->getName() == info)) {
            temp->data->Xuat();
            system("pause");
            return;
        }
        temp = temp->next;
    }
    cout<<"Khong tim thay gia tri can tim\n";
}
#endif
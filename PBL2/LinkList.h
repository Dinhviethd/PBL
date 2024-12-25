#ifndef LINKLIST_H
#define LINKLIST_H
#include <iostream>
#include "Entity.h"
#include <cstring>
#include <iomanip>
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
    Node* getHeader() const {
    return header;
}
    void insertNode(Entity *data);
    void deleteNode(string info, string _type);
    void undoDelete();
    Entity *operator[](int index)    {

        Node *temp = getHeader();
        for (int i = 0; i < index; i++)
        {
            temp = temp->next;
        }
        return temp->data;
    };
    bool search(string info,string _type, Node *&foundNode);
    void sort(string _type);
    void output();
    bool checkDuplicate(Entity *data);
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
bool LinkList::checkDuplicate(Entity *data){
    Node* foundNode = NULL;
    return search(data->getID(), "ID", foundNode);
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
int count(Node *head){
        int cnt=0;
    while (head!=NULL){
        cnt++;
        head=head->next;
    }
    return cnt;
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

void LinkList::sort(string _type) {
    if (header == NULL || header->next == NULL) {
        cout << "Danh sach trong hoac chi co 1 phan tu, khong can sap xep." << endl;
        return;
    }
    
    bool swapped;
    do {
        swapped = false;
        Node *current = getHeader();
        
        while (current->next != NULL) {
            bool needSwap = false;

            if (_type == "ID" && current->data->getID() > current->next->data->getID()) {
                needSwap = true;
            } else if (_type == "name" && current->data->getName() > current->next->data->getName()) {
                needSwap = true;
            }

            if (needSwap) {
                Entity *tempData = current->data;
                current->data = current->next->data;
                current->next->data = tempData;
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);

    cout << "Da sap xep theo yeu cau." << endl;
}

void LinkList::output() {
    if (header == NULL) {
        cout << "Danh sach rong!" << endl;
        return;
    }
    cnt = 0;
    Node *temp = header;
    while (temp != NULL) {
        temp->data->Xuat();
        temp = temp->next;
    }
}

#endif
//
//  main.c
//  LinkedLists
//
//  Created by Alok K. Shukla on 07/03/13.
//  Copyright (c) 2013 Alok Kumar Shukla. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node* next;
};

typedef struct node Node;


int Length(Node *head){
    Node* current=head;
    int length=0;
    while (current!=NULL) {
        length++;
        current=current->next;
    }
    return length;
}


Node* BuildOneTwoThree(){
    Node* head=NULL;
    Node* second=NULL;
    Node* third=NULL;
    
    head=malloc(sizeof(Node));
    second=malloc(sizeof(Node));
    third=malloc(sizeof(Node));
    
    head->data=1;
    head->next=second;
    
    second->data=2;
    second->next=third;
    
    third->data=3;
    third->next=NULL;
    
    return head;
}

void Push(Node** headRef, int data){
    Node* newNode=malloc(sizeof(Node));
    newNode->data=data;
    newNode->next=*headRef;
    *headRef=newNode;
}

Node* BuildWithDummyNode(){
    Node dummy;
    Node* tail=&dummy;
    
    int i;
    dummy.next=NULL; //Its a Node, not a pointer to Node
    
    for (i=1; i<6; i++) {
        Push(&(tail->next), i);
        tail=tail->next;
    }
    return dummy.next;
}

void appendNode(Node** headRef, int data){
    Node* current=*headRef;
    Node* newNode;
    newNode=malloc(sizeof(Node));
    newNode->data=data;
    newNode->next=NULL;
    
    if (current==NULL) {
        *headRef=newNode;
    }
    else{
        while (current->next!=NULL) {
            current=current->next;
        }
        current->next=newNode;
    }
}

void appendNodeWithPush(Node** headRef, int data){
    Node* current=*headRef;
    if (current==NULL) {
        Push(headRef, data);
    }
    else{
        while (current->next!=NULL) {
            current=current->next;
        }
        Push(&(current->next), data);
    }
}
Node* BuildWithSpecialCase(){
    Node* head=NULL;
    Node* tail=head;
    
    int i;
    
    Push(&head, 1);
    tail=head;
    
    for (i=2; i<6; i++) {
        Push(&(tail->next), i);
        tail=tail->next;
    }
    
    return head;
}

Node* BuildWithLocalRef(){
    Node* head=NULL;
    Node** lastPtrRef=&head;
    
    int i;
    
    for (i=1; i<6; i++) {
        Push(lastPtrRef, i);
        lastPtrRef=&((*lastPtrRef)->next);
    }
    return head;
}
void printList(Node* head){
    printf("[ ");
    Node* temp=head;
    while (temp->next!=NULL) {
        printf("%d-->",temp->data);
        temp=temp->next;
    }
    printf("%d ]\n\n",temp->data);
}
Node* copyList(Node* head){
    Node* current=head;
    Node* newList=NULL;
    Node* tail=NULL;
    
    while (current!=NULL) {
        if (newList==NULL) {
            newList=malloc(sizeof(Node));
            newList->data=current->data;
            newList->next=NULL;
            tail=newList;
        }
        else{
            tail->next=malloc(sizeof(Node));
            tail=tail->next;
            tail->data=current->data;
            tail->next=NULL;
        }
        current=current->next;
    }
    return newList;
}
Node* copyListWithPush(Node* head){
    Node* current=head;
    Node* newList=NULL;
    Node* tail=NULL;
    
    while (current!=NULL) {
        if (newList!=NULL) {
            Push(&newList, current->data);
            tail=newList;
        }
        else{
            Push(&(tail->next), current->data);
            tail=tail->next;
        }
        current=current->next;
    }
    return newList;
}
Node* copyListWithDummy(Node* head){
    Node dummy;
    Node* current=head;
    Node* tail;
    
    dummy.next=NULL;
    tail=&dummy;
    
    while (current!=NULL) {
        Push(&(tail->next), current->data);
        tail=tail->next;
        current=current->next;

    }
    
    return dummy.next;
}

Node* copyListWithLocalRef(Node* head){
    Node* current=head;
    Node* newList=NULL;
    Node** lastPtrRef=&newList;
    
    while (current!=NULL) {
        Push(lastPtrRef, current->data);
        lastPtrRef=&(*lastPtrRef)->next;
        current=current->next;
    }
    return newList;
}
Node* copyListRecursive(Node* head){
    Node* current=head;
    if (head==NULL) {
        return NULL;
    }
    else{
        Node* newList=malloc(sizeof(Node));
        newList->data=current->data;
        newList->next=copyListRecursive(current->next);
        return newList;
    }
}
    
int main(int argc, const char * argv[])
{
    
    //printList(appendNode(&(BuildWithLocalRef()), 2)); //doesn't work? &(2376ut) doesn't work not a lvalue
    Node* head=BuildOneTwoThree();
    appendNodeWithPush(&head, 4);
    printList(copyList(head));
    printList(BuildWithDummyNode());
    printList(BuildWithSpecialCase());
    printList(copyList(BuildWithLocalRef()));
    printList(copyListWithDummy(BuildWithSpecialCase()));
    printList(copyListWithLocalRef(BuildWithLocalRef()));
    printList(copyListRecursive(BuildOneTwoThree()));
    return 0;
}


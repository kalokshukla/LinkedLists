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
    if (temp==NULL) {
        printf(" ]");
        return;
    }
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

int countOccurences(Node* head, int term){
    Node* current=head;
    int count=0;
    while (current!=NULL) {
        if (current->data==term) {
            count++;
        }
        current=current->next;
    }
    return count;
}

int getNth(Node* head, int n){
    Node* current=head;
    if (head==NULL) {
        printf("List is empty");
        exit(-2);
    }
    else{
        while (--n>0&&current!=NULL) {
            current=current->next;
        }
        if (current!=NULL) {
            return current->data;
        }
        else{
            printf("Index out of bound.\n");
            exit(-2);
        }
    }
}
void deleteList(Node** headRef){
    Node* current=*headRef;
    Node* temp=current;
    while (temp!=NULL) {
        temp=current->next;
        free(current);
        current=temp;
    }
    *headRef=NULL;
}
int pop(Node** headRef){
    if (*headRef==NULL) {
        printf("\n\nList is already empty.\n");
        exit(-9);
    }
    Node* temp=*headRef;
    int result=temp->data;
    temp=temp->next;
    free(*headRef);
    *headRef=temp;
    return result;
}
void insertNth(Node** headRef, int n, int data){
    Node* current=*headRef;
    if (*headRef==NULL&&n>1) {
        printf("\nInserting in empty list at a postion other than first.\n");
    }
    if (n==1) {
        Push(headRef, data);
        
        
    }
    else{
        while (--n>1&&current!=NULL) {
            current=current->next;
        }
        if (current==NULL&&n>1) {
            printf("Reached end of list.\n");
            exit(-10);
        }
        Node* newNode=malloc(sizeof(Node));
        newNode->data=data;
        newNode->next=current->next;
        current->next=newNode;
    }
}

void sortedInsert(Node** headRef, Node* newNode){
    Node* current=*headRef;
    if(current==NULL||current->data>=newNode->data){
        newNode->next=current;
        *headRef=newNode;
        
    }
    else{
        while (current->next->data<newNode->data&&current->next!=NULL) {
            current=current->next;
        }

        newNode->next=current->next;
        current->next=newNode;
    }
}
void insertSort(Node** headRef){
    Node* result = NULL;      // build the answer here
    Node* current = *headRef; // iterate over the original list
    Node* next;
    while (current!=NULL) {
        next = current->next;   // tricky - note the next pointer before we change it
        sortedInsert(&result, current);
        current = next;
    }
    *headRef = result;
}
void append(Node** aRef, Node** bRef){
    if (*aRef==NULL) {
        aRef=bRef;
    }
    else{
        Node* current=*aRef;
        while (current->next!=NULL) {
            current=current->next;
        }
        current->next=*bRef;
        *bRef=NULL;
    }
}
/*void Split(Node* head, Node** first, Node** second){
    Node* fast=head;
    Node* slow=head;
    while (fast->next->next!=NULL) {
        fast=fast->next->next;
        slow=slow->next;
    }
    *second=slow->next;
    slow->next=NULL;
    *first=head;
}*/
int main(int argc, const char * argv[])
{
    
    //printList(appendNode(&(BuildWithLocalRef()), 2)); //doesn't work? &(2376ut) doesn't work not a lvalue
    Node* head=BuildOneTwoThree();
    appendNodeWithPush(&head, 4);
    appendNode(&head, 4);
    appendNode(&head, 4);
    printList(head);
    printf("4 occured %d times.\n\n",countOccurences(head, 4));
    /*printList(BuildWithDummyNode());
    printList(BuildWithSpecialCase());
    printList(copyList(BuildWithLocalRef()));
    printList(copyListWithDummy(BuildWithSpecialCase()));
    printList(copyListWithLocalRef(BuildWithLocalRef()));
    printList(copyListRecursive(BuildOneTwoThree()));*/
    printf("4th element in list is %d.\n",getNth(head, 4));
    printList(head);
    deleteList(&head);
    printf("List after deletion is: ");
    printList(head);
    printf("\nTest list: ");
    Node* test=BuildWithSpecialCase();
    printList(test);
    pop(&test);
    printList(test);
    Push(&test, 5);
    printList(test);
    Node* test3=BuildOneTwoThree();
    pop(&test3);
    pop(&test3);
    pop(&test3);
    insertNth(&test3, 1, 234);
    printList(test3);
    insertNth(&(head), 1, 89);
    //printList(test);
    //insertSort(&test);
    //printList(test);
    Node* test4=BuildWithLocalRef();
    Node new;
    new.data=57;
    new.next=NULL;
    insertNth(&test4, 6, 67);
    printList(test4);
    sortedInsert(&test4, &new);
    printList(test4);
    Node* test5=BuildWithLocalRef();
    Push(&test5, 6);
    insertNth(&test5, 4, 3);
    printList(test5);
    insertSort(&test5);
    append(&test5, &test4);
    printList(test5);
    return 0;
}


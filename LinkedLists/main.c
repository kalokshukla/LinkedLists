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
int main(int argc, const char * argv[])
{
    printList(BuildWithLocalRef());
    printList(BuildWithDummyNode());
    printList(BuildWithSpecialCase());
    return 0;
}


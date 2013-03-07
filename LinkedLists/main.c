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
    Node* head=BuildOneTwoThree();
    Node* head2=NULL;
    Push(&head2, 23);
    printList(head2);
    Push(&head2, 24);
    printList(head2);
    Push(&head2, 25);
    printList(head2);
    printList(head);
    int len=Length(head);
    printf("%d\n",len);
    Push(&head, 0);
    printList(head);
    Push(&head, -1);
    printList(head);
    len=Length(head);
    printf("%d\n",len);
    return 0;
}


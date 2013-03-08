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
    Node* result = NULL;      
    Node* current = *headRef; 
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

void split(Node* head, Node** first, Node** second){
    Node* slow=head;
    Node* fast=head->next;
    if (slow==NULL||fast==NULL) {
        *first=head;
        *second=NULL;
        return;
    }
    else{
        while (fast!=NULL) {
            fast=fast->next;
            if (fast!=NULL) {
                fast=fast->next;
                slow=slow->next;
            }
        }
        *first=head;
        *second=slow->next;
        slow->next=NULL;
    }
}

void removeDuplicates(Node* head){
    Node* current=head;
    while (current->next!=NULL) {
        if (current->data==current->next->data) {
            Node* nextNext=current->next->next;
            free(current->next);
            current->next=nextNext;
        }
        else{
            current=current->next;
        }
    }
}

void moveNode(Node** sourceRef, Node** destRef){
    
    Push(destRef, pop(sourceRef));
}

void alternatingSplit(Node* source, Node** aRef, Node** bRef){
    //assert(source!=NULL);
    Node* a=NULL;
    Node* b=NULL;
    Node* current=source;
    while (current!=NULL) {
        moveNode(&current, &a);
        if (current!=NULL) {
            moveNode(&current, &b);
        }
    }
    *aRef=a;
    *bRef=b;
}

Node* shuffleMerge(Node* a, Node* b){
    Node dummy;
    Node* tail=&dummy;
    dummy.next=NULL;
    while (1) {
        if (a==NULL) {
            tail->next=b;
            break;
        }
        else if (b==NULL){
            tail->next=a;
            break;
        }
        else{
            moveNode(&a, &(tail->next));
            tail=tail->next;
            moveNode(&b, &(tail->next));
            tail=tail->next;
        }
    }
    return dummy.next;
}

Node* shuffleMergeRecursive(Node* a, Node* b){
    Node *result, *recur;
    if (a==NULL) {
        return b;
    }
    else if (b==NULL) {
        return a;
    }
    else{
        recur=shuffleMergeRecursive(a->next, b->next);
        result=a;
        a->next=b;
        b->next=recur;
        return result;
    }
}

Node* sortedMerge(Node* a, Node*b){
    Node* result;
    Node** lastPtrRef=&result;
    while (1) {
        if (a==NULL) {
            *lastPtrRef=b;
            break;
        }
        else if(b==NULL){
            *lastPtrRef=a;
            break;
        }
        if (a->data<=b->data) {
            moveNode(&a, lastPtrRef);
        }
        else{
            moveNode(&b, lastPtrRef);
        }
        lastPtrRef=&((*lastPtrRef)->next);
    }
    return result;
}

Node* sortedMergeRecursive(Node* a, Node* b){
    Node *result=NULL;
    if (a==NULL) {
        return b;
    }
    if (b==NULL) {
        return a;
    }
    else{
        if (a->data <= b->data) {
            result=a;
            result->next=shuffleMergeRecursive(a->next, b);
        }
        else{
            result=b;
            result->next=shuffleMerge(a, b->next);
        }
        return result;
    }
    
}

void mergeSort(Node** headRef){
    Node* head=*headRef;
    Node* first;
    Node* second;
    if (head==NULL||head->next==NULL) {
        return;
    }
    split(head, &first, &second);
    mergeSort(&first);
    mergeSort(&second);
    *headRef = sortedMerge(first, second);
}

Node* sortedIntersect(Node* a, Node* b){
    Node* result = NULL;
    Node** lastPtrRef = &result;
    while (a!=NULL && b!=NULL) {
        if (a->data == b->data) {     
            Push(lastPtrRef, a->data);
            lastPtrRef = &((*lastPtrRef)->next);
            a=a->next;
            b=b->next; }
        else if (a->data < b->data) {
            a=a->next;
        } else {
            b=b->next;
        }
    }
    return(result);
}

void reverse(Node** headRef){
    Node* current=*headRef;
    Node* result=NULL;
    while (current!=NULL) {
        moveNode(&current, &result);
    }
    *headRef=result;
}

void reverseV2(Node** headRef){
    Node* current=*headRef;
    Node* result=NULL;
    Node* next=NULL;
    while (current!=NULL) {
        next=current->next;
        current->next=result;
        result=current;
        current=next;
    }
    *headRef=result;
}

void reverseV3(Node** headRef){
    Node* middle=*headRef;
    Node* front= middle->next;
    Node* back=NULL;
    if (*headRef!=NULL) {
        while (1) {
            middle->next=back;
            if (front==NULL) {
                break;
            }
            
            back=middle;
            middle=front;
            front=front->next;
        }
        *headRef=middle;
    }
    
}

void recursiveReverse(Node** headRef){
    Node* first=*headRef;
    Node* rest=first->next;
    if (rest==NULL) {
        return;
    }
    recursiveReverse(&rest);
    first->next->next=first;
    first->next=NULL;
    *headRef=rest;
}

int main(int argc, const char * argv[])
{
    
    //printList(appendNode(&(BuildWithLocalRef()), 2)); //doesn't work? &(2376ut) doesn't work not a lvalue
    Node* head=BuildOneTwoThree();
    appendNodeWithPush(&head, 4);
    appendNode(&head, 4);
    appendNode(&head, 4);
    Node* test5=BuildWithLocalRef();
    Push(&test5, 6);
    insertNth(&test5, 4, 3);
    //printList(test5);
    insertSort(&test5);
    append(&test5, &head);
    //printList(test5);
    Node *first=NULL,*second=NULL;
    //pop(&test5);
    //split(test5, &first, &second);
    //printList(first);
    //printList(second);
    //removeDuplicates(second);
    //printList(first);
    //printList(second);
    //moveNode(&first, &second);
    //printList(first);
    //printList(second);
    alternatingSplit(test5, &first, &second);
    //printList(first);
    //printList(second);
    //Node* test=shuffleMergeRecursive(first, second);
    //printList(test);
    Node* test1=BuildOneTwoThree();
    Node* test2=BuildOneTwoThree();
    pop(&test2);
    appendNode(&test2, 7);;
    appendNode(&test1, 5);
    //printList(test1);
    //printList(test2);
    append(&test1, &test2);
    //printList(test1);
    mergeSort(&test1);
    //printList(test1);
    Node* t4=BuildOneTwoThree();
    Node* t5=BuildOneTwoThree();
    appendNode(&t5, 6);
    appendNode(&t4, 6);
    appendNode(&t4, 7);
    appendNode(&t5, 8);
    Push(&t5, 0);
    Push(&(t5->next), 1);
    //printList(t5);
    //printList(t4);
    
    //printList(sortedIntersect(t4, t5));
    recursiveReverse(&t5);
    printList(t5);
    return 0;
}
;

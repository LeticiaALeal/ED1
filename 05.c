#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

typedef struct _doubly_node {
    int val;
    struct _doubly_node *prev;
    struct _doubly_node *next;
} DoublyNode, Node;

typedef struct _doubly_linked_list {
    Node *begin;
    Node *end;
    size_t size;
} DoublyLinkedList, List;

Node *Node_create(int val) {
    Node *node = (Node*) calloc(1, sizeof(Node));
    node->prev = NULL;
    node->next = NULL;
    node->val = val;

    return node;
}

List *List_create() {
    List *L = (List*) calloc(1, sizeof(List));
    L->begin = NULL;
    L->end = NULL;
    L->size = 0;

    return L;
}


void List_destroy(List **L_ref) {
    List *L = *L_ref;

    Node *p = L->begin;
    Node *aux = NULL;

    while (p != NULL) {
        aux = p;
        p = p->next;
        free(aux);
    }
    free(L);

    *L_ref = NULL;
}

bool List_is_empty(const List *L) {
    return L->size == 0;
}

void List_add_first(List *L, int val) {
    Node *p = Node_create(val);
    p->next = L->begin;

    if (List_is_empty(L)) {
        L->end = p;
    }
    else {
        L->begin->prev = p;
    }

    L->begin = p;
    L->size++;
}

void List_add_last(List *L, int val) {
    Node *p = Node_create(val);
    p->prev = L->end;

    if (List_is_empty(L)) {
        L->begin = p;
    }
    else {
        L->end->next = p;
    }

    L->end = p;
    L->size++;
}

void print(const List *L) {
    Node *p = L->begin;
    Node *q = L->end;

    printf("Size: %lu\n", L->size);
    printf("L -> begin -> ");

    while (p != NULL) {
        printf("%d -> ", p->val);
        p = p->next;
    }
    printf("NULL\n");

    // IMPRESSÃO INVERTIDA
    printf("L -> end -> ");

    while (q != NULL) {
        printf("%d -> ", q->val);
        q = q->prev;
    }
    printf("NULL\n");

    puts("");
}

void add_at(List *L, int index, int val) {
int size = L->size;
if(index > -2 && index < size){

    if(index == 0 && !List_is_empty(L)){
            List_add_first(L, val);
    }

    else if(index == -1){
            List_add_last(L, val);
    }

    else if (!List_is_empty(L)){
        Node *p = Node_create(val);
        Node *q = L->begin->next;

        for (int i = 1; i < index; i++) {
            q = q->next;
            }

        q->prev->next = p;
        p->next = q;
        p->prev = q->prev;
        q->prev = p;

        L->size++;
    }
}
}

void remove_at(List *L, int index) {
int size = L->size;
    if (!List_is_empty(L) && index > -2 && index < size) {

        Node *p = L->begin;

        //Remoção no final da lista
        if (index == -1){
            while(p != L->end){
                p = p->next;
            }

            L->end = p->prev;
            L->end->next = NULL;
        }

        //Lista só tem um elemento ou foi informado o primeiro elemento
        else if(index == 0){
            L->begin = p->next;

            // a lista possui apenas um único elemento
            if (L->end == p) {
                L->end = NULL;
            }
            // a lista possui mais de um elemento
            else {
                L->begin->prev = NULL;
            }

        }

        else{

            //Caminhada até o índice informado
            for (int i = 0; i != index; i++) {
                p = p->next;
            }

            //Foi informado o último índice
            if (L->end == p) {
                L->end = p->prev;
                L->end->next = NULL;
            }

            //Índice informado está no meio da lista
            else {
                p->prev->next = p->next;
                p->next->prev = p->prev;
            }

        }

        free(p);
        p = NULL;
        L->size--;

    }
}

void invert(List *L ){
    Node *p = L->begin;
    L->begin = L->end;
    L->end = p;
    int count = 0;

    while(count < L->size){
            if(count < L->size-1){
                p = p->next;
                p->prev->next = p->prev->prev;
                p->prev->prev = p;
            }
            else{
                p->next = p->prev;
                p->prev = NULL;
        }
        count++;
    }

}

int main() {
    List *L = List_create();
    char comando[64];

    scanf ("%s",comando);
    while(strcmp(comando, "stop") != 0 ){
        int index, val;
        if(strcmp(comando,"add_at") == 0) {
            scanf ("%d %d", &index, &val);
            add_at(L, index, val);
            }

            else if(strcmp(comando,"remove_at") == 0){
                scanf ("%d", &index);
                remove_at(L, index);
            }

            else if(strcmp(comando,"print") == 0){
                print(L);
            }

            else if(strcmp(comando,"invert") == 0){
                invert(L);
            }
            scanf ("%s" , comando);
    }

    List_destroy(&L);

    return 0;
}

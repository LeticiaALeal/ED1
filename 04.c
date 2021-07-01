#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

typedef struct _snode {
    int val;
    struct _snode *next;
} SNode;

typedef struct _linked_list {
    SNode *begin;
    SNode *end;
    size_t size;
} LinkedList;


SNode *SNode_create(int val) {
    SNode *snode = (SNode*) calloc(1, sizeof(SNode));
    snode->val = val;
    snode->next = NULL;

    return snode;
}

LinkedList *LinkedList_create() {
    LinkedList *L = (LinkedList *) calloc(1, sizeof(LinkedList));
    L->begin = NULL;
    L->end = NULL;
    L->size = 0;

    return L;
}

void LinkedList_destroy(LinkedList **L_ref) {
    LinkedList *L = *L_ref;

    SNode *p = L->begin;
    SNode *aux = NULL;

    while (p != NULL) {
        aux = p;
        p = p->next;
        free(aux);
    }
    free(L);

    *L_ref = NULL;
}


bool LinkedList_is_empty(const LinkedList *L) {
    return L->size == 0;
}

void LinkedList_add_first(LinkedList *L, int val) {
    SNode *p = SNode_create(val);
    p->next = L->begin;
    L->begin = p;
    L->size++;
}

void LinkedList_add_last(LinkedList *L, int val) {
    SNode *q = SNode_create(val);

    // se a lista estiver vazia
    if (LinkedList_is_empty(L)) {
        L->begin = q;
        L->end = q;
    }
    else {
        L->end->next = q;
        L->end = L->end->next;
    }

    L->size++;
}

void print(const LinkedList *L) {
    SNode *p = L->begin;

    printf("L -> ");

    // enquanto p não chegou ao fim da lista, isto é,
    // enquanto p estiver apontando para um nó da lista
    while (p != NULL) {
        printf("%d -> ", p->val);
        p = p->next;
    }
    printf("NULL\n");

    if (L->end == NULL) {
        printf("L -> end -> NULL\n");
    }
    else {
        printf("L -> end -> %d\n", L->end->val);
    }

    printf("Size: %lu\n", L->size);
    puts("");
}

void remove_at(LinkedList *L, int index) {
int size = L->size;
    if (!LinkedList_is_empty(L) && index > -2 && index < size) {

        SNode *prev = NULL;
        SNode *pos = L->begin;

        if (index == -1){
            while(pos != L->end){
                prev = pos;
                pos = pos->next;
            }

            L->end = prev;
            L->end->next = NULL;
        }

        else {
            for (int i = 0; i != index; i++) {
                prev = pos;
                pos = pos->next;
            }

            if (L->end == pos) {
                L->end = prev;
                L->end->next = NULL;
            }
            if (L->begin == pos) {
                L->begin = L->begin->next;
            }
            else {
                prev->next = pos->next;
            }
        }

        free(pos);
        L->size--;
    }
}

void add_at(LinkedList *L, int index, int val) {
int size = L->size;
if(index > -2 && index < size){

    if(index == 0 && !LinkedList_is_empty(L)){
            LinkedList_add_first(L, val);
    }

    else if(index == -1){
            LinkedList_add_last(L, val);
    }

    else if (!LinkedList_is_empty(L)){
        SNode *prev = NULL;
        SNode *pos = L->begin;
        SNode *q = SNode_create(val);

        for (int i = 0; i != index; i++) {
            prev = pos;
            pos = pos->next;
            }

        prev->next = q;
        q->next = pos;

        L->size++;
    }
}

}

void invert(LinkedList *L ){
    SNode *prev = NULL;
    SNode *current = L->begin;
    SNode *pos = NULL;

    L->begin = L->end;
    L->end = current;

    while(current != NULL){
        pos = current->next;
        current->next = prev;
        prev = current;
        current = pos;
    }
}


int main() {
    LinkedList *L = LinkedList_create();
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

    LinkedList_destroy(&L);

    return 0;
}

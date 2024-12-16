#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct Node* NodePointer;
typedef struct Node {
    NodePointer previous;
    int data;
    NodePointer next;
} Node;

void pushBack(int n, NodePointer* first, NodePointer* last);
void pushFront(int n, NodePointer* first, NodePointer* last);
NodePointer popBack(NodePointer* last);
NodePointer popFront(NodePointer* first);
void printLinkedList(NodePointer first);
void freeLinkedList(NodePointer first);
void testLinkedList();

typedef struct treeNode* treeNodePointer;
typedef struct treeNode {
    treeNodePointer parent;
    int data;
    treeNodePointer leftChild, rightChild;
} treeNode;

void maxHeapPush(int n, treeNodePointer* first, int* size);
int maxHeapPop(treeNodePointer* first, int* size);
void printHeap(treeNodePointer first, int size);
void freeMaxHeap(treeNodePointer first);
void testHeap();

void quickSort(int array[], int s, int e);
int partition(int array[], int s, int e);
void swap(int array[], int i, int j);
void printArray(int a[], int n);
void testSort();

int main() {
    testLinkedList();
    testSort();
    testHeap();
    return 0;
}

/*
연결 리스트 구현
*/

void pushBack(int n, NodePointer* first, NodePointer* last) {
    NodePointer tmp = (NodePointer)malloc(sizeof(Node));
    tmp->previous = NULL;
    tmp->data = n;
    tmp->next = NULL;

    if (*first == NULL) *first = tmp;
    else {
        (*last)->next = tmp;
        tmp->previous = *last;
    }
    *last = tmp;
}

void pushFront(int n, NodePointer* first, NodePointer* last) {
    NodePointer tmp = (NodePointer)malloc(sizeof(Node));
    tmp->previous = NULL;
    tmp->data = n;
    tmp->next = NULL;

    if (*first == NULL) *last = tmp;
    else {
        (*first)->previous = tmp;
        tmp->next = *first;
    }
    *first = tmp;
}

NodePointer popBack(NodePointer* last) {
    if (*last == NULL) return NULL;

    NodePointer tmp = *last;
    *last = (*last)->previous;

    if (*last != NULL) (*last)->next = NULL;

    return tmp;
}

NodePointer popFront(NodePointer* first) {
    if (*first == NULL) return NULL;

    NodePointer tmp = *first;
    *first = (*first)->next;

    if (*first != NULL) (*first)->previous = NULL;

    return tmp;
}

void printLinkedList(NodePointer first) {
    for (NodePointer ptr = first; ptr != NULL; ptr = ptr->next) {
        printf("%d ", ptr->data);
    }
    printf("\n");
}

void freeLinkedList(NodePointer first) {
    if (first != NULL) {
        freeLinkedList(first->next);
        free(first);
    }
}

void testLinkedList() {
    NodePointer first = NULL;
    NodePointer last = NULL;

    printf("test linked list\n");

    pushBack(3, &first, &last);
    pushBack(4, &first, &last);
    pushBack(5, &first, &last);
    pushFront(1, &first, &last);

    printLinkedList(first);

    printf("pop back :  %d\n", popBack(&last)->data);
    printf("pop back :  %d\n", popBack(&last)->data);
    printf("pop front :  %d\n", popFront(&first)->data);

    printLinkedList(first);

    freeLinkedList(first);
}

void maxHeapPush(int n, treeNodePointer* first, int* size) {
    treeNodePointer tmp = (treeNodePointer)malloc(sizeof(treeNode));
    tmp->data = n;
    tmp->parent = NULL;
    tmp->leftChild = NULL;
    tmp->rightChild = NULL;

    if (*first == NULL) *first = tmp;
    else if ((*first)->data < n) {
        tmp->leftChild = *first;
        (*first)->parent = tmp;
        (*first) = tmp;
    } else {
        treeNodePointer ptr = *first;
        while (1) {
            if (ptr->leftChild == NULL) {
                ptr->leftChild = tmp;
                tmp->parent = ptr;
                break; 
            } else if (ptr->rightChild == NULL) {
                ptr->rightChild = tmp;
                tmp->parent = ptr;
                break;
            } else if (ptr->leftChild->data < n) {
                tmp->parent = ptr;
                tmp->leftChild = ptr->leftChild;
                tmp->leftChild->parent = tmp;
                ptr->leftChild = tmp;
                break;
            } else if (ptr->rightChild->data < n) {
                tmp->parent = ptr;
                tmp->leftChild = ptr->rightChild;
                tmp->leftChild->parent = tmp;
                ptr->rightChild = tmp;
                break;
            } else if (ptr->leftChild->data < ptr->rightChild->data) ptr = ptr->leftChild;
            else ptr = ptr->rightChild;
        }
    }

    (*size)++;
}

int maxHeapPop(treeNodePointer* first, int* size) {
    if (*first == NULL) return NULL;

    treeNodePointer ptr = *first;
    int tmp = ptr->data;
    while (1) {
        if (ptr->leftChild != NULL && ptr->rightChild != NULL) {
            if (ptr->leftChild->data > ptr->rightChild->data) {
                ptr->data = ptr->leftChild->data;
                ptr = ptr->leftChild;
            } else {
                ptr->data = ptr->rightChild->data;
                ptr = ptr->rightChild;
            }
        } else if (ptr->leftChild != NULL) {
            ptr->data = ptr->leftChild->data;
            ptr = ptr->leftChild;
        } else if (ptr->rightChild != NULL) {
            ptr->data = ptr->rightChild->data;
            ptr = ptr->rightChild;
        } else {
            if (ptr == ptr->parent->leftChild) ptr->parent->leftChild = NULL;
            else ptr->parent->rightChild = NULL;
            free(ptr);
            break;
        }
    }

    (*size)--;

    return tmp;
}

void printHeap(treeNodePointer ptr, int size) {
    NodePointer first = NULL;
    NodePointer last = NULL;

    int queuesize = (int)pow(2,size);
    treeNodePointer queue[queuesize];
    queue[0] = ptr;

    int s = 0, e;
    while (s < size) {
        treeNodePointer node = queue[s++];

        if (node == NULL) {
            queue[2*s-1] = NULL;
            queue[2*s] = NULL;
        } else {
            if (node->leftChild != NULL) queue[2*s-1] = node->leftChild;
            else queue[2*s-1] = NULL;

            if (node->rightChild != NULL) queue[2*s] = node->rightChild;
            else queue[2*s] = NULL;
        }
        e = 2*s;
    }

    for (int i = 0; i < e; i++) {
        if (queue[i] == NULL) printf("-1 ");
        else printf("%d ", queue[i]->data);
    }
    printf("\n");
}

void freeMaxHeap(treeNodePointer first) {
    if (first == NULL) {
        freeMaxHeap(first->leftChild);
        freeMaxHeap(first->rightChild);
        free(first);
    }
}

void testHeap() {
    treeNodePointer first = NULL;
    int size = 0;

    printf("test heap\n");

    maxHeapPush(20, &first, &size);
    maxHeapPush(10, &first, &size);
    maxHeapPush(3, &first, &size);
    maxHeapPush(6, &first, &size);

    printHeap(first, size);

    printf("max heap pop : %d\n", maxHeapPop(&first, &size));
    printf("max heap pop : %d\n", maxHeapPop(&first, &size));
    printf("max heap pop : %d\n", maxHeapPop(&first, &size));

    printHeap(first, size);

    printf("%d\n", first->data);

    freeMaxHeap(first);

    printf("%d\n", first->data);

    if (first->leftChild == NULL) printf("true\n");
    else printf("false\n");

    if (first->rightChild == NULL) printf("true\n");
    else printf("false\n");
}


/*
퀵정렬 알고리즘
*/

void quickSort(int array[], int s, int e) {
    if (s < e) {
        int pivotIndex = partition(array, s, e);

        quickSort(array, s, pivotIndex - 1);
        quickSort(array, pivotIndex + 1, e);
    }
}

int partition(int array[], int s, int e) {
    int pivot = array[e];
    int i = s;

    for (int j = s; j < e; j++) {
        if (array[j] < pivot) { 
            swap(array, i, j);
            i++;
        }
    }

    swap(array, i, e);

    return i;
}

void swap(int array[], int i, int j) {
    int tmp = array[i];
    array[i] = array[j];
    array[j] =tmp;
}

void printArray(int a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void testSort() {
    int array[] = { 4, 3, 6, 1, 2, 8, -2, 7, 0, -4, 0};
    int n = sizeof(array) / sizeof(array[0]);

    printf("test sort\n");

    printArray(array, n);
    quickSort(array, 0, n-1);
    printArray(array, n);
}
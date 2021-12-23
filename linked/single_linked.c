#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct Node {
    // 数据
    ElemType data;
    // 下一个节点
    struct Node *next;
} List, *LinkedList;

// 定义链表
// typedef struct Node *LinkedList; 

/**
 * 构造有头单链表
*/
LinkedList create() {
    LinkedList q = malloc(sizeof(LinkedList));
    q->data = NULL;
    q->next = NULL;
    return q;
}

/**
 * 头插法
*/
void headInsert(LinkedList linkedList, ElemType data) {
    LinkedList q = malloc(sizeof(LinkedList));
    q->data = data;
    q->next = linkedList->next;
    linkedList->next = q;
}

/**
 * 尾插法
*/
void tailInsert(LinkedList linkedList, ElemType data) {
    LinkedList q = malloc(sizeof(LinkedList));
    q->data = data;
    q->next = NULL;
    LinkedList p = linkedList;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = q;
}

/**
 * 遍历
 */
void traverse(LinkedList linkedList) {
    LinkedList q = linkedList->next;
    while (q != NULL) {
        printf("%d,", q->data);
        q = q->next;
    }
}

/**
 * 删除某个元素
*/
void delete(LinkedList linkedList, ElemType data) {
    LinkedList q = linkedList;
    while (q->next != NULL && q->next->data != data) {
        q = q->next;
    }
    if (q != NULL) {
        q->next = q->next->next;
        free(q->next);
    }
}


void main() {
    LinkedList linkedList = create();
    for (int i = 0; i < 10; i++)
    {
        tailInsert(linkedList, i);
        // headInsert(linkedList, i);
    }
    printf("删除前\n");
    traverse(linkedList);
    delete(linkedList, 2);
    printf("\n删除后\n");
    traverse(linkedList);

}
#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

struct Node {
    // 数据
    ElemType data;
    // 下一个节点
    struct Node *next;
} List;

// 定义链表
typedef struct Node *LinkedList;

/**
 * 构造有头单循环链表
*/
struct Node* create() {
    struct Node *q = (struct Node*)malloc(sizeof(struct Node));
    q->data = NULL;
    q->next = q;
    return q;
}

/**
 * 头插法
*/
void headInsert(struct Node *h, ElemType data) {
    struct Node *p = (struct Node*)malloc(sizeof(struct Node));
    p->data = data;
    p->next = h->next;
    h->next = p;
}

/**
 * 尾插法
*/
void tailInsert(struct Node *h, ElemType data) {
    struct Node *q = h;
    struct Node *p = (struct Node*)malloc(sizeof(struct Node));
    p->data = data;
    p->next = h;
    while (q->next != h) {
        q = q->next;
    }
    q->next = p;
}

/**
 * 单循环链表遍历
 */
void traverse(struct Node *head) {
    struct Node *q = head->next;
    while (q != head) {
        printf("%d,", q->data);
        q = q->next;
    }
}

/**
 * 删除某个元素
*/
void delete(struct Node *h, ElemType data) {
    struct Node *q = h;
    while (q->next != h && q->next->data != data) {
        q = q->next;
    }
    struct Node *p = q->next;
    q->next = q->next->next;
    free(p);
}

/**
 * 倒置
*/
void reversal(struct Node *h) {
    struct Node *q = h->next;
    h->next = h;

    while (q != h) {
        struct Node *p = q->next;
        q->next = h->next;
        h->next = q;
        q = p;
    }
}

void main() {
    struct Node *linkedList = create();
    // headInsert(linkedList, 1);
    // headInsert(linkedList, 2);
    // headInsert(linkedList, 3);
    tailInsert(linkedList, 1);
    tailInsert(linkedList, 2);
    tailInsert(linkedList, 3);
    tailInsert(linkedList, 4);
    tailInsert(linkedList, 5);
    printf("删除前\n");
    traverse(linkedList);
    // delete(linkedList, 3);
    // printf("\n删除后\n");
    reversal(linkedList);
    printf("\n倒置后\n");
    traverse(linkedList);
}
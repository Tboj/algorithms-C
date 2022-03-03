#include <stdio.h>
#include <stdlib.h>

void display(int a[], int size) {
    for(int i = 0; i < size; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void direct_insertion_sort(int a[], int size) {
    for(int i = 1; i < size; i++) {
        int temp = a[i]; // 把准备比较的元素先放到临时元素
        int j = i - 1; // 比较的是i的前一位
        for (int j = i - 1; j >= 0 && temp < a[j]; j--) {
            a[j + 1] = a[j]; // temp还是比a[j]小，后移一位
            j--; // 再向前取一个元素来比较
        }
        a[j + 1] = temp; // 遇到不比temp小了或者是前面没有元素了，在后面插入
        display(a, size);
    }
}

void main() {
    if (5) {
        printf("sdfsdf");
    }
}
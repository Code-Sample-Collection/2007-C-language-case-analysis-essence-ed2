#include <stdio.h>
#include <conio.h> // _getch
#include <stdlib.h> // system
void clrscr() { system("cls"); }
void quit() { printf("\n\nPress any key to quit...\n"); _getch(); exit(0); }


void rest(int a[], int n) {
    int i, low, high, t;

    for (i = 0, low = 0, high = n - 1; i <= high; ) {
        if (a[i] > 0) {
            /*a[i]与a[high]交换，随之high减1*/
            t = a[i];
            a[i] = a[high];
            a[high] = t;
            high--;
        } else if (a[i] == 0) {
            i++; /* 掠过该元素 */
        } else {
            /* a[i]与a[low]交换，随之low增1, i增1 */
            t = a[i];
            a[i] = a[low];
            a[low] = t;
            low++;
            i++;
        } // if-set
    } // for
} // rest(int a[], int n)

int main() {
    int arr[] = { 8,4,0, -1,6,0, -5 };
    int i, arr_len = sizeof(arr) / sizeof(arr[0]);

    clrscr();
    printf("\n The arry before rest is:\n");
    for (i = 0; i < arr_len; i++) {
        printf("%4d", arr[i]);
    }
    rest(arr, arr_len);
    printf("\n The arry after rest is:\n");
    for (i = 0; i < arr_len; i++) {
        printf("%4d", arr[i]);
    }

    quit();
}
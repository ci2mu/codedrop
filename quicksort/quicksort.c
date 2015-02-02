// Quick sort of an array; C implementation
//
// Algorithm: partition the array by a pivot element (here we use the middle
// element), and do quick sort on sub-arrays recursively. In each quick sort,
// the elements smaller than pivot are moved to the left of pivot, and the
// elements larger than pivot are moved to the right of pivot. Elements equal
// to pivot are left where they are.
//
// Running time complexity: average O(Nlog(N)) if initial array is randomly
// shufffled; worst case O(N^2) if the initial array is almost sorted.

#include <stdio.h>
#include <stdlib.h>

void quick_sort(int arr[], int left, int right) {

    int i = left, j = right;
    int tmp;
    int pivot = arr[(left + right) / 2];

    while (1) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i <= j) {
            //
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
        else break;
    };

    // Specify recursive condition.
    // For base cases where left==right, no further quick_sort() is called thus
    // recursion ends.
    if (left < j)
        quick_sort(arr, left, j);
    if (i < right)
        quick_sort(arr, i, right);
}

int main() {
    int a[5]={4, 5, 1, 3, 8};
    quick_sort(a, 0, 4);
    int ii=0;
    for(; ii<5; ii++) printf("%d", a[ii]);
    return 1;
}

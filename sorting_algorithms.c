#include <stdio.h>
#define NMAX 10

void swap(int *x, int *y);
void bubble_sort(int *a);
void merge(int *b, int left, int mid, int right);
void merge_sort(int *b, int left, int right);
void heap_sort(int *c);
void heapify(int *c, int n, int i);
void quick_sort(int *d, int left, int right);
void output(int *a, int *b, int *c);

int main() {
    int data[NMAX];
    int data_bs[NMAX], data_ms[NMAX], data_hs[NMAX], data_qs[NMAX];
    for (int *p = data; p - data < NMAX; ++p) {
        scanf("%d", p);
    }

    for (int i = 0; i < NMAX; ++i) {
        data_bs[i] = data[i];
        data_ms[i] = data[i];
        data_hs[i] = data[i];
        data_qs[i] = data[i];
    }

    bubble_sort(data_bs);
    merge_sort(data_ms, 0, NMAX - 1);
    heap_sort(data_hs);
    quick_sort(data_qs, 0, NMAX - 1);
    output(data_bs, data_ms, data_hs);
}

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void bubble_sort(int *a) {
    for (int i = 0; i < NMAX - 1; ++i) {
        for (int j = 0; j < NMAX - i - 1; ++j) {
            if (a[j] > a[j + 1]) {
                swap(&a[j], &a[j + 1]);
            }
        }
    }
}

void merge_sort(int *b, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        merge_sort(b, left, mid);
        merge_sort(b, mid + 1, right);

        merge(b, left, mid, right);
    }
}

void merge(int *b, int left, int mid, int right) {
    int i, j, k;
    int n_left = mid - left + 1;
    int n_right = right - mid;

    int left_arr[NMAX], right_arr[NMAX];

    for (i = 0; i < n_left; ++i) {
        left_arr[i] = b[left + i];
    }

    for (j = 0; j < n_right; ++j) {
        right_arr[j] = b[mid + j + 1];
    }

    i = 0;
    j = 0;
    k = left;

    while (i < n_left && j < n_right) {
        if (left_arr[i] <= right_arr[j]) {
            b[k] = left_arr[i];
            ++i;
        } else {
            b[k] = right_arr[j];
            ++j;
        }
        ++k;
    }

    while (i < n_left) {
        b[k] = left_arr[i];
        ++i;
        ++k;
    }

    while (j < n_right) {
        b[k] = right_arr[j];
        ++j;
        ++k;
    }
}

void heap_sort(int *c) {
    for (int i = NMAX / 2 - 1; i >= 0; --i) {
        heapify(c, NMAX, i);
    }

    for (int i = NMAX - 1; i >= 0; --i) {
        swap(&c[0], &c[i]);

        heapify(c, i, 0);
    }
}

void heapify(int *c, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && c[left] > c[largest]) {
        largest = left;
    }

    if (right < n && c[right] > c[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(&c[i], &c[largest]);

        heapify(c, n, largest);
    }
}

void quick_sort(int *d, int left, int right) {
    if (left >= right) return;

    int p = d[(left + right) / 2];
    int i = left;
    int j = right;

    while (i <= j) {
        while (d[i] <= p) ++i;
        while (d[j] >= p) --j;

        if (i <= j) {
            swap(&d[i], &d[j]);
            ++i;
            --j;
        }
    }

    quick_sort(d, left, i);
    quick_sort(d, j, right);
}

void output(int *a, int *b, int *c) {
    for (int *p = a; p - a < NMAX; ++p) {
        printf("%d ", *p);
    }

    printf("\n");

    for (int *p = b; p - b < NMAX; ++p) {
        printf("%d ", *p);
    }

    printf("\n");

    for (int *p = c; p - c < NMAX; ++p) {
        printf("%d ", *p);
    }

    printf("\n");
}
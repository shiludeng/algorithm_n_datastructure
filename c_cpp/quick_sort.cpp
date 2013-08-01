#include <stdio.h>
#include <string.h>

const int MAX_LEN = 1000;

void swap(int &a, int &b) {
	int t = a;
	a = b;
	b = t;
}

void quick_sort(int *a, int left, int right) {
	if (left >= right)
		return;

	int i = left, j = right + 1;
	int tmp = a[left];

	while (true) {
		do i++; while (i < right && a[i] <= tmp);
		do j--; while (j > left && a[j] >= tmp);
		if (i >= j) break;
		swap(a[i], a[j]);
	}
	a[left] = a[j];
	a[j] = tmp;

	quick_sort(a, left, j - 1);
	quick_sort(a, j + 1, right);
}

int main() {
	int len;
	int *a;

	while (scanf("%d", &len) != -1) {
		a = new int[len];
		for (int i = 0; i < len; i++) {
			scanf("%d", &a[i]);
		}

		quick_sort(a, 0, len - 1);

		for (int i = 0; i < len; i++) {
			printf("%d ", a[i]);
		}
		printf("\n");
	}
}

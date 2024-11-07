#include <stdio.h>

void fifo(int pages[], int n, int capacity) {
    int frames[capacity];
    int page_faults = 0;
    int index = 0;

    for (int i = 0; i < capacity; i++) {
        frames[i] = -1; // Initialize frames to -1 (indicates empty)
    }

    for (int i = 0; i < n; i++) {
        int found = 0;

        // Check if page is already in frames
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        // Page not found, replace the oldest page
        if (!found) {
            frames[index] = pages[i];
            index = (index + 1) % capacity; // FIFO replacement
            page_faults++;
        }
    }

    printf("FIFO - Total Page Faults: %d\n", page_faults);
}

int main() {
    int pages[] = {1, 3, 0, 3, 5, 6};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 3;

    fifo(pages, n, capacity);
    return 0;
}

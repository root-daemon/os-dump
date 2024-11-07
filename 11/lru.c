#include <stdio.h>

void lru(int pages[], int n, int capacity) {
    int frames[capacity];
    int counter[capacity]; // Stores the time when each page was last used
    int page_faults = 0;
    int time = 0;

    for (int i = 0; i < capacity; i++) {
        frames[i] = -1;
        counter[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int found = 0;
        int least_recent = 0;

        // Check if page is already in frames
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                counter[j] = time++; // Update last used time
                break;
            }
        }

        // Page not found, replace the least recently used page
        if (!found) {
            int min = 0;
            for (int k = 1; k < capacity; k++) {
                if (counter[k] < counter[min]) {
                    min = k;
                }
            }

            frames[min] = pages[i];
            counter[min] = time++;
            page_faults++;
        }
    }

    printf("LRU - Total Page Faults: %d\n", page_faults);
}

int main() {
    int pages[] = {1, 3, 0, 3, 5, 6};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 3;

    lru(pages, n, capacity);
    return 0;
}

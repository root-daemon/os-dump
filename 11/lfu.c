#include <stdio.h>

struct Page {
    int number;
    int frequency;
};

void lfu(int pages[], int n, int capacity) {
    struct Page frames[capacity];
    int page_faults = 0;

    for (int i = 0; i < capacity; i++) {
        frames[i].number = -1;
        frames[i].frequency = 0;
    }

    for (int i = 0; i < n; i++) {
        int found = 0;
        int min_freq_index = 0;

        // Check if page is already in frames
        for (int j = 0; j < capacity; j++) {
            if (frames[j].number == pages[i]) {
                frames[j].frequency++;
                found = 1;
                break;
            }
        }

        // Page not found, replace the least frequently used page
        if (!found) {
            for (int k = 1; k < capacity; k++) {
                if (frames[k].frequency < frames[min_freq_index].frequency ||
                    (frames[k].frequency == frames[min_freq_index].frequency && frames[min_freq_index].number != -1)) {
                    min_freq_index = k;
                }
            }

            frames[min_freq_index].number = pages[i];
            frames[min_freq_index].frequency = 1;
            page_faults++;
        }
    }

    printf("LFU - Total Page Faults: %d\n", page_faults);
}

int main() {
    int pages[] = {1, 3, 0, 3, 5, 6};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 3;

    lfu(pages, n, capacity);
    return 0;
}

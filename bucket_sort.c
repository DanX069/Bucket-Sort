#include <stdio.h>
#include <stdlib.h>

#define NUM_BUCKETS 10

// Define a bucket data structure
typedef struct Bucket {
    float *values;
    int count;
} Bucket;

// Define the bucket sort function
void bucket_sort(float *arr, int n) {
    // Initialize the buckets
    Bucket buckets[NUM_BUCKETS];
    for (int i = 0; i < NUM_BUCKETS; i++) {
        buckets[i].values = (float*) malloc(sizeof(float) * n);
        buckets[i].count = 0;
    }

    // Distribute the values into the buckets
    for (int i = 0; i < n; i++) {
        int bucket_idx = arr[i] * NUM_BUCKETS;
        buckets[bucket_idx].values[buckets[bucket_idx].count++] = arr[i];
    }

    // Sort each bucket using insertion sort
    for (int i = 0; i < NUM_BUCKETS; i++) {
        for (int j = 1; j < buckets[i].count; j++) {
            float key = buckets[i].values[j];
            int k = j - 1;
            while (k >= 0 && buckets[i].values[k] > key) {
                buckets[i].values[k + 1] = buckets[i].values[k];
                k--;
            }
            buckets[i].values[k + 1] = key;
        }
    }

    // Concatenate the sorted buckets into the output array
    int idx = 0;
    for (int i = 0; i < NUM_BUCKETS; i++) {
        for (int j = 0; j < buckets[i].count; j++) {
            arr[idx++] = buckets[i].values[j];
        }
        free(buckets[i].values);
    }
}

// Main function to test the bucket sort
int main() {
    int p;
    printf("Enter the size of the array: ");
    scanf("%d", &p);

    float arr[p];
    printf("Enter %d floating point numbers: ", p);
    for (int i = 0; i < p; i++) {
        scanf("%f", &arr[i]);
    }

    bucket_sort(arr, p);

    printf("Sorted array: ");
    for (int i = 0; i < p; i++) {
        printf("%.7f ", arr[i]);
    }
    printf("\n");

    return 0;
}

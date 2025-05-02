#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 10  
int arr[SIZE] = {38, 27, 43, 3, 9, 82, 10, 5, 19, 50};
int sorted_arr[SIZE];  


typedef struct {
    int start;
    int end;
} parameters;


void bubble_sort(int start, int end) {
    for (int i = start; i < end - 1; i++) {
        for (int j = start; j < end - (i - start) - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


void *sort_thread(void *param) {
    parameters *p = (parameters *)param;
    bubble_sort(p->start, p->end);
    pthread_exit(0);
}


void *merge_thread(void *param) {
    int mid = SIZE / 2;
    int i = 0, j = mid, k = 0;

    while (i < mid && j < SIZE) {
        if (arr[i] <= arr[j]) {
            sorted_arr[k++] = arr[i++];
        } else {
            sorted_arr[k++] = arr[j++];
        }
    }

   
    while (i < mid) {
        sorted_arr[k++] = arr[i++];
    }

   
    while (j < SIZE) {
        sorted_arr[k++] = arr[j++];
    }

    pthread_exit(0);
}

int main() {
    pthread_t threads[3];


    parameters *data1 = (parameters *)malloc(sizeof(parameters));
    data1->start = 0;
    data1->end = SIZE / 2;
    pthread_create(&threads[0], NULL, sort_thread, data1);


    parameters *data2 = (parameters *)malloc(sizeof(parameters));
    data2->start = SIZE / 2;
    data2->end = SIZE;
    pthread_create(&threads[1], NULL, sort_thread, data2);

  
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);


    pthread_create(&threads[2], NULL, merge_thread, NULL);
    pthread_join(threads[2], NULL);


    printf("Sorted array: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", sorted_arr[i]);
    }
    printf("\n");

    
    free(data1);
    free(data2);

    return 0;
}

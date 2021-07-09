#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <time.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <pthread.h>


#define NUM_THREADS    10
#define MAX 10000

int numPros;
double timer;

// struct for my threads
struct thread_data {
    int thread_id;
    struct Earthquakes *earthquakes1[10000];
    int size;
};

// struct for data
struct Earthquakes {
    char time[100];
    char latitude[20];
    char longitude[20];
    char depth[20];
    char mag[20];
};

struct thread_data thread_data_array[NUM_THREADS];
struct Earthquakes *earthquakes[MAX];

int read_file(char *fileName) {
//    fprintf(stderr, "Try to open file!\n");
    FILE *file = fopen(fileName, "r");
    const size_t line_size = 2049;
    char *line = malloc(line_size);
    // checking file error
    if (!file) {
        fprintf(stderr, "Unable to open file!\n");
        return -1;
    }
// instrumentaion start
    time_t t;
    t = time(NULL);

    fgets(line, line_size, file);


    fgets(line, line_size, file);
    int index = 0;
    while (fgets(line, line_size, file) && (index < MAX)) {
        // allocate mem for the earthquakes structure
        earthquakes[index] = (struct Earthquakes *) malloc(sizeof(struct Earthquakes));

        char *token;
        // get token from line
        token = strtok(line, ",");
        strcpy(earthquakes[index]->time, token);
        token = strtok(NULL, ",");
        strcpy(earthquakes[index]->latitude, token);
        token = strtok(NULL, ",");
        strcpy(earthquakes[index]->longitude, token);
        token = strtok(NULL, ",");
        strcpy(earthquakes[index]->depth, token);
        token = strtok(NULL, ",");
        strcpy(earthquakes[index]->mag, token);

        index++;
    }
    free(line);
    return 1;
}

// Put the arrays back together after sort
void merge(struct Earthquakes *earth[], int size) {
    struct Earthquakes *temp;
    for (int i = 1; i < size; i++) {
        for (int j = 0; j < size - i; j++) {
            if (strcmp(earth[j]->latitude, earth[j + 1]->latitude) > 0) {
                temp = earth[j];
                earth[j] = earth[j + 1];
                earth[j + 1] = temp;
            }
        }
    }

}

// sort using bubble sort
void *Sort(void *threadarg) {
    int taskid, sum, size;
    char *hello_msg;
    struct thread_data *my_data;
    struct Earthquakes *earth;

    sleep(1);
    my_data = (struct thread_data *) threadarg;
    taskid = my_data->thread_id;
    size = my_data->size;

    //sorting code

    // start timer
    double time_spent = 0.0;
    clock_t begin = clock();

    struct Earthquakes *temp;

    for (int i = 1; i < size; i++) {
        for (int j = 0; j < size - i; j++) {
            if (atof(my_data->earthquakes1[j]->latitude) > atof(my_data->earthquakes1[j + 1]->latitude)) {
                temp = my_data->earthquakes1[j];
                my_data->earthquakes1[j] = my_data->earthquakes1[j + 1];
                my_data->earthquakes1[j + 1] = temp;
            }
        }
    }

    clock_t end = clock();
    time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
    timer = time_spent;
    //end sorting code
    pthread_exit(NULL);
}

void split(int numPros) {
    int j = 0;
    // this is my split
    // data into one array
    if (numPros == 1) {
        for (int k = 0; k < 10000; k++) {
            thread_data_array[0].earthquakes1[k] = earthquakes[k];
        }
    }

    //split data into 2 arrays, 5k data each
    if (numPros == 2) {
        for (int k = 0; k < 5000; k++) {
            thread_data_array[0].earthquakes1[k] = earthquakes[k];
        }
        j = 0;
        for (int k = 5000; k < 10000; k++) {
            thread_data_array[1].earthquakes1[j] = earthquakes[k];
            j++;
        }
    }

    // split data into 4 arrays, 2500 data each
    if (numPros == 4) {
        for (int k = 0; k < 2500; k++) {
            thread_data_array[0].earthquakes1[k] = earthquakes[k];
        }
        j = 0;
        for (int k = 2500; k < 5000; k++) {
            thread_data_array[1].earthquakes1[j] = earthquakes[k];
            j++;
        }
        j = 0;
        for (int k = 5000; k < 7500; k++) {
            thread_data_array[2].earthquakes1[j] = earthquakes[k];
            j++;
        }
        j = 0;
        for (int k = 7500; k < 10000; k++) {
            thread_data_array[3].earthquakes1[j] = earthquakes[k];
            j++;
        }
    }

    // split data into 10 arrays, 1k data each
    if (numPros == 10) {
        for (int k = 0; k < 1000; k++) {
            thread_data_array[0].earthquakes1[k] = earthquakes[k];
        }
        j = 0;
        for (int k = 1000; k < 2000; k++) {
            thread_data_array[1].earthquakes1[j] = earthquakes[k];
            j++;
        }
        j = 0;
        for (int k = 2000; k < 3000; k++) {
            thread_data_array[2].earthquakes1[j] = earthquakes[k];
            j++;
        }
        j = 0;
        for (int k = 3000; k < 4000; k++) {
            thread_data_array[3].earthquakes1[j] = earthquakes[k];
            j++;
        }
        j = 0;
        for (int k = 4000; k < 5000; k++) {
            thread_data_array[4].earthquakes1[j] = earthquakes[k];
            j++;
        }
        j = 0;
        for (int k = 5000; k < 6000; k++) {
            thread_data_array[5].earthquakes1[j] = earthquakes[k];
            j++;
        }
        j = 0;
        for (int k = 6000; k < 7000; k++) {
            thread_data_array[6].earthquakes1[j] = earthquakes[k];
            j++;
        }
        j = 0;
        for (int k = 7000; k < 8000; k++) {
            thread_data_array[7].earthquakes1[j] = earthquakes[k];
            j++;
        }
        j = 0;
        for (int k = 8000; k < 9000; k++) {
            thread_data_array[8].earthquakes1[j] = earthquakes[k];
            j++;
        }
        j = 0;
        for (int k = 9000; k < 10000; k++) {
            thread_data_array[9].earthquakes1[j] = earthquakes[k];
            j++;
        }

    }
}

int main(int argc, char *argv[]) {
    char *earthquake_filename = "./all_month.csv";

    //read csv file
    read_file(earthquake_filename);

    // number of total threads
    pthread_t threads[NUM_THREADS];
    int *taskids[NUM_THREADS];
    int rc, t, j;

    // menu
    printf("Enter number of Threads (1, 2, 4, 10): ");
    scanf("%d", &numPros);
    printf("\nRunning %d Threads:\n",numPros);

    //split the data
    split(numPros);


    // start running data
    for (t = 0; t < numPros; t++) {

        thread_data_array[t].thread_id = t;

        if (numPros == 1) {
            thread_data_array[t].size = 10000;
        }
        if (numPros == 2) {
            thread_data_array[t].size = 5000;
        }
        if (numPros == 4) {
            thread_data_array[t].size = 2500;
        }
        if (numPros == 10) {
            thread_data_array[t].size = 1000;
        }

        //printf("Running thread %d\n", t + 1);
        rc = pthread_create(&threads[t], NULL, Sort, (void *) &thread_data_array[t]);

        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    // check for how long to wait for data to sort
    if (numPros == 1){
        sleep(20);
    }
    if (numPros == 2){
        sleep(10);
    }
    if (numPros == 4){
        sleep(8);
    }
    if (numPros == 10){
        sleep(5);
    }

    // print out time elapsed
    printf("\nTime elapsed is %f seconds\n", timer);

    pthread_exit(NULL);
}
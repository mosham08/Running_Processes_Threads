#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <time.h>

#define MAX 10000

// Struct to hold data for first 5 columns
struct Earthquakes {
    char time[100];
    char latitude[20];
    char longitude[20];
    char depth[20];
    char mag[20];
};
// Create more a main array with all of the data
// also create 10 different arrays to hold more data
struct Earthquakes *earthquakes[MAX];
struct Earthquakes *earthquakes1[10000];
struct Earthquakes *earthquakes2[10000];
struct Earthquakes *earthquakes3[10000];
struct Earthquakes *earthquakes4[10000];
struct Earthquakes *earthquakes5[10000];
struct Earthquakes *earthquakes6[10000];
struct Earthquakes *earthquakes7[10000];
struct Earthquakes *earthquakes8[10000];
struct Earthquakes *earthquakes9[10000];
struct Earthquakes *earthquakes10[10000];


// Read the csv file
int read_file(char *fileName) {
//    fprintf(stderr, "Try to open file!\n");
    FILE *file = fopen(fileName, "r");
    const size_t line_size = 2049;
    // allocate memory for line
    char *line = malloc(line_size);
    // checking file error
    if (!file) {
        fprintf(stderr, "Unable to open file!\n");
        return -1;
    }
// instrumentaion start
    time_t t;
    t = time(NULL);

    // get line
    fgets(line, line_size, file);


    fgets(line, line_size, file);
    int index = 0;

    // move through the csv file and load data into arrays
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
    // free allocated memory
    free(line);
    return 1;
}

void split(int numPros) {

    // Split data into two seprate arrays, 5k data each
    if (numPros == 2) {
        for (int i = 0; i < 5000; ++i) {
            earthquakes1[i] = (struct Earthquakes *) malloc(sizeof(struct Earthquakes));
            earthquakes1[i] = earthquakes[i];
        }

        int j = 0;
        for (int i = 5000; i < 10000; ++i) {
            earthquakes2[j] = (struct Earthquakes *) malloc(sizeof(struct Earthquakes));
            earthquakes2[j] = earthquakes[i];
            j++;
        }
    }

    // Split data into 4 different arrays, 2500 data each one
    if (numPros == 4) {
        for (int i = 0; i < 2500; ++i) {
            earthquakes1[i] = (struct Earthquakes *) malloc(sizeof(struct Earthquakes));
            earthquakes1[i] = earthquakes[i];
        }

        int j = 0;
        for (int i = 2500; i < 5000; ++i) {
            earthquakes2[j] = (struct Earthquakes *) malloc(sizeof(struct Earthquakes));
            earthquakes2[j] = earthquakes[i];
            j++;
        }

        j = 0;
        for (int i = 5000; i < 7500; ++i) {
            earthquakes3[j] = (struct Earthquakes *) malloc(sizeof(struct Earthquakes));
            earthquakes3[j] = earthquakes[i];
            j++;
        }

        j = 0;
        for (int i = 7500; i < 10000; ++i) {
            earthquakes4[j] = (struct Earthquakes *) malloc(sizeof(struct Earthquakes));
            earthquakes4[j] = earthquakes[i];
            j++;
        }
    }

    // Split all the data into 10 arrays, 1k of data each
    if (numPros == 10) {
        for (int i = 0; i < 1000; ++i) {
            earthquakes1[i] = (struct Earthquakes *) malloc(sizeof(struct Earthquakes));
            earthquakes1[i] = earthquakes[i];
        }

        int j = 0;
        for (int i = 1000; i < 2000; ++i) {
            earthquakes2[j] = (struct Earthquakes *) malloc(sizeof(struct Earthquakes));
            earthquakes2[j] = earthquakes[i];
            j++;
        }

        j = 0;
        for (int i = 2000; i < 3000; ++i) {
            earthquakes3[j] = (struct Earthquakes *) malloc(sizeof(struct Earthquakes));
            earthquakes3[j] = earthquakes[i];
            j++;
        }

        j = 0;
        for (int i = 3000; i < 4000; ++i) {
            earthquakes4[j] = (struct Earthquakes *) malloc(sizeof(struct Earthquakes));
            earthquakes4[j] = earthquakes[i];
            j++;
        }

        j = 0;
        for (int i = 4000; i < 5000; ++i) {
            earthquakes5[j] = (struct Earthquakes *) malloc(sizeof(struct Earthquakes));
            earthquakes5[j] = earthquakes[i];
            j++;
        }

        j = 0;
        for (int i = 5000; i < 6000; ++i) {
            earthquakes6[j] = (struct Earthquakes *) malloc(sizeof(struct Earthquakes));
            earthquakes6[j] = earthquakes[i];
            j++;
        }

        j = 0;
        for (int i = 6000; i < 7000; ++i) {
            earthquakes7[j] = (struct Earthquakes *) malloc(sizeof(struct Earthquakes));
            earthquakes7[j] = earthquakes[i];
            j++;
        }

        j = 0;
        for (int i = 7000; i < 8000; ++i) {
            earthquakes8[j] = (struct Earthquakes *) malloc(sizeof(struct Earthquakes));
            earthquakes8[j] = earthquakes[i];
            j++;
        }

        j = 0;
        for (int i = 8000; i < 9000; ++i) {
            earthquakes9[j] = (struct Earthquakes *) malloc(sizeof(struct Earthquakes));
            earthquakes9[j] = earthquakes[i];
            j++;
        }

        j = 0;
        for (int i = 9000; i < 10000; ++i) {
            earthquakes10[j] = (struct Earthquakes *) malloc(sizeof(struct Earthquakes));
            earthquakes10[j] = earthquakes[i];
            j++;
        }
    }
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

// function to print data in arrays
void printEarthquake(struct Earthquakes *earthquakes) {
    printf("%-40s", earthquakes->time);
    printf("%-20s", earthquakes->latitude);
    printf("%-20s", earthquakes->longitude);
    printf("%-12s", earthquakes->depth);
    printf("%-12s\n", earthquakes->mag);
}

// Sort your data, using bubbleSort
void Sort(struct Earthquakes *earth[], char *process, int size) {
    struct Earthquakes *temp;
    for (int i = 1; i < size; i++) {
        for (int j = 0; j < size - i; j++) {
            // Sort by latitude
            if (atof(earth[j]->latitude) > atof(earth[j + 1]->latitude)) {
                temp = earth[j];
                earth[j] = earth[j + 1];
                earth[j + 1] = temp;
            }
        }
    }

}


int main() {
    time_t t;

    char *earthquake_filename = "./all_month.csv";
    // read csv file
    read_file(earthquake_filename);

    // Ask user for number of processes to run
    int numPros;
    printf("Enter number of processes (1, 2, 4, 10): ");
    scanf("%d", &numPros);

    // Split your data by number of processes user requests
    split(numPros);

    printf("\nNumber of Running Processes: %d\n", numPros);
    char wait = "";

    // checks if only one process needs to run
    if (numPros == 1) {
        // start to time your sort
        double time_spent = 0.0;
        clock_t begin = clock();

        Sort(earthquakes, "1 Process", MAX);

        // collect the end of the time
        clock_t end = clock();
        time_spent += (double) (end - begin) / CLOCKS_PER_SEC;
        printf("\n1 Process running time elpased is %f seconds\n", time_spent);

    }

    // checks if only 2 processes need to run
    if (numPros == 2) {
        //start timing
        double time_spent = 0.0;
        clock_t begin = clock();

        int pid = fork();

        // 2 processes
        if (pid == 0) {
            Sort(earthquakes1, "Process 1", 5000);
            printf("\n");
            exit(1);
        } else {
            Sort(earthquakes2, "Process 2", 5000);
        }

        // end timing
        clock_t end = clock();
        time_spent += (double) (end - begin) / CLOCKS_PER_SEC;
        printf("\n2 Process running time elpased is %f seconds\n", time_spent);

        sleep(1);
    }

    // checks if only 4 processes need to run
    if (numPros == 4) {
        //start timing
        double time_spent = 0.0;
        clock_t begin = clock();

        //first two processes
        int pid = fork();

        if (pid == 0) {
            Sort(earthquakes1, "Process 1", 2500);
            printf("\n");
            exit(1);
        } else {
            Sort(earthquakes2, "Process 2", 2500);
        }

        // second two processes
        pid = fork();
        if (pid == 0) {
            Sort(earthquakes3, "Process 3", 2500);
            printf("\n");
            exit(1);
        } else {
            Sort(earthquakes4, "Process 4", 2500);
        }

        // end timing
        clock_t end = clock();
        time_spent += (double) (end - begin) / CLOCKS_PER_SEC;
        printf("\n4 Process running time elpased is %f seconds\n", time_spent);

        sleep(1);
    }
    // checks if only 10 processes need to run
    if (numPros == 10) {
        //start timing
        double time_spent = 0.0;
        clock_t begin = clock();

        // start fork and run 10 different processes
        int pid = fork();

        if (pid == 0) {
            Sort(earthquakes1, "Process 1", 1000);
            printf("\n");
            exit(1);
        } else {
            Sort(earthquakes2, "Process 2", 1000);
        }

        pid = fork();
        if (pid == 0) {
            Sort(earthquakes3, "Process 3", 1000);
            printf("\n");
            exit(1);
        } else {
            Sort(earthquakes4, "Process 4", 1000);
        }

        if (pid == 0) {
            Sort(earthquakes5, "Process 5", 1000);
            printf("\n");
            exit(1);
        } else {
            Sort(earthquakes6, "Process 6", 1000);
        }

        pid = fork();
        if (pid == 0) {
            Sort(earthquakes7, "Process 7", 1000);
            printf("\n");
            exit(1);
        } else {
            Sort(earthquakes8, "Process 8", 1000);
        }

        if (pid == 0) {
            Sort(earthquakes9, "Process 9", 1000);
            printf("\n");
            exit(1);
        } else {
            Sort(earthquakes10, "Process 10", 1000);
        }
        // end timing
        clock_t end = clock();
        time_spent += (double) (end - begin) / CLOCKS_PER_SEC;
        printf("\n10 Process running time elpased is %f seconds\n", time_spent);

        sleep(1);
    }

    // Display a random part of your sorted arrays
//    printf("\nDisplaying random part of sorted array:\n");
//    printf("\n");
//    if (numPros == 1){
//        for (int k = 0; k < 10; ++k) {
//            printEarthquake(earthquakes[k]);
//        }
//    }
//    if (numPros == 2 || numPros == 4 || numPros == 10)
//    {
//        for (int k = 800; k < 810; ++k) {
//            printEarthquake(earthquakes2[k]);
//        }
//    }

    // keeping program running by waiting for user input to end
    printf("\nType 'n' to Exit: ");
    scanf("%s", &wait);
    if (wait == 'n') {
        return 0;
    }

}
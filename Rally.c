#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Rally.h"



/*Adds a driver named "lastname" and who is representing "team" to buffer of length "size".
  Returns 1 if the operation was successful, 0 otherwise.*/

int add_driver(struct driver *buffer, char *lastname, char *team) {
    int i;
    for (i = 0; buffer[i].lastname[0] != '\0'; i++) //Find out the size of buffer
    
    buffer = realloc(buffer, (i + 2) * sizeof(struct driver));
    if (!buffer) return 0;  //if memory allocation failed
    strcpy(buffer[i].lastname, lastname);
    strcpy(buffer[i].team, team);
    buffer[i].time = 0;  //Initially the total time is 0
    buffer[i+1].lastname[0] = 0;
    return 1;
}


void update_time(struct driver *buffer, char *lastname, int time) {
    int flag = 0;
    for (int i = 0; buffer[i].lastname[0] != '\0'; i++) {
        if (!strcmp(buffer[i].lastname, lastname)) {
            buffer[i].time += time;
            flag = 1;
        }
    }
    if (!flag) printf("ERROR: Did not find driver: '%s'\n", lastname);
}

//Helper function for print_results:

int compare (const void* p1, const void* p2) {
    struct driver a = *(struct driver*)p1;
    struct driver b  = *(struct driver*)p2;
    if (a.time < b.time) return -1;
    else if (a.time > b.time) return 1;
    else return 0;
}



void print_results(struct driver *buffer) {
    //First sort the buffer
    int j;
    for (j = 0; buffer[j].lastname[0] != '\0'; j++);    
    qsort(buffer, j, sizeof(struct driver), compare);

    //Then print
    printf("Current results of the race:\n\n");
    for (int i = 0; buffer[i].lastname[0] != '\0'; i++) {
        printf("%s - %s - %dh %dmin %ds\n", buffer[i].lastname, buffer[i].team, buffer[i].time / 3600,
        (buffer[i].time % 3600) / 60, (buffer[i].time % 3600) % 60);
    }
}


int write_results(const char *filename) {

}



int main() {
    
    struct driver *buffer = malloc(sizeof(struct driver));
    buffer->lastname[0] = 0;

    
    add_driver(buffer, "Kankkunen", "Renault");
    update_time(buffer, "Kankkunen", 4325);
    add_driver(buffer, "Räikkönen", "Peugeot");
    update_time(buffer, "Räikkönen", 3333);
    add_driver(buffer, "Svakar Teknolog", "Lada");
    update_time(buffer, "Svakar Teknolog", 3333333);
    print_results(buffer);
    return 1;
}
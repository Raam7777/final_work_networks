#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define MAXCHAR 255

struct info_arrival {
    unsigned int slack;
    unsigned int value_of_packet;
    unsigned int is_cell_occupied; // True or False
};

unsigned int total_dropped = 0;
unsigned int total_arrived = 0;
unsigned int total_transmitted = 0;
unsigned int total_value = 0;


struct queue_template {
    struct info_arrival *buffer;
    int occupied_slots;
    unsigned int queue_capcity;
    int queue_tail;
};

int check_available_place_in_queue(struct queue_template *q) {
    return (q->queue_capcity > q->occupied_slots);
}

int find_the_earliest_packet_to_evacuate(struct queue_template *q) {
    unsigned int min = q->buffer[0].value_of_packet;
    unsigned int min_index = 0;

    for (int i = 1; i < q->queue_capcity; ++i) {
        if (q->buffer[i].value_of_packet < min) {
            min = q->buffer[i].value_of_packet;
            min_index = i;
        }
    }

    return min_index;
}

int update_slack(struct queue_template *q) {
    int start = 0;
    if (q->queue_tail > 0)
        start = q->queue_tail;
    else if (q->queue_tail == 0) {
        start = 1;
    } else { //(q->queue_tail == -1)
        start = 0;
    }

    for (int i = start; i < q->queue_capcity; ++i) {

        q->buffer[i].slack--;

        if (q->buffer[i].slack == 0) {

            // Shift to the right
            for (int i = q->queue_capcity - 2; i >= 0; i--) {
                memcpy(&(q->buffer[i + 1]), &(q->buffer[i]), sizeof(struct info_arrival));
            }
            
            memset(&(q->buffer[start - 1]), '\0', sizeof(struct info_arrival));
            q->occupied_slots--;
            total_dropped++;
            q->queue_tail++;
        }
    }
}


int parse_tuple(char *tuple, struct queue_template *q) {
    char *token;
    char *rest = tuple + 1;
    int raw_data;
    unsigned int part = 0;
    unsigned int num_packets;
    unsigned int slack;         
    unsigned int packet_value;
    unsigned int evacuated_cell;

    struct info_arrival new_arrival_tuple;

    while ((token = strtok_r(rest, ",", &rest))) {
        part += 1;
        raw_data = atoi(token);
        switch (part) {
            case 1:
                num_packets = raw_data;
                total_arrived += num_packets;
                break;
            case 2:
                slack = raw_data;
                break;
            case 3:
                packet_value = raw_data;
                break;
            default:
                printf("finished processing row\n");
        }
    }

    for (int i = 0; i < num_packets; ++i) {
        if (check_available_place_in_queue(q)) {
            // q_tail the first cell which is free from the right
            if (q->queue_tail == -1) {
                q->queue_tail = 0;
            }
            q->buffer[q->queue_tail].slack = slack;
            q->buffer[q->queue_tail].value_of_packet = packet_value;
            q->buffer[q->queue_tail].is_cell_occupied = TRUE;
            q->occupied_slots++;

            if (q->queue_tail >= 0) {
                q->queue_tail--;
                // Import to know:
                // if queue_tail ==-1 it means the queue is full
            }
        } else {
            evacuated_cell = find_the_earliest_packet_to_evacuate(q);
            total_dropped++;

            if (q->queue_tail != -1) {
                q->queue_tail++;
            }

            q->buffer[evacuated_cell].value_of_packet = packet_value;
            q->buffer[evacuated_cell].slack = slack;
            q->buffer[evacuated_cell].is_cell_occupied = TRUE;
        }

    }
}

/* Command is whole */
int parse_command(char *line, struct queue_template *q) {
    int part = 0;
    char *token;
    char *rest = line;


    while ((token = strtok_r(rest, " ", &rest))) {
        parse_tuple(token, q);
        printf("\n");
    }

}


void processing_packet(struct queue_template *q) {
    total_transmitted += 1;
    total_value += (q->buffer[q->queue_capcity - 1].value_of_packet);

    for (int i = q->queue_capcity - 2; i >= 0; i--) {
        memcpy(&(q->buffer[i + 1]), &(q->buffer[i]), sizeof(struct info_arrival));
    }

    q->queue_tail++;
    memset(&(q->buffer[q->queue_tail]), '\0', sizeof(struct info_arrival));

    // final part - free space was created
    q->buffer[q->queue_tail].is_cell_occupied = FALSE;
    q->occupied_slots--;

}

int main(int argc, char **argv) {

    struct queue_template *ptr_queue;
    unsigned char buffer_single_row_from_text_file[MAXCHAR];
    FILE *fd;
    unsigned int len;
    unsigned int q_len;
    unsigned int evacuated_cell;

    if (argc < 1) {
        printf("Error, you should pass a queue length\n");
        exit(1);
    }

    q_len = atoi(argv[1]);
    printf("The Queue length is: %d", q_len);

    ptr_queue = (struct queue_template *) malloc(sizeof(struct queue_template));
    ptr_queue->buffer = (struct info_arrival *) malloc(sizeof(struct info_arrival) * q_len);
    memset(ptr_queue->buffer, '\0', sizeof(struct info_arrival) * q_len);
    ptr_queue->queue_tail = q_len - 1;
    ptr_queue->queue_capcity = q_len;

    fd = fopen("/home/raamb/Desktop/tikshoret_work/Q2/sample_input.txt", "r");

    while (len = fgets(buffer_single_row_from_text_file, MAXCHAR, fd) != NULL) {
        parse_command(buffer_single_row_from_text_file, ptr_queue);
        update_slack(ptr_queue);
        processing_packet(ptr_queue);
        memset(buffer_single_row_from_text_file, '\0', MAXCHAR);
    }

    while (ptr_queue->occupied_slots > 0) {
        update_slack(ptr_queue);
        if(ptr_queue->queue_tail != ptr_queue->queue_capcity - 1 && ptr_queue->buffer[ptr_queue->queue_capcity - 1].slack != 0)
        processing_packet(ptr_queue);
    }

    printf("Total arrived packets %d , Total dropped packets %d , Total transmitted packets %d, Total value packets %d\n", total_arrived, total_dropped, total_transmitted, total_value);


    free(ptr_queue->buffer);
    free(ptr_queue);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#define RED "\033[31m"
#define RESET "\033[0m"
#define SIZE_T_MAX 0xFFFFFFFFU

int main(int argc, char *argv[]) {
    
    FILE *fp;
    size_t index = 0;
    size_t n;
    size_t max_iters; // gives number of filled lines + one last unfilled (or filled) line
    size_t bytes_left_to_read = SIZE_T_MAX;
    size_t bytes_in_each_line = 16;
    size_t i = 0;
    int w_found = 0;
    int n_found = 0;
    int s_found = 0;
    long long w = 16;
    long offset = 0;
    int reference = SEEK_SET;
    int spaces[16] = {49, 46, 43, 39, 36, 33, 30, 26, 23, 20, 17, 13, 10, 7, 4, 0};
    long long no_of_bytes = SIZE_T_MAX;
    char *endptr;
    errno = 0;
    long size = 0;
    int indicate_size = 0;
    int any_bytes_read = 0;
    long group_size = 4;
    // for debug
    // printf("argc = %d, argv = ", argc);
    // for(int i = 0; i < argc; i++) {
    //     printf("%s ",argv[i]);
    // }
    // printf("\n");

    if(argc < 2) {
        char filepath[100];
        printf("You are running a hexdump tool. Pass relative or absolute paths to files to be hexdumped\n");
        printf("Enter the file path (separator: /) here: ");
        scanf("%99s", filepath);
        printf("You entered: %s\n", filepath);

        printf("Enter the number of bytes to read (-1 if all): ");
        if(!scanf("%lld", &no_of_bytes)) {
            printf("Error. Enter a valid number.");
            return 1;
        }

        if(no_of_bytes == 0) {
            printf("Number of bytes should not be zero. Please try again");
            return 1;
        }

        if(no_of_bytes < -1) {
            printf("Number of bytes cannot be less than -1. Please try again");
            return 1;
        }
        
        printf("Enter the offset:\n-- 0 for default\n-- positive to start from beginning\n-- negative to start from the end\nHere: ");
        if(!scanf("%d",&offset)) {
            printf("Error. Enter an integer value for offset.");
            return 1;
        }

        printf("Enter the width (-1 if default of 16): ");
        scanf("%lld",&w);
        if(w < -1 || !w) {
            printf("The width cannot be less than -1 or 0. Please try again");
            return 1;
        }

        printf("Enter 1 if the file size should be indicated, else 0: ");
        if(!scanf("%d",&indicate_size) || indicate_size > 1 || indicate_size < 0) {
            printf("Error: Invalid character. Please enter 0 to ignore or 1 to indicate size");
            return 1;
        }

        if(w == -1) w = 16;
        bytes_in_each_line = (size_t)w;
        if(no_of_bytes == -1) no_of_bytes = SIZE_T_MAX;
        bytes_left_to_read = (size_t)no_of_bytes;

        printf("Enter the group size (-1 for default 4): ");

        if(!scanf("%ld", &group_size) || !group_size || group_size < -1 || group_size > (long)bytes_in_each_line) {
            printf("Entered group size: %ld\n", group_size);
            printf("Error: Group size needs to be either -1 or a natural number less than the width. Please try again");
            return 1;
        } 
        
        if(group_size == -1) group_size = 4;
        fp = fopen(filepath, "rb");
    } else {
        if(argc == 2) {
            w = 16;
            bytes_left_to_read = SIZE_T_MAX;
            bytes_in_each_line = (size_t)w;
        } else {
            for(int i = 0; i < argc; i++) {
                if(strcmp(argv[i], "-n") == 0) {
                    n_found = 1;
                    no_of_bytes = strtoll(argv[i+1], NULL, 0);

                    if(!no_of_bytes) {
                        printf("Number of bytes should not be zero or an invalid string. Please try again");
                        return 1;
                    }

                    if(no_of_bytes < -1) {
                        printf("Number of bytes cannot be less than -1. Please try again");
                        return 1;
                    }

                    if(no_of_bytes == -1) no_of_bytes = SIZE_T_MAX;
                    bytes_left_to_read = (size_t)no_of_bytes;
                } // -n flag

                if(strcmp(argv[i], "-w") == 0) {
                    w_found = 1;
                    w = strtoll(argv[i+1], NULL, 0);

                    if(!w) {
                        printf("Width should not be zero or an invalid string. Please try again");
                        return 1;
                    }

                    if(w < -1) {
                        printf("Width cannot be less than -1. Please try again");
                        return 1;
                    }

                    if(w == -1) w = 16;
                    bytes_in_each_line = (size_t)w;
                } // -w flag

                if(strcmp(argv[i],"-s") == 0) {
                    s_found  = 1;
                    
                    offset = strtol(argv[i+1], &endptr, 0);

                    if(errno == ERANGE) {
                        printf("Error: The offset cannot be more than %ld or less than %ld. Please try again.", LONG_MAX, LONG_MIN);
                        return 1;
                    } 

                    if(endptr == argv[i+1]) {
                        printf("Error. The offset cannot be an invalid character. Please try again.");
                        return 1;
                    }
                } // -s flag

                if(strcmp(argv[i],"-S") == 0) {
                    indicate_size = 1;
                } // -S flag

                if(strcmp(argv[i],"-g") == 0) {
                    group_size = strtol(argv[i+1], &endptr, 0);

                    if(errno == ERANGE) {
                        printf("Error: group size exceeds %ld or is less than %ld", LONG_MAX, LONG_MIN);
                        return 1;
                    }

                    if(endptr == argv[i+1]) {
                        printf("Error: Group size -g needs to be -1 or a natural number less than width");
                        return 1;
                    }

                    if(!group_size) {
                        printf("Error: Group size cannot be 0. Please try again");
                        return 1;
                    }

                    if(group_size < -1 || group_size > w) {
                        printf("Error: Group size cannot be less than -1 or more than the width");
                        return 1;
                    }

                    if(group_size == -1) group_size = 4;
                } // -g flag
            }
            if(!w_found) {
                w = 16;
                bytes_in_each_line = (size_t)w;
            }
            if(!n_found) {
                bytes_left_to_read = SIZE_T_MAX;
            }
            if(!s_found) {
                offset = 0;
            }
        }
        fp = fopen(argv[1], "rb");
    }
    
    if(fp == NULL) {
        printf("Either the filepath is wrong or the file doesn't exist. Please try again.");
        return 1;
    }

    if(offset < 0) {
        reference = SEEK_END;
    }

    unsigned char buffer[w];

    if(indicate_size) {
        if(fseek(fp, 0L, SEEK_END) != 0) {
            printf("Cannot seek through the file. Please try again.");
            return 1;
        }

        size = ftell(fp);
        if(size == -1L) {
            printf("Error: Cannot determine file size.");
            return 1;
        }

        fseek(fp, 0L, SEEK_SET);
    }

    int remainder_bytes = bytes_left_to_read % w;
    
    if(remainder_bytes == 0) {
        max_iters = (bytes_left_to_read) / w;
    } else {
        max_iters = (bytes_left_to_read - remainder_bytes) / w + 1;
    }

    // for debug
    //printf("max iters = %d, bytes left to read = %d, bytes in each line = %d\n", (int)max_iters,(int)bytes_left_to_read,(int)bytes_in_each_line);

    if(bytes_left_to_read < w) bytes_in_each_line = bytes_left_to_read;
    
    fseek(fp, offset, reference);
    index = offset >= 0? offset : -offset;

    while( ((n = fread(buffer, 1, bytes_in_each_line, fp)) != 0) && (i < max_iters) ) { // n is the number of bytes in each line. if 0, loop stops. 
        any_bytes_read = 1;
        printf("%08zX: ", index);

        for(int j = 0; j < n; j++) {
            printf("%02X", buffer[j]);
            if((j+1) % group_size == 0) printf(" ");
        }

        if(w == 16 && n <= 16) for(int i = 0; i < spaces[n-1]; i++) printf(" ");

        printf("|");

        for(int j = 0; j < n; j++) {
            if(buffer[j] >= 32 && buffer[j] <= 126) {
                printf("%c",(char)buffer[j]);
            } else {
                printf(RED "." RESET);
            }
        }

        if( (i == max_iters - 2) && (remainder_bytes != 0) ) bytes_in_each_line = remainder_bytes;
        printf("|\n");
        index += w;
        i++;
    } 

    if(!any_bytes_read) {
        printf("Can't read any bytes!\n");
    }

    if(indicate_size) printf("File size is %ld bytes\n", size);

    fclose(fp);

    return 0;
}

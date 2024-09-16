#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>

bool is_initialized(char file_name[]);
void write_on_file(char file_name[], char text[], char mode[]);
void copy_and_paste (char* file_name, char* destination);
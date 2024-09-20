/**
 * @file archivos.h
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>

bool is_initialized(char file_name[]);
void copy_and_paste (char* file_name, char* destination);
bool is_folder_empty(char* folder);
bool is_core_file(struct dirent *entry);
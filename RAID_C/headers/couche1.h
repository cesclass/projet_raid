#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

#include "raid_defines.h"

#define ERROR_FILE 1

int compute_nblock(char filename[]);

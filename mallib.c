

#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>

extern pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t sbmutex = PTHREAD_MUTEX_INITIALIZER;

#include "MyNode.h"
#include "arr.c"
#include "arenaliblist.c"
#include "mallocarena.c"
#include "freearena.c"
#include "calloc.c"
#include "realloc.c"
#include "memalign.c"
#include "posixmemalign.c"
#include "reallocarray.c"

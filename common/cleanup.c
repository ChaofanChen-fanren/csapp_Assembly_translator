#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <headers/common.h>

typedef void (*cleanup_t)();

static cleanup_t **events = NULL;

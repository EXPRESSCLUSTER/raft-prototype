#ifndef __MODULES_H_INCLUDED__
#define __MODULES_H_INCLUDED__

#include <stdbool.h>
#include <sys/time.h>
#include <time.h>

bool check_timeout(struct timespec std, struct timespec timeout);

void reset_timer(struct timespec *timer);

#endif
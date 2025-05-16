#include <stdio.h>

#ifdef STM32
#ifdef DISC
#include "stm32f4xx_hal.h"
#elif L4R5ZI
#include "stm32l4xx_hal.h"
#else
#error "You forgot to select the good board"
#endif
typedef uint32_t clock_t;
#define clock() HAL_GetTick()
#define CLOCKS_PER_SEC 1000
#else
#include <time.h>
#endif

static clock_t global_timer;

clock_t tic(void)
{
    global_timer = clock();
    return global_timer;
}

float tac(void)
{
    float ms = (1000.0f * (float)(clock() - global_timer) / CLOCKS_PER_SEC);
    return ms;
}

float TAC(const char *str)
{
    float ms = (1000.0f * (float)(clock() - global_timer) / CLOCKS_PER_SEC);
#ifndef NDEBUG
    printf("%s [%d ms]\n", str, (int)ms);
#endif
    return ms;
}

float toc(const clock_t t)
{
    float ms = (1000.0f * (float)(clock() - t) / CLOCKS_PER_SEC);
    return ms;
}

float TOC(const clock_t t, const char *str)
{
    float ms = (1000.0f * (float)(clock() - t) / CLOCKS_PER_SEC);
    printf("%s [%d ms]\n", str, (int)ms);
    return ms;
}

float TOC_clock(const clock_t t, const char *str)
{
    printf("%s [%lu]\n", str, (unsigned long)(clock() - t));
    return (float)(clock() - t);
}

clock_t dclock(const clock_t t)
{
    return clock() - t;
}

float clock_to_time(const clock_t t, const char *str)
{
    float ms = (1000.0f * (float)t / CLOCKS_PER_SEC);
    printf("%s [%d ms]\n", str, (int)ms);
    return ms;
}

float clock_print(const clock_t t, const char *str)
{
    printf("%s [%lu]\n", str, (unsigned long)t);
    return (float)t;
}

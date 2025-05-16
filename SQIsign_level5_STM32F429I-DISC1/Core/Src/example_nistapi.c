// SPDX-License-Identifier: Apache-2.0

/**
 * An example to demonstrate how to use SQIsign with the NIST API.
 */

#include <inttypes.h>
#include "mem.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>

#include "api.h"
#include "rng.h"
#include "bench_test_arguments.h"
#if defined(TARGET_BIG_ENDIAN)
#include "tutil.h"
#endif

//#define PRINT_MAIN
#define STM32_BENCHMARK

#if defined(STM32_BENCHMARK)
	#define STACK_PATTERN 0xAB

	#include "stm32f429xx.h"
	#include "core_cm4.h"
	extern uint8_t *__sbrk_heap_end;

	void reset_cycle_counter(void) {
		CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
		DWT->CYCCNT = 0;
		DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
	}


	uint32_t get_cycle_count(void) {
	    return DWT->CYCCNT;
	}

	void paint_stack(void) {
	    register uint32_t sp;
	    __asm volatile ("mrs %0, msp" : "=r" (sp));

	    uint8_t *p = __sbrk_heap_end;
	    while ((uint32_t)p < sp) {
	        *p++ = STACK_PATTERN;
	    }
	}

	uint32_t measure_stack_usage(void) {
	    register uint32_t sp;
	    __asm volatile ("mrs %0, msp" : "=r" (sp));

	    uint8_t *p = __sbrk_heap_end;
	    while ((uint32_t)p < sp && *p == STACK_PATTERN) {
	        p++;
	    }
	    return sp - (uint32_t)p;
	}



#endif

static uint32_t rand_u32()
{
    unsigned char buf[4];
    if (randombytes(buf, sizeof(buf)))
        abort();
    return ((uint32_t) buf[3] << 24)
         | ((uint32_t) buf[2] << 16)
         | ((uint32_t) buf[1] <<  8)
         | ((uint32_t) buf[0] <<  0);
}

/**
 * Example for SQIsign variant:
 * - crypto_sign_keypair
 * - crypto_sign
 * - crypto_sign_open
 *
 * @return int return code
 */
int example_sqisign(void)
{

#if defined(STM32_BENCHMARK)
	uint8_t *heap_snapshot = NULL;
	uint32_t start;
	uint32_t cycles;
	uint32_t end;
	uint32_t used_heap;
	uint32_t used_stack;
	uint32_t heap_used;
#endif

    unsigned long long msglen = rand_u32() % 100;
    unsigned long long smlen = CRYPTO_BYTES + msglen;

    unsigned char *sk = calloc(CRYPTO_SECRETKEYBYTES, 1);
    unsigned char *pk = calloc(CRYPTO_PUBLICKEYBYTES, 1);

    unsigned char *sm = calloc(smlen, 1);

#if defined(STM32_BENCHMARK)
    heap_snapshot = __sbrk_heap_end;
#endif
    unsigned char msg[msglen], msg2[msglen];
    printf("%s\n", CRYPTO_ALGNAME);


#if defined(STM32_BENCHMARK)
    printf("KEY GENERATION \n");
    paint_stack();
    start = HAL_GetTick();
    reset_cycle_counter();
#endif
    int res = crypto_sign_keypair(pk, sk);
#if defined(STM32_BENCHMARK)
    cycles = get_cycle_count();
    end = HAL_GetTick();
    printf("TIME : %lu ms \n", end - start);
    printf("NUMBER CYCLE : %lu cycles \n", cycles);

    used_stack = measure_stack_usage();
    printf("STACK USED : %lu bytes\n", used_stack);

    //used_heap = (uint32_t)(__sbrk_heap_end - heap_snapshot);
    //printf("HEAP USAGE : %lu bytes\n", (unsigned long)used_heap);
    //clean_heap_pointer_from(heap_snapshot);
#endif

#if defined(PRINT_MAIN)

    printf("crypto_sign_keypair -> ");

    if (res) {
        printf("FAIL\n");
        goto err;
    } else {
        printf("OK\n");
    }

    // choose a random message
    for (size_t i = 0; i < msglen; ++i)
        msg[i] = rand_u32();
#endif

#if defined(STM32_BENCHMARK)
    printf("SIGN \n");
    paint_stack();
    start = HAL_GetTick();
    reset_cycle_counter();
#endif
    res = crypto_sign(sm, &smlen, msg, msglen, sk);
#if defined(STM32_BENCHMARK)
    cycles = get_cycle_count();
    end = HAL_GetTick();
    printf("TIME : %lu ms \n", end - start);
    printf("NUMBER CYCLE : %lu cycles \n", cycles);

    used_stack = measure_stack_usage();
    printf("STACK USED : %lu bytes\n", used_stack);


    //used_heap = (uint32_t)(__sbrk_heap_end - heap_snapshot);
    //printf("HEAP USAGE : %lu bytes\n", (unsigned long)used_heap);
    //clean_heap_pointer_from(heap_snapshot);
#endif


#if defined(PRINT_MAIN)

    printf("crypto_sign -> ");

    if (res) {
        printf("FAIL\n");
        goto err;
    } else {
        printf("OK\n");
    }
#endif

#if defined(STM32_BENCHMARK)
    printf("VERIFICATION \n");
    paint_stack();
    start = HAL_GetTick();
    reset_cycle_counter();
#endif
    res = crypto_sign_open(msg2, &msglen, sm, smlen, pk);
#if defined(STM32_BENCHMARK)
    cycles = get_cycle_count();
    end = HAL_GetTick();
    printf("TIME : %lu ms \n", end - start);
    printf("NUMBER CYCLE : %lu cycles \n", cycles);

    used_stack = measure_stack_usage();
    printf("STACK USED : %lu bytes\n", used_stack);
    heap_used = (uint32_t)__sbrk_heap_end - 0xD0000000;
    printf("HEAP USAGE : %lu bytes\n", (unsigned long)heap_used);
    //used_heap = (uint32_t)(__sbrk_heap_end - heap_snapshot);
    //printf("HEAP USAGE : %lu bytes\n", (unsigned long)used_heap);
    //clean_heap_pointer_from(heap_snapshot);
#endif



#if defined(PRINT_MAIN)
    printf("crypto_sign_open (with correct signature) -> ");
    if (res || msglen != sizeof(msg) || memcmp(msg, msg2, msglen)) {
        printf("FAIL\n"); // signature was not accepted!?
        goto err;
    } else {
        printf("OK\n");
    }


    // fill with random bytes
    for (size_t i = 0; i < msglen; ++i)
        msg2[i] = rand_u32();

    // let's try a single bit flip
    size_t pos = rand_u32() % smlen;
    sm[pos / 8] ^= 1 << pos % 8;

    res = crypto_sign_open(msg2, &msglen, sm, smlen, pk);

    printf("crypto_sign_open (with altered signature) -> ");
    if (!res) {
        printf("FAIL\n"); // signature was accepted anyway!?
        res = -1;
        goto err;
    }
    else {
        printf("OK\n");
        res = 0;

        if (msglen)
            printf("WARNING: verification failed but the message length was returned nonzero; misuse-prone API\n");

        unsigned char any = 0;
        for (size_t i = 0; i < msglen; ++i)
            any |= msg2[i];
        if (any)
            printf("WARNING: verification failed but the message buffer was not zeroed out; misuse-prone API\n");
    }

err:


#endif

	sqisign_secure_free(sk, CRYPTO_SECRETKEYBYTES);
    free(pk);
    free(sm);
    //heap_snapshot = NULL;
    //clean_heap_pointer();

}



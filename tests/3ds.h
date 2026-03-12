#ifndef _3DS_H
#define _3DS_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint32_t u32;
typedef int32_t s32;
typedef uint16_t u16;
typedef uint8_t u8;
typedef u32 Result;
typedef void* Handle;

#define R_FAILED(res) ((res) != 0)

typedef struct {
    // mock
} PrintConsole;

typedef struct {
    // mock
} LightLock;

typedef enum {
    GFX_TOP,
    GFX_BOTTOM
} gfxScreen_t;

typedef enum {
    debugDevice_CONSOLE
} debugDevice;

// Function prototypes to mock
void hidInit(void);
void psInit(void);
void gfxInitDefault(void);
void consoleInit(gfxScreen_t screen, PrintConsole* console);
void LightLock_Init(LightLock* lock);
void fsInit(void);
void consoleDebugInit(debugDevice device);
void ndmuInit(void);
void aptSetSleepAllowed(bool allowed);
Result NDMU_EnterExclusiveState(u32 state);
void NDMU_LockState(void);
Result socInit(u32* context_addr, u32 context_size);
void socExit(void);
void gfxExit(void);
void hidExit(void);
void psExit(void);
void NDMU_UnlockState(void);
void NDMU_LeaveExclusiveState(void);
void ndmuExit(void);

#define NDM_EXCLUSIVE_STATE_INFRASTRUCTURE 0

#endif

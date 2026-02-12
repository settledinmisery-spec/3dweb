#include "3ds.h"
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <malloc.h>
#include <fcntl.h>
#include <arpa/inet.h>

// Mock implementation of 3DS functions
void hidInit(void) { printf("hidInit called\n"); }
void psInit(void) { printf("psInit called\n"); }
void gfxInitDefault(void) { printf("gfxInitDefault called\n"); }
void consoleInit(gfxScreen_t screen, PrintConsole* console) { printf("consoleInit called\n"); }
void LightLock_Init(LightLock* lock) { printf("LightLock_Init called\n"); }
void fsInit(void) { printf("fsInit called\n"); }
void consoleDebugInit(debugDevice device) { printf("consoleDebugInit called\n"); }
void ndmuInit(void) { printf("ndmuInit called\n"); }
void aptSetSleepAllowed(bool allowed) { printf("aptSetSleepAllowed called: %d\n", allowed); }
Result NDMU_EnterExclusiveState(u32 state) { printf("NDMU_EnterExclusiveState called\n"); return 0; }
void NDMU_LockState(void) { printf("NDMU_LockState called\n"); }
Result socInit(u32* context_addr, u32 context_size) { printf("socInit called\n"); return 0; }
void socExit(void) { printf("socExit called\n"); }
void gfxExit(void) { printf("gfxExit called\n"); }
void hidExit(void) { printf("hidExit called\n"); }
void psExit(void) { printf("psExit called\n"); }
void NDMU_UnlockState(void) { printf("NDMU_UnlockState called\n"); }
void NDMU_LeaveExclusiveState(void) { printf("NDMU_LeaveExclusiveState called\n"); }
void ndmuExit(void) { printf("ndmuExit called\n"); }

// Mock utils functions
int printTop(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    return 0;
}
void failExit(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    exit(1);
}

// Mock init_handlers
void init_handlers() { printf("init_handlers called\n"); }

// Mock start_connection_thread
#include "httpserver.h"

// Define gethostid macro to return localhost IP
long my_gethostid() {
    return (long)inet_addr("127.0.0.1");
}
#define gethostid my_gethostid

void start_connection_thread(http_server *server_template, s32 client_id, struct sockaddr_in client_addr) {
    printf("start_connection_thread called for client %d\n", client_id);
    close(client_id); // simulate thread handling connection and closing it
}

// Mock SystemConfig sys_conf
SystemConfig sys_conf = { .is_new_3ds = false, .stack_size = 16384, .socket_buffer_size = 4096 };

// Include the source file
#include "../src/server.c"

int main() {
    printf("--- Starting Verification Test ---\n");

    // Call init
    init(8080);
    printf("--- Init passed ---\n");

    // Call destroy to test memory leak fix
    destroy();
    printf("--- Destroy passed ---\n");

    // Cleanup
    remove("index.html");
    chdir("..");
    rmdir("Websites");

    return 0;
}

#include <iostream>
using namespace std;

extern unsigned char MESSAGE_HEADER[954];

extern unsigned char COMMAND_HEADER[906];

extern unsigned char SHUTDOWN_HEADER[582];

extern unsigned char REBOOT_HEADER[582];

extern int MESSAGE_INDEX;

extern int COMMAND_INDEX;

extern int MESSAGE_HEADER_LEN;

extern int COMMAND_HEADER_LEN;

extern int SHUTDOWN_REBOOT_HEADER_LEN;

#define DATA_LENGTH(a) wcslen(a) * 2 + 1
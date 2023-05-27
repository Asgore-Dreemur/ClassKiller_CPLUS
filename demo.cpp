#include <iostream>
#include <vector>
#include <stdio.h>
#include "DataDefine.h"
#include "DataHandle.h"
#include <string>
#include <stdlib.h>
#include <string.h>
using namespace std;

int main(){
    unsigned char testdata[DATA_LENGTH(L"hello")];
    unsigned char cansend[MESSAGE_HEADER_LEN]; //COMMAND_HEADER_LEN或SHUTDOWN_REBOOT_HEADER_LEN
    int size = EncodeData(L"hello", testdata);
    PackageMessage(testdata, size, cansend);
    SendData(cansend, "127.0.0.1", 4709);
    SendData(SHUTDOWN_HEADER, "127.0.0.1", 4709); //发送关机指令,重启指令同样
    return 0;
}
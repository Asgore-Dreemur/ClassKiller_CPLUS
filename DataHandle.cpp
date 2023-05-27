#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DataDefine.h"
#include "DataHandle.h"
#include <winsock2.h>

using namespace std;

/*
用于编码数据,发送消息和指令时需要
data:数据，宽字节
out:输出缓冲区
返回数组长度
*/
int EncodeData(wchar_t* data, unsigned char* out){
    unsigned char finaldata[DATA_LENGTH(data)];
    int index = 0;
    for(int i=0;i<wcslen(data);i++){
        wchar_t dchar = data[i];
        int unidchar = (int)dchar;
        char *hexstr = new char[5];
        sprintf(hexstr, "%04x", unidchar);//Unicode码转为十六进制字符串
        string hexstring = hexstr;
        int high, low;
        sscanf(hexstring.substr(0, 2).c_str(), "%x", &high);
        sscanf(hexstring.substr(2).c_str(), "%x", &low);
        finaldata[index] = low;
        index++;
        finaldata[index] = high;
        index++;
    }
    memcpy(out, finaldata, sizeof(finaldata));
    return index + 1;
}

/*
将发送内容与头结合，发送消息时使用
messagedata:经过编码后的发送数据
datalength:数据长度
out:输出缓冲区
*/
int PackageMessage(unsigned char* messagedata, int datalength, unsigned char* out){
    unsigned char header[MESSAGE_HEADER_LEN] = {0};
    memcpy(header, MESSAGE_HEADER, MESSAGE_HEADER_LEN);
    int index = MESSAGE_INDEX; //从MESSAGE_INDEX这个索引开始填充数据
    for(int i=0;i<datalength;i++){
        header[index] = messagedata[i];
        index++;
    }
    memcpy(out, header, sizeof(header));
    return MESSAGE_HEADER_LEN;
}

/*
将发送内容与头结合，发送命令时使用
messagedata:经过编码后的发送数据
datalength:数据长度
out:输出缓冲区
*/
int PackageCommand(unsigned char* messagedata, int datalength, unsigned char* out){
    unsigned char header[COMMAND_HEADER_LEN] = {0};
    memcpy(header, MESSAGE_HEADER, MESSAGE_HEADER_LEN);
    int index = COMMAND_INDEX; //从COMMAND_INDEX这个索引开始填充数据
    for(int i=0;i<datalength;i++){
        header[index] = messagedata[i];
        index++;
    }
    memcpy(out, header, sizeof(header));
    return COMMAND_HEADER_LEN;
}

/*
发送数据
data:数据
如果是消息和指令需要经过编码和打包,否则可以直接发送
*/
void SendData(unsigned char *data, char* ip, int port){
    WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	sockaddr_in sendAddr;
	SOCKET sendSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	sendAddr.sin_family = AF_INET;
	sendAddr.sin_addr.s_addr = inet_addr(ip);			
	sendAddr.sin_port = htons(port);
    sendto(sendSock, data, 1024, 0, (sockaddr *)&sendAddr, sizeof(sendAddr));
}

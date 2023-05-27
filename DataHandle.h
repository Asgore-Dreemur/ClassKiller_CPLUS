extern int EncodeData(wchar_t* data, unsigned char* out);

extern int PackageMessage(unsigned char* messagedata, int datalength, unsigned char* out);

extern int PackageCommand(unsigned char* messagedata, int datalength, unsigned char* out);

extern void SendData(unsigned char *data, char* ip, int port);
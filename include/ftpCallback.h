#ifndef FTP_H
#define FTP_H

#include <Arduino.h>
#include <SimpleFTPServer.h>

void _callback(FtpOperation ftpOperation, unsigned int freeSpace, unsigned int totalSpace);
void _transferCallback(FtpTransferOperation ftpOperation, const char* name, unsigned int transferredSize);

#endif // FTP_H

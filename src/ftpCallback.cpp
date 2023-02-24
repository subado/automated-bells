#include "ftpCallback.h"

void _callback(FtpOperation ftpOperation, unsigned int freeSpace, unsigned int totalSpace)
{
	switch (ftpOperation)
	{
		case FTP_CONNECT:
			Serial.println(F("FTP: Connected!"));
			break;
		case FTP_DISCONNECT:
			Serial.println(F("FTP: Disconnected!"));
			break;
		case FTP_FREE_SPACE_CHANGE:
			Serial.printf("FTP: Free space change, free %u of %u!\n", freeSpace, totalSpace);
			break;
		default:
			break;
	}
}

void _transferCallback(FtpTransferOperation ftpOperation, const char* name, unsigned int transferredSize)
{
	switch (ftpOperation)
	{
		case FTP_UPLOAD_START:
			Serial.println(F("FTP: Upload start!"));
			break;
		case FTP_UPLOAD:
			Serial.printf("FTP: Upload of file %s byte %u\n", name, transferredSize);
			break;
		case FTP_TRANSFER_STOP:
			Serial.println(F("FTP: Finish transfer!"));
			break;
		case FTP_TRANSFER_ERROR:
			Serial.println(F("FTP: Transfer error!"));
			break;
		case FTP_DOWNLOAD_START:
			Serial.println(F("FTP: Download start!"));
			break;
		case FTP_DOWNLOAD:
			Serial.printf("FTP: Download of file %s byte %u\n", name, transferredSize);
			break;
		default:
			break;
	}
}

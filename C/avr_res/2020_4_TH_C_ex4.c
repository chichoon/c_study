#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main()
{
	char c;
	HANDLE hSerial;

	unsigned long bytes_written;
  // https://docs.microsoft.com/en-us/windows/desktop/api/winbase/ns-winbase-dcb 참고
	DCB dcbSerialParams = { 0 };
  // https://docs.microsoft.com/en-us/windows/desktop/api/winbase/ns-winbase-commtimeouts 참고
	COMMTIMEOUTS timeouts = { 0 };

// https://docs.microsoft.com/en-us/windows/desktop/api/fileapi/nf-fileapi-createfilea 참고
	hSerial = CreateFile(L"COM2" , GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
// VSPE 세팅을 했음에도 불구하고, COM port를 여는 과정에 문제가 생긴다면, L"COM2"에서 L을 지우고 다시 빌드하세요.)
	if (hSerial == INVALID_HANDLE_VALUE)
	{
		if (GetLastError() == ERROR_FILE_NOT_FOUND)
		{
			printf("ERROR!! COM2 PORT NOT FOUND\n");
		}
		printf("ERROR!! FAIIED TO ACCESS TO COM2 SUCCESSFULLY\n");
	}

	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

  // https://docs.microsoft.com/en-us/windows/desktop/api/winbase/nf-winbase-getcommstate 참고
	if (!GetCommState(hSerial, &dcbSerialParams))
	{
		printf("ERROR!! FAIIED TO GET SERIAL PARAMETERS\n");
	}

	dcbSerialParams.BaudRate = CBR_57600;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.Parity = NOPARITY;
	dcbSerialParams.StopBits = ONESTOPBIT;
  // https://docs.microsoft.com/en-us/windows/desktop/api/winbase/nf-winbase-setcommstate 참고
	if (!SetCommState(hSerial, &dcbSerialParams))
	{
		printf("ERROR, Setting serial port state");
	}

	timeouts.ReadIntervalTimeout = 50;
	timeouts.ReadTotalTimeoutConstant = 50;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 50;
	timeouts.WriteTotalTimeoutMultiplier = 10;

// https://docs.microsoft.com/en-us/windows/desktop/api/winbase/nf-winbase-setcommtimeouts 참고
	if (!SetCommTimeouts(hSerial, &timeouts))
	{
		printf("ERROR!! Time Out\n");
		return 1;
	}
	else
	{
		while (1)
		{
			c = getchar();
			if (c == '\0')
			{
				break;
			}
			else
			{
        // https://docs.microsoft.com/en-us/windows/desktop/api/fileapi/nf-fileapi-writefile 참고
				WriteFile(hSerial, &c, 1, &bytes_written, NULL);
			}
		}
	}
	
	CloseHandle(hSerial);
	return 0;
}

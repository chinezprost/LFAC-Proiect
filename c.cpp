//make me a tcp client that connect to a cs 1.6 server and get the player to say "suck my nuts"

#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winuser.h>
#include <wininet.h>
#include <windowsx.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cctype>
#include <ctime>
#include <tlhelp32.h>
#include <tchar.h>
#include <psapi.h>
#include <shlwapi.h>
#include <shlobj.h>
#include <shellapi.h>
#include <iphlpapi.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <psapi.h>
#include <shlwapi.h>
#include <shlobj.h>
#include <shellapi.h>
#include <iphlpapi.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <psapi.h>
#include <shlwapi.h>
#include <shlobj.h>
#include <shellapi.h>
#include <iphlpapi.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <psapi.h>
#include <shlwapi.h>
#include <shlobj.h>

#pragma comment(lib, "Ws2_32.lib")

using namespace std;


int main()
{
    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo *result = NULL,
                    *ptr = NULL,
                    hints;
    const char *sendbuf = "suck my nuts";
    char recvbuf[512];
    int iResult;
    int recvbuflen = 512;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo("

    if ( iResult != 0 ) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Attempt to connect to an address until one succeeds

    // Create a SOCKET for connecting to server
    ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, 
        ptr->ai_protocol);
            


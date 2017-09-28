//
//  utils.cpp
//  pwnednet
//
#include "utils.h"


void debug(string in) {
    cout << "[debug] " + in << endl;
}

const char* cstr(string in) {
    return in.c_str();
}

void clear()
{
    system("clear");
}

bool DoesFileExist(const string& name) {
    ifstream f(name.c_str());
    return f.good();
}

bool strpos(string str, string str2) {
    if (str.find(str2) != std::string::npos)
        return true;
    else
        return false;
}

bool StringToBool(string in) {
    
    if(strpos(in, "true"))
        return true;
    else if(strpos(in, "false"))
        return false;
    else
        return false;
    
}


bool DoesPIDExist(const char* Program) {
    
    pid_t PID = Util::GetProcessByName(Program);
    
    if(PID)
        return true;
    
    return false;
}

void KillProcess(string processname) {
    system(cstr("killall " + processname));
}

void KillActivityMonitor() {
    
    int tskmgr_pid = Util::GetProcessByName("Activity Monitor");
    
    if(tskmgr_pid) {
        
        string cmd = "kill " + to_string(tskmgr_pid);
        system(cmd.c_str());
        
    }
    
}


string exec(const char* cmd) {
    
    array<char, 128> buffer;
    string result;
    shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    
    if (!pipe)
        throw runtime_error("");
    
    while (!feof(pipe.get())) {
        
        if (fgets(buffer.data(), 128, pipe.get()) != NULL) {
            result += buffer.data();
        }
        
    }
    
    return result;
}

string Util::GetHWID() {
    return exec("ioreg -rd1 -c IOPlatformExpertDevice | awk '/IOPlatformUUID/ { split($0, line, \"\\\"\"); printf(\"%s\\n\", line[4]); }'");
}


pid_t Util::GetProcessByName(const char *name) {
    
    int procCnt = proc_listpids(PROC_ALL_PIDS, 0, NULL, 0);
    pid_t pids[1024];
    memset(pids, 0, sizeof pids);
    proc_listpids(PROC_ALL_PIDS, 0, pids, sizeof(pids));
    
    for (int i = 0; i < procCnt; i++) {
        
        if (!pids[i])
            continue;
        
        char curPath[PROC_PIDPATHINFO_MAXSIZE];
        char curName[PROC_PIDPATHINFO_MAXSIZE];
        
        memset(curPath, 0, sizeof curPath);
        proc_pidpath(pids[i], curPath, sizeof curPath);
        size_t len = strlen(curPath);
        
        if (len) {
            
            size_t pos = len;
            while (pos && curPath[pos] != '/') --pos;
            strcpy(curName, curPath + pos + 1);
            
            if (!strcmp(curName, name)) {
                return pids[i];
            }
            
        }
        
    }
    
    return -1;
}

int Util::GetCores() {
    
    int nm[2];
    size_t len = 4;
    uint32_t count;
    
    nm[0] = CTL_HW; nm[1] = HW_AVAILCPU;
    sysctl(nm, 2, &count, &len, NULL, 0);
    
    if(count < 1) {
        
        nm[1] = HW_NCPU;
        sysctl(nm, 2, &count, &len, NULL, 0);
        
        if(count < 1) {
            count = 1;
        }
        
    }
    
    return count;
}


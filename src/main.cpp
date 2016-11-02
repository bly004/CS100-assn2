#include "AndConnector.h"
#include "Arguments.h"
#include "Connectors.h"
#include "Executables.h"
#include "Input.h"
#include "InputComposite.h"
#include "Line.h"
#include "OrConnector.h"
#include "Program.h"

#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fstream>





int main() {
    
    //finding user login info
    string user, info;
    
    char hostInfo[256];
    struct passwd *u = getpwuid(getuid());
    int h = gethostname(hostInfo, 256);
    
    if(u != 0 && h != -1) {
        user = u->pw_name;
        info = user + "@" + hostInfo + "$ ";
    } else {
        user = "anon_user";
        info = user + "@host_name$ ";
    }
    
    
    
    
}
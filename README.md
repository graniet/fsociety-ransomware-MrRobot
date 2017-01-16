# FSociety ransomware

![Fsociety ransomware graniet](https://s3.postimg.org/y861zq31v/Capture_d_cran_de_2016_10_30_12_18_08.png)

# On movie

![Fsociety ransomware graniet](http://www.welivesecurity.com/wp-content/uploads/2016/07/mrrobot11-1024x590.jpg)


#### Required lib :
+ Crypto++
+ CURL

#### G++ flags used for test
+ g3
+ ggdb
+ O0
+ Wall
+ Wextra
+ Wno-unused
+ lcryptopp
+ lcurl

#### Ransomware Step
+ Initial
+ File listing
+ File parser
+ Encrypt files source with AES Library
+ Change filename with filename+.locked
+ Send to jester C&C (Number file...)
+ Ask reward & setup jester pages

(For security reason the ransomware crypt only .txt but you can change on c++ file)

#### please remember this  is just a PoC the ransomware is not stable is just for fun!

#### Advanced

In futur i'll add multiple  step (Decrypt on file for free,  FAQ  ...).

#### DISCLAIMER
This is Jester ransomware like, in Mr Robot movie (coded by Darlene S1E2,3),
Please beware warning, after start you can't recover the files (In movie, the public key is not shared).
Please don't use this malware on personal computer.
This project is just a wink of mr robot serie.

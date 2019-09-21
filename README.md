## certexp

This software can extract certifcate expiry information for given domains.

### Usage
Create a text file with a list of domains to check. Please insert one domain
per line.

Example (assuming you are in the source code directory):

```
echo "v-gar.de" >> domainlist.txt; echo "vgapps.de" >> domainlist.txt
```

Then run certexp:

```
bin/certexp domainlist.txt
```

The output looks like this:

```
Domain: v-gar.de
Expire date: Sun Dec  2 06:35:01 2019
 (expires in 71 days)
 (SAN: v-gar.de)
Expire date: Sun Dec  2 06:35:01 2019
 (expires in 71 days)
 (SAN: *.v-gar.de)

Domain: vgapps.de
Expire date: Sun Dec  6 07:55:27 2019
 (expires in 75 days)
 (SAN: www.vgapps.de)
Expire date: Sun Dec  6 07:55:27 2019
 (expires in 75 days)
 (SAN: vgapps.de)
```

### Compile and install
This software is written in C++ (C++17 standard) and uses libcurl.

You need:

- a C++ compiler: gcc >= 8
- cmake >= 3.2
- libcurl

For Ubuntu / Debian you can install this software using apt:

```
sudo apt install build-essential cmake libcurl4-openssl-dev
```

Compilation is easy: go to this source code directory and do:

```
mkdir build
cmake ..
make
make install
```

The binary will be copied/installed to the ./bin/ dir.

## License

The code is licensed under the MIT license. See COPYING.

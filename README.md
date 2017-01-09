# locateJson

## Overview

locateJson: a tool for converting mlocate databases to JSON.

mlocate databases contain an index of files and directories for efficient lookup. `man locate` and `man mlocate.db` for more details.

## TL; DR

From the repository root:

```bash
cmake -DCMAKE_BUILD_TYPE=Release ./
make
make install
ln -s /opt/locatejson/bin/locatejson /usr/bin/locatejson
```

Then (you may need to `sudo`):

```bash
locatejson -o /tmp/output.json
```

## Questions & Answers

**What's this for?**

A component for any application that needs access to an index of files and directories on Linux in a modern, easily-parsable format.

**How can I pretty-print locateJson's output?**

locateJson can't produce pretty-printed JSON itself, but you can use Python to do this:

```bash
python -m json.tool condensed.json > pretty.json
```

**How will locateJson handle massive databases and JSON outputs?**

The maximum file sizes supported by locateJson are limited only by your file system.

locateJson intentionally doesn't use much memory - the mlocate database and resulting JSON aren't buffered, so locateJson's memory usage is low regardless of how big they are.

## Building & Testing

### What you need

+ C++11 compatible compiler (at least g++ 4.8.5 recommended)
+ cmake >= version 2.6
+ valgrind, for dynamic analysis tests
+ cppcheck, for static analysis tests

### Instructions

From the repository root:

```bash
cmake -DCMAKE_BUILD_TYPE=Release ./
make
make test
```

## Packaging & Installing

### What you need

If you're using a DEB or RPM based platform, it's recommended you generate a compatible package (see below for instructions) and install using this. To do this, you'll need package building tools such as:

+ rpm-build
+ builddeb

### Instructions

**To install from a package:**

In the repository root, run one of the following commands depending on whether you want to generate an RPM or DEB package:

```bash
cmake -DCMAKE_BUILD_TYPE=Release -DCPACK_GENERATOR=RPM ./
```

or

```bash
cmake -DCMAKE_BUILD_TYPE=Release -DCPACK_GENERATOR=DEB ./
```

Run the following commands:

```bash
make
make package
```

Install the package now present in the repository root, e.g.

```bash
sudo yum install locatejson-0.1-1.x86_64.rpm 
```

or

```bash
sudo dpkg -i locatejson-0.1-1.x86_64.deb
```

**To install without generating a package:**

```bash
cmake -DCMAKE_BUILD_TYPE=Release ./
make
make install
```

## Usage

### Synopsis

locatejson [-n <string>] [-o <filename>] [-i <filename>] [--] [--version] [-h]

### Options

+ **-n <string>,  --hostname <string>** Hostname to associate with the file entries in the converted JSON. If ommitted, the current host's name is used.
+ **-o <filename>,  --output <filename>** Filename of the JSON file to write. If ommitted, standard output is used.
+ **-i <filename>,  --input <filename>** Filename of the database to convert. If ommitted, `/var/lib/mlocate/mlocate.db` is used.
+ **--,  --ignore_rest** Ignores the rest of the labeled arguments following this flag.
+ **--version** Displays version information and exits.
+ **-h,  --help** Displays usage information and exits.

### Exit status

The exit status is 0 if the database was successfully converted, and 1 if an error occurred.

## Contact

**Found a bug or want a new feature?** Please create a ticket at https://sourceforge.net/p/locatejson/tickets

**Need help developing a solution?** I may be available to help - contact me via SourceForge at https://sourceforge.net/u/jmistry/profile/send_message


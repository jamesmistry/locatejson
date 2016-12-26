# locateJson

## Overview

locateJson doesn't use much memory - the mlocate database and resulting JSON aren't buffered, so their size doesn't affect locateJson's memory usage. For example, a test mlocate database of approximately 10 MiB in size that resulted in a JSON file of over 43 MiB in size was processed with a peak memory usage of less than 90 KiB.

`man mlocate.db` for more details.

## Building

### What you need


### Instructions

## Installing

### What you need



### Instructions



## Usage

### Synopsis

./build/Debug/bin/locatejson [-n <string>] [-o <filename>] [-i <filename>] [--] [--version] [-h]

### Options

+ **-n <string>,  --hostname <string>** Hostname to associate with the file entries in the converted JSON. If ommitted, the current host's name is used.
+ **-o <filename>,  --output <filename>** Filename of the JSON file to write. If ommitted, standard output is used.
+ **-i <filename>,  --input <filename>** Filename of the database to convert. If ommitted, `/var/lib/mlocate/mlocate.db` is used.
+ **--,  --ignore_rest** Ignores the rest of the labeled arguments following this flag.
+ **--version** Displays version information and exits.
+ **-h,  --help** Displays usage information and exits.

### Exit status

The exit status is 0 if the database was successfully converted, and 1 if an error occurred.

## Contributing



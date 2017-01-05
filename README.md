# locateJson

## Overview

locateJson: a tool for converting mlocate databases to JSON.

mlocate databases contain an index of files and directories for efficient lookup. `man locate` and `man mlocate.db` for more details.

locateJson doesn't use much memory - the mlocate database and resulting JSON aren't buffered, so locateJson's memory usage is independent of how big they are.

You may find locateJson useful for creating distributed `locate` functionality using a search engine like Elasticsearch - see the `examples/` directory for a basic guide.

## Building & Testing

### What you need


### Instructions

## Installing

### What you need



### Instructions



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

**Need help developing a solution?** I may be available to offer consultancy - contact me via SourceForge at https://sourceforge.net/u/jmistry/profile/send_message


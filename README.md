# Saminal
A simple implementation of a terminal built in c++

### Dependencies
Boost
- For linux: `sudo apt-get install libboost-all-dev`
- For MacOS: `brew install boost`

### Usage
######Running
- Execute the runner executable to lanch the shell in normal mode
- Execute the tester executable to run the unit tests, lanch the shell and catch errors which will fail the test.

######Basic Commands
- ls optional:[filePath/DirPath]
    - Lists the contents of the current directory or dir of passed in relative path
- cd [DirPath]
    - Changes the current directory to the passed in relative path
    - use `~` for home starting from home directory
- cat [filePath]
    - Prints the contents of the passed in file to standard output
- pwd
    - Prints the current working directory

######Added Commands
- join [num of files] [fileX] [fileX column] ... [outputFile]
    - Joins the passed in file based on some like column
    - **Can handle N files**
    - Files can't have empty line at end of the file, for parsing reasons

# Saminal
A simple implementation of a terminal built in c++

### Dependencies
Boost
- For linux: `sudo apt-get install libboost-all-dev`
- For MacOS: `brew install boost`

### Usage
#####Basic Commands
- ls optional:[filePath/DirPath]
    - Lists the contents of the current directory or dir of passed in relative path
- cd [DirPath]
    - Changes the current directory to the passed in relative path
    - use `~` for home starting from home directory
- cat [filePath]
    - Prints the contents of the passed in file to standard output
- pwd
    - Prints the current working directory
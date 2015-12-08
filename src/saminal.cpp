#include "../include/saminal.hpp"


//max colors for the color printer
#define MAX_COLORS 3

//Just because I don't want to debug based on one file line
#define SAFE_NET 5

#define MAX_FILE_LINE 1024

typedef struct fileLine{
    char line[MAX_FILE_LINE+1];
}_fileLine;

//alias the filesystem namespace to make it easier
namespace fs = boost::filesystem;

//type def for the function pointer declaration
typedef int (Saminal::*FnPtr)(std::vector<std::string>);

//see header file for comments
Saminal::Saminal(){

    //add the func pointers to the map for the basic commands
    b_cmd_map["ls"] = &Saminal::ls;
    b_cmd_map["pwd"] = &Saminal::pwd;
    b_cmd_map["cat"] = &Saminal::cat;
    b_cmd_map["cd"] = &Saminal::cd;

    //get the home directory env var for the system
    homeDir = fs::path(getenv("HOME"));

    //make sure the env var is valid
    if(!fs::exists(homeDir) && !fs::is_directory(homeDir)){
         throw std::runtime_error("Error while starting home directory, this is a big issue");
    }
}

//see header file for comments
void Saminal::printColor(std::string text,int color){
    //set up the array
    std::string colorTable[MAX_COLORS] = {"\033[1;33m","\033[1;36m","\033[1;31m"};

    //param check
    if(color >= 0 && color < (sizeof(colorTable)/sizeof(*colorTable))){
        std::cout<<colorTable[color]<<text<<"\033[0m";
    }

}

//see header file for comments
int Saminal::ls(std::vector<std::string> args){
    //param check
    if(args.size() > 0){

        //set up dir iterators, man boost makes life easier
        fs::directory_iterator end_iter;
        fs::path relative_move;

        //check if the user wants to list a different directory
        (args.size() > 1) ? (relative_move = fs::path(args.at(1))) : (relative_move = fs::path(""));

        int lineCount = 0;

        //gotta love try catches
        try{
            //get the canonical path from the relative
            fs::path dirToLs = fs::canonical(relative_move,fs::current_path());

            //make sure its a dir
            if(!fs::is_directory(dirToLs)){
                std::cout<<dirToLs.filename().string()<<std::endl;
                return 1;
            }

            //iterate through the dir and print the contents
            for(fs::directory_iterator iter(dirToLs); iter != end_iter; iter++){
                //if the file has a doc ignore it
                if(iter->path().filename().string()[0] != '.'){
                    lineCount++;
                    //print dirs one color
                    if(fs::is_directory(iter->path())){
                        printColor(iter->path().filename().string(),1);
                    }
                    //and files a different color
                    else{
                         printColor(iter->path().filename().string(),0);
                    }
                    //I only want five names on one line so its pretty
                    std::cout<<"   ";
                    if(lineCount >= 5){
                        lineCount = 0;
                        std::cout<<std::endl;
                    }
                }
            }
            return 1;
        }
        catch(...){
            std::cerr<<"Could not list, either it doesn't exist or it is not a directory"<<std::endl;
            return -1;
        }
    }
    return -1;
}

//see header file for comments
int Saminal::cd(std::vector<std::string> args){
    if(args.size() > 1 && !args.at(1).empty()){
        //just to keep things even
        fs::path errorPath("");

        std::string sArg = args.at(1);

        //check if user wants to go from the home dir
        if(sArg[0] == '~'){
            //add the home direcctory to the path
            fs::path newPath(std::string(homeDir.string()) + sArg.erase(0,1));
            if(fs::exists(newPath) && fs::is_directory(newPath)){
                fs::current_path(newPath);
                return 1;
            }
            errorPath = newPath;
        }
        else{
            fs::path relative_move(sArg);
            //try and make the canonical path from the relative path passed in
            try{
                fs::path newCurrDir = fs::canonical(relative_move,fs::current_path());
                if(fs::is_directory(newCurrDir)){
                    fs::current_path(newCurrDir);
                    return 1;
                }
                errorPath = newCurrDir;
            }
            //yea probably not best to catch everything but it works nicley here
            catch(...){
                std::cerr<<"Path "<<relative_move.string()<<" either doesn't exist or is not a directory"<<std::endl;
                return -1;
            }
        }
        std::cerr<<"Path "<<errorPath.string()<<" either doesn't exist or is not a directory"<<std::endl;
        return -1;
    }
    std::cerr<<"Must say which directory to change to: cd <directory>"<<std::endl;
    return -1;
}


//see header file for comments
int Saminal::pwd(std::vector<std::string> args){
    //simple enough, just print out the current path
    //prob not used much since i put the working dir as the main line
    std::cout<<fs::current_path().string()<<std::endl;
    return 1;
}

//see header file for comments
int Saminal::cat(std::vector<std::string> args){
    if(args.size() > 1){

        std::string line;
        std::ifstream myfile(args.at(1));

        //check if the file was able to be opened
        if(myfile.is_open()){
            //get the lines out and then print them to the screen
            while(std::getline(myfile,line)){
               std::cout<<line<<std::endl;
            }
            return 1;
        }
        std::cerr<<"File does not exist"<<std::endl;
        return -1;
    }
    std::cerr<<"Must provide a file to print out: cat <file>"<<std::endl;
    return -1;
}

//see header file for comments
std::vector<std::string> Saminal::parse_args(std::string args){

    std::vector<std::string> tokens;
    //param check
    if(!args.empty()){

        //man, your the best boost, so many great things to make my life nice
        //even though c++11 now comes with alot, I still like using good old boost
        boost::algorithm::split(tokens, args, boost::is_any_of(" "));

        return tokens;
    }
    std::cerr<<"Must pass string to parsers"<<std::endl;
    //return an empty vector for an error
    return tokens;
}

//see header file for comments
int Saminal::exec_basic(std::vector<std::string> args){
    if(args.size() > 0){
        //call the basic command passed in and execte the func pointer for it
        auto func = b_cmd_map[args.at(0)];
        return (this->*func)(args);
    }
    std::cerr<<"Must provide a command"<<std::endl;
    return -1;
}

//see header file for comments
//not needed for this milestone
//just fill in for skeleton
int Saminal::exec_added(std::vector<std::string> args){
    if(args.size() > 1){
        if(args.at(1) == "join"){
            return this->join(args);
        }
    }
    std::cerr<<"Failed params for exec added"<<std::endl;
    return -1;
}


//see header file for comments
int Saminal::check_cmd_exist(std::string cmd){
    if(cmd.length() > 0){
        for(auto bcmd : b_cmd_map){
            if(bcmd.first == cmd){
                return 1;
            }
        }
    }
    return 0;
}


//see header file for comments
int Saminal::join(std::vector<std::string> args){
    //param check
    if(args.size() > 6){
        //make sure the files exist
        //gotta love that try catch though
        try{

            int numFiles = stoi(args.at(1));

            if(numFiles < 2 || args.size() < (3 + numFiles * 2)){
                std::cerr<<"Must have at least 2 files: join <file1> <file1 column> <file2> <file2 column> <outputFile>"<<std::endl;
                return -1;
            }

            std::ifstream *o_files = new std::ifstream[numFiles];
            int fLineCountSums[numFiles];
            int columns[numFiles];

            //set up all files and informations
            for(int i = 0; i < numFiles; i++){
                o_files[i].open(args.at(i*2+2));

                if(!o_files[i].is_open()){
                    std::cout<<"1 or more files could not be found, all files must be vaild to join :)"<<std::endl;
                    return -1;
                }

                fLineCountSums[i] = std::count(std::istreambuf_iterator<char>(o_files[i]), std::istreambuf_iterator<char>(), '\n') + 1;
                std::cout<<"sumbefore:"<<i<<" "<<fLineCountSums[i]<<std::endl;
                if(i != 0){
                    fLineCountSums[i] += fLineCountSums[i-1];
                }

                std::cout<<"sum:"<<i<<" "<<fLineCountSums[i]<<std::endl;

                //get the column to search for each file
                columns[i] = stoi(args.at(i*2+3));

                if(columns[i] <= 0 ){
                    throw std::invalid_argument("");
                }
            }




            int shmId;          // ID of shared memory segment
            key_t shmKey = 123460;      // key to pass to shmget(), key_t is an IPC key type defined in sys/types
            int shmFlag = IPC_CREAT | 0666; // Flag to create with rw permissions
            _fileLine * shm;
            pid_t pid;
            unsigned long * sharedIndexPtr = NULL;

            //create the shared memeory
            if ((shmId = shmget(shmKey, fLineCountSums[numFiles-1] * sizeof(_fileLine), shmFlag)) < 0){
                std::cerr << "Init: Failed to initialize shared memory (" << shmId << ")" << std::endl;
                return -1;
            }

            if ((shm = (_fileLine *)shmat(shmId, NULL, 0)) == (_fileLine *) -1){
                std::cerr << "Init: Failed to attach shared memory (" << shmId << ")" << std::endl;
                return -1;
            }

            for(int i; i < numFiles; i++){
                pid = fork();

                if ( pid < 0 ){
                    std::cerr << "Could not fork!!! ("<< pid <<")" << std::endl;
                    return -1;
                }
                //this is the child taking over
                else if (pid == 0){
                    std::string line;

                    //reset the file pointers
                    o_files[i].clear();
                    o_files[i].seekg(0);

                    int index_count = 0;
                    int index_start = 0;
                    if(i != 0){
                        index_start = fLineCountSums[i-1];;
                    }


                    //add each line of the file to shared memory
                    while ( std::getline (o_files[i],line) ){
                        std::cout<<"file line: "<<line<<std::endl;
                        std::strcpy(shm[index_count+index_start].line,line.c_str());
                        index_count++;
                    }

                    //close the file in the child proc and exit
                    o_files[i].close();
                    exit(1);

                }
                else{
                    //close the file in the parent proc
                    o_files[i].close();
                }

            }

            //wait for all the child procs to finish
            for(int i = 0; i < numFiles; i++){
                wait(NULL);
            }


            for(int i=0; i<fLineCountSums[numFiles-1]; i++){
                std::cout<<shm[i].line<<std::endl;
            }

            std::cout<<"all childs finish, parent auty"<<std::endl;
            return 1;

        }
        catch(const std::invalid_argument){
            std::cout<<"Must have valid column numbers for the files"<<std::endl;
            return -1;
        }

    }
    std::cerr<<"Not enough arguments: join <file1> <file1 column> <file2> <file2 column> <outputFile>"<<std::endl;
    return -1;
}

//see header file for comments
void Saminal::run(){
    //clear the current screen to make it look prettier
    system("clear");

    //becasue I like saying things in my programs, I guess just to much time alone
    std::cout<<"\n\nGet ready for the best terminal experience of your life.....\n\n\n\n";

    //the good old inintie loops
    while(true){

        std::string command;
        std::vector<std::string> cmd_list;
        //print the pretty command thingy
        std::cout<<std::endl;

        //print the curr wd as the cool starting thingy
        //also make it red cause that looks cool
        printColor(fs::current_path().string(),2);

        //the $ makes it seem like a big boy terminal
        std::cout<<"$ ";

        //get that command from the user
        std::getline(std::cin,command);

        //If they are tired of us, then i guess let them leave
        if(command == "exit"){
            return;
        }

        //parse taht string into a vector list
        cmd_list = parse_args(command);

        if(cmd_list.size() > 0){
            //if its a basic cmd, then execute that little guy
            if(check_cmd_exist(cmd_list.at(0)) == 1){
                exec_basic(cmd_list);
                continue;
            }
            std::cerr<<"Commmand Doesn't exist"<<std::endl;
            continue;
        }


    }
}



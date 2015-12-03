#include "../include/saminal.hpp"

namespace fs = boost::filesystem;



    // fs::path full_path( fs::initial_path<fs::path>() );
    // cout<<full_path<<endl;
    // cout<<full_path.filename()<<endl;
    // cout<<fs::is_directory(full_path.parent_path())<<endl;


Saminal::Saminal(){
    homeDir = fs::path(getenv("HOME"));
    if(!fs::exists(homeDir) && !fs::is_directory(homeDir)){
         throw std::runtime_error("Error while starting home directory, this is a big issue");
    }
}

void Saminal::printColor(std::string text,int color){
    std::string colorTable[3] = {"\033[1;33m","\033[1;36m","\033[1;31m"};
    if(color >= 0 && color < (sizeof(colorTable)/sizeof(*colorTable))){
        std::cout<<colorTable[color]<<text<<"\033[0m";
    }

}

int Saminal::ls(){
    if(fs::exists(fs::current_path())){
        fs::directory_iterator end_iter;
        int lineCount = 0;
        for(fs::directory_iterator iter(fs::current_path()); iter != end_iter; iter++){
            if(iter->path().filename().string()[0] != '.'){
                lineCount++;
                if(fs::is_directory(iter->path())){
                    printColor(iter->path().filename().string(),1);
                }
                else{
                     printColor(iter->path().filename().string(),0);
                }

                std::cout<<"   ";
                if(lineCount >= 5){
                    lineCount = 0;
                    std::cout<<std::endl;
                }
            }
        }
        return 1;
    }
    std::cerr<<"currDir not correct for ls command"<<std::endl;
    return -1;
}

int Saminal::cd(std::string args){
    if(!args.empty()){
        fs::path errorPath("");

        if(args[0] == '~'){
            fs::path newPath(std::string(homeDir.string()) + args.erase(0,1));
            if(fs::exists(newPath) && fs::is_directory(newPath)){
                fs::current_path(newPath);
                return 1;
            }
            errorPath = newPath;
        }
        else{
            fs::path relative_move(args);
            try{
                fs::path newCurrDir = fs::canonical(relative_move,fs::current_path());
                if(fs::is_directory(newCurrDir)){
                    fs::current_path(newCurrDir);
                    return 1;
                }
                errorPath = newCurrDir;
            }
            catch(...){
                std::cerr<<"Path "<<relative_move.string()<<" either doesn't exist or is not a directory"<<std::endl;
                return -1;
            }
        }
        std::cerr<<"Path "<<errorPath.string()<<" either doesn't exist or is not a directory"<<std::endl;
        return -1;
    }
    std::cerr<<"Must pass path to the cd command"<<std::endl;
    return -1;
}

int Saminal::pwd(){
    std::cout<<fs::current_path().string()<<std::endl;
    return 1;
}

int Saminal::cat(std::string file){
    if(!file.empty()){
        std::string line;
        std::ifstream myfile(file);

        if(myfile.is_open()){
            while(std::getline(myfile,line)){
               std::cout<<line<<std::endl;
            }
            return 1;
        }
        std::cerr<<"File does not exist"<<std::endl;
        return -1;
    }
    std::cerr<<"File was empty"<<std::endl;
    return -1;
}
std::string* Saminal::parse_args(std::string args){
    return nullptr;
}
int Saminal::exec_basic(std::string* args){
    return -1;
}
int Saminal::exec_added(std::string* args){
    return -1;
}

int Saminal::check_cmd_exit(std::string cmd){
    for(std::string bcmd : basic_cmds){
        if(bcmd == cmd){
            return 1;
        }
    }
    return 0;
}

void Saminal::run(){
    std::cout<<"\n\nGet ready for the best terminal experience of your life.....\n\n\n\n";
    while(true){
        std::string command;
        printColor(fs::current_path().string(),2);
        std::cout<<"$ ";
        std::cin>>command;
        if(command == "exit"){
            return;
        }
    }
}



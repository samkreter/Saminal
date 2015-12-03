#include "../include/saminal.hpp"

namespace fs = boost::filesystem;

typedef int (Saminal::*FnPtr)(std::vector<std::string>);

    // fs::path full_path( fs::initial_path<fs::path>() );
    // cout<<full_path<<endl;
    // cout<<full_path.filename()<<endl;
    // cout<<fs::is_directory(full_path.parent_path())<<endl;


Saminal::Saminal(){
    b_cmd_map["ls"] = &Saminal::ls;
    b_cmd_map["pwd"] = &Saminal::pwd;
    b_cmd_map["cat"] = &Saminal::cat;
    b_cmd_map["cd"] = &Saminal::cd;

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

int Saminal::ls(std::vector<std::string> args){
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

int Saminal::cd(std::vector<std::string> args){
    if(!args.at(0).empty()){
        fs::path errorPath("");
        std::string sArg = args.at(0);
        if(sArg[0] == '~'){
            fs::path newPath(std::string(homeDir.string()) + sArg.erase(0,1));
            if(fs::exists(newPath) && fs::is_directory(newPath)){
                fs::current_path(newPath);
                return 1;
            }
            errorPath = newPath;
        }
        else{
            fs::path relative_move(sArg);
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

int Saminal::pwd(std::vector<std::string> args){
    std::cout<<fs::current_path().string()<<std::endl;
    return 1;
}

int Saminal::cat(std::vector<std::string> args){
    if(!args.at(0).empty()){
        std::string line;
        std::ifstream myfile(args.at(0));
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
std::vector<std::string> Saminal::parse_args(std::string args){
    std::vector<std::string> tokens;
    if(!args.empty()){

        boost::algorithm::split(tokens, args, boost::is_any_of(" "));
        return tokens;
    }
    std::cerr<<"Must pass string to parsers"<<std::endl;
    //return an empty vector for an error
    return tokens;
}

int Saminal::exec_basic(std::vector<std::string> args){
    return -1;
}
int Saminal::exec_added(std::vector<std::string> args){
    return -1;
}

int Saminal::check_cmd_exist(std::string cmd){
    for(auto bcmd : b_cmd_map){
        if(bcmd.first == cmd){
            return 1;
        }
    }
    return 0;
}

void Saminal::run(){
    std::cout<<"\n\nGet ready for the best terminal experience of your life.....\n\n\n\n";
    while(true){
        std::string command;
        std::vector<std::string> cmd_list;
        //print the pretty command thingy
        printColor(fs::current_path().string(),2);
        //the $ makes it seem like a big boy terminal
        std::cout<<"$ ";

        std::cin>>command;
        if(command == "exit"){
            return;
        }
        cmd_list = parse_args(command);
        if(cmd_list.size() > 0){
            if(check_cmd_exist(cmd_list.at(0)) == 1){
                if(exec_basic(cmd_list) > 0){
                    continue;
                }
            }
            std::cerr<<"Commmand Doesn't exist"<<std::endl;
            continue;
        }


    }
}



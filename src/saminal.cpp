#include "../include/saminal.hpp"

namespace fs = boost::filesystem;



    // fs::path full_path( fs::initial_path<fs::path>() );
    // cout<<full_path<<endl;
    // cout<<full_path.filename()<<endl;
    // cout<<fs::is_directory(full_path.parent_path())<<endl;


Saminal::Saminal(){
    currDir = fs::path(getenv("HOME"));
    if(!fs::exists(currDir) && !fs::is_directory(currDir)){
         throw std::runtime_error("Error while starting home directory, this is a big issue");
    }
}

void Saminal::printColor(std::string text,int color){
    std::string colorTable[2] = {"\033[1;31m","\033[1;36m"};
    if(color >= 0 && color < (sizeof(colorTable)/sizeof(*colorTable))){
        std::cout<<colorTable[color]<<text<<"\033[0m";
    }

}

int Saminal::ls(){
    fs::directory_iterator end_iter;
    int lineCount = 0;
    for(fs::directory_iterator iter(this->currDir); iter != end_iter; iter++){
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

    return -1;
}
int Saminal::cd(std::string* args){
    return -1;
}

void Saminal::pwd(){
    fs::path full_path( fs::initial_path<fs::path>() );
    std::cout<<full_path.string()<<std::endl;
}

int Saminal::cat(){
    return -1;
}
std::string* Saminal::parse_args(std::string* args){
    return nullptr;
}
int Saminal::exec_basic(std::string* args){
    return -1;
}
int Saminal::exec_added(std::string* args){
    return -1;
}

void Saminal::run(){
    return;
}



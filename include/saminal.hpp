#ifndef SAMINAL_HPP__
#define SAMINAL_HPP__

class Saminal{

    const std::string basic_cmd[4] = {"ls","cd","pwd","cat"};

    int ls();
    int cd(std::string* args);
    int pwd();
    int cat();
    std::string* parse_args(std::string* args);
    int exec_basic(std::string* args);
    int exec_added(std::string* args);

public:
    void run();
};


#endif
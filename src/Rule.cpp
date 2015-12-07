#include "Rule.h"

Rule::Rule() : name("N/A") {}

Rule::Rule(std::string name, std::vector<std::string> cmd, std::vector<std::string> dependencies) :
        name(name), cmd(cmd), dependencies(dependencies), executed(false), toExecute(false) {}

void Rule::execute(std::map<std::string, Rule*> dictionary, std::string masterComputer) {
    mpi::communicator world;
    //Parcours des dépendances pour demander les fichiers
    for(std::vector<int>::size_type i = 0; i != dependencies.size(); i++) {
        if (dictionary.find(dependencies.at(i)) != dictionary.end() || file_exists(dependencies.at(i))) {
            std::stringstream messageSend;
            messageSend << world.rank() << ";file;" << dependencies.at(i);
            std::cout << "esclave rank " << world.rank() << " envoit " << messageSend.str() << std::endl;
            world.send(0, 0, messageSend.str());
            std::string message;
            world.recv(0, 1, message);
            std::cout << "esclave recoit " << message << std::endl;
            if (message.compare("OK") != 0) {
                std::cout << dependencies.at(i) << " : Non recu" << std::endl;
                exit(1);
            }
        }
    }

  //  #pragma omp for ordered
    for(std::vector<int>::size_type i = 0; i < cmd.size(); i++) {
        std::string exec = cmd.at(i).substr(0, cmd.at(i).find(' '));

        std::string toExec;

        // If it's a local rule or existing file, add ./
        if (dictionary.find(exec) != dictionary.end() || file_exists(exec)) {
            std::stringstream ss;
            ss << "./" << cmd.at(i).c_str();
            toExec = ss.str();
        } else {
            toExec = cmd.at(i);
        }

      //  #pragma omp ordered
        system(toExec.c_str());
    }
    //Envoie de tous les fichiers
    std::stringstream commandSCP;
    commandSCP << "sshpass -p \"admin\" scp -o StrictHostKeyChecking=no " << get_name() << " " << masterComputer << ":";
    std::cout << commandSCP.str() << std::endl;
    system(commandSCP.str().c_str());
    //Suppression des fichiers
    //system("rm *");
    executed = true;
}

std::string Rule::get_name() {
    return this->name;
}

std::vector<std::string> Rule::get_cmd() {
    return this->cmd;
}

std::vector<std::string> Rule::get_dependencies() {
    return this->dependencies;
}

bool Rule::has_dependencies() {
    return (this->dependencies.size() != 0);
}

bool Rule::has_been_executed() {
    return executed;
}

bool Rule::alreadyExists() {
    return file_exists(name);
}

void Rule::addParent(std::string pereName) {
    //std::cout << name << " : Add pere : " << pereName << std::endl;
    this->parents.push_back(pereName);
}

void Rule::addChild(std::string childName) {
    //std::cout << name << " : Add child : " << childName << std::endl;
    this->childs.push_back(childName);
}

std::vector<std::string> Rule::get_parents() {
    return parents;
}

void Rule::removeChild(std::string childName) {
    for( std::vector<std::string>::iterator iter = childs.begin(); iter != childs.end(); ++iter )
    {
        if(childName.compare(*iter) == 0)
        {
            childs.erase(iter);
            break;
        }
    }
}

void Rule::removeParent(std::string parentName) {
    for( std::vector<std::string>::iterator iter = parents.begin(); iter != parents.end(); ++iter )
    {
        if(parentName.compare(*iter) == 0)
        {
            parents.erase(iter);
            break;
        }
    }
}

bool Rule::have_childs() {
    //std::cout << "Nombre fils : " << childs.size() << std::endl;
    return childs.size() != 0;
}

bool Rule::have_parents() {
    return parents.size() != 0;
}

void Rule::printRule() {
    for( std::vector<std::string>::iterator iter = childs.begin(); iter != childs.end(); ++iter )
    {
        std::cout << *iter << std::endl;
    }
    for( std::vector<std::string>::iterator iter = parents.begin(); iter != parents.end(); ++iter )
    {
        std::cout << *iter << std::endl;
    }
}
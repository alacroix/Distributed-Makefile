//
// Created by robin on 05/12/15.
//

#ifndef DISTRIBUTED_MAKEFILE_QUEUEDOABLE_H
#define DISTRIBUTED_MAKEFILE_QUEUEDOABLE_H

#include <iostream>
#include <vector>

class QueueDoable {
public:
    QueueDoable();

    void pushDoable(std::string nomFile);
    std::string popDoable();
    void printDoable();
    bool empty();
    std::vector<std::string> getQueueDoable();
private:
    //Pour gérer une file unique de nom de regle faisable
    std::vector<std::string> queueDoable;

};

#endif //DISTRIBUTED_MAKEFILE_QUEUEDOABLE_H

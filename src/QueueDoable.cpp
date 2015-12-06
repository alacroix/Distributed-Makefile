#include "QueueDoable.h"

QueueDoable::QueueDoable() {}

void QueueDoable::printDoable() {
    std::cout << queueDoable.size() << std::endl;
    std::vector<std::string>::iterator it;
    for (it = queueDoable.begin(); it != queueDoable.end(); ++it) {
        std::cout << *it << std::endl;
    }
}

void QueueDoable::pushDoable(std::string nomFile) {
    for (std::vector<std::string>::iterator it = queueDoable.begin(); it != queueDoable.end(); ++it)
    {
        if (nomFile.compare(*it) == 0) { //L'element existe deja, on ne l'ajoute pas
            return;
        }
    }
    queueDoable.push_back(nomFile);
}

std::string QueueDoable::popDoable() {
    std::string rule = queueDoable.back();
    queueDoable.pop_back();
    return rule;
}

bool QueueDoable::empty() {
    return queueDoable.empty();
}

std::vector<std::string> QueueDoable::getQueueDoable() {
    return queueDoable;
}

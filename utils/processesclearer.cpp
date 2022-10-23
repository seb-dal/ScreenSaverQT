#include "processesclearer.h"

#include "utils/utilMacro.h"

QList<QProcess*> ProcessesClearer::processes;

void ProcessesClearer::add(QProcess* p) { processes.push_back(p); }

void ProcessesClearer::clearAll()
{
    for (auto p = processes.begin(); p != processes.end(); p++) {
        if (*p) {
            (*p)->kill();
            deleteIfReq((*p));
        }
    }
    processes.clear();
}

#include "processesclearer.h"

#include "utils/utilMacro.h"

QList<QProcess*> ProcessesClearer::processes;

void ProcessesClearer::add(QProcess* p) { processes.push_back(p); }

void ProcessesClearer::clearAll()
{
    for (QProcess* p : processes) {
        p->kill();
        deleteIfReq(p);
    }
    processes.clear();
}

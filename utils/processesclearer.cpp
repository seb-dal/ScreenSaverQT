#include "processesclearer.h"

QList<QProcess*> ProcessesClearer::processes;

void ProcessesClearer::add(QProcess* p) { processes.push_back(p); }

void ProcessesClearer::clearAll()
{
    for (QProcess* p : processes) {
        p->kill();
        delete p;
    }
    processes.clear();
}

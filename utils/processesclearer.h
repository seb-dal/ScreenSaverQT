#ifndef PROCESSESCLEARER_H
#define PROCESSESCLEARER_H

#include <QList>
#include <QProcess>

class ProcessesClearer {
public:
    static void add(QProcess* p);

    static void clearAll();

private:
    static QList<QProcess*> processes;
};

#endif // PROCESSESCLEARER_H

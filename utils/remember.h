#ifndef REMEMBER_H
#define REMEMBER_H

#include <QString>
#include <QVariant>

class Remember {
public:
    static void initialize();
    static void saveData();

    static void put(const QString name, const QVariant& val);

    static QVariant get(const QString name);

    template <typename T>
    static T get_(const QString name, T defaultValue)
    {
        QVariant v = get(name);
        if (!v.isValid() || !v.canConvert<T>() || v.type() != QVariant(defaultValue).type()) {
            put(name, defaultValue);
            return defaultValue;
        }

        T res = v.value<T>();

        return res;
    }

private:
    static QHash<QString, QVariant> values;
};

#endif // REMEMBER_H

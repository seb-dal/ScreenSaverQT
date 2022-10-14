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
        // Verification if value convertable to output
        if (!v.isValid() || !v.canConvert<T>()) {
            put(name, defaultValue);
            return defaultValue;
        }

        // Verification convertion from QString to ANY give True but may not necessary be convertable
        QVariant v2 = v;
        bool convert = v2.convert(QVariant(defaultValue).type());
        if (!convert) {
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

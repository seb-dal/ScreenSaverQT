#ifndef OPTIONS_H
#define OPTIONS_H

#include <QDialog>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Options;
}
QT_END_NAMESPACE

struct option_vars {
};

class Options : public QDialog {
    Q_OBJECT
public:
    Options(QWidget* parent = nullptr);
    ~Options();

protected:
    void load();
public slots:
    void save();
    void translate();

    void validate();

private:
    Ui::Options* ui;
    option_vars temp;
};

#endif // OPTIONS_H

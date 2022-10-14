#ifndef SWITCHBUTTON_H
#define SWITCHBUTTON_H

#include <QPushButton>
#include <QWidget>

class SwitchButton : public QPushButton {
    Q_OBJECT
public:
    SwitchButton(QWidget* parent = nullptr);
    ~SwitchButton();
public slots:
    void Translate();
};

#endif // SWITCHBUTTON_H

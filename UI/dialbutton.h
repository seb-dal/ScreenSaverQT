#ifndef DIALBUTTON_H
#define DIALBUTTON_H

#include <QWidget>

namespace Ui {
class DialButton;
}

class DialButton : public QWidget {
    Q_OBJECT
public:
    explicit DialButton(QString title, QWidget* parent = nullptr);
    ~DialButton();

signals:
    void valueChange(int);

private slots:
    void value(int v);

protected:
    void resizeEvent(QResizeEvent*) override;

private:
    Ui::DialButton* ui;
};

#endif // DIALBUTTON_H

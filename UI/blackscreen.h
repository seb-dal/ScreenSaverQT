#ifndef BLACKSCREEN_H
#define BLACKSCREEN_H

#include <QDialog>
#include <QWidget>

class BlackScreen : public QDialog {
    Q_OBJECT
public:
    BlackScreen();
    ~BlackScreen();

protected:
    void mouseReleaseEvent(QMouseEvent*) override;
};

#endif // BLACKSCREEN_H

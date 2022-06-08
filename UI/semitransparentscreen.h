#ifndef SEMITRANSPARENTSCREEN_H
#define SEMITRANSPARENTSCREEN_H

#include <QLabel>
#include <QWidget>

class SemiTransparentScreen : public QWidget {
    Q_OBJECT
public:
    SemiTransparentScreen(QWidget* parent);
    ~SemiTransparentScreen();

public slots:
    void setTransparenty(int tr);

private:
    QLabel* frame;
};

#endif // SEMITRANSPARENTSCREEN_H

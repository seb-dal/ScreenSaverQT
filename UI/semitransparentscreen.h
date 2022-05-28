#ifndef SEMITRANSPARENTSCREEN_H
#define SEMITRANSPARENTSCREEN_H

#include <QLabel>
#include <QWidget>

class SemiTransparentScreen : public QWidget {
public:
    SemiTransparentScreen(QWidget* parent);

public slots:
    void setTransparenty(int tr);

private:
    QLabel* frame;
};

#endif // SEMITRANSPARENTSCREEN_H

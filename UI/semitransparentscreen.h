#ifndef SEMITRANSPARENTSCREEN_H
#define SEMITRANSPARENTSCREEN_H

#include <QLabel>
#include <QWidget>

class SemiTransparentScreen : public QWidget {
    Q_OBJECT
public:
    SemiTransparentScreen();
    ~SemiTransparentScreen();

    static int getTransparency_save();

public slots:
    void setTransparenty(int tr);

private:
    QLabel* frame;
    static int transparency_save;
};

#endif // SEMITRANSPARENTSCREEN_H

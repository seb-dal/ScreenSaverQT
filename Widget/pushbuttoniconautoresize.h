#ifndef PUSHBUTTONIMAGEAUTOMATICRESIZE_H
#define PUSHBUTTONIMAGEAUTOMATICRESIZE_H

#include <QPushButton>

class PushButtonIconAutoResize : public QPushButton
{
    Q_OBJECT

public:
    PushButtonIconAutoResize(const QString &text, QWidget *parent=0);
    ~PushButtonIconAutoResize();

private:
    void paintEvent(QPaintEvent *);

    int pad;
    int minSize;
};

#endif // PUSHBUTTONIMAGEAUTOMATICRESIZE_H

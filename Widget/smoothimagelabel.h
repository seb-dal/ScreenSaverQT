#ifndef SMOOTHIMAGELABEL_H
#define SMOOTHIMAGELABEL_H

#include <QLabel>

class SmoothImageLabel : public QLabel {
    Q_OBJECT
public:
    SmoothImageLabel(QWidget* parent);

    void setCurrent(QImage* pix);

protected:
    void paintEvent(QPaintEvent*) override;

private:
    QImage* current = nullptr;
};

#endif // SMOOTHIMAGELABEL_H

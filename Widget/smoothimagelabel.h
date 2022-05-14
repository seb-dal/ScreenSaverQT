#ifndef SMOOTHIMAGELABEL_H
#define SMOOTHIMAGELABEL_H

#include <QLabel>

class SmoothImageLabel : public QLabel {
    Q_OBJECT
public:
    SmoothImageLabel(QWidget* parent);

protected:
    void paintEvent(QPaintEvent*) override;
};

#endif // SMOOTHIMAGELABEL_H

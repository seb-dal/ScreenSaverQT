#ifndef TIMERBUTTON_PUSHBUTTON_H
#define TIMERBUTTON_PUSHBUTTON_H

#include "smoothimagelabel.h"

#include "model/TimerButton_DOT.h"
#include <QDateTime>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

enum TBPB_state {
    normal,
    pressed,
    actif,
};

class TimerButton_PushButton : public QPushButton {
public:
    TimerButton_PushButton(QWidget* parent = nullptr);
    ~TimerButton_PushButton();

    bool isActif() const;

    void setNumberAfterDot(TimerButton_AFTER_DOT newDiv);

    void setBt_action(const std::function<void()>& newBt_action);

    void setMaxTimer(int newMax);

    static void initialize();
public slots:
    void onPressed();

    void onReleased();

    void setActif(bool actif);

    void updateActif();

    void updateText();

    void updateIcon(bool force = false);

protected:
    void resizeEvent(QResizeEvent*) override;

private:
    bool actif = false;
    int remain;
    int max = 5;

    TimerButton_AFTER_DOT nbNumber = ZERO;
    int factor = 1;
    int timeInterval = 1000;

    QTimer* timer;

    QVBoxLayout* MainLayout;
    SmoothImageLabel* BT_icon;
    QDateTime resize;
    int sizeIcon;
    int currentIcon = 0;
    int appliedIcon = -1;

    QVBoxLayout* layout;
    QLabel* textBT;

    std::function<void()> bt_action = []() {};

    static QPixmap* icon_normal;
    static QPixmap* icon_normal_pressed;
    static QPixmap* icon_actif;
    static QPixmap* icon_actif_pressed;
};

#endif // TIMERBUTTON_PUSHBUTTON_H

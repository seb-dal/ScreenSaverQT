#ifndef TIMERBUTTON_PUSHBUTTON_H
#define TIMERBUTTON_PUSHBUTTON_H

#include "model/TimerButton_DOT.h"
#include "smoothimagelabel.h"
#include <QDateTime>
#include <QImage>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

enum TBPB_state {
    normal,
    pressed,
    actif,
};

class TimerButton_PushButton : public QPushButton {
    Q_OBJECT
public:
    TimerButton_PushButton(QWidget* parent = nullptr);
    ~TimerButton_PushButton();

    bool isActif() const;

    void setNumberAfterDot(TimerButton_AFTER_DOT newDiv);

    void setBt_action(const std::function<void()>& newBt_action);

    void setMaxTimer(int newMax_ms);

    static void initialize();
    static void deleteStatic();
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
    int remainTime;
    int maxTime = 5000;

    TimerButton_AFTER_DOT nbNumber = ZERO;
    int factor = 1;
    int timeInterval = 1000;
    int compensation = 1;

    QTimer* timer;

    QVBoxLayout* MainLayout;
    SmoothImageLabel* BT_icon;
    QDateTime lastResize;
    int sizeIcon;
    int currentIcon = 0;
    int appliedIcon = -1;

    QVBoxLayout* layout;
    QLabel* textBT;

    std::function<void()> bt_action = []() {};

    static QImage* icon_normal;
    static QImage* icon_normal_pressed;
    static QImage* icon_actif;
    static QImage* icon_actif_pressed;
};

#endif // TIMERBUTTON_PUSHBUTTON_H

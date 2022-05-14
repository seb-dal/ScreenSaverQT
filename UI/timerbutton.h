#ifndef TIMERBUTTON_H
#define TIMERBUTTON_H

#include <QTimer>
#include <QWidget>

#include <model/TimerButton_DOT.h>

namespace Ui {
class TimerButton;
}

class TimerButton : public QWidget {
    Q_OBJECT

public:
    explicit TimerButton(QString title, QWidget* parent = nullptr);
    ~TimerButton();

    void setFunction(const std::function<void()>& newBt_action);
    void setNumberAfterDot(TimerButton_AFTER_DOT newDiv);
    void setMaxTimer(int newMax);

public slots:
    void updateButton();

protected:
    void resizeEvent(QResizeEvent*) override;

private:
    Ui::TimerButton* ui;
};

#endif // TIMERBUTTON_H

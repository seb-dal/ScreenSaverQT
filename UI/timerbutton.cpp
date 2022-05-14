#include "timerbutton.h"
#include "timerbutton_ui.h"

TimerButton::TimerButton(QString title, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::TimerButton)
{
    ui->setupUi(this);
    ui->Title->setText(title);

    QFont f(ui->Title->font());
    f.setBold(true);
    ui->Title->setFont(f);
}

TimerButton::~TimerButton()
{
    delete ui;
}

void TimerButton::resizeEvent(QResizeEvent*)
{
    int size = qMin(this->sizeHint().height(), this->sizeHint().width());
    float ratio = size / 200.f;

    QFont f(ui->Title->font());
    f.setPixelSize(44 * ratio);
    ui->Title->setFont(f);
    //ui->Title->setp
}

void TimerButton::setFunction(const std::function<void()>& newBt_action)
{
    ui->bt->setBt_action(newBt_action);
}

void TimerButton::setNumberAfterDot(TimerButton_AFTER_DOT newDiv)
{
    ui->bt->setNumberAfterDot(newDiv);
}

void TimerButton::setMaxTimer(int newMax)
{
    ui->bt->setMaxTimer(newMax);
}

void TimerButton::updateButton()
{
    ui->bt->updateIcon(true);
}

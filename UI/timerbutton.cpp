#include "timerbutton.h"
#include "timerbutton_ui.h"

#include "utils/appConst.h"
#include "utils/util.h"
#include "utils/utilMacro.h"

TimerButton::TimerButton(QString title, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::TimerButton)
{
    ui->setupUi(this);
    ui->Title->setText(title);
}

TimerButton::~TimerButton() { deleteIfReq(ui); }

void TimerButton::resizeEvent(QResizeEvent*)
{
    float ratio = util::computeRatio(this);
    util::setFontSize(ui->Title, appConst::sizeTitleText * ratio);
}

void TimerButton::setFunction(const std::function<void()>& newBt_action) { ui->bt->setBt_action(newBt_action); }

void TimerButton::setNumberAfterDot(TimerButton_AFTER_DOT newDiv) { ui->bt->setNumberAfterDot(newDiv); }

void TimerButton::setMaxTimer(int newMax) { ui->bt->setMaxTimer(newMax); }

void TimerButton::updateButton() { ui->bt->updateIcon(true); }

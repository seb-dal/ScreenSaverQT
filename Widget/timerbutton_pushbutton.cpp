#include "timerbutton_pushbutton.h"

#include "UI/ui_template.h"
#include "utils/appConst.h"
#include "utils/util.h"
#include <QIcon>
#include <QPaintEngine>
#include <QResizeEvent>
#include <QString>
#include <QStylePainter>
#include <QTimer>

QPixmap* TimerButton_PushButton::icon_normal;
QPixmap* TimerButton_PushButton::icon_normal_pressed;
QPixmap* TimerButton_PushButton::icon_actif;
QPixmap* TimerButton_PushButton::icon_actif_pressed;

void TimerButton_PushButton::initialize()
{
    TimerButton_PushButton::icon_normal = new QPixmap("://img/bt_normal.png");

    TimerButton_PushButton::icon_normal_pressed = new QPixmap("://img/bt_actif.png");

    TimerButton_PushButton::icon_actif = new QPixmap("://img/bt_actif.png");

    TimerButton_PushButton::icon_actif_pressed = new QPixmap("://img/bt_actif_pressed.png");
}

TimerButton_PushButton::TimerButton_PushButton(QWidget* parent)
    : QPushButton("", parent)
{
    this->setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));
    this->setContentsMargins(0, 0, 0, 0);
    this->setFlat(true);

    componentCreate(MainLayout, QVBoxLayout, this);
    {
        MainLayout->setContentsMargins(0, 0, 0, 0);

        componentCreate(BT_icon, SmoothImageLabel, this);
        {
            BT_icon->setText("");
            BT_icon->setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));
            BT_icon->setAlignment(Qt::AlignmentFlag::AlignCenter);
            MainLayout->addWidget(BT_icon);

            componentCreate(layout, QVBoxLayout, BT_icon);
            {
                layout->setContentsMargins(0, 0, 0, 0);

                componentCreate(textBT, QLabel, BT_icon);
                {
                    layout->addWidget(textBT);
                    textBT->setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding));
                    textBT->setAlignment(Qt::AlignmentFlag::AlignCenter);

                    util::setFontBold(this->textBT, true);
                }
            }
        }
    }

    timer = new QTimer(this);
    {
        QObject::connect(timer, &QTimer::timeout, this, &TimerButton_PushButton::updateActif);
    }

    QObject::connect(this, &QPushButton::pressed, this, &TimerButton_PushButton::onPressed);
    QObject::connect(this, &QPushButton::released, this, &TimerButton_PushButton::onReleased);
}

TimerButton_PushButton::~TimerButton_PushButton()
{
    delete textBT;
    delete layout;
    delete timer;
}

bool TimerButton_PushButton::isActif() const { return actif; }
void TimerButton_PushButton::setBt_action(const std::function<void()>& newBt_action) { bt_action = newBt_action; }
void TimerButton_PushButton::setMaxTimer(int newMax) { maxTime = newMax; }

void TimerButton_PushButton::resizeEvent(QResizeEvent* /*event*/)
{
    QSize s = this->size();
    sizeIcon = qMin(s.height(), s.width());
    updateIcon();

    float ratio = util::computeRatio(this);
    util::setFontSize(this->textBT, appConst::sizeButtonText * ratio);
}

void TimerButton_PushButton::setNumberAfterDot(TimerButton_AFTER_DOT newDiv)
{
    nbNumber = newDiv;
    int v = qMin(qMax((int)newDiv, 0), 2);

    factor = util::powTenInt(v);
    timeInterval = util::powTenInt(3 - v);
}

void TimerButton_PushButton::onPressed()
{
    currentIcon = (isActif() ? TBPB_state::actif : TBPB_state::normal) | TBPB_state::pressed;

    updateIcon();
}

void TimerButton_PushButton::onReleased()
{
    currentIcon = (isActif() ? TBPB_state::normal : TBPB_state::actif);

    updateIcon();
    setActif(!isActif());
}

void TimerButton_PushButton::setActif(bool actif)
{
    this->actif = actif;
    if (actif) {
        remainTime = maxTime * factor;
        timer->start(timeInterval);
    } else {
        timer->stop();
    }
    updateText();
}

void TimerButton_PushButton::updateActif()
{
    if (remainTime > 0) {
        --remainTime;
    } else {
        timer->stop();
        actif = false;
        currentIcon = TBPB_state::normal;
        updateIcon();

        this->bt_action();
    }
    updateText();
}

void TimerButton_PushButton::updateText()
{
    if (isActif()) {
        if (factor == 1) {
            textBT->setText(QString::number(remainTime));
        } else {
            textBT->setText(QString::number(remainTime / (double(factor)), 'f', (int)nbNumber));
        }
    } else {
        textBT->setText("");
    }
}

void TimerButton_PushButton::updateIcon(bool force)
{
    QDateTime now = QDateTime::currentDateTime();
    if (!force) {
        qint64 diff = lastResize.msecsTo(now);
        static const qint64 minTime = 100;
        if (currentIcon == appliedIcon && diff < minTime) {
            return;
        }
    }
    lastResize = now;
    appliedIcon = currentIcon;

    QSize s = this->size();
    sizeIcon = qMin(s.height(), s.width());
    QPixmap* current;
    switch (currentIcon) {
    case TBPB_state::normal:
        current = icon_normal;
        break;

    case TBPB_state::normal | TBPB_state::pressed:
        current = icon_normal_pressed;
        break;

    case TBPB_state::actif:
        current = icon_actif;
        break;

    case TBPB_state::actif | TBPB_state::pressed:
        current = icon_actif_pressed;
        break;

    default:
        current = nullptr;
    }

    if (current != nullptr)
        BT_icon->setPixmap(current->scaled(QSize(sizeIcon, sizeIcon), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

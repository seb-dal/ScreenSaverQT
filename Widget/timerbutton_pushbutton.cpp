#include "timerbutton_pushbutton.h"

#include "UI/ui_template.h"
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
    sizeIcon = qMin(this->sizeHint().height(), this->sizeHint().width());
    float ratio = sizeIcon / 200.f;

    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //this->setIcon(QIcon("://img/bt_normal.png"));
    this->setFlat(true);

    componentCreate(MainLayout, QVBoxLayout, this);
    {
        MainLayout->setContentsMargins(0, 0, 0, 0);

        componentCreate(BT_icon, SmoothImageLabel, this);
        {
            BT_icon->setText("");
            BT_icon->setAlignment(Qt::AlignmentFlag::AlignCenter);
            MainLayout->addWidget(BT_icon);

            componentCreate(layout, QVBoxLayout, BT_icon);
            {
                layout->setContentsMargins(0, 0, 0, 0);

                componentCreate(textBT, QLabel, BT_icon);
                {
                    layout->addWidget(textBT);
                    textBT->setAlignment(Qt::AlignmentFlag::AlignCenter);

                    QFont f(this->textBT->font());
                    {
                        f.setBold(true);
                        f.setPointSize(44 * ratio);
                        this->textBT->setFont(f);
                    }
                }
            }
        }
    }

    timer = new QTimer(this);
    {
        QObject::connect(timer, &QTimer::timeout, [&] { this->updateActif(); });
    }

    QObject::connect(this, &QPushButton::pressed, [&] { onPressed(); });
    QObject::connect(this, &QPushButton::released, [&] { onReleased(); });
}

TimerButton_PushButton::~TimerButton_PushButton()
{
    delete textBT;
    delete layout;
    delete timer;
}

bool TimerButton_PushButton::isActif() const
{
    return actif;
}
void TimerButton_PushButton::setBt_action(const std::function<void()>& newBt_action)
{
    bt_action = newBt_action;
}
void TimerButton_PushButton::setMaxTimer(int newMax)
{
    max = newMax;
}

void TimerButton_PushButton::resizeEvent(QResizeEvent* /*event*/)
{
    QSize s = this->size();
    sizeIcon = qMin(s.height(), s.width());
    updateIcon();
    float ratio = sizeIcon / 200.f;

    QFont f(this->textBT->font());
    f.setPointSize(44 * ratio);
    this->textBT->setFont(f);
}

static int powTenInt(int nb)
{
    int x = 1;
    for (int i = 0; i < nb; ++i)
        x *= 10;
    return x;
}

void TimerButton_PushButton::setNumberAfterDot(TimerButton_AFTER_DOT newDiv)
{
    nbNumber = newDiv;
    int v = qMin(qMax((int)newDiv, 0), 2);

    factor = powTenInt(v);
    timeInterval = powTenInt(3 - v);
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
        remain = max * factor;
        timer->start(timeInterval);
    } else {
        timer->stop();
    }
    updateText();
}

void TimerButton_PushButton::updateActif()
{
    if (remain > 0) {
        --remain;
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
            textBT->setText(QString::number(remain));
        } else {
            textBT->setText(QString::number(remain / (double(factor)), 'f', (int)nbNumber));
        }
    } else {
        textBT->setText("");
    }
}

void TimerButton_PushButton::updateIcon(bool force)
{
    QDateTime now = QDateTime::currentDateTime();
    if (!force) {
        qint64 diff = resize.msecsTo(now);
        static const qint64 minTime = 100;
        if (currentIcon == appliedIcon && diff < minTime) {
            return;
        }
    }
    resize = now;
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

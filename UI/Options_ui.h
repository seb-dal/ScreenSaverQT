#ifndef OPTIONS_UI_H
#define OPTIONS_UI_H

#include "ui_template.h"
#include "utils/appConst.h"
#include "utils/util.h"

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

#include "Widget/switchbutton.h"

QT_BEGIN_NAMESPACE

class Ui_Options {
    friend class Options;
    QVBoxLayout* verticalLayout;
    QGridLayout* OtherLayout;
    QLabel* TimeBeforeAction_label;
    QLabel* pn_label;
    QLabel* hibernate_label;
    QLabel* hideAfter_label;
    QHBoxLayout* horizontalLayout_2;
    QFrame* line;
    QGridLayout* gridLayout;
    QLabel* standby_label;
    QLabel* screenOff_label;
    QLabel* BlackScreen_label;
    QLabel* OpacityScreen_label;
    QLabel* RC_label;
    QFrame* line_2;
    QGridLayout* gridLayout_2;
    QLabel* lang_label;
    QHBoxLayout* horizontalLayout;

protected:
    QSpinBox* TimeBeforeAction_spinBox;
    SwitchButton* hideAfter_pushButton;
    QRadioButton* pn_0;
    QRadioButton* pn_1;
    QRadioButton* pn_2;
    SwitchButton* hibernate_pushButton;
    SwitchButton* OpacityScreen_pushButton;
    SwitchButton* BlackScreen_pushButton;
    SwitchButton* screenOff_pushButton;
    SwitchButton* standby_pushButton;
    SwitchButton* RC_pushButton;
    QComboBox* Lang_comboBox;

    QPushButton* ok;
    QPushButton* cancel;

#define Separator(NAME, LAYOUT, PARENT)       \
    componentCreate(NAME, QFrame, PARENT);    \
    {                                         \
        NAME->setFrameShape(QFrame::HLine);   \
        NAME->setFrameShadow(QFrame::Sunken); \
    }                                         \
    LAYOUT->addWidget(NAME);

public:
    void setupUi(QDialog* parent)
    {
        if (parent->objectName().isEmpty())
            parent->setObjectName(QString::fromUtf8("Options"));
        parent->resize(360, 440);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(parent->sizePolicy().hasHeightForWidth());
        parent->setSizePolicy(sizePolicy);

        componentCreate(verticalLayout, QVBoxLayout, parent);
        {
            componentCreate(OtherLayout, QGridLayout, nullptr);
            {
                {
                    componentCreate(TimeBeforeAction_label, QLabel, parent);
                    OtherLayout->addWidget(TimeBeforeAction_label, 0, 0, 1, 1);

                    componentCreate(TimeBeforeAction_spinBox, QSpinBox, parent);
                    {
                        TimeBeforeAction_spinBox->setSuffix(QString::fromUtf8(" sec"));
                        TimeBeforeAction_spinBox->setMinimum(0);
                        TimeBeforeAction_spinBox->setMaximum(2147483647);
                    }
                    OtherLayout->addWidget(TimeBeforeAction_spinBox, 0, 1, 1, 1);
                }
                {
                    componentCreate(pn_label, QLabel, parent);
                    OtherLayout->addWidget(pn_label, 1, 0, 1, 1);

                    componentCreate(horizontalLayout_2, QHBoxLayout, nullptr);
                    {
                        componentCreate(pn_0, QRadioButton, parent);
                        {
                            pn_0->setText("X");
                        }
                        horizontalLayout_2->addWidget(pn_0);

                        componentCreate(pn_1, QRadioButton, parent);
                        {
                            pn_1->setText("X.X");
                        }
                        horizontalLayout_2->addWidget(pn_1);

                        componentCreate(pn_2, QRadioButton, parent);
                        {
                            pn_2->setText("X.XX");
                        }
                        horizontalLayout_2->addWidget(pn_2);
                    }
                    OtherLayout->addLayout(horizontalLayout_2, 1, 1, 1, 1);
                }
                {
                    componentCreate(hideAfter_label, QLabel, parent);
                    OtherLayout->addWidget(hideAfter_label, 2, 0, 1, 1);

                    componentCreate(hideAfter_pushButton, SwitchButton, parent);
                    OtherLayout->addWidget(hideAfter_pushButton, 2, 1, 1, 1);
                }
                {
                    componentCreate(hibernate_label, QLabel, parent);
                    OtherLayout->addWidget(hibernate_label, 3, 0, 1, 1);

                    componentCreate(hibernate_pushButton, SwitchButton, parent);
                    OtherLayout->addWidget(hibernate_pushButton, 3, 1, 1, 1);
                }
            }
            verticalLayout->addLayout(OtherLayout);

            Separator(line, verticalLayout, parent);

            componentCreate(gridLayout, QGridLayout, nullptr);
            {
                {
                    componentCreate(standby_label, QLabel, parent);
                    gridLayout->addWidget(standby_label, 0, 0, 1, 1);

                    componentCreate(standby_pushButton, SwitchButton, parent);
                    gridLayout->addWidget(standby_pushButton, 0, 1, 1, 1);
                }
                {
                    componentCreate(screenOff_label, QLabel, parent);
                    gridLayout->addWidget(screenOff_label, 1, 0, 1, 1);

                    componentCreate(screenOff_pushButton, SwitchButton, parent);
                    gridLayout->addWidget(screenOff_pushButton, 1, 1, 1, 1);
                }
                {
                    componentCreate(BlackScreen_label, QLabel, parent);
                    gridLayout->addWidget(BlackScreen_label, 2, 0, 1, 1);

                    componentCreate(BlackScreen_pushButton, SwitchButton, parent);
                    gridLayout->addWidget(BlackScreen_pushButton, 2, 1, 1, 1);
                }
                {
                    componentCreate(OpacityScreen_label, QLabel, parent);
                    gridLayout->addWidget(OpacityScreen_label, 3, 0, 1, 1);

                    componentCreate(OpacityScreen_pushButton, SwitchButton, parent);
                    gridLayout->addWidget(OpacityScreen_pushButton, 3, 1, 1, 1);
                }
                {
                    componentCreate(RC_label, QLabel, parent);
                    gridLayout->addWidget(RC_label, 4, 0, 1, 1);

                    componentCreate(RC_pushButton, SwitchButton, parent);
                    gridLayout->addWidget(RC_pushButton, 4, 1, 1, 1);
                }
            }
            verticalLayout->addLayout(gridLayout);

            Separator(line_2, verticalLayout, parent);

            componentCreate(gridLayout_2, QGridLayout, nullptr);
            {
                componentCreate(lang_label, QLabel, parent);
                gridLayout_2->addWidget(lang_label, 0, 0, 1, 1);

                componentCreate(Lang_comboBox, QComboBox, parent);
                {
                    Lang_comboBox->addItem(QString("fr"));
                    Lang_comboBox->addItem(QString("en"));
                }
                gridLayout_2->addWidget(Lang_comboBox, 0, 1, 1, 1);
            }
            verticalLayout->addLayout(gridLayout_2);

            componentCreate(horizontalLayout, QHBoxLayout, nullptr);
            {
                componentCreate(ok, QPushButton, parent);
                horizontalLayout->addWidget(ok);

                componentCreate(cancel, QPushButton, parent);
                horizontalLayout->addWidget(cancel);
            }
            verticalLayout->addLayout(horizontalLayout);
        }

        retranslateUi(parent);

        QObject::connect(ok, &QPushButton::released, parent, qOverload<>(&QDialog::accept));
        QObject::connect(cancel, &QPushButton::released, parent, qOverload<>(&QDialog::reject));
    }

    void retranslateUi(QDialog* parent)
    {
        parent->setWindowTitle(QCoreApplication::translate("Options", "Options", nullptr));
        TimeBeforeAction_label->setText(QCoreApplication::translate("Options", "Time before Action", nullptr));
        pn_label->setText(QCoreApplication::translate("Options", "Precision number", nullptr));
        hibernate_label->setText(QCoreApplication::translate("Options", "StandBy hibernate Mode", nullptr));
        hideAfter_label->setText(QCoreApplication::translate("Options", "Hide after Action", nullptr));

        hideAfter_pushButton->Translate();
        hibernate_pushButton->Translate();
        OpacityScreen_pushButton->Translate();
        BlackScreen_pushButton->Translate();
        screenOff_pushButton->Translate();
        standby_pushButton->Translate();
        RC_pushButton->Translate();
        ok->setText(QCoreApplication::translate("Options", "ok", nullptr));
        cancel->setText(QCoreApplication::translate("Options", "cancel", nullptr));

        standby_label->setText(QCoreApplication::translate("Options", "Show StandBy Button", nullptr));
        screenOff_label->setText(QCoreApplication::translate("Options", "Show ScreenOff Button", nullptr));
        BlackScreen_label->setText(QCoreApplication::translate("Options", "Show BlackScreen Button", nullptr));
        OpacityScreen_label->setText(QCoreApplication::translate("Options", "Show OpacityScreen Button", nullptr));
        RC_label->setText(QCoreApplication::translate("Options", "Show Right-Click Menu", nullptr));
        lang_label->setText(QCoreApplication::translate("Options", "Language", nullptr));

    } // retranslateUi
};

Ui_decl(Options);

QT_END_NAMESPACE

#endif // OPTIONS_UI_H

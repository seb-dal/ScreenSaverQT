#include "options.h"
#include "Options_ui.h"

#include <QComboBox>

#include "utils/Remember_keys.h"
#include "utils/remember.h"
#include "utils/translator.h"
#include "utils/utilMacro.h"

Options::Options(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::Options)
{
    ui->setupUi(this);
    load();
    connect(this, &QDialog::accepted, this, &Options::save);
    connect(ui->Lang_comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(translate()));
}

Options::~Options()
{
    deleteIfReq(ui);
}

void Options::load()
{
    int t = Remember::get_(APP::Time_After_Button_Clicked::name(), 3);
    ui->TimeBeforeAction_spinBox->setValue(t);

    bool hide = Remember::get_(APP::Hide_After_Action::name(), 1);
    ui->hideAfter_pushButton->setChecked(hide);

    int pn = Remember::get_(APP::Number_After_Dot::name(), 1);
    ui->pn_0->setChecked(pn == 0);
    ui->pn_1->setChecked(pn == 1);
    ui->pn_2->setChecked(pn == 2);

    bool m_h = Remember::get_(APP::Standby_HibernateMode::name(), 0);
    ui->hibernate_pushButton->setChecked(m_h);

    bool bt_opa = Remember::get_(APP::Show_ShadeScreen_Button::name(), 1);
    ui->OpacityScreen_pushButton->setChecked(bt_opa);

    bool bt_blk = Remember::get_(APP::Show_BlackScreen_Button::name(), 1);
    ui->BlackScreen_pushButton->setChecked(bt_blk);

    bool bt_off = Remember::get_(APP::Show_ScreenOff_Button::name(), 1);
    ui->screenOff_pushButton->setChecked(bt_off);

    bool bt_stand = Remember::get_(APP::Show_Standby_Button::name(), 1);
    ui->standby_pushButton->setChecked(bt_stand);

    bool bt_rc = Remember::get_(APP::ShowContextMenu::name(), 1);
    ui->RC_pushButton->setChecked(bt_rc);

    QString lang = Remember::get_(APP::Language::name(), QString("en"));
    ui->Lang_comboBox->setCurrentText(lang);
}

void Options::save()
{
    int t = ui->TimeBeforeAction_spinBox->value();
    Remember::put(APP::Time_After_Button_Clicked::name(), t);

    bool hide = ui->hideAfter_pushButton->isChecked();
    Remember::put(APP::Hide_After_Action::name(), hide ? 1 : 0);

    int pn = ui->pn_0->isChecked() ? 0 : (ui->pn_1->isChecked() ? 1 : (ui->pn_2->isChecked() ? 2 : 1));
    Remember::put(APP::Number_After_Dot::name(), pn);

    bool m_h = ui->hibernate_pushButton->isChecked();
    Remember::put(APP::Standby_HibernateMode::name(), m_h ? 1 : 0);

    bool bt_opa = ui->OpacityScreen_pushButton->isChecked();
    Remember::put(APP::Show_ShadeScreen_Button::name(), bt_opa ? 1 : 0);

    bool bt_blk = ui->BlackScreen_pushButton->isChecked();
    Remember::put(APP::Show_BlackScreen_Button::name(), bt_blk ? 1 : 0);

    bool bt_off = ui->screenOff_pushButton->isChecked();
    Remember::put(APP::Show_ScreenOff_Button::name(), bt_off ? 1 : 0);

    bool bt_stand = ui->standby_pushButton->isChecked();
    Remember::put(APP::Show_Standby_Button::name(), bt_stand ? 1 : 0);

    bool bt_rc = ui->RC_pushButton->isChecked();
    Remember::put(APP::ShowContextMenu::name(), bt_rc ? 1 : 0);

    QString lang = ui->Lang_comboBox->currentText();
    Remember::put(APP::Language::name(), lang);
}

void Options::translate()
{
    QString lang = ui->Lang_comboBox->currentText();
    Translator::setLanguage(lang);
    ui->retranslateUi(this);
}

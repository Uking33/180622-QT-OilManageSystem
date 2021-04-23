#ifndef WIDGETBANK_H
#define WIDGETBANK_H

#include "wingwidget.h"
class WidgetBankDetails;
class WidgetBankEdit;
class WidgetBank: public WingWidget
{
    Q_OBJECT
public:
    WidgetBank(OutPut *m_output, WingWidget *m_parent);
    ~WidgetBank();
private:
    QList<WidgetBankDetails*> m_bankDetailsWidgetList;
    WidgetBankEdit *m_editWidget1,*m_editWidget2;
private:
    void CreateNew();
    int m_count;
public slots:
    void ButtonFindPress();
    void ButtonAddPress();
    void ButtonDetailsPress();
    void ButtonEditPress();
    void ButtonDelPress();
    void ButtonOutputPress();
    void ButtonChangePress();
};

#endif // WIDGETBANK_H

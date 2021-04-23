#ifndef WIDGETBANKDETAILS_H
#define WIDGETBANKDETAILS_H

#include "wingwidget.h"
class OutPut;
class WidgetBankEdit;
class WidgetBankDetailsEdit;

class WidgetBankDetails : public WingWidget
{
    Q_OBJECT
public:
    WidgetBankDetails(OutPut *m_output, WingWidget *m_parent, int index);
    ~WidgetBankDetails();
    void SetDate(QString str1,QString str2);
private:
    void CreateNew();
    WidgetBankDetailsEdit *m_editWidget1,*m_editWidget2;
    WidgetBankEdit *m_upEditWidget;
    int m_index;
    int m_count;
public slots:
    void ButtonFindPress();
    void ButtonAddPress();
    void ButtonEditPress();
    void ButtonDelPress();
    void ButtonOutputPress();
};

#endif // WIDGETBANKDETAILS_H

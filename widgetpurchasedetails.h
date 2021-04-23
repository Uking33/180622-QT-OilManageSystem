#ifndef WIDGETPURCHASEDETAILS_H
#define WIDGETPURCHASEDETAILS_H

#include "wingwidget.h"
class OutPut;
class WidgetPurchaseEdit;
class WidgetPurchaseDetailsEdit;

class WidgetPurchaseDetails : public WingWidget
{
    Q_OBJECT
public:
    WidgetPurchaseDetails(OutPut *m_output, WingWidget *m_parent, int index);
    ~WidgetPurchaseDetails();
    void SetDate(QString str1,QString str2);
private:
    void CreateNew();
    WidgetPurchaseDetailsEdit *m_editWidget1,*m_editWidget2;
    WidgetPurchaseEdit *m_upEditWidget;
    int m_index;
    int m_count;
public slots:
    void ButtonFindPress();
    void ButtonAddPress();
    void ButtonEditPress();
    void ButtonDelPress();
    void ButtonOutputPress();
};

#endif // WIDGETPURCHASEDETAILS_H

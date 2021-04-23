#ifndef WIDGETINCOMEDETAILS_H
#define WIDGETINCOMEDETAILS_H

#include "wingwidget.h"
class OutPut;
class WidgetPurchaseDetails;
class WidgetSellDetails;
class WidgetIncomeDetails : public WingWidget
{
    Q_OBJECT
public:
    WidgetIncomeDetails(OutPut *m_output, WingWidget *m_parent, int index);
    ~WidgetIncomeDetails();
    void SetDate(QString str1,QString str2);
private:
    void CreateNew();
    int m_index;
    int m_count;
    QList<WidgetPurchaseDetails*> m_purchaseDetailsWidgetList;
    QList<WidgetSellDetails*> m_sellDetailsWidgetList;
public slots:
    void ButtonFindPress();
    void ButtonDetailsPress();
};

#endif // WIDGETINCOMEDETAILS_H

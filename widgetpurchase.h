#ifndef WIDGETPURCHASE_H
#define WIDGETPURCHASE_H

#include "wingwidget.h"
class WidgetPurchaseDetails;
class WidgetPurchaseEdit;
class WidgetPurchase: public WingWidget
{
    Q_OBJECT
public:
    WidgetPurchase(OutPut *m_output, WingWidget *m_parent);
    ~WidgetPurchase();
private:
    QList<WidgetPurchaseDetails*> m_purchaseDetailsWidgetList;
    WidgetPurchaseEdit *m_editWidget1,*m_editWidget2;
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

#endif // WIDGETPURCHASE_H

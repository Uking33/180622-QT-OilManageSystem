#ifndef WIDGETSELLDETAILS_H
#define WIDGETSELLDETAILS_H

#include "wingwidget.h"
class OutPut;
class WidgetSellEdit;
class WidgetSellDetailsEdit;

class WidgetSellDetails : public WingWidget
{
    Q_OBJECT
public:
    WidgetSellDetails(OutPut *m_output, WingWidget *m_parent, int index);
    ~WidgetSellDetails();
    void SetDate(QString str1,QString str2);
private:
    void CreateNew();
    WidgetSellDetailsEdit *m_editWidget1,*m_editWidget2;
    WidgetSellEdit *m_upEditWidget;
    int m_index;
    int m_count;
public slots://槽函数
    void ButtonFindPress();
    void ButtonAddPress();
    void ButtonEditPress();
    void ButtonDelPress();
    void ButtonOutputPress();
};

#endif // WIDGETSELLDETAILS_H

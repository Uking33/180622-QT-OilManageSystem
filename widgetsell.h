#ifndef WIDGETSELL_H
#define WIDGETSELL_H

#include "wingwidget.h"
class WidgetSellDetails;
class WidgetSellEdit;
class WidgetSell: public WingWidget
{
    Q_OBJECT
public:
    WidgetSell(OutPut *m_output, WingWidget *m_parent);
    ~WidgetSell();
private:
    QList<WidgetSellDetails*> m_sellDetailsWidgetList;
    WidgetSellEdit *m_editWidget1,*m_editWidget2;
private:
    void CreateNew();
    int m_count;
public slots://保护槽函数
    void ButtonFindPress();
    void ButtonAddPress();
    void ButtonDetailsPress();
    void ButtonEditPress();
    void ButtonDelPress();
    void ButtonOutputPress();
    void ButtonChangePress();
};
#endif // WIDGETSELL_H

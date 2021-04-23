#ifndef WIDGETINCOME_H
#define WIDGETINCOME_H

#include "wingwidget.h"
class WidgetIncomeDetails;
class WidgetIncome: public WingWidget
{
    Q_OBJECT
public:
    WidgetIncome(OutPut *m_output, WingWidget *m_parent);
    ~WidgetIncome();
private:
    QList<WidgetIncomeDetails*> m_incomeDetailsWidgetList;
private:
    void CreateNew();
    QStringList m_tableType0;
    int m_count;
public slots:
    void ButtonFindPress();
    void ButtonDetailsPress();
};

#endif // WIDGETINCOME_H

#ifndef WIDGETSELLDETAILSEDIT_H
#define WIDGETSELLDETAILSEDIT_H

#include "editwidget.h"
class OutPut;
class WidgetSellDetailsEdit : public EditWidget
{
    Q_OBJECT
public:
    WidgetSellDetailsEdit(OutPut *m_output, WingWidget *m_parent, int index1, int index2=-1);
    virtual void BtnFlash();
    virtual void BtnCal();
};

#endif // WIDGETSELLDETAILSEDIT_H

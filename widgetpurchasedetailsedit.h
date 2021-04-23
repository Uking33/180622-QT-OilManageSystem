#ifndef WIDGETPURCHASEDETAILSEDIT_H
#define WIDGETPURCHASEDETAILSEDIT_H

#include "editwidget.h"
class OutPut;
class WidgetPurchaseDetailsEdit : public EditWidget
{
    Q_OBJECT
public:
    WidgetPurchaseDetailsEdit(OutPut *m_output, WingWidget *m_parent, int index1, int index2=-1);
    virtual void BtnFlash();
    virtual void BtnCal();
};

#endif // WIDGETPURCHASEDETAILSEDIT_H

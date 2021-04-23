#ifndef WIDGETPURCHASEEDIT_H
#define WIDGETPURCHASEEDIT_H

#include "editwidget.h"
class OutPut;

class WidgetPurchaseEdit : public EditWidget
{
    Q_OBJECT
public:
    WidgetPurchaseEdit(OutPut *m_output, WingWidget *m_parent, int index=-1, bool isDetails=false);
    virtual void BtnFlash();
    virtual void BtnCal();
    bool m_isDetails;
};

#endif // WIDGETPURCHASEEDIT_H

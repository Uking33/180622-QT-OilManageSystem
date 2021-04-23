#ifndef WIDGETBANKDETAILSEDIT_H
#define WIDGETBANKDETAILSEDIT_H

#include "editwidget.h"
class OutPut;
class WidgetBankDetailsEdit : public EditWidget
{
    Q_OBJECT
public:
    WidgetBankDetailsEdit(OutPut *m_output, WingWidget *m_parent, int index1, int index2=-1);
    virtual void BtnFlash();
    virtual void BtnCal();
};


#endif // WIDGETBANKDETAILSEDIT_H

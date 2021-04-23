#ifndef WIDGETBANKEDIT_H
#define WIDGETBANKEDIT_H

#include "editwidget.h"
class OutPut;

class WidgetBankEdit : public EditWidget
{
    Q_OBJECT
public:
    WidgetBankEdit(OutPut *m_output, WingWidget *m_parent, int index=-1, bool isDetails=false);
    virtual void BtnFlash();
    virtual void BtnCal();
    bool m_isDetails;
};

#endif // WIDGETBANKEDIT_H

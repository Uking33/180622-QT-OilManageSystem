#ifndef WIDGETSELLEDIT_H
#define WIDGETSELLEDIT_H

#include "editwidget.h"
class OutPut;

class WidgetSellEdit : public EditWidget
{
    Q_OBJECT
public:
    WidgetSellEdit(OutPut *m_output, WingWidget *m_parent, int index=-1, bool isDetails=false);
    virtual void BtnFlash();
    virtual void BtnCal();
    bool m_isDetails;
};
#endif // WIDGETSELLEDIT_H

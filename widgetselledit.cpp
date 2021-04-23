#include "widgetselledit.h"
#include "widgetsell.h"
#include "widgetselldetails.h"
#include "output.h"
#include <QVariant>

WidgetSellEdit::WidgetSellEdit(OutPut *m_output, WingWidget *m_parent, int index, bool isDetails)
    :EditWidget(m_output,m_parent)
{
    m_isDetails = isDetails;
    m_var1 = &(m_output->vars3);
    m_var2 = &(m_output->vars4);
    SetIndex(index);
    m_headerLabels1 = m_output->m_headerLabels3;
    m_headerLabels2 = m_output->m_headerLabels4;
    m_tableType1 = m_output->m_tableType3;
    m_tableType2 = m_output->m_tableType4;
    m_tableAuto1 = m_output->m_tableAuto3;
    m_tableAuto2 = m_output->m_tableAuto4;
    m_tagMap.insert("日期", "Date");
    m_typeMap.insert("日期", "Date");
    m_tagMap.insert("名称", "Name");
    m_typeMap.insert("名称", "Text");
    m_tagMap.insert("客户", "User");
    m_typeMap.insert("客户", "Text");
    m_tagMap.insert("订单号", "Number");
    m_typeMap.insert("订单号", "Text");
    m_tagMap.insert("品种", "Type");
    m_typeMap.insert("品种", "Text");
    m_tagMap.insert("单价", "Value");
    m_typeMap.insert("单价", "Number");
    m_tagMap.insert("状态", "Check");
    m_typeMap.insert("状态", "Radio");
}
void WidgetSellEdit::BtnFlash(){
    if(m_parent!=NULL){
        if(m_isDetails)
            ((WidgetSellDetails*)m_parent)->ButtonFindPress();
        else
            ((WidgetSell*)m_parent)->ButtonFindPress();
    }
}
void WidgetSellEdit::BtnCal(){
    m_output->CheckChoose(m_headerLabels2, m_headerLabels1, m_tableAuto1, m_output->vars4, m_output->vars3);
}

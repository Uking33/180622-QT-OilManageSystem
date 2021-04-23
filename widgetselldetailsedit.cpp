#include "widgetselldetailsedit.h"
#include "widgetselldetails.h"
#include "output.h"
#include <QVariant>

WidgetSellDetailsEdit::WidgetSellDetailsEdit(OutPut *m_output, WingWidget *m_parent, int index1, int index2)
    :EditWidget(m_output,m_parent)
{
    m_index1 = index1;
    m_var1 = &(m_output->vars3);
    m_var2 = &(m_output->vars4);
    SetIndex(index1,index2,true);
    m_headerLabels1 = m_output->m_headerLabels3;
    m_headerLabels2 = m_output->m_headerLabels4;
    m_tableType1 = m_output->m_tableType3;
    m_tableType2 = m_output->m_tableType4;
    m_tableAuto1 = m_output->m_tableAuto3;
    m_tableAuto2 = m_output->m_tableAuto4;
    m_tagMap.insert("日期", "Date");
    m_typeMap.insert("日期", "Date");
    m_tagMap.insert("车号", "Car");
    m_typeMap.insert("车号", "Text");
    m_tagMap.insert("数量/T", "SumNumber");
    m_typeMap.insert("数量/T", "Number");
    m_tagMap.insert("收款金额", "Payment");
    m_typeMap.insert("收款金额", "Number");
    m_tagMap.insert("备注", "Addition");
    m_typeMap.insert("备注", "Text");
}
void WidgetSellDetailsEdit::BtnFlash(){
    if(m_parent!=NULL)
        ((WidgetSellDetails*)m_parent)->ButtonFindPress();
}
void WidgetSellDetailsEdit::BtnCal(){
    m_output->CheckChoose(m_headerLabels2, m_headerLabels1, m_tableAuto1, m_output->vars4, m_output->vars3);
}

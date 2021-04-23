#include "widgetpurchasedetailsedit.h"
#include "widgetpurchasedetails.h"
#include "output.h"
#include <QVariant>

WidgetPurchaseDetailsEdit::WidgetPurchaseDetailsEdit(OutPut *m_output, WingWidget *m_parent, int index1, int index2)
    :EditWidget(m_output,m_parent)
{
    m_index1 = index1;
    m_var1 = &(m_output->vars1);
    m_var2 = &(m_output->vars2);
    SetIndex(index1,index2,true);
    m_headerLabels1 = m_output->m_headerLabels1;
    m_headerLabels2 = m_output->m_headerLabels2;
    m_tableType1 = m_output->m_tableType1;
    m_tableType2 = m_output->m_tableType2;
    m_tableAuto1 = m_output->m_tableAuto1;
    m_tableAuto2 = m_output->m_tableAuto2;
    m_tagMap.insert("日期", "Date");
    m_typeMap.insert("日期", "Date");
    m_tagMap.insert("提货单号", "Number");
    m_typeMap.insert("提货单号", "Text");
    m_tagMap.insert("车号", "Car");
    m_typeMap.insert("车号", "Text");
    m_tagMap.insert("订单数量", "SumNumber");
    m_typeMap.insert("订单数量", "Int");
    m_tagMap.insert("来货数", "ComingNumber");
    m_typeMap.insert("来货数", "Int");
    m_tagMap.insert("卸货数", "UnloadingNumber");
    m_typeMap.insert("卸货数", "Int");
    m_tagMap.insert("付款金额", "Payment");
    m_typeMap.insert("付款金额", "Number");
    m_tagMap.insert("备注", "Addition");
    m_typeMap.insert("备注", "Text");
}
void WidgetPurchaseDetailsEdit::BtnFlash(){
    if(m_parent!=NULL)
        ((WidgetPurchaseDetails*)m_parent)->ButtonFindPress();
}
void WidgetPurchaseDetailsEdit::BtnCal(){
    m_output->CheckChoose(m_headerLabels2, m_headerLabels1, m_tableAuto1, m_output->vars2, m_output->vars1, m_index1);
}

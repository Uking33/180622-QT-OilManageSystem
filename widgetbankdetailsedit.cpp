#include "widgetbankdetailsedit.h"
#include "widgetbankdetails.h"
#include "output.h"
#include <QVariant>

WidgetBankDetailsEdit::WidgetBankDetailsEdit(OutPut *m_output, WingWidget *m_parent, int index1, int index2)
    :EditWidget(m_output,m_parent)
{
    m_index1 = index1;
    m_var1 = &(m_output->vars5);
    m_var2 = &(m_output->vars6);
    SetIndex(index1,index2,true);
    m_headerLabels1 = m_output->m_headerLabels5;
    m_headerLabels2 = m_output->m_headerLabels6;
    m_tableType1 = m_output->m_tableType5;
    m_tableType2 = m_output->m_tableType6;
    m_tableAuto1 = m_output->m_tableAuto5;
    m_tableAuto2 = m_output->m_tableAuto6;
    m_tagMap.insert("日期", "Date");
    m_typeMap.insert("日期", "Date");
    m_tagMap.insert("收款金额", "Income");
    m_typeMap.insert("收款金额", "Number");
    m_tagMap.insert("付款金额", "Payment");
    m_typeMap.insert("付款金额", "Number");
    m_tagMap.insert("客户/供应商", "User");
    m_typeMap.insert("客户/供应商", "Text");
    m_tagMap.insert("合同号/订单号", "Number");
    m_typeMap.insert("合同号/订单号", "Text");
    m_tagMap.insert("用途", "Function");
    m_typeMap.insert("用途", "Text");
    m_tagMap.insert("备注", "Addition");
    m_typeMap.insert("备注", "Text");
}
void WidgetBankDetailsEdit::BtnFlash(){
    if(m_parent!=NULL)
        ((WidgetBankDetails*)m_parent)->ButtonFindPress();
}
void WidgetBankDetailsEdit::BtnCal(){
    m_output->CheckChoose(m_output->m_headerLabels2, m_output->m_headerLabels1, m_output->m_tableAuto1, m_output->vars2, m_output->vars1);
    m_output->CheckChoose(m_output->m_headerLabels4, m_output->m_headerLabels3, m_output->m_tableAuto3, m_output->vars4, m_output->vars3);
}

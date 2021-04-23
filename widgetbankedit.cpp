#include "widgetbankedit.h"
#include "widgetbank.h"
#include "widgetbankdetails.h"
#include "output.h"
#include <QVariant>

WidgetBankEdit::WidgetBankEdit(OutPut *m_output, WingWidget *m_parent, int index, bool isDetails)
    :EditWidget(m_output,m_parent)
{
    m_isDetails = isDetails;
    m_var1 = &(m_output->vars5);
    m_var2 = &(m_output->vars6);
    SetIndex(index);
    m_headerLabels1 = m_output->m_headerLabels5;
    m_headerLabels2 = m_output->m_headerLabels6;
    m_tableType1 = m_output->m_tableType5;
    m_tableType2 = m_output->m_tableType6;
    m_tableAuto1 = m_output->m_tableAuto5;
    m_tableAuto2 = m_output->m_tableAuto6;
    m_tagMap.insert("日期", "Date");
    m_typeMap.insert("日期", "Date");
    m_tagMap.insert("银行名称", "Bank");
    m_typeMap.insert("银行名称", "Text");
}
void WidgetBankEdit::BtnFlash(){
    if(m_parent!=NULL){
        if(m_isDetails)
            ((WidgetBankDetails*)m_parent)->ButtonFindPress();
        else
            ((WidgetBank*)m_parent)->ButtonFindPress();
    }
}
void WidgetBankEdit::BtnCal(){
    m_output->CheckChoose(m_output->m_headerLabels2, m_output->m_headerLabels1, m_output->m_tableAuto1, m_output->vars2, m_output->vars1);
    m_output->CheckChoose(m_output->m_headerLabels4, m_output->m_headerLabels3, m_output->m_tableAuto3, m_output->vars4, m_output->vars3);
}

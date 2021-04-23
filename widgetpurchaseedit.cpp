#include "widgetpurchaseedit.h"
#include "widgetpurchase.h"
#include "widgetpurchasedetails.h"
#include "output.h"
#include <QVariant>

WidgetPurchaseEdit::WidgetPurchaseEdit(OutPut *m_output, WingWidget *m_parent, int index, bool isDetails)
    :EditWidget(m_output,m_parent)
{
    m_isDetails = isDetails;
    m_var1 = &(m_output->vars1);
    m_var2 = &(m_output->vars2);
    SetIndex(index);
    m_headerLabels1 = m_output->m_headerLabels1;
    m_headerLabels2 = m_output->m_headerLabels2;
    m_tableType1 = m_output->m_tableType1;
    m_tableType2 = m_output->m_tableType2;
    m_tableAuto1 = m_output->m_tableAuto1;
    m_tableAuto2 = m_output->m_tableAuto2;
    m_tagMap.insert("日期", "Date");
    m_typeMap.insert("日期", "Date");
    m_tagMap.insert("供应商", "User");
    m_typeMap.insert("供应商", "Text");
    m_tagMap.insert("合同号", "Number");
    m_typeMap.insert("合同号", "Text");
    m_tagMap.insert("品种", "Type");
    m_typeMap.insert("品种", "Text");
    m_tagMap.insert("单价", "Value");
    m_typeMap.insert("单价", "Number");
    m_tagMap.insert("状态", "Check");
    m_typeMap.insert("状态", "Radio");
}
void WidgetPurchaseEdit::BtnFlash(){
    if(m_parent!=NULL){
        if(m_isDetails)
            ((WidgetPurchaseDetails*)m_parent)->ButtonFindPress();
        else
            ((WidgetPurchase*)m_parent)->ButtonFindPress();
    }
}
void WidgetPurchaseEdit::BtnCal(){
    m_output->CheckChoose(m_headerLabels2, m_headerLabels1, m_tableAuto1, m_output->vars2, m_output->vars1, m_index1);
}

/*
bool WidgetPurchaseEdit::Check(){
    QString str = m_lineHash["Number"]->GetValue();
    if(str==""){
        m_output->MessageHit("请输入合同号");
        return false;
    }
    for(int i=0;i<m_output->vars1.count();i++)
        if(str == m_output->vars1[i][2].toString()){

    m_output->MessageHit("合同号已存在");
            return false;
        }
    return true;
}*/

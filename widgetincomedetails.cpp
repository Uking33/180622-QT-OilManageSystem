#include "widgetincomedetails.h"
#include "widgetpurchasedetails.h"
#include "widgetselldetails.h"
#include "ubutton.h"
#include "udatebox.h"
#include "output.h"
#include <QTableWidget>

WidgetIncomeDetails::WidgetIncomeDetails(OutPut *m_output, WingWidget *m_parent, int index)
    :WingWidget(m_output, m_parent)
{
    this->setWindowTitle("收益-详情");
    m_index=index;
    m_type = 1;
    m_count = 0;
    m_isDetails = true;
    m_findLabels.append(m_output->m_findLabels8);
    m_headerLabels1.append(m_output->m_headerLabels7);
    m_headerLabels2.append(m_output->m_headerLabels8);
    m_tableType1.append(m_output->m_tableType7);
    m_tableType2.append(m_output->m_tableType8);
    Create();
    CreateNew();
}
WidgetIncomeDetails::~WidgetIncomeDetails(){
    for(int i=m_purchaseDetailsWidgetList.count()-1;i>=0;i--){
        delete m_purchaseDetailsWidgetList[i];
        m_purchaseDetailsWidgetList.removeAt(i);
    }
    for(int i=m_sellDetailsWidgetList.count()-1;i>=0;i--){
        delete m_sellDetailsWidgetList[i];
        m_sellDetailsWidgetList.removeAt(i);
    }
}
void WidgetIncomeDetails::CreateNew(){
    //Table
    QList<int> list1;
    list1.append(1);
    list1.append(2);
    for(int i=list1.count()-1;i>=0;i--){
        m_table->removeColumn(list1[i]);
    }
    //New btn
    m_btn1 = new UButton("查询(Enter)","",80,30,m_btnLayout);
    m_btn2 = new UButton("详情(Space)","Space",80,30,m_btnLayout);
    m_btn1->setFocusPolicy(Qt::NoFocus);
    m_btn2->setFocusPolicy(Qt::NoFocus);
    //Connect
    connect(m_btn1,SIGNAL(clicked()),this,SLOT(ButtonFindPress()));
    connect(m_btn2,SIGNAL(clicked()),this,SLOT(ButtonDetailsPress()));
    m_btn2->setEnabled(false);
    connect(m_table,&QTableWidget::itemSelectionChanged,[=](){
        if(m_table_up!=NULL){
            m_table_up->clearSelection();
        }
        if(m_table->currentRow()<m_count){
            m_btn2->setEnabled(true);
        }
        else{
            m_btn2->setEnabled(false);
        }
    });
    connect(m_table,&QTableWidget::doubleClicked,[=](){
        ButtonDetailsPress();
    });
    if(m_table_up!=NULL){
        connect(m_table_up,&QTableWidget::itemSelectionChanged,[=](){
            m_table->clearSelection();
            m_btn2->setEnabled(true);
        });
        connect(m_table_up,&QTableWidget::doubleClicked,[=](){
            ButtonDetailsPress();
        });
    }
}
void WidgetIncomeDetails::SetDate(QString str1,QString str2){
    m_dateSBox->Update(str1);
    m_dateEBox->Update(str2);
}
void WidgetIncomeDetails::ButtonFindPress(){
    m_output->Add78();
    //m_table
    m_count = WingWidget::BtnFind(this->m_output->vars8[m_index], m_table, m_tableType2, 8);
    //m_table_up
    this->m_output->CheckDate(m_headerLabels1,m_headerLabels2,m_tableType1,m_tableType2,m_output->vars7,m_output->vars8,
                              m_dateSBox->GetValue(),m_dateEBox->GetValue(), m_index);
    QList<QList<QVariant>> list2;
    list2.append(this->m_output->vars7[0]);
    list2.append(this->m_output->vars7[m_index]);
    this->m_output->VarToTable(list2, m_table_up, m_tableType1, 1);
}
void WidgetIncomeDetails::ButtonDetailsPress(){
    if(m_table->hasFocus()){
        if(m_table->currentRow()<m_count){
            int index=m_indexList[m_table->currentRow()+1];

        }
    }
    else if(m_table_up->hasFocus()){
        int type=m_output->m_typeList.at(m_index-1);
        int index=m_output->m_typeIndexList.at(m_index-1);
        switch(type){
        case 1:{
            WidgetPurchaseDetails *m_purchaseDetailsWidget = new WidgetPurchaseDetails(m_output,NULL,index);
            m_purchaseDetailsWidget->SetDate(m_dateSBox->GetValue(),m_dateEBox->GetValue());
            m_purchaseDetailsWidget->ButtonFindPress();
            m_purchaseDetailsWidget->show();
            m_purchaseDetailsWidgetList.append(m_purchaseDetailsWidget);
            break;
        }
        case 3:{
            WidgetSellDetails *m_sellDetailsWidget = new WidgetSellDetails(m_output,NULL,index);
            m_sellDetailsWidget->SetDate(m_dateSBox->GetValue(),m_dateEBox->GetValue());
            m_sellDetailsWidget->ButtonFindPress();
            m_sellDetailsWidget->show();
            m_sellDetailsWidgetList.append(m_sellDetailsWidget);
            break;
        }
        }
    }
}

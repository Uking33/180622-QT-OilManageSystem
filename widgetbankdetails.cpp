#include "widgetbankdetails.h"
#include "widgetbankedit.h"
#include "widgetbankdetailsedit.h"
#include "ubutton.h"
#include "udatebox.h"
#include "output.h"
#include <QTableWidget>
#include <QFileDialog>

WidgetBankDetails::WidgetBankDetails(OutPut *m_output, WingWidget *m_parent, int index)
    :WingWidget(m_output, m_parent)
{
    this->setWindowTitle("银行-详情");
    m_index=index;
    m_type = 1;
    m_count = 0;
    m_isDetails = true;
    m_findLabels.append(m_output->m_findLabels6);
    m_headerLabels1.append(m_output->m_headerLabels5);
    m_headerLabels2.append(m_output->m_headerLabels6);
    m_tableType1.append(m_output->m_tableType5);
    m_tableType2.append(m_output->m_tableType6);
    Create();
    CreateNew();
}
WidgetBankDetails::~WidgetBankDetails(){
    if(m_editWidget1!=NULL)delete m_editWidget1;
    if(m_editWidget2!=NULL)delete m_editWidget2;
    if(m_upEditWidget!=NULL)delete m_upEditWidget;
}
void WidgetBankDetails::CreateNew(){
    //Init
    m_editWidget1=NULL;
    m_editWidget2=NULL;
    m_upEditWidget=NULL;
    //Table
    QList<int> list1;
    list1.append(1);
    for(int i=list1.count()-1;i>=0;i--){
        m_table->removeColumn(list1[i]);
    }
    //New btn
    m_btn1 = new UButton("查询(Enter)","",80,30,m_btnLayout);
    m_btn2 = new UButton("添加(Insert)","Insert",80,30,m_btnLayout);
    m_btn3 = new UButton("编辑(Space)","Space",80,30,m_btnLayout);
    m_btn4 = new UButton("删除(Delete)","Delete",80,30,m_btnLayout);
    m_btn5 = new UButton("导出(Ctrl+S)","Ctrl+S",80,30,m_btnLayout);
    m_btn1->setFocusPolicy(Qt::NoFocus);
    m_btn2->setFocusPolicy(Qt::NoFocus);
    m_btn3->setFocusPolicy(Qt::NoFocus);
    m_btn4->setFocusPolicy(Qt::NoFocus);
    m_btn5->setFocusPolicy(Qt::NoFocus);
    //Connect
    connect(m_btn1,SIGNAL(clicked()),this,SLOT(ButtonFindPress()));
    connect(m_btn2,SIGNAL(clicked()),this,SLOT(ButtonAddPress()));
    connect(m_btn3,SIGNAL(clicked()),this,SLOT(ButtonEditPress()));
    connect(m_btn4,SIGNAL(clicked()),this,SLOT(ButtonDelPress()));
    connect(m_btn5,SIGNAL(clicked()),this,SLOT(ButtonOutputPress()));
    m_btn3->setEnabled(false);
    m_btn4->setEnabled(false);
    connect(m_table,&QTableWidget::itemSelectionChanged,[=](){
        if(m_table_up!=NULL){
            m_table_up->clearSelection();
        }
        if(m_table->currentRow()<m_count){
            m_btn3->setEnabled(true);
            m_btn4->setEnabled(true);
        }
        else{
            m_btn3->setEnabled(false);
            m_btn4->setEnabled(false);
        }
    });
    connect(m_table,&QTableWidget::doubleClicked,[=](){
        ButtonEditPress();
    });
    if(m_table_up!=NULL){
        connect(m_table_up,&QTableWidget::itemSelectionChanged,[=](){
            m_table->clearSelection();
            m_btn3->setEnabled(true);
            m_btn4->setEnabled(true);
        });
        connect(m_table_up,&QTableWidget::doubleClicked,[=](){
            ButtonEditPress();
        });
    }
}
void WidgetBankDetails::SetDate(QString str1,QString str2){
    m_dateSBox->Update(str1);
    m_dateEBox->Update(str2);
}
void WidgetBankDetails::ButtonFindPress(){
    //m_table
    m_count = WingWidget::BtnFind(this->m_output->vars6[m_index], m_table, m_tableType2, 8);
    //m_table_up
    this->m_output->CheckDate(m_headerLabels1,m_headerLabels2,m_tableType1,m_tableType2,m_output->vars5,m_output->vars6,
                              m_dateSBox->GetValue(),m_dateEBox->GetValue(), m_index);
    QList<QList<QVariant>> list2;
    list2.append(this->m_output->vars5[0]);
    list2.append(this->m_output->vars5[m_index]);
    this->m_output->VarToTable(list2, m_table_up, m_tableType1, 1);
}
void WidgetBankDetails::ButtonAddPress(){
    if(m_editWidget1 == NULL){
        m_editWidget1 = new WidgetBankDetailsEdit(m_output,this,m_index);
        m_editWidget1->SetType(EditWidget::WidgetType::Add);
        m_editWidget1->show();
    }
    else{
        m_editWidget1->SetIndex(m_index,-1,true);
        m_editWidget1->showNormal();
        m_editWidget1->activateWindow();
    }
}
void WidgetBankDetails::ButtonEditPress(){
    if(m_table->hasFocus()){
        if(m_table->currentRow()<m_count){
            int index=m_indexList[m_table->currentRow()+1];
            if(m_editWidget2 == NULL){
                m_editWidget2 = new WidgetBankDetailsEdit(m_output,this,m_index,index);
                m_editWidget2->SetType(EditWidget::WidgetType::Edit);
                m_editWidget2->Loading();
                m_editWidget2->show();
            }
            else{
                m_editWidget2->SetIndex(m_index,index,true);
                m_editWidget2->Loading();
                m_editWidget2->showNormal();
                m_editWidget2->activateWindow();
            }
        }
        else
            ButtonAddPress();
    }
    else if(m_table_up->hasFocus()){
        if(m_upEditWidget == NULL){
            m_upEditWidget = new WidgetBankEdit(m_output,this,m_index,true);
            m_upEditWidget->SetType(EditWidget::WidgetType::Edit);
            m_upEditWidget->Loading();
            m_upEditWidget->show();
        }
        else{
            m_upEditWidget->SetIndex(m_index);
            m_upEditWidget->Loading();
            m_upEditWidget->showNormal();
            m_upEditWidget->activateWindow();
        }
    }
}
void WidgetBankDetails::ButtonDelPress(){
    QList<int>* indexList=WingWidget::BtnDel(m_count);
    for(int i=indexList->count()-1;i>=0;i--)
        if(indexList->at(i)<m_count){
            m_output->vars6[m_index].removeAt(indexList->at(i)+1);
        }
    DelSum(indexList, m_index, &m_output->vars5, &m_output->vars6, m_output->m_tableAuto6, m_output->m_tableType6);
    ButtonFindPress();
    delete indexList;
}
void WidgetBankDetails::ButtonOutputPress(){
    QString str;
    if(m_output->MessageQuestion("导出当前已搜索的内容，单独导出一个文件")){
        str = QFileDialog::getSaveFileName(this,
                tr("保存文件"),
                ".",
                "Excel files (*.xls *.xlsx)");
        if (!str.isNull()){
            QList<QList<QVariant>> list;
            for(int i=0;i<m_indexList.count();i++)
                list.append(m_output->vars6[m_index][m_indexList.at(i)]);
            m_output->SaveOne(str, list);
            m_output->MessageHit("已导出");
        }
    }
}

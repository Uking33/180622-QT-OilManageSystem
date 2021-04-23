#include "widgetincome.h"
#include "widgetincomedetails.h"
#include "ubutton.h"
#include "udatebox.h"
#include "output.h"
#include <QTableWidget>

WidgetIncome::WidgetIncome(OutPut *m_output, WingWidget *m_parent)
    :WingWidget(m_output,m_parent)
{
    this->setWindowTitle("收益");
    m_type = 1;
    m_count = 0;
    m_isCheck = false;
    m_isDetails = true;
    m_findLabels.append(m_output->m_findLabels7);
    m_headerLabels1.append(m_output->m_headerLabels7);
    m_headerLabels2.append(m_output->m_headerLabels8);
    m_tableType1.append(m_output->m_tableType7);
    m_tableType2.append(m_output->m_tableType8);
    Create();
    CreateNew();
}
WidgetIncome::~WidgetIncome(){
    for(int i=m_incomeDetailsWidgetList.count()-1;i>=0;i--){
        delete m_incomeDetailsWidgetList[i];
        m_incomeDetailsWidgetList.removeAt(i);
    }
}
void WidgetIncome::CreateNew(){
    //New btn
    m_btn1 = new UButton("查询(Enter)","Return",80,30,m_btnLayout);
    m_btn2 = new UButton("详情(Space)","Space",80,30,m_btnLayout);
    m_btn1->setFocusPolicy(Qt::NoFocus);
    m_btn2->setFocusPolicy(Qt::NoFocus);
    //Table
    QList<int> list1;
    list1.append(0);
    list1.append(1);
    list1.append(2);
    m_tableType0 = m_tableType1;
    for(int i=list1.count()-1;i>=0;i--){
        m_table_up->removeColumn(list1[i]);
        m_tableType0.removeAt(list1[i]);
    }
    //Connect
    connect(m_btn1,SIGNAL(clicked()),this,SLOT(ButtonFindPress()));
    connect(m_btn2,SIGNAL(clicked()),this,SLOT(ButtonDetailsPress()));
    connect(m_table,&QTableWidget::doubleClicked,this,&WidgetIncome::ButtonDetailsPress);
    m_btn2->setEnabled(false);
    connect(m_table,&QTableWidget::itemSelectionChanged,[=](){
        if(m_table->currentRow()<m_count){
            m_btn2->setEnabled(true);
        }
        else{
            m_btn2->setEnabled(false);
        }
    });
    //Loading
    ButtonFindPress();
}
void WidgetIncome::ButtonFindPress(){
    m_output->Add78();
    //m_table
    m_count = WingWidget::BtnFind(this->m_output->vars7, m_table, m_tableType1, 8);
    //m_table_up
    QString sDate=m_dateSBox->GetValue();
    QString eDate=m_dateEBox->GetValue();
    QList<QList<QVariant>> list2;
    QList<QVariant> list;
    QStringList t_tableType;
    for(int i=3;i<m_tableType1.count();i++)
        list.append(this->m_output->vars7[0][i]);
    list2.append(list);
    list.clear();
    for(int j=0;j<m_tableType1.count();j++){
        float fSum=0;
        float cSum=0;
        int iSum=0;
        QVariant value;
        QString tag="";
        for(int i=1;i<m_output->vars7.count();i++){
            int indexDate=m_tableType1.indexOf("date");
            QStringList dateList = m_output->vars7[i][indexDate].toString().split('.');
            QString date = QString("%1%2%3").arg(dateList[0].toInt(),4,10,
                    QChar('0')).arg(dateList[1].toInt(),2,10,QChar('0')).arg(dateList[2].toInt(),2,10,QChar('0'));
            if(sDate<=date && date<=eDate){
                if (m_tableType1.at(j)=="num") {
                    tag="num";
                    fSum+=m_output->vars7[i][j].toFloat();
                }
                else if (m_tableType1.at(j)=="numS") {
                    if(tag==""){
                        tag="numS";
                        cSum=m_output->vars7[i][j].toFloat();
                    }
                }
                else if (m_tableType1.at(j)=="numE") {
                    if(tag=="")
                        tag="numE";
                    cSum=m_output->vars7[i][j].toFloat();
                }
                else if (m_tableType1.at(j)=="int") {
                    tag="int";
                    iSum+=m_output->vars7[i][j].toInt();
                }
                else{
                    //text
                    //date
                    tag="others";
                    value=m_output->vars7[i][j];
                }
            }
        }
        if(tag=="num"){
            list.append(QVariant(fSum));
            t_tableType.append(m_tableType1.at(j));
        }
        else if(tag=="numS"){
            list.append(QVariant(cSum));
            t_tableType.append(m_tableType1.at(j));
        }
        else if(tag=="numE"){
            list.append(QVariant(cSum));
            t_tableType.append(m_tableType1.at(j));
        }
        else if(tag=="int"){
            list.append(QVariant(iSum));
            t_tableType.append(m_tableType1.at(j));
        }
        else{
        }
    }
    list2.append(list);
    this->m_output->VarToTable(list2, m_table_up, m_tableType0, 1);
}
void WidgetIncome::ButtonDetailsPress(){
    if(m_table->currentRow()<m_count){
        int index=m_indexList[m_table->currentRow()+1];
        WidgetIncomeDetails *m_incomeDetailsWidget = new WidgetIncomeDetails(m_output,this,index);
        m_incomeDetailsWidget->SetDate(m_dateSBox->GetValue(),m_dateEBox->GetValue());
        m_incomeDetailsWidget->ButtonFindPress();
        m_incomeDetailsWidget->show();
        m_incomeDetailsWidgetList.append(m_incomeDetailsWidget);
    }
}

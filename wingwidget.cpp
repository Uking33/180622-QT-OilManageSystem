//窗口
#include "wingwidget.h"
#include "output.h"
#include "uloading.h"
#include <QResizeEvent>
//布局
#include <QVBoxLayout>
#include <QHBoxLayout>
//控件
#include "umulradio.h"
#include "ubutton.h"
#include "uline.h"
#include "udatebox.h"
#include "utimebox.h"
#include "urectbox.h"
#include <QTableWidget>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QCheckBox>
//辅助
#include <QHeaderView>
#include <QMimeData>
#include <QList>

WingWidget::WingWidget(OutPut *m_output, WingWidget *m_parent){
    setAttribute(Qt::WA_QuitOnClose, false);
    this->m_output = m_output;
    this->m_parent = m_parent;
    this->m_type = 1;
    this->m_isDetails = false;
    this->m_isCheck = false;
}
WingWidget::~WingWidget(){
    delete m_dateSBox;
    delete m_dateSBtn1;
    delete m_dateSBtn2;
    delete m_findLabel;
    delete m_findBox;
    delete m_findEdit;
    delete m_dateELabel;
    delete m_dateEBox;
    delete m_dateEBtn1;
    delete m_dateEBtn2;
    m_table->clearContents();
    delete m_table;
    if(m_table_up!=NULL){
        m_table_up->clearContents();
        delete m_table_up;
    }
    if(m_radio1!=NULL) delete m_radio1;
    if(m_radio2!=NULL) delete m_radio2;
    if(m_radio3!=NULL) delete m_radio3;
    if(m_btn1!=NULL) delete m_btn1;
    if(m_btn2!=NULL) delete m_btn2;
    if(m_btn3!=NULL) delete m_btn3;
    if(m_btn4!=NULL) delete m_btn4;
    if(m_btn5!=NULL) delete m_btn5;
    if(m_btn6!=NULL) delete m_btn6;
    delete m_dateSLayout;
    delete m_findLayout;
    delete m_dateELayout;
    delete m_btnLayout;
    delete m_layout1;
    delete m_layout2;
    if(m_layout3!=NULL) delete m_layout3;
    delete m_layout;
}
void WingWidget::Create(){
    m_layout = new QVBoxLayout();
    m_layout1 = new QHBoxLayout();
    m_layout1->setAlignment(Qt::AlignLeft);
    m_layout2 = new QHBoxLayout();
    m_layout2->setAlignment(Qt::AlignLeft);
    m_layout3=NULL;
    //---筛选控件---
    m_dateSLayout= new QHBoxLayout();
    m_dateSLabel = new QLabel("起始时间");
    m_dateSBox = new UDateBox(2);
    m_dateSLayout->addWidget(m_dateSLabel);
    m_dateSLayout->addWidget(m_dateSBox);
    m_dateSBtn1 = new UButton("日","F1",25,25,m_dateSLayout);
    m_dateSBtn1->setFocusPolicy(Qt::NoFocus);
    connect(m_dateSBtn1,&UButton::clicked,m_dateSBox,&UDateBox::Today);
    m_dateSBtn2 = new UButton("周","F2",25,25,m_dateSLayout);
    m_dateSBtn2->setFocusPolicy(Qt::NoFocus);
    connect(m_dateSBtn2,&UButton::clicked,m_dateSBox,&UDateBox::ToWeek);

    m_findLayout= new QHBoxLayout();
    m_findLabel = new QLabel("字段");
    m_findBox = new QComboBox();
    m_findBox->addItems(m_findLabels);
    m_findEdit = new QLineEdit();
    m_findEdit->setFocusPolicy(Qt::StrongFocus);
    m_findEdit->setMaxLength(50);
    m_findEdit->setValidator(new QRegExpValidator(QRegExp("[^, ☺]*$"), m_findEdit));
    m_findEdit->setPlaceholderText("全部");
    m_findLayout->addWidget(m_findLabel);
    m_findLayout->addWidget(m_findBox);
    m_findLayout->addWidget(m_findEdit);
    connect(m_findBox,SIGNAL(currentIndexChanged(int)),
            this,SLOT(FindChange(int)));

    m_dateELabel = new QLabel("结束时间");
    m_dateEBox = new UDateBox(3,m_dateSBox);
    m_dateSBox->ChooseDay(m_dateSBox->m_comboBoxDay->currentText());
    m_dateELayout= new QHBoxLayout();
    m_dateELayout->addWidget(m_dateELabel);
    m_dateELayout->addWidget(m_dateEBox);
    m_dateEBtn1 = new UButton("月","F3",25,25,m_dateELayout);
    m_dateEBtn1->setFocusPolicy(Qt::NoFocus);
    connect(m_dateEBtn1,&UButton::clicked,m_dateSBox,&UDateBox::ToMonth);
    m_dateEBtn2 = new UButton("年","F4",25,25,m_dateELayout);
    m_dateEBtn2->setFocusPolicy(Qt::NoFocus);
    connect(m_dateEBtn2,&UButton::clicked,m_dateSBox,&UDateBox::ToYear);
    if(m_isCheck){
        m_radio1 = new UMulRadio("含税：","全部","是","否");
        m_radio2 = new UMulRadio("完成：","全部","是","否");
        m_radio3 = new UMulRadio("支付：","全部","是","否");
    }
    else{
        m_radio1 = NULL;
        m_radio2 = NULL;
        m_radio3 = NULL;
    }
    //---按钮---
    m_btnLayout = new QHBoxLayout();
    m_btn1 = NULL;
    m_btn2 = NULL;
    m_btn3 = NULL;
    m_btn4 = NULL;
    m_btn5 = NULL;
    m_btn6 = NULL;
    //---添加表格---
    int rows;
    if(m_isDetails)
        rows=8;
    else
        rows=10;
    //创建表格
    QStringList headerLabels;
    QStringList headerLabels_up;
    QStringList m_tableType;
    QStringList m_tableType_up;
    if(m_isDetails){
        headerLabels=m_headerLabels2;
        headerLabels_up=m_headerLabels1;
        m_tableType=m_tableType2;
        m_tableType_up=m_tableType1;
    }
    else{
        headerLabels=m_headerLabels1;
        m_tableType=m_tableType1;
    }
    m_table=new QTableWidget(rows,headerLabels.count());
    if(m_isDetails){
        m_table->setMaximumHeight(45*8+27);
        m_table->setMinimumHeight(45*8+27);
    }
    else{
        m_table->setMaximumHeight(45*10+27);
        m_table->setMinimumHeight(45*10+27);
    }
    if(m_tableType.count()==headerLabels.count()){
        //行标题
        m_table->setHorizontalHeaderLabels(headerLabels);
        m_table->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
        m_table->resizeColumnsToContents();
        m_table->verticalHeader()->setDefaultSectionSize(45);//行高
        //m_table->horizontalHeader()->setDefaultSectionSize(85);//列宽
        //m_table->setColumnWidth(6,100);
        //设置对齐
        m_table->horizontalHeader()->setStretchLastSection(true);//右边界对齐
        m_table->verticalHeader()->setStretchLastSection(true);//下边界对齐
        m_table->horizontalHeader()->setFont(QFont("宋体",10));
        m_table->verticalHeader()->setFont(QFont("宋体",10));
        connect(m_table->horizontalHeader(),SIGNAL(sectionClicked(int)),this, SLOT(TableSort(int)));
        m_table->setFocusPolicy(Qt::ClickFocus);
        ChangeType();
    }
    if(m_isDetails){
        m_table_up=new QTableWidget(1,headerLabels_up.count());
        m_table_up->setMaximumHeight(45+27);
        m_table_up->setMinimumHeight(45+27);
        if(m_tableType_up.count()==headerLabels_up.count()){
            //行标题
            m_table_up->setHorizontalHeaderLabels(headerLabels_up);
            m_table_up->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
            m_table_up->resizeColumnsToContents();
            m_table_up->verticalHeader()->setDefaultSectionSize(45);//行高
            //设置对齐
            m_table_up->horizontalHeader()->setStretchLastSection(true);//右边界对齐
            m_table_up->verticalHeader()->setStretchLastSection(true);//下边界对齐
            m_table_up->horizontalHeader()->setFont(QFont("宋体",10));
            m_table_up->verticalHeader()->setFont(QFont("宋体",10));
            m_table_up->setFocusPolicy(Qt::ClickFocus);

            m_table_up->setSelectionBehavior (QAbstractItemView::SelectRows);//设置表格的选择方式
            m_table_up->setEditTriggers(QAbstractItemView::NoEditTriggers);        //不能编辑行内容
            m_table_up->setSelectionMode(QAbstractItemView::SingleSelection);
        }
    }
    else
        m_table_up=NULL;
    //---布局---
    if(m_isDetails){
        m_layout1->addLayout(m_dateSLayout);
        m_layout1->addLayout(m_findLayout);
        m_layout2->addLayout(m_dateELayout);
        m_btnLayout->setSpacing(5);
        m_layout2->addLayout(m_btnLayout);
        m_layout->addStretch(1);
        m_layout->addLayout(m_layout1);
        m_layout->addLayout(m_layout2);
        m_layout->addStretch(1);
        m_layout->addWidget(m_table_up);
        m_layout->addWidget(m_table);
    }
    else{
        m_layout1->addLayout(m_dateSLayout);
        m_layout1->addLayout(m_findLayout);
        m_layout2->addLayout(m_dateELayout);
        m_btnLayout->setSpacing(5);
        m_layout2->addLayout(m_btnLayout);
        if(m_isCheck){
            m_layout3 = new QHBoxLayout();
            m_layout3->addWidget(m_radio1);
            m_layout3->addWidget(m_radio2);
            m_layout3->addWidget(m_radio3);
        }
        m_layout->addStretch(1);
        m_layout->addLayout(m_layout1);
        m_layout->addLayout(m_layout2);
        if(m_isCheck)
            m_layout->addLayout(m_layout3);
        m_layout->addStretch(1);
        m_layout->addWidget(m_table);
    }
    this->setLayout(m_layout);

    //---大小---
    QSize size;
    size.setWidth(800);
    size.setHeight(600);
    this->resize(size);
    this->setMinimumSize(size);
}
void WingWidget::ChangeType(int tpye){
    if(tpye!=-1)
        m_type = tpye;
    //设置方式
    switch (m_type) {
    case 1:
        m_table->setSelectionBehavior (QAbstractItemView::SelectRows);//设置表格的选择方式
        m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);        //不能编辑行内容
        m_table->setSelectionMode(QAbstractItemView::SingleSelection);
        break;
    case 2:
        m_table->setSelectionBehavior (QAbstractItemView::SelectItems);//设置表格的选择方式
        m_table->setEditTriggers(QAbstractItemView::AllEditTriggers);        //编辑行内容
        m_table->setSelectionMode(QAbstractItemView::SingleSelection);
        break;
    default:
        break;
    }
}
void WingWidget::FindChange(int index){
    m_findEdit->setPlaceholderText(m_findLabels.at(index));
}
void WingWidget::TableSort(int index){
    static bool f = true;
    m_output->SortByCol(m_table, index, m_indexList, f ? Qt::AscendingOrder : Qt::DescendingOrder);
    f = !f;
}
int WingWidget::BtnFind(QList<QList<QVariant>> &oList, QTableWidget *tableWidget, QStringList strList, int maxRow){
    m_indexList.clear();
    for(int i=0;i<oList.count();i++)
        m_indexList.append(i);
    QString sDate = m_dateSBox->GetValue();
    QString eDate = m_dateEBox->GetValue();
    QList<QList<QVariant>> list(oList);
    bool isExist;
    for(int i=list.count()-1;i>=1;i--){
        QStringList dateList = list[i][0].toString().split('.');
        if(dateList.count() == 3){
            QString date = QString("%1%2%3").arg(dateList[0].toInt(),4,10,
                    QChar('0')).arg(dateList[1].toInt(),2,10,QChar('0')).arg(dateList[2].toInt(),2,10,QChar('0'));
            //date
            if(!(sDate<=date && date<=eDate)){
                list.removeAt(i);
                m_indexList.removeAt(i);
            }
            else{
                //radio
                if(m_isCheck){
                    if((m_radio1->GetValue()==2 && list[i][list[i].count()-3]=="否")
                            || (m_radio1->GetValue()==3 && list[i][list[i].count()-3]=="是")){
                        list.removeAt(i);
                        m_indexList.removeAt(i);
                    }
                    if((m_radio2->GetValue()==2 && list[i][list[i].count()-2]=="否")
                            || (m_radio2->GetValue()==3 && list[i][list[i].count()-2]=="是")){
                        list.removeAt(i);
                        m_indexList.removeAt(i);
                    }
                    if((m_radio3->GetValue()==2 && list[i][list[i].count()-1]=="否")
                            || (m_radio3->GetValue()==3 && list[i][list[i].count()-1]=="是")){
                        list.removeAt(i);
                        m_indexList.removeAt(i);
                    }
                }
                //string
                isExist = false;
                if(m_findEdit->text()!=""){
                    switch (m_findBox->currentIndex()) {
                    case 0:{
                        for(int j=1;j<list[0].count();j++){
                            if(m_findLabels.contains(list[0][j].toString())){
                                if(list[i][j].toString().contains(m_findEdit->text(), Qt::CaseSensitive)){
                                    isExist = true;
                                }
                            }
                        }
                        break;
                    }
                    default:{
                        int j = m_findBox->currentIndex();
                        if(m_findLabels.contains(list[0][j].toString())){
                            if(list[i][j].toString().contains(m_findEdit->text(), Qt::CaseSensitive)){
                                isExist = true;
                            }
                        }
                        break;
                    }
                    }
                    if(!isExist){
                        list.removeAt(i);
                        m_indexList.removeAt(i);
                    }
                }
            }
        }
    }
    return this->m_output->VarToTable(list, tableWidget, strList, maxRow);
}
QList<int>* WingWidget::BtnDel(int maxCount){
    //获取选中
    int count=m_table->selectedItems().count()/m_table->columnCount();
    if(count==0)
        return NULL;
    QList<int>* indexList = new QList<int>();
    QList<QTableWidgetSelectionRange> selectionRange;
    selectionRange=m_table->selectedRanges();
    //记录
    foreach(QTableWidgetSelectionRange range,selectionRange){
        for(int i=range.topRow();i<=range.bottomRow();i++){
            if(i>=maxCount)
                break;
            indexList->append(i);
        }
    }
    //询问是否删除
    QString str;
    if(count==1)
        str=QString("是否删除%1行数据（第%2行）?").arg(count).arg(indexList->first()+1);
    else
        str=QString("是否删除%1行数据（从第%2行到第%3行）?").arg(count).arg(indexList->first()+1).arg(indexList->last()+1);
    //删除
    if(m_output->MessageQuestion(str)){
        if(!m_output->MessageQuestion("请再次确认")){
            delete indexList;
            return NULL;
        }
        return indexList;
    }
    delete indexList;
    return NULL;
}
void WingWidget::DelSum(QList<int>* indexList, int m_index, QList<QList<QVariant>>*m_var1, QList<QList<QList<QVariant>>>*m_var2, QStringList m_tableAuto,QStringList  m_tableType){
    if(indexList!=NULL){
        //var2-cal
        for(int j=1;j<(*m_var2)[m_index].count();j++){
            for(int i=0;i<m_headerLabels2.count();i++){
                QStringList strList1=((QString)m_tableAuto[i]).split(':');
                QStringList strList2;
                switch(((QString)strList1[0]).toInt()){
                case 2:{
                    strList2=((QString)strList1[1]).split(',');
                    float sum;
                    if(m_tableType.at(i)=="numE"){
                        if(j==1)
                            sum = 0;
                        else
                            sum = (*m_var2)[m_index][j-1][i].toFloat();
                    }
                    else
                        sum = 0;
                    for(int n=0;n<strList2.count();n++){
                        int index=((QString)strList2[n]).toInt();
                        if(index>0)
                            sum += (*m_var2)[m_index][j][index-1].toFloat();
                        else if(index<0)
                            sum -= (*m_var2)[m_index][j][-index-1].toFloat();
                    }
                    (*m_var2)[m_index][j][i] = QVariant(sum);
                    break;
                }
                case 4:{
                    strList2=((QString)strList1[1]).split(',');
                    float sum;
                    if(m_tableType.at(i)=="numE"){
                        if(j==1)
                            sum = 1;
                        else
                            sum = (*m_var2)[m_index][j-1][i].toFloat();
                    }
                    else
                        sum = 1;
                    for(int n=0;n<strList2.count();n++){
                        int index=((QString)strList2[n]).toInt();
                        if(index>0)
                            sum *= (*m_var2)[m_index][j][index-1].toFloat();
                        else if(index<0)
                            sum /= (*m_var2)[m_index][j][-index-1].toFloat();
                    }
                    (*m_var2)[m_index][j][i] = QVariant(sum);
                    break;
                }
                case 5:{
                    QVariant value;
                    if(((QString)strList1[1]).contains('$')){
                        int rows = (*m_var2)[m_index].count();
                        strList2=((QString)((QString)strList1[1]).remove('$')).split('/');
                        if(strList2.count()==2){
                            int n1 = ((QString)strList2[0]).toInt();
                            int n2 = ((QString)strList2[1]).toInt();
                            if(n1>0)
                                value = (*m_var2)[m_index][n1][n2-1];
                            else
                                value = (*m_var2)[m_index][rows+n1][n2-1];
                        }
                    }
                    (*m_var2)[m_index][j][i] = value;
                    break;
                }
                }
            }
        }
        //var1
        for(int i=0;i<m_headerLabels1.count();i++){
            int index = m_headerLabels2.indexOf(m_headerLabels1[i]);
            if(index!=-1){
            if(m_tableType[index]=="int"){
                int sum = 0;
                for(int j=1;j<(*m_var2)[m_index].count();j++){
                    sum += (*m_var2)[m_index][j][index].toInt();
                }
                (*m_var1)[m_index][i] = QVariant(sum);
            }
            else if(m_tableType[index]=="num"){
                float sum = 0;
                for(int j=1;j<(*m_var2)[m_index].count();j++){
                    sum += (*m_var2)[m_index][j][index].toFloat();
                }
                (*m_var1)[m_index][i] = QVariant(sum);
            }
            else if(m_tableType[index]=="numE")
                (*m_var1)[m_index][i] = QVariant((*m_var2)[m_index][(*m_var2)[m_index].count()-1][index].toFloat());
            else if(m_tableType[index]=="numS")
                (*m_var1)[m_index][i] = QVariant((*m_var2)[m_index][1][index].toFloat());
            }
        }
    }
}

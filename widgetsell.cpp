#include "widgetsell.h"
#include "widgetselldetails.h"
#include "ubutton.h"
#include "udatebox.h"
#include "widgetselledit.h"
#include "output.h"
#include <QTableWidget>
#include <QFileDialog>

WidgetSell::WidgetSell(OutPut *m_output, WingWidget *m_parent)
    :WingWidget(m_output,m_parent)
{
    this->setWindowTitle("销售");
    m_type = 1;
    m_count = 0;
    m_isCheck = true;
    m_findLabels.append(m_output->m_findLabels3);
    m_headerLabels1.append(m_output->m_headerLabels3);
    m_headerLabels2.append(m_output->m_headerLabels4);
    m_tableType1.append(m_output->m_tableType3);
    m_tableType2.append(m_output->m_tableType4);
    Create();
    CreateNew();
}
WidgetSell::~WidgetSell(){
    for(int i=m_sellDetailsWidgetList.count()-1;i>=0;i--){
        delete m_sellDetailsWidgetList[i];
        m_sellDetailsWidgetList.removeAt(i);
    }
    if(m_editWidget1!=NULL) delete m_editWidget1;
    if(m_editWidget2!=NULL) delete m_editWidget2;
}
void WidgetSell::CreateNew(){
    //Init
    m_editWidget1=NULL;
    m_editWidget2=NULL;
    //New btn
    m_btn1 = new UButton("查询(Enter)","Return",80,30,m_btnLayout);
    m_btn2 = new UButton("添加(Insert)","Insert",80,30,m_btnLayout);
    m_btn3 = new UButton("详情(Space)","Space",80,30,m_btnLayout);
    m_btn4 = new UButton("删除(Delete)","Delete",80,30,m_btnLayout);
    m_btn5 = new UButton("导出(Ctrl+P)","Print",80,30,m_btnLayout);
    m_btn6 = new UButton("模式-查看","·",80,30,m_findLayout);
    m_btn1->setFocusPolicy(Qt::NoFocus);
    m_btn2->setFocusPolicy(Qt::NoFocus);
    m_btn3->setFocusPolicy(Qt::NoFocus);
    m_btn4->setFocusPolicy(Qt::NoFocus);
    m_btn5->setFocusPolicy(Qt::NoFocus);
    m_btn6->setFocusPolicy(Qt::NoFocus);
    //Connect
    connect(m_btn1,SIGNAL(clicked()),this,SLOT(ButtonFindPress()));
    connect(m_btn2,SIGNAL(clicked()),this,SLOT(ButtonAddPress()));
    connect(m_btn3,SIGNAL(clicked()),this,SLOT(ButtonDetailsPress()));
    connect(m_btn4,SIGNAL(clicked()),this,SLOT(ButtonDelPress()));
    connect(m_btn5,SIGNAL(clicked()),this,SLOT(ButtonOutputPress()));
    connect(m_btn6,SIGNAL(clicked()),this,SLOT(ButtonChangePress()));
    connect(m_table,&QTableWidget::doubleClicked,this,&WidgetSell::ButtonDetailsPress);
    m_btn3->setEnabled(false);
    m_btn4->setEnabled(false);
    connect(m_table,&QTableWidget::itemSelectionChanged,[=](){
        if(m_table->currentRow()<m_count){
            m_btn3->setEnabled(true);
            m_btn4->setEnabled(true);
        }
        else{
            m_btn3->setEnabled(false);
            m_btn4->setEnabled(false);
        }
    });
    //Loading
    m_count = BtnFind(this->m_output->vars3, m_table, m_tableType1);
}
void WidgetSell::ButtonFindPress(){
    m_count = WingWidget::BtnFind(this->m_output->vars3, m_table, m_tableType1);
}
void WidgetSell::ButtonAddPress(){
    if(m_editWidget1 == NULL){
        m_editWidget1 = new WidgetSellEdit(m_output,this);
        m_editWidget1->SetType(EditWidget::WidgetType::Add);
        m_editWidget1->show();
    }
    else{
        m_editWidget1->SetIndex();
        m_editWidget1->showNormal();
        m_editWidget1->activateWindow();
    }
}
void WidgetSell::ButtonDetailsPress(){
    if(m_table->currentRow()<m_count){
        int index=m_indexList[m_table->currentRow()+1];
        WidgetSellDetails *m_sellDetailsWidget = new WidgetSellDetails(m_output,this,index);
        m_sellDetailsWidget->SetDate(m_dateSBox->GetValue(),m_dateEBox->GetValue());
        m_sellDetailsWidget->ButtonFindPress();
        m_sellDetailsWidget->show();
        m_sellDetailsWidgetList.append(m_sellDetailsWidget);
    }
    else
        ButtonAddPress();
}
void WidgetSell::ButtonEditPress(){
    if(m_table->currentRow()<m_count){
        int index=m_indexList[m_table->currentRow()+1];
        if(m_editWidget2 == NULL){
            m_editWidget2 = new WidgetSellEdit(m_output,this,index);
            m_editWidget2->SetType(EditWidget::WidgetType::Edit);
            m_editWidget2->Loading();
            m_editWidget2->show();
        }
        else{
            m_editWidget2->SetIndex(index);
            m_editWidget2->Loading();
            m_editWidget2->showNormal();
            m_editWidget2->activateWindow();
        }
    }
    else
        ButtonAddPress();
}
void WidgetSell::ButtonDelPress(){
    QList<int>* indexList=WingWidget::BtnDel(m_count);
    if(indexList!=NULL){
        //Remove
        for(int i=indexList->count()-1;i>=0;i--)
            if(indexList->at(i)<m_count){
                m_output->vars3.removeAt(indexList->at(i)+1);
                m_output->vars4.removeAt(indexList->at(i)+1);
            }
        ButtonFindPress();
        delete indexList;
    }
}
void WidgetSell::ButtonOutputPress(){
    QString str;
    QString path;
    if(m_output->MessageQuestion("导出当前已搜索的内容,子级全部导出。\n请选择文件夹，导入新数据。\n选择原文件夹，会覆盖同名文件。建议选择新文件夹。")){
        QFileDialog *fileDialog = new QFileDialog(this);
        fileDialog->setWindowTitle("选择文件夹");
        fileDialog->setFileMode(QFileDialog::DirectoryOnly);
        if(fileDialog->exec()){
            str = fileDialog->selectedFiles()[0];
            QList<QList<QVariant>> list;
            for(int i=1;i<m_indexList.count();i++){
                list.clear();
                for(int j=0;j<m_output->vars4[m_indexList.at(i)].count();j++)
                    list.append(m_output->vars4[m_indexList.at(i)][j]);
                QDir dir;
                if(!dir.exists(str+"/"+tr("销售")))//判断需要创建的文件夹是否存在
                    dir.mkdir(str+"/"+tr("销售")); //创建文件夹
                path = str+"/"+tr("销售")+"/"+m_output->vars3[m_indexList.at(i)][3].toString()+".xls";
                m_output->SaveOne(path, list);
            }
            m_output->MessageHit("已导出");
        }
    }
}
void WidgetSell::ButtonChangePress(){
    if(m_btn6->text() == "模式-查看"){
        m_btn6->setText("模式-修改");
        m_btn3->setText("修改(Space)");
        m_btn3->setShortcut(QKeySequence("Space"));
        disconnect(m_btn3,SIGNAL(clicked()),this,SLOT(ButtonDetailsPress()));
        disconnect(m_table,&QTableWidget::doubleClicked,this,&WidgetSell::ButtonDetailsPress);
        connect(m_btn3,SIGNAL(clicked()),this,SLOT(ButtonEditPress()));
        connect(m_table,&QTableWidget::doubleClicked,this,&WidgetSell::ButtonEditPress);
    }
    else{
        m_btn6->setText("模式-查看");
        m_btn3->setText("详情(Space)");
        m_btn3->setShortcut(QKeySequence("Space"));
        disconnect(m_btn3,SIGNAL(clicked()),this,SLOT(ButtonEditPress()));
        disconnect(m_table,&QTableWidget::doubleClicked,this,&WidgetSell::ButtonEditPress);
        connect(m_btn3,SIGNAL(clicked()),this,SLOT(ButtonDetailsPress()));
        connect(m_table,&QTableWidget::doubleClicked,this,&WidgetSell::ButtonDetailsPress);
    }
}


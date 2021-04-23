#include "widgetbank.h"
#include "widgetbankdetails.h"
#include "ubutton.h"
#include "udatebox.h"
#include "widgetbankedit.h"
#include "output.h"
#include <QTableWidget>
#include <QFileDialog>

WidgetBank::WidgetBank(OutPut *m_output, WingWidget *m_parent)
    :WingWidget(m_output,m_parent)
{
    this->setWindowTitle("银行");
    m_type = 1;
    m_count = 0;
    m_findLabels.append(m_output->m_findLabels5);
    m_headerLabels1.append(m_output->m_headerLabels5);
    m_headerLabels2.append(m_output->m_headerLabels6);
    m_tableType1.append(m_output->m_tableType5);
    m_tableType2.append(m_output->m_tableType6);
    Create();
    CreateNew();
}
WidgetBank::~WidgetBank(){
    for(int i=m_bankDetailsWidgetList.count()-1;i>=0;i--){
        delete m_bankDetailsWidgetList[i];
        m_bankDetailsWidgetList.removeAt(i);
    }
    if(m_editWidget1!=NULL) delete m_editWidget1;
    if(m_editWidget2!=NULL) delete m_editWidget2;
}
void WidgetBank::CreateNew(){
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
    connect(m_table,&QTableWidget::doubleClicked,this,&WidgetBank::ButtonDetailsPress);
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
    m_count = BtnFind(this->m_output->vars5, m_table, m_tableType1);
}
void WidgetBank::ButtonFindPress(){
    this->m_output->CheckDate(m_headerLabels1,m_headerLabels2,m_tableType1,m_tableType2,m_output->vars5,m_output->vars6,
                              m_dateSBox->GetValue(),m_dateEBox->GetValue());
    m_count = WingWidget::BtnFind(this->m_output->vars5, m_table, m_tableType1);
}
void WidgetBank::ButtonAddPress(){
    if(m_editWidget1 == NULL){
        m_editWidget1 = new WidgetBankEdit(m_output,this);
        m_editWidget1->SetType(EditWidget::WidgetType::Add);
        m_editWidget1->show();
    }
    else{
        m_editWidget1->SetIndex();
        m_editWidget1->showNormal();
        m_editWidget1->activateWindow();
    }
}
void WidgetBank::ButtonDetailsPress(){
    if(m_table->currentRow()<m_count){
        int index=m_indexList[m_table->currentRow()+1];
        WidgetBankDetails *m_bankDetailsWidget = new WidgetBankDetails(m_output,this,index);
        m_bankDetailsWidget->SetDate(m_dateSBox->GetValue(),m_dateEBox->GetValue());
        m_bankDetailsWidget->ButtonFindPress();
        m_bankDetailsWidget->show();
        m_bankDetailsWidgetList.append(m_bankDetailsWidget);
    }
    else
        ButtonAddPress();
}
void WidgetBank::ButtonEditPress(){
    if(m_table->currentRow()<m_count){
        int index=m_indexList[m_table->currentRow()+1];
        if(m_editWidget2 == NULL){
            m_editWidget2 = new WidgetBankEdit(m_output,this,index);
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
void WidgetBank::ButtonDelPress(){
    QList<int>* indexList=WingWidget::BtnDel(m_count);
    if(indexList!=NULL){
        //Remove
        for(int i=indexList->count()-1;i>=0;i--)
            if(indexList->at(i)<m_count){
                m_output->vars5.removeAt(indexList->at(i)+1);
                m_output->vars6.removeAt(indexList->at(i)+1);
            }
        ButtonFindPress();
        delete indexList;
    }
}
void WidgetBank::ButtonOutputPress(){
    QString str;
    QString path;
    if(m_output->MessageQuestion("导出当前已搜索的内容,子级全部导出。\n请选择文件夹，导入新数据。\n选择原文件夹，会覆盖同名文件。建议选择新文件夹。")){
        QFileDialog *fileDialog = new QFileDialog(this);
        fileDialog->setWindowTitle("选择文件夹");
        fileDialog->setFileMode(QFileDialog::DirectoryOnly);
        if(fileDialog->exec()){
            str = fileDialog->selectedFiles()[0];
            QList<QList<QVariant>> list;
            int t_num=0;
            for(int i=1;i<m_indexList.count();i++){
                list.clear();
                for(int j=0;j<m_output->vars6[m_indexList.at(i)].count();j++)
                    list.append(m_output->vars6[m_indexList.at(i)][j]);
                QDir dir;
                if(!dir.exists(str+"/"+tr("银行")))//判断需要创建的文件夹是否存在
                    dir.mkdir(str+"/"+tr("银行")); //创建文件夹
                if(m_output->vars5[m_indexList.at(i)][1].isNull() || m_output->vars5[m_indexList.at(i)][1].toString()=="")
                    path = str+"/"+tr("银行")+"/Book"+(++t_num)+".xls";
                else
                    path = str+"/"+tr("银行")+"/"+m_output->vars5[m_indexList.at(i)][1].toString()+".xls";
                m_output->SaveOne(path, list);
            }
            m_output->MessageHit("已导出");
        }
    }
}
void WidgetBank::ButtonChangePress(){
    if(m_btn6->text() == "模式-查看"){
        m_btn6->setText("模式-修改");
        m_btn3->setText("修改(Space)");
        m_btn3->setShortcut(QKeySequence("Space"));
        disconnect(m_btn3,SIGNAL(clicked()),this,SLOT(ButtonDetailsPress()));
        disconnect(m_table,&QTableWidget::doubleClicked,this,&WidgetBank::ButtonDetailsPress);
        connect(m_btn3,SIGNAL(clicked()),this,SLOT(ButtonEditPress()));
        connect(m_table,&QTableWidget::doubleClicked,this,&WidgetBank::ButtonEditPress);
    }
    else{
        m_btn6->setText("模式-查看");
        m_btn3->setText("详情(Space)");
        m_btn3->setShortcut(QKeySequence("Space"));
        disconnect(m_btn3,SIGNAL(clicked()),this,SLOT(ButtonEditPress()));
        disconnect(m_table,&QTableWidget::doubleClicked,this,&WidgetBank::ButtonEditPress);
        connect(m_btn3,SIGNAL(clicked()),this,SLOT(ButtonDetailsPress()));
        connect(m_table,&QTableWidget::doubleClicked,this,&WidgetBank::ButtonDetailsPress);
    }
}

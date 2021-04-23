#include "widgetpurchase.h"
#include "widgetpurchasedetails.h"
#include "ubutton.h"
#include "udatebox.h"
#include "widgetpurchaseedit.h"
#include "output.h"
#include <QTableWidget>
#include <QFileDialog>

WidgetPurchase::WidgetPurchase(OutPut *m_output, WingWidget *m_parent)
    :WingWidget(m_output,m_parent)
{
    this->setWindowTitle("采购");
    m_type = 1;
    m_count = 0;
    m_isCheck = true;
    m_findLabels.append(m_output->m_findLabels1);
    m_headerLabels1.append(m_output->m_headerLabels1);
    m_headerLabels2.append(m_output->m_headerLabels2);
    m_tableType1.append(m_output->m_tableType1);
    m_tableType2.append(m_output->m_tableType2);
    Create();
    CreateNew();
}
WidgetPurchase::~WidgetPurchase(){
    for(int i=m_purchaseDetailsWidgetList.count()-1;i>=0;i--){
        delete m_purchaseDetailsWidgetList[i];
        m_purchaseDetailsWidgetList.removeAt(i);
    }
    if(m_editWidget1!=NULL) delete m_editWidget1;
    if(m_editWidget2!=NULL) delete m_editWidget2;
}
void WidgetPurchase::CreateNew(){
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
    connect(m_table,&QTableWidget::doubleClicked,this,&WidgetPurchase::ButtonDetailsPress);
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
    m_count = WingWidget::BtnFind(this->m_output->vars1, m_table, m_tableType1);
}
void WidgetPurchase::ButtonFindPress(){
    m_count = WingWidget::BtnFind(this->m_output->vars1, m_table, m_tableType1);
}
void WidgetPurchase::ButtonAddPress(){
    if(m_editWidget1 == NULL){
        m_editWidget1 = new WidgetPurchaseEdit(m_output,this);
        m_editWidget1->SetType(EditWidget::WidgetType::Add);
        m_editWidget1->show();
    }
    else{
        m_editWidget1->SetIndex();
        m_editWidget1->showNormal();
        m_editWidget1->activateWindow();
    }
}
void WidgetPurchase::ButtonDetailsPress(){
    if(m_table->currentRow()<m_count){
        int index=m_indexList[m_table->currentRow()+1];
        WidgetPurchaseDetails *m_purchaseDetailsWidget = new WidgetPurchaseDetails(m_output,this,index);
        m_purchaseDetailsWidget->SetDate(m_dateSBox->GetValue(),m_dateEBox->GetValue());
        m_purchaseDetailsWidget->ButtonFindPress();
        m_purchaseDetailsWidget->show();
        m_purchaseDetailsWidgetList.append(m_purchaseDetailsWidget);
    }
    else
        ButtonAddPress();
}
void WidgetPurchase::ButtonEditPress(){
    if(m_table->currentRow()<m_count){
        int index=m_indexList[m_table->currentRow()+1];
        if(m_editWidget2 == NULL){
            m_editWidget2 = new WidgetPurchaseEdit(m_output,this,index);
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
void WidgetPurchase::ButtonDelPress(){
    QList<int>* indexList=WingWidget::BtnDel(m_count);
    if(indexList!=NULL){
        //Remove
        for(int i=indexList->count()-1;i>=0;i--)
            if(indexList->at(i)<m_count){
                m_output->vars1.removeAt(indexList->at(i)+1);
                m_output->vars2.removeAt(indexList->at(i)+1);
            }
        ButtonFindPress();
        delete indexList;
    }
}
void WidgetPurchase::ButtonOutputPress(){
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
                for(int j=0;j<m_output->vars2[m_indexList.at(i)].count();j++)
                    list.append(m_output->vars2[m_indexList.at(i)][j]);
                QDir dir;
                if(!dir.exists(str+"/"+tr("采购")))//判断需要创建的文件夹是否存在
                    dir.mkdir(str+"/"+tr("采购")); //创建文件夹
                if(m_output->vars1[m_indexList.at(i)][2].isNull() || m_output->vars1[m_indexList.at(i)][2].toString()=="")
                    path = str+"/"+tr("采购")+"/Book"+(++t_num)+".xls";
                else
                    path = str+"/"+tr("采购")+"/"+m_output->vars1[m_indexList.at(i)][2].toString()+".xls";
                m_output->SaveOne(path, list);
            }
            m_output->MessageHit("已导出");
        }
    }
}
void WidgetPurchase::ButtonChangePress(){
    if(m_btn6->text() == "模式-查看"){
        m_btn6->setText("模式-修改");
        m_btn3->setText("修改(Space)");
        m_btn3->setShortcut(QKeySequence("Space"));
        disconnect(m_btn3,SIGNAL(clicked()),this,SLOT(ButtonDetailsPress()));
        disconnect(m_table,&QTableWidget::doubleClicked,this,&WidgetPurchase::ButtonDetailsPress);
        connect(m_btn3,SIGNAL(clicked()),this,SLOT(ButtonEditPress()));
        connect(m_table,&QTableWidget::doubleClicked,this,&WidgetPurchase::ButtonEditPress);
    }
    else{
        m_btn6->setText("模式-查看");
        m_btn3->setText("详情(Space)");
        m_btn3->setShortcut(QKeySequence("Space"));
        disconnect(m_btn3,SIGNAL(clicked()),this,SLOT(ButtonEditPress()));
        disconnect(m_table,&QTableWidget::doubleClicked,this,&WidgetPurchase::ButtonEditPress);
        connect(m_btn3,SIGNAL(clicked()),this,SLOT(ButtonDetailsPress()));
        connect(m_table,&QTableWidget::doubleClicked,this,&WidgetPurchase::ButtonDetailsPress);
    }
}

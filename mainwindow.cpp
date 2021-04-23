//窗口
#include "mainwindow.h"
#include "widgetpurchase.h"
#include "widgetsell.h"
#include "widgetbank.h"
#include "widgetincome.h"

#include <QGridLayout>
#include "ubutton.h"

#include "uloading.h"
#include <QTabWidget>
#include <QAction>
#include <QMenuBar>
//数据
#include "inidata.h"
#include "output.h"
//辅助
#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>
#include <QTimer>
#include <QInputDialog>
#include <QLineEdit>
#include <QCheckBox>
#include <QFileDialog>

MainWindow::MainWindow(IniData *ini, QWidget *parent) :
    QMainWindow(parent)
{
    //初始化
    m_ini=ini;
    setWindowTitle("销售管理系统");
    setAttribute(Qt::WA_QuitOnClose, true);
    m_output = new OutPut();
    CreateWidget();
    Loading();
}

MainWindow::~MainWindow(){
    if(m_purchaseWidget!=NULL) delete m_purchaseWidget;
    if(m_sellWidget!=NULL) delete m_sellWidget;
    if(m_bankWidget!=NULL) delete m_bankWidget;
    if(m_incomeWidget!=NULL) delete m_incomeWidget;
    delete m_output;

    delete m_layout;
    delete m_btn1;
    delete m_btn2;
    delete m_btn3;
    delete m_btn4;
    delete m_btn5;
    delete m_btn6;
}
//创建
void MainWindow::CreateWidget(){//创建窗口
    m_centerWindow = new QWidget(this);
    m_centerWindow->setFocusPolicy(Qt::NoFocus);
    m_layout = new QGridLayout();
    m_layout->setAlignment(Qt::AlignCenter);
    m_layout->setSpacing(20);
    m_layout->setMargin(50);
    m_btn1 = new UButton("采购", "", 100, 50, m_layout,0,0);
    m_btn2 = new UButton("销售", "", 100, 50, m_layout,1,0);
    m_btn3 = new UButton("银行", "", 100, 50, m_layout,2,0);
    m_btn4 = new UButton("收益", "", 100, 50, m_layout,0,1);
    m_btn5 = new UButton("导入", "", 100, 50, m_layout,1,1);
    m_btn6 = new UButton("导出", "", 100, 50, m_layout,2,1);
    m_purchaseWidget = NULL;
    m_sellWidget = NULL;
    m_bankWidget = NULL;
    m_incomeWidget = NULL;
    connect(m_btn1,  SIGNAL(clicked()), this, SLOT(OpenLayer1()));
    connect(m_btn2,  SIGNAL(clicked()), this, SLOT(OpenLayer2()));
    connect(m_btn3,  SIGNAL(clicked()), this, SLOT(OpenLayer3()));
    connect(m_btn4,  SIGNAL(clicked()), this, SLOT(OpenLayer4()));
    connect(m_btn5,  SIGNAL(clicked()), this, SLOT(OpenLayer5()));
    connect(m_btn6,  SIGNAL(clicked()), this, SLOT(OpenLayer6()));
    this->setCentralWidget(m_centerWindow);
    m_centerWindow->setLayout(m_layout);
}
void MainWindow::Loading(){
    //导入
    if(m_output->MessageQuestion("是否导入数据？")){
        QFileDialog *fileDialog = new QFileDialog(this);
        fileDialog->setWindowTitle("选择文件夹");
        fileDialog->setFileMode(QFileDialog::DirectoryOnly);
        if(fileDialog->exec()){
            QString str;
            str = m_output->Read(fileDialog->selectedFiles()[0]);
            m_output->MessageHit(str);
        }
    }
}
void MainWindow::OpenLayer1(){
    if(m_purchaseWidget == NULL){
        m_purchaseWidget = new WidgetPurchase(m_output,NULL);
        m_purchaseWidget->show();
    }
    else{
        m_purchaseWidget->showNormal();
        m_purchaseWidget->activateWindow();
    }
}
void MainWindow::OpenLayer2(){
    if(m_sellWidget == NULL){
        m_sellWidget = new WidgetSell(m_output,NULL);
        m_sellWidget->show();
    }
    else{
        m_sellWidget->showNormal();
        m_sellWidget->activateWindow();
    }
}
void MainWindow::OpenLayer3(){
    if(m_bankWidget == NULL){
        m_bankWidget = new WidgetBank(m_output,NULL);
        m_bankWidget->show();
    }
    else{
        m_bankWidget->showNormal();
        m_bankWidget->activateWindow();
    }

}
void MainWindow::OpenLayer4(){
    if(m_incomeWidget == NULL){
        m_incomeWidget = new WidgetIncome(m_output,NULL);
        m_incomeWidget->show();
    }
    else{
        m_incomeWidget->showNormal();
        m_incomeWidget->activateWindow();
    }
}
void MainWindow::OpenLayer5(){
    QString str;
    if(m_output->MessageQuestion("导入将清空当前已导入的数据。是否导入？")){
        QFileDialog *fileDialog = new QFileDialog(this);
        fileDialog->setWindowTitle("选择文件夹");
        fileDialog->setFileMode(QFileDialog::DirectoryOnly);
        if(fileDialog->exec()){
            str = m_output->Read(fileDialog->selectedFiles()[0]);
            m_output->MessageHit(str);
        }
    }
}
void MainWindow::OpenLayer6(){
    QString str;
    QString path;
    if(m_output->MessageQuestion("导出所有内容,子级全部导出。\n请选择文件夹，导入新数据。\n选择原文件夹，会覆盖同名文件。建议选择新文件夹。")){
        QFileDialog *fileDialog = new QFileDialog(this);
        fileDialog->setWindowTitle("选择文件夹");
        fileDialog->setFileMode(QFileDialog::DirectoryOnly);
        if(fileDialog->exec()){
            str = fileDialog->selectedFiles()[0];
            QList<QList<QVariant>> list;
            //采购
            int t_num=0;
            for(int i=1;i<m_output->vars2.count();i++){
                list.clear();
                for(int j=0;j<m_output->vars2[i].count();j++)
                    list.append(m_output->vars2[i][j]);
                QDir dir;
                if(!dir.exists(str+"/"+tr("采购")))//判断需要创建的文件夹是否存在
                    dir.mkdir(str+"/"+tr("采购")); //创建文件夹
                if(m_output->vars1[i][2].isNull() || m_output->vars1[i][2].toString()=="")
                    path = str+"/"+tr("采购")+"/Book"+(++t_num)+".xls";
                else
                    path = str+"/"+tr("采购")+"/"+m_output->vars1[i][2].toString()+".xls";
                m_output->SaveOne(path, list);
            }
            //销售
            t_num=0;
            for(int i=1;i<m_output->vars4.count();i++){
                list.clear();
                for(int j=0;j<m_output->vars4[i].count();j++)
                    list.append(m_output->vars4[i][j]);
                QDir dir;
                if(!dir.exists(str+"/"+tr("销售")))//判断需要创建的文件夹是否存在
                    dir.mkdir(str+"/"+tr("销售")); //创建文件夹
                if(m_output->vars3[i][3].isNull() || m_output->vars3[i][3].toString()=="")
                    path = str+"/"+tr("销售")+"/Book"+(++t_num)+".xls";
                else
                    path = str+"/"+tr("销售")+"/"+m_output->vars3[i][3].toString()+".xls";
                m_output->SaveOne(path, list);
            }
            //银行
            t_num=0;
            for(int i=1;i<m_output->vars6.count();i++){
                list.clear();
                for(int j=0;j<m_output->vars6[i].count();j++)
                    list.append(m_output->vars6[i][j]);
                QDir dir;
                if(!dir.exists(str+"/"+tr("银行")))//判断需要创建的文件夹是否存在
                    dir.mkdir(str+"/"+tr("银行")); //创建文件夹
                if(m_output->vars5[i][1].isNull() || m_output->vars5[i][1].toString()=="")
                    path = str+"/"+tr("银行")+"/Book"+(++t_num)+".xls";
                else
                    path = str+"/"+tr("银行")+"/"+m_output->vars5[i][1].toString()+".xls";
                m_output->SaveOne(path, list);
            }
            m_output->MessageHit("已导出");
        }
    }
}

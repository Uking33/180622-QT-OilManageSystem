#include "uloading.h"

#include <QHBoxLayout>
#include <QProgressBar>
#include <QPushButton>

#include <QLabel>

#include "uthread.h"
#include "output.h"

#include <QCloseEvent>
#include <QMessageBox>
#include <QTimer>

ULoading::ULoading(OutPut *output){
    //init
    m_output = output;
    m_thread = NULL;
    //界面
    progressBar = new QProgressBar();
    debug = new QLabel();
    layout = new QHBoxLayout();

    debug->setFixedWidth(120);
    debug->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);

    layout->addWidget(progressBar);
    layout->addWidget(debug);
    this->setLayout(layout);
}
ULoading::~ULoading(){
    delete progressBar;
    delete debug;
    delete layout;
    if(m_thread!=NULL){
        m_thread->stop();
        delete m_thread;
    }
}
void ULoading::RunGet(QString str){
    debug->setText("加载-"+str);
    m_gress++;
    progressBar->setValue(m_gress*100/m_count);
    if(m_gress==m_count)
        End();
}
void ULoading::Start(int count, QString fun, QString str1, QString str2, QString str3){
    m_gress=0;
    progressBar->setValue(0);
    m_count = count;
    m_thread = new UThread;
    m_thread->Set(m_output,fun,str1,str2,str3);
    connect(m_thread, &UThread::finished, m_thread, &UThread::deleteLater);
    connect(m_output, &OutPut::LoadHit,
            this, &ULoading::RunGet, Qt::QueuedConnection);
    m_thread->start();
    this->exec();
    disconnect(m_output, &OutPut::LoadHit,
               this, &ULoading::RunGet);
}
//void ULoading::Start(int count, QString fun, QString str1, QString str2, QList<QList<QVariant>> *list){
//    m_gress=0;
//    progressBar->setValue(0);
//    m_count = count;
//    m_thread = new UThread;
//    m_thread->Set(m_output,fun,str1,str2,list);
//    connect(m_thread, &UThread::finished, m_thread, &UThread::deleteLater);
//    connect(m_output, &OutPut::LoadHit,
//            this, &ULoading::RunGet, Qt::QueuedConnection);
//    m_thread->start();
//    this->exec();
//    disconnect(m_output, &OutPut::LoadHit,
//               this, &ULoading::RunGet);
//}
void ULoading::End(){
    this->close();
}

void ULoading::closeEvent(QCloseEvent *event)
{
    if(progressBar->value()<100){
        event->ignore();  //忽略退出信号，程序继续运行
        QMessageBox message(QMessageBox::Information, "提示", QString("请等待运行完毕!"));
        message.exec();
    }
}

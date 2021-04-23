#include "uthread.h"
#include "output.h"
#include <QVariant>
UThread::UThread(QObject *parent)
        : QThread(parent)
{
}

void UThread::stop(){
    //QMetaObject::invokeMethod(m_data, "Stop", Qt::DirectConnection);
}
void UThread::Set(OutPut *output, const QString fun, const QString str1, const QString str2, const QString str3)
{
    m_model=1;
    m_output=output;
    m_str1=str1;
    m_str2=str2;
    m_str3=str3;
    m_fun=fun;
}
//void UThread::Set(OutPut *output, QString fun, QString str1, QString str2, QList<QList<QVariant>> *list){
//    m_model=2;
//    m_output=output;
//    m_str1=str1;
//    m_str2=str2;
//    m_list=list;
//    m_fun=fun;
//}
void UThread::run() {
    switch(m_model){
        case 1:
            QMetaObject::invokeMethod(m_output, m_fun.toLocal8Bit().data(), Qt::DirectConnection, Q_ARG(QString, m_str1), Q_ARG(QString, m_str2), Q_ARG(QString, m_str3));
            break;
//        case 2:
//            qRegisterMetaType<QList<QList<QVariant>>*>("QList<QList<QVariant>>*");
//            QMetaObject::invokeMethod(m_output, m_fun.toLocal8Bit().data(), Qt::DirectConnection, Q_ARG(QString, m_str1), Q_ARG(QString, m_str2), Q_ARG(QList<QList<QVariant>>*, m_list));
//            break;
    }
}

#ifndef UTHREAD_H
#define UTHREAD_H

#include <QThread>
#include <QStringList>
class OutPut;
//class PhoneData;

class UThread:public QThread{
    Q_OBJECT
public slots:
    void stop();
public:
    explicit UThread(QObject *parent = 0);
    void Set(OutPut *output, QString fun, const QString str1, QString str2, QString str3);
    //void Set(OutPut *output, QString fun, QString dateS, QString str2, QList<QList<QVariant>> *list);
protected:
    void run();
private:
    OutPut *m_output;
    QString m_fun;
    QString m_str1;
    QString m_str2;
    QString m_str3;
    QList<QList<QVariant>> * m_list;

    int m_model;
signals:
    void done();
    void runHint(QString str);
};

#endif // UTHREAD_H

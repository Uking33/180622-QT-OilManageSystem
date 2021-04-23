#ifndef ULOADING_H
#define ULOADING_H

#include <QDialog>
class QProgressBar;
class QPushButton;
class QHBoxLayout;
class QLabel;

class OutPut;
class PhoneData;
class UThread;

class ULoading : public QDialog
{
    Q_OBJECT
public:
    ULoading(OutPut *output);
    ~ULoading();
    UThread * m_thread;
public slots:
    void RunGet(QString str);
    void Start(int count, QString fun, QString str1, QString str2, QString str3);
    //void Start(int count, QString fun, QString str1, QString str2, QList<QList<QVariant>> *list);
    void End();
protected:
    void closeEvent(QCloseEvent *event);
private:
    QProgressBar *progressBar;
    QHBoxLayout *layout;
    QLabel *debug;
    OutPut *m_output;
    long long m_count;
    long long m_gress;
};


#endif // ULOADING_H

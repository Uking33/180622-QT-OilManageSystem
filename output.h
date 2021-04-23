#ifndef OUTPUT_H
#define OUTPUT_H

#include <QList>
#include <QObject>
#include <QMap>

class QVariant;
class QTableWidget;
class QStringList;
class ULoading;

class OutPut: public QObject
{
    Q_OBJECT
public:
    OutPut();
    ~OutPut();
    QVariant GetEmpty(QString type);
    void SaveOne(QString path, QList<QList<QVariant>>& varList);
    QString m_hit;
    ULoading *m_uloading;
    QString Read(QString pathPre);
    bool ReadAll(QString pathPre, QStringList strList, QStringList tableType, QStringList autoList, QList<QList<QList<QVariant>>>& varList);
    void ReadOne(QString path, QStringList strList, QStringList tableType, QStringList autoList, QList<QList<QList<QVariant> > > &varList);
    void Sum(QStringList strList1, QStringList strList2, QStringList tableType1, QStringList tableAuto,
             QList<QList<QList<QVariant>>>& varList1, QList<QList<QVariant>>& var);
    void CheckChoose(QStringList strList1, QStringList strList2, QStringList tableAuto,
                             QList<QList<QList<QVariant>>>& varList1, QList<QList<QVariant>>& var, int index=-1);
    void CheckDate(QStringList strList1, QStringList strList2, QStringList tableType1, QStringList tableType2,
                   QList<QList<QVariant>>& var1, QList<QList<QList<QVariant>>>& var2, QString date1, QString date2, int index=-1);
    bool SortByStringList(QList<QList<QVariant> > &list, QStringList sortList);    
    bool SortByDate(QList<QList<QVariant>> &list, int index);    
    bool SortByCol(QTableWidget* table, int index, QList<int> &indexList, Qt::SortOrder order);
    int VarToTable(QList<QList<QVariant>>& var, QTableWidget *tableWidget, QStringList strList, int maxRow=10);
public:
    QList<QList<QVariant>> vars1, vars3, vars5, vars7;
    QList<QList<QList<QVariant>>> vars2, vars4, vars6, vars8;
    QStringList m_findLabels1, m_findLabels2, m_findLabels3, m_findLabels4, m_findLabels5, m_findLabels6, m_findLabels7, m_findLabels8;
    QStringList m_headerLabels1, m_headerLabels2, m_headerLabels3, m_headerLabels4, m_headerLabels5, m_headerLabels6, m_headerLabels7, m_headerLabels8;
    QStringList m_tableType1, m_tableType2, m_tableType3, m_tableType4, m_tableType5, m_tableType6, m_tableType7, m_tableType8;
    //0-SINGLE 1-ALL 2-SUM 3-CHOOSE/IF 4-* 5-OTHER
    //3:0 等于总
    //$n1,n2,n3,(n4) n1-ArrayName
    //n2-正数=行，0=当前行，-1=上一行
    //n3-正数=行，0=当前行，-1=全部~=n4项匹配
    //n4-项目
    QStringList m_tableAuto1, m_tableAuto2, m_tableAuto3, m_tableAuto4, m_tableAuto5, m_tableAuto6, m_tableAuto7, m_tableAuto8;
    QMap<QString,int> m_indexList;
    QList<int> m_typeList;
    QList<int> m_typeIndexList;
public:
    //弹框
    void MessageHit(const QString &text);
    void MessageHit(const QString &text, int msec);
    bool MessageQuestion(const QString &text);
public slots:
    void ReadRun(QString path1,QString path2,QString path3);
    void Add78();
signals:
    void LoadHit(QString str);
};

#endif // OUTPUT_H

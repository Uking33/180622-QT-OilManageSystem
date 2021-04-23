#ifndef WINGWIDGET_H
#define WINGWIDGET_H

//窗口
#include <QWidget>
class OutPut;
//布局
class QVBoxLayout;
class QHBoxLayout;
//控件
class QTableWidget;
class QLabel;
class QComboBox;
class QLineEdit;
class UButton;
class UDateBox;
class UTimeBox;
class ULine;
class URectBox;
class UMulRadio;
//辅助
class QTableWidgetSelectionRange;
class QTableWidgetItem;
class QresizeEvent;
class ULoading;

class WingWidget: public QWidget
{
    Q_OBJECT
public://公有函数
    WingWidget(OutPut *m_output, WingWidget *m_parent);
    ~WingWidget();
    void ChangeType(int tpye = -1);
protected://保护数据
    OutPut *m_output;
    WingWidget *m_parent;
    QList<int> m_indexList;
    ULoading *m_uloading;
protected://保护控件
    QVBoxLayout *m_layout;
    QHBoxLayout *m_layout1;
    QHBoxLayout *m_layout2;
    QHBoxLayout *m_layout3;

    QHBoxLayout *m_dateSLayout;
    QLabel *m_dateSLabel;
    UDateBox *m_dateSBox;
    UButton *m_dateSBtn1;
    UButton *m_dateSBtn2;

    QHBoxLayout *m_findLayout;
    QLabel *m_findLabel;
    QComboBox *m_findBox;
    QLineEdit *m_findEdit;

    QHBoxLayout *m_dateELayout;
    QLabel *m_dateELabel;
    UDateBox *m_dateEBox;
    UButton *m_dateEBtn1;
    UButton *m_dateEBtn2;

    bool m_isCheck;
    UMulRadio *m_radio1;
    UMulRadio *m_radio2;
    UMulRadio *m_radio3;

    QHBoxLayout *m_btnLayout;
    UButton *m_btn1;
    UButton *m_btn2;
    UButton *m_btn3;
    UButton *m_btn4;
    UButton *m_btn5;
    UButton *m_btn6;

    QTableWidget *m_table_up;
    QTableWidget *m_table;

    QStringList m_findLabels;
    QStringList m_headerLabels1;
    QStringList m_headerLabels2;
    QStringList m_tableType1;
    QStringList m_tableType2;
    int m_type; //table choose type
    bool m_isDetails;
protected://保护函数
    void ClearWidget();
    void Create();
protected slots://保护槽函数
    void FindChange(int index);
    void TableSort(int index);
public:
    int BtnFind(QList<QList<QVariant> > &oList, QTableWidget *tableWidget, QStringList strList, int maxRow=10);
    QList<int> *BtnDel(int maxCount);   //outside delete *
    void DelSum(QList<int>* indexList, int m_index, QList<QList<QVariant>>*m_var1, QList<QList<QList<QVariant> > > *m_var2, QStringList m_tableAuto, QStringList  m_tableType);
};

#endif // WINGWIDGET_H

#ifndef EDITWIDGET_H
#define EDITWIDGET_H

//窗口
#include <QWidget>
//布局
class QVBoxLayout;
class QHBoxLayout;
//控件
class QTableWidget;
class QLabel;
class QComboBox;
class QLineEdit;
class QCheckBox;
class UButton;
class UDateBox;
class UTimeBox;
class ULine;
class URectBox;
class URadio;

#include <QMap>

class OutPut;
class WingWidget;

class EditWidget: public QWidget
{
    Q_OBJECT
public:
    enum EditType {
        Text = 0,
        Number,
        Int,
        ComboBox,
        Date,
        Radio
    };
    enum WidgetType {
        None = 0,
        Info,
        Add,
        Edit
    };
    class EditLine{
    public:
        QString tag;
        QString name;
        EditType type;
        QString tip;
        QList<QString> list;
        EditLine();
        EditLine(QString name, QString tag, EditType type, QString tip);
        EditLine(QString name, QString tag, EditType type, QString tip, QList<QString> list);
    };
public:
    EditWidget(OutPut *m_output, WingWidget *m_parent);
    ~EditWidget();
    void SetType(WidgetType type);
    void SetIndex(int index1=-1, int index2=-1, bool isDetails=false);
    void BtnAdd();
    void BtnEdit();
    virtual void BtnFlash();
    virtual void BtnCal();
    bool Check();
    void Loading();
    void AddLine(EditLine line);
    void AddButton(WidgetType type);
private:
    QVBoxLayout *m_layout;
    QHBoxLayout *m_btnLayout;
    QHBoxLayout *m_dateLayout;
protected:
    OutPut *m_output;
    WingWidget *m_parent;
    int m_index1,m_index2;
    QMap<QString,QString> m_tagMap;
    QMap<QString,QString> m_typeMap;
    QList<QList<QVariant>>* m_var1;
    QList<QList<QList<QVariant>>>* m_var2;
    QStringList m_headerLabels1;
    QStringList m_headerLabels2;
    QStringList m_tableType1;
    QStringList m_tableType2;
    QStringList m_tableAuto1;
    QStringList m_tableAuto2;
public:
    QHash<QString, ULine*> m_lineHash;
    QHash<QString, UDateBox*> m_dateHash;
    QHash<QString, URadio*> m_radioHash;
    QHash<QString, UButton*> m_btnHash;
    QHash<QString, QComboBox*> m_qComboBoxHash;
    QHash<QString, QLabel*> m_labelHash;
};


#endif // EDITWIDGET_H

#ifndef URADIO_H
#define URADIO_H

//窗口
#include <QHBoxLayout>
//控件
class QCheckBox;
class QLabel;

class URadio:public QHBoxLayout{
    Q_OBJECT
public:
    URadio(QString str, QString text1, QString text2="", QString text3="", int widthLabel=80, int heightLabel=25);
    ~URadio();
    QLabel *m_label;
    QCheckBox *m_btn1;
    QCheckBox *m_btn2;
    QCheckBox *m_btn3;
    bool GetValue(int index);
    void SetValue(int index, bool isChecked);
};

#endif // URADIO_H

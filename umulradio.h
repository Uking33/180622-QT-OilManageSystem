#ifndef UMULRADIO_H
#define UMULRADIO_H

//窗口
#include <QGroupBox>
//控件
class QHBoxLayout;
class QRadioButton;
class QLabel;

class UMulRadio:public QGroupBox{
    Q_OBJECT
public:
    UMulRadio(QString str, QString text1, QString text2="", QString text3="", int widthLabel=80, int heightLabel=25);
    ~UMulRadio();
    QLabel *m_label;
    QHBoxLayout * m_layout;
    QRadioButton *m_btn1;
    QRadioButton *m_btn2;
    QRadioButton *m_btn3;
    int GetValue();
    void SetValue(int index);
};

#endif // UMULRADIO_H

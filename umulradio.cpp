#include "umulradio.h"
#include <QRadioButton>
#include <QLabel>
#include <QHBoxLayout>

UMulRadio::UMulRadio(QString str,QString text1,QString text2,QString text3,int widthLabel,int heightLabel){
    m_label = new QLabel(str);
    m_label->setMaximumSize(widthLabel,heightLabel);
    m_label->setMinimumSize(widthLabel,heightLabel);
    m_btn1 = new QRadioButton();
    m_btn1->setText(text1);
    m_btn2 = new QRadioButton();
    m_btn2->setText(text2);
    m_btn3 = new QRadioButton();
    m_btn3->setText(text3);
    m_layout = new QHBoxLayout();
    m_layout->addWidget(m_label);
    m_layout->addWidget(m_btn1);
    m_layout->addWidget(m_btn2);
    m_layout->addWidget(m_btn3);
    this->setLayout(m_layout);
    m_btn1->setChecked(true);
}
UMulRadio::~UMulRadio(){
    delete m_label;
    delete m_btn1;
    delete m_btn2;
    delete m_btn3;
    delete m_layout;
}
int UMulRadio::GetValue(){
    if(m_btn1->isChecked())
        return 1;
    else if(m_btn2->isChecked())
        return 2;
    else if(m_btn3->isChecked())
        return 3;
    return 0;
}
void UMulRadio::SetValue(int index){
    switch(index){
    case 1:
        m_btn1->setChecked(true);
        m_btn2->setChecked(false);
        m_btn3->setChecked(false);
        break;
    case 2:
        m_btn1->setChecked(false);
        m_btn2->setChecked(true);
        m_btn3->setChecked(false);
        break;
    case 3:
        m_btn1->setChecked(false);
        m_btn2->setChecked(false);
        m_btn3->setChecked(true);
        break;
    default:
        break;
    }
}

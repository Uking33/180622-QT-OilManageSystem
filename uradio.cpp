#include "uradio.h"
#include <QCheckBox>
#include <QLabel>

URadio::URadio(QString str,QString text1,QString text2,QString text3,int widthLabel,int heightLabel){
    m_label = new QLabel(str);
    m_label->setMaximumSize(widthLabel,heightLabel);
    m_label->setMinimumSize(widthLabel,heightLabel);
    this->addWidget(m_label);
    m_btn1 = new QCheckBox();
    m_btn1->setText(text1);
    this->addWidget(m_btn1);
    if(text2!=""){
        m_btn2 = new QCheckBox();
        m_btn2->setText(text2);
        this->addWidget(m_btn2);
    }
    else
        m_btn2=NULL;
    if(text3!=""){
        m_btn3 = new QCheckBox();
        m_btn3->setText(text3);
        this->addWidget(m_btn3);
    }
    else
        m_btn3=NULL;
}
URadio::~URadio(){
    delete m_label;
    delete m_btn1;
    if(m_btn2!=NULL) delete m_btn2;
    if(m_btn3!=NULL) delete m_btn3;
}
bool URadio::GetValue(int index){
    switch(index){
    case 1:
        return m_btn1->isChecked();
    case 2:
        if(m_btn2!=NULL)
            return m_btn2->isChecked();
        else
            return false;
    case 3:
        if(m_btn3!=NULL)
            return m_btn3->isChecked();
        else
            return false;
    default:
        return false;
    }
}
void URadio::SetValue(int index, bool isChecked){
    switch(index){
    case 1:
        m_btn1->setChecked(isChecked);
        break;
    case 2:
        if(m_btn2!=NULL)
            m_btn2->setChecked(isChecked);
        break;
    case 3:
        if(m_btn3!=NULL)
            m_btn3->setChecked(isChecked);
        break;
    default:
        break;
    }
}

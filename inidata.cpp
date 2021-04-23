#include "inidata.h"
#include "QSettings"

IniData::IniData()
{
    //Loading();
}

IniData::~IniData()
{

}

void IniData::Loading(){
    QSettings *configIni = new QSettings("config.ini", QSettings::IniFormat);
    //---账单---
    //读
    m_recordTitle=configIni->value("/record/title").toString();
    m_recordAddress=configIni->value("/record/address").toString();
    m_recordPhone=configIni->value("/record/phone").toString();
    m_recordAddition=configIni->value("/record/addition").toString();
    if(m_recordTitle==""||m_recordAddress==""||m_recordPhone==""||m_recordAddition==""){
        //写
        m_recordTitle="";
        m_recordAddress="";
        m_recordPhone="";
        m_recordAddition="";
        configIni->setValue("/record/title",m_recordTitle);
        configIni->setValue("/record/address",m_recordAddress);
        configIni->setValue("/record/phone",m_recordPhone);
        configIni->setValue("/record/addition",m_recordAddition);
    }
    //---登录---
    //读
    m_loginName=configIni->value("/login/name").toString();
    if(m_loginName=="")//写
        configIni->setValue("/login/name","");
    delete configIni;
}

void IniData::recordSave(){
    QSettings *configIni = new QSettings("config.ini", QSettings::IniFormat);
    configIni->setValue("/record/title",m_recordTitle);
    configIni->setValue("/record/address",m_recordAddress);
    configIni->setValue("/record/phone",m_recordPhone);
    configIni->setValue("/record/addition",m_recordAddition);
    delete configIni;
}

void IniData::loginSave(){
    QSettings *configIni = new QSettings("config.ini", QSettings::IniFormat);
    configIni->setValue("/login/name",m_loginName);
    delete configIni;
}

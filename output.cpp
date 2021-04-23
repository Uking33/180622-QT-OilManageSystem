#include "output.h"
#include "uloading.h"
#include <QTableWidget>
#include <QHeaderView>
#include <QFileDialog>
#include <QDesktopServices>
#include <QMessageBox>
#include <QAxObject>
#include <QApplication>

#include "excelengine.h"
#include <QMessageBox>
#include <QTimer>
#include <QDate>

OutPut::OutPut()
{
    //tag-purchase
    m_findLabels1<< "全部"<< "供应商"<< "合同号"<< "品种";
    m_headerLabels1<< "日期"<< "供应商"<< "合同号"<< "品种"<< "订单数量"<< "来货数"<< "卸货数"
        << "单价"<< "应付金额"<< "付款金额"<< "余额"<< "含税"<< "完成"<< "支付";
    m_tableType1<< "date"<< "text"<< "text"<< "text"<< "int"<< "int"<< "int"
               << "numC"<< "num"<< "num"<< "numE"<< "text"<< "text"<< "text";
    m_tableAuto1<< "0"<< "0"<< "0"<< "0"<< "1"<< "1"<< "1"
                << "0"<< "4:5,8"<< "1"<< "2:-9,10"<< "3:"<< "3:$11=0"<< "3:$1/0/9=$6/-1/3~8/5";
    m_findLabels2<< "全部"<< "提货单号"<< "车号"<< "备注";
    m_headerLabels2<< "日期"<< "供应商"<< "合同号"<< "品种"<< "提货单号"<< "车号"<< "订单数量"<< "来货数"<< "卸货数"
        << "单价"<< "应付金额"<< "付款金额"<< "余额"<< "备注"<< "含税"<< "完成"<< "支付";
    m_tableType2<< "date"<< "text"<< "text"<< "text"<< "text"<< "text"<< "int"<< "int"<< "int"
               << "numC"<< "num"<< "num"<< "numE"<< "text"<< "text"<< "text"<< "text";
    m_tableAuto2<< "0"<< "1"<< "1"<< "1"<< "0"<< "0"<< "0"<< "0"<< "0"
                << "1"<< "4:7,10"<< "0"<< "2:-11,12"<< "0"<< "3:"<< "3:0"<< "3:0";
    //tag-sell
    m_findLabels3<< "全部"<< "名称"<< "客户"<< "订单号"<< "品种";
    m_headerLabels3<< "日期"<< "名称"<< "客户"<< "订单号"<< "品种"<< "数量/T"
                << "单价"<< "金额"<< "收款金额"<< "应收余额"<< "含税"<< "完成"<< "支付";
    m_tableType3<< "date"<< "text"<< "text"<< "text"<< "text"<< "num"
               << "numC"<< "num"<< "num"<< "numE"<< "text"<< "text"<< "text";
    m_tableAuto3<< "0"<< "0"<< "0"<< "0"<< "0"<< "1"
                << "0"<< "4:5,6"<< "1"<< "2:7,-8"<< "3:"<< "3:$9=0"<< "3:$3/0/9=$6/-1/4~8/4";
    m_findLabels4<< "全部"<< "订单号"<< "车号"<< "备注";
    m_headerLabels4<< "日期"<< "名称"<< "客户"<< "订单号"<< "品种"<< "车号"<< "数量/T"
        << "单价"<< "金额"<< "收款金额"<< "应收余额"<< "备注"<< "含税"<< "完成"<< "支付";
    m_tableType4<< "date"<< "text"<< "text"<< "text"<< "text"<< "text"<< "num"
               << "numC"<< "num"<< "num"<< "numE"<< "text"<< "text"<< "text"<< "text";
    m_tableAuto4<< "0"<< "1"<< "1"<< "1"<< "1"<< "0"<< "1"
                << "1"<< "4:7,8"<< "0"<< "2:9,-10"<< "0"<< "3:"<< "3:0"<< "3:0";
    //tag-bank
    m_findLabels5<< "全部"<< "银行名称";
    m_headerLabels5<< "日期"<< "银行名称"<< "上期余额"<< "收款金额"<< "付款金额"<< "本期余额";
    m_tableType5<< "date"<< "text"<< "numS"<< "num"<< "num"<< "numE";
    m_tableAuto5<< "0"<< "0"<< "5:0"<< "1"<< "1"<< "2:4,-5";
    m_findLabels6<< "全部"<< "银行名称"<< "客户/供应商"<< "合同号/订单号"<< "用途"<< "备注";
    m_headerLabels6<< "日期"<< "银行名称"<< "上期余额"<< "收款金额"<< "付款金额"<< "本期余额"
                   << "客户/供应商"<< "合同号/订单号"<< "用途"<< "备注";
    m_tableType6<< "date"<< "text"<< "numS"<< "num"<< "num"<< "numE"
               << "text"<< "text"<< "text"<< "text";
    m_tableAuto6<< "0"<< "1"<< "5:$-1/6"<< "0"<< "0"<< "2:4,-5"
                << "0"<< "0"<< "0"<< "0";
    //tag-income
    m_findLabels7<< "全部";
    m_headerLabels7<< "日期"<< "合同号/订单号"<< "客户/供应商"
                   << "上期余额"<< "收款金额"<< "付款金额"<< "本期余额"<<"应收未收"<<"应付未付"<<"利润";
    m_tableType7<< "date"<< "text"<< "text"
                << "numS"<< "num"<< "num"<< "numE"<< "num"<< "num"<< "num";
    m_findLabels8<< "全部"<< "合同号/订单号"<< "客户/供应商"<< "银行名称";
    m_headerLabels8<< "日期"<< "合同号/订单号"<< "客户/供应商"<< "银行名称"
                   << "上期余额"<< "收款金额"<< "付款金额"<< "本期余额";
    m_tableType8<< "date"<< "text"<< "text"<< "text"
                << "numS"<< "num"<< "num"<< "numE";
    //Add78
}
OutPut::~OutPut(){
}

void OutPut::SaveOne(QString path, QList<QList<QVariant>>& varList){
    path =  path.replace('/','\\');
    ExcelEngine excel; //创建excl对象
    excel.Open(path,1,false); //打开指定的xls文件的指定sheet，且指定是否可见
    for (int i=0; i<varList.count(); i++)
    {
        for (int j=0; j<varList.at(i).count(); j++)
        {
            excel.SetCellData(i+1,j+1,varList.at(i).at(j)); //修改指定单元数据
        }
    }
    excel.Save(); //保存
    excel.Close();
}

QVariant OutPut::GetEmpty(QString type){
    if(type=="date"){
        return QVariant(QDate::currentDate().toString("yyyy.M.d"));
    }
    else if(type=="text"){
        return QVariant("");
    }
    else if(type=="int"){
        return QVariant((int)0);
    }
    else if(type=="num" || type=="numC" || type=="numS" || type=="numE"){
        return QVariant((double)0);
    }
    return QVariant("");
}
QString OutPut::Read(QString pathPre){
    vars1.clear();
    vars2.clear();
    vars3.clear();
    vars4.clear();
    vars5.clear();
    vars6.clear();
    m_hit.clear();
    QString path1,path2,path3;
    path1 = pathPre.replace('/','\\')+'\\'+"银行";
    path2 = pathPre.replace('/','\\')+'\\'+"采购";
    path3 = pathPre.replace('/','\\')+'\\'+"销售";
    m_uloading=new ULoading(this);
    //count
    QStringList nameFilters;
    QDir dir;
    int count = 2+2;
    nameFilters << "*.xls" << "*.xlsx";
    dir.setPath(path1);
    count += 1+dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name).count();
    dir.setPath(path2);
    count += 1+dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name).count();
    dir.setPath(path3);
    count += 1+dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name).count();
    m_uloading->Start(count,"ReadRun",path1,path2,path3);
    delete m_uloading;
    return m_hit;
}
void OutPut::ReadRun(QString path1,QString path2,QString path3){
    //begin
    bool b;
    emit LoadHit("开始导入");
    //银行
    b=this->ReadAll(path1, m_headerLabels6, m_tableType6, m_tableAuto6, this->vars6);
    this->Sum(m_headerLabels6, m_headerLabels5, m_tableType5, m_tableAuto5, this->vars6, this->vars5);
    emit LoadHit("完成银行导入");
    if(b)
        m_hit+="已导入银行数据\n";
    else
        m_hit+="子文件夹不存在文件夹-银行\n";
    //采购
    b=this->ReadAll(path2, m_headerLabels2, m_tableType2, m_tableAuto2, this->vars2);
    this->Sum(m_headerLabels2, m_headerLabels1, m_tableType1, m_tableAuto1, this->vars2, this->vars1);
    emit LoadHit("完成采购导入");
    if(b)
        m_hit+="已导入采购数据\n";
    else
        m_hit+="子文件夹不存在文件夹-采购\n";
    //销售
    b=this->ReadAll(path3, m_headerLabels4, m_tableType4, m_tableAuto4, this->vars4);
    this->Sum(m_headerLabels4, m_headerLabels3, m_tableType3, m_tableAuto3, this->vars4, this->vars3);
    emit LoadHit("完成销售导入");
    if(b)
        m_hit+="已导入销售数据\n";
    else
        m_hit+="子文件夹不存在文件夹-销售\n";
    emit LoadHit("计算统计信息");
    Add78();
    emit LoadHit("完成计算统计信息");
    emit LoadHit("完成导入");
}
bool OutPut::ReadAll(QString pathPre, QStringList strList, QStringList tableType, QStringList autoList, QList<QList<QList<QVariant>>>& varList){
    QDir dir(pathPre);
    QStringList nameFilters;
    nameFilters << "*.xls" << "*.xlsx";
    QStringList files = dir.entryList(nameFilters, QDir::Files|QDir::Readable, QDir::Name);
    varList.append(QList<QList<QVariant>>());
    for(int i=0; i<files.count(); i++){
        QString path = pathPre+'\\'+files.at(i);
        ReadOne(path,strList,tableType,autoList,varList);
        emit LoadHit(path);
    }
    if(files.count()==0)
        return false;
    return true;
}

void OutPut::ReadOne(QString path, QStringList strList, QStringList tableType, QStringList autoList, QList<QList<QList<QVariant>>>& varList){
    QList<QList<QVariant>> t_var;
    QStringList t_strList(strList);
    QStringList t_tableType(tableType);
    ExcelEngine excel(path);
    excel.Open();
    if(excel.IsOpen() && excel.IsValid()){
        int rows = excel.GetRowCount();
        t_var = excel.GetAllCellsData();
        //Add others
        if(t_var.count()==0){
            excel.Close();
            return;
        }
        for(int i=0;i<t_var[0].count();i++){
            if(strList.contains(t_var[0][i].toString())){
                t_tableType.removeAt(t_strList.indexOf(t_var[0][i].toString()));
                t_strList.removeOne(t_var[0][i].toString());
            }
            else{
                for(int j=0;j<rows;j++){
                    t_var[j].removeAt(i);
                }
                i--;
            }
        }
        for(int k=0;k<t_strList.count();k++){
            t_var[0].append(QVariant(t_strList.at(k)));
            for(int j=1;j<rows;j++){
                t_var[j].append(GetEmpty(t_tableType.at(k)));
            }
        }
        //Sort
        SortByStringList(t_var,strList);
        //Insert
        for(int j=1;j<rows;j++){
            for(int i=0;i<t_var[0].count();i++){
                QStringList strList1=((QString)autoList[i]).split(';');
                for(int k=0;k<strList1.count();k++){
                    QStringList strList2=((QString)strList1[k]).split(':');
                    QStringList strList3;
                    switch (((QString)strList2[0]).toInt()) {
                    case 0:
                    case 1:{
                        if(t_var[j][i].isNull() || !t_var[j][i].isValid()){
                            t_var[j][i].setValue(GetEmpty(tableType.at(i)));
                        }
                        else{
                            QString type = tableType.at(i);
                            if(type=="date"){
                                QString str=t_var[j][i].toString();
                                QStringList dateList;
                                if(str.contains('T')){
                                    int index=str.indexOf('T');
                                    str=str.remove(index,str.count()-index);
                                }
                                if(str.contains('.'))
                                    dateList=str.split('.');
                                else if(str.contains('/'))
                                    dateList=str.split('/');
                                else if(str.contains('-'))
                                    dateList=str.split('-');
                                else if(str.count()==8){
                                    dateList.append(str.mid(0,4));
                                    dateList.append(str.mid(4,2));
                                    dateList.append(str.mid(6,2));
                                }
                                if(dateList.count()==3)
                                    t_var[j][i].setValue(QVariant(QString("%1.%2.%3").arg(((QString)dateList[0]).toInt()).
                                                         arg(((QString)dateList[1]).toInt()).arg(((QString)dateList[2]).toInt())));
                                else
                                    t_var[j][i].setValue(QVariant(QDate::currentDate().toString("yyyy.M.d")));
                            }
                        }
                        break;
                    }
                    case 2:{
                        strList3=((QString)strList2[1]).split(',');
                        float sum;
                        if(j==0)
                            sum = 0;
                        else
                            sum = t_var[j-1][i].toFloat();
                        for(int n=0;n<strList3.count();n++){
                            int index=((QString)strList3[n]).toInt();
                            if(index>0)
                                sum += t_var[j][index-1].toFloat();
                            else if(index<0)
                                sum -= t_var[j][-index-1].toFloat();
                        }
                        t_var[j][i] = QVariant(sum);
                        break;
                    }
                    case 3:{
                        //if((QString)strList2[1]==""){
                            if(t_var[j][i].toString()!="是")
                                t_var[j][i] = QVariant("否");
                        //}
                        break;
                    }
                    case 4:{
                        strList3=((QString)strList2[1]).split(',');
                        float sum;
                        sum = 1;
                        for(int n=0;n<strList3.count();n++){
                            int index=((QString)strList3[n]).toInt();
                            if(index>0)
                                sum *= t_var[j][index-1].toFloat();
                            else if(index<0)
                                sum /= t_var[j][-index-1].toFloat();
                        }
                        t_var[j][i] = QVariant(sum);
                        break;
                    }
                    case 5:{
                        strList3=((QString)strList2[1]).split(',');
                        if(((QString)strList2[1]).contains('$')){
                            strList3=((QString)((QString)strList2[1]).remove('$')).split('/');
                            if(strList3.count()==2){
                                int n1 = ((QString)strList3[0]).toInt();
                                int n2 = ((QString)strList3[1]).toInt();
                                if(n1>0)
                                    t_var[j][i] = t_var[n1][n2-1];
                                else{
                                    if(j+n1>1)
                                        t_var[j][i] = t_var[j+n1][n2-1];
                                    else
                                        t_var[j][i] = 0;
                                }
                            }
                        }
                        break;
                    }
                    default:{
                        break;
                    }
                    }
                }
            }
        }
        //Sort
        SortByDate(t_var,tableType.indexOf("date"));
        varList.append(t_var);
    }
    excel.Close();
}
void OutPut::Sum(QStringList strList1, QStringList strList2, QStringList tableType, QStringList tableAuto,
                 QList<QList<QList<QVariant>>>& varList1, QList<QList<QVariant>>& var){
    QList<QVariant> list;
    //header
    for(int i=0; i<strList2.count(); i++){
        list.append(QVariant(strList2[i]));
    }
    var.append(list);
    //Sum
    for(int i=1; i<varList1.count(); i++){//i means var1 rows
        list.clear();
        for(int j=0; j<strList2.count(); j++){//j means var2 headlabel
            if(strList1.contains(strList2[j])){
                int index = strList1.indexOf(strList2[j]);
                if(tableType[j]=="num"){
                    float sum=0;
                    for(int k=1; k<varList1[i].count(); k++){
                        sum += varList1[i][k][index].toFloat();
                    }
                    list.append(QVariant(sum));
                }
                else if(tableType[j]=="int"){
                    int sum=0;
                    for(int k=1; k<varList1[i].count(); k++){
                        sum += varList1[i][k][index].toInt();
                    }
                    list.append(QVariant(sum));
                }
                else if(tableType[j]=="numE"){
                    QVariant value;
                    value = QVariant(varList1[i][varList1[i].count()-1][index]);
                    list.append(value);
                }
                else if(tableType[j]=="numS"){
                    QVariant value;
                    value = QVariant(varList1[i][1][index]);
                    list.append(value);
                }
                else if(tableType[j]=="date"){
                    QVariant value;
                    value = QVariant(varList1[i][varList1[i].count()-1][index]);
                    list.append(value);
                }
                else{
                    QVariant value;
                    for(int k=1;k<varList1[i].count();k++){
                        value = varList1[i][k][index];
                        if(value.toString()!="")
                            break;
                    }
                    list.append(value);
                    //Sum-apart
                    for(int k=1; k<varList1[i].count(); k++){
                        if(varList1[i][k][index] != value)
                            varList1[i][k][index] = value;
                    }
                }
            }
        }
        if(list.count()>0)
            var.append(list);
    }
    CheckChoose(strList1, strList2, tableAuto, varList1, var);
}
void OutPut::CheckChoose(QStringList strList1, QStringList strList2, QStringList tableAuto,
                         QList<QList<QList<QVariant>>>& varList1, QList<QList<QVariant>>& var, int index){
    //Choose
    int start,end;
    if(index==-1){
        start=1;
        end=var.count();
    }
    else{
        start=index;
        end=index+1;
    }
    for(int i=start; i<end; i++){//i means var1 rows
        if(varList1.at(i).count()<=1)
            continue;
        for(int j=0; j<strList2.count(); j++){//j means var1 headlabel
            QStringList t_strList1 = ((QString)tableAuto[j]).split(':');
            if(t_strList1[0]=="3"){
                if(t_strList1[1]!=""){
                    QVariant oriValue = var[i][j];
                    QStringList t_strList2 = ((QString)t_strList1[1]).split('=');
                    QStringList t_strList3;
                    QList<double> num;
                    for(int t1=0;t1<t_strList2.count();t1++){
                        if(((QString)t_strList2[t1]).contains('$')){
                            t_strList3 = ((QString)t_strList2[t1]).remove('$').split('/');
                            QList<QString> indexStringList;
                            for(int t2=0;t2<t_strList3.count();t2++){
                                indexStringList.append(t_strList3[t2]);
                            }
                            if(t_strList3.count()==1){
                                num.append(var[i][((QString)t_strList3[0]).toInt()-1].toFloat());
                            }
                            else if(t_strList3.count()==3){
                                int n1 = ((QString)t_strList3[0]).toInt();
                                QList<QList<QVariant>> t_var;
                                switch(n1){
                                case 1:
                                    t_var = vars1;
                                    break;
                                case 3:
                                    t_var = vars3;
                                    break;
                                case 5:
                                    t_var = vars5;
                                    break;
                                }
                                int n2 = ((QString)t_strList3[1]).toInt();
                                int n3 = ((QString)t_strList3[2]).toInt();
                                if(n2>0)
                                    num.append(var[n2-1][n3-1].toFloat());
                                else if(n2==0)
                                    num.append(var[i][n3-1].toFloat());
                            }
                            else if(t_strList3.count()==4){
                                int n1 = ((QString)t_strList3[0]).toInt();
                                QList<QList<QList<QVariant>>> t_var;
                                switch(n1){
                                case 2:
                                    t_var = vars2;
                                    break;
                                case 4:
                                    t_var = vars4;
                                    break;
                                case 6:
                                    t_var = vars6;
                                    break;
                                }
                                int n2 = ((QString)t_strList3[1]).toInt();
                                int n31 = ((QString)((QString)t_strList3[2]).split('~')[0]).toInt();
                                int n32 = ((QString)((QString)t_strList3[2]).split('~')[1]).toInt();
                                int n4 = ((QString)t_strList3[3]).toInt();
                                if(n2==-1){
                                    QString tag = var[0][n31-1].toString();
                                    float t_num = 0;
                                    for(int t2=1;t2<t_var.count();t2++){
                                        for(int t3=1;t3<t_var[t2].count();t3++){
                                            if(t_var[t2][0][n32-1].toString().contains(tag)
                                                    && t_var[t2][t3][n32-1].toString()==var[i][n31-1].toString()){
                                                t_num += t_var[t2][t3][n4-1].toFloat();
                                                continue;
                                            }
                                        }
                                    }
                                    num.append(t_num);
                                }
                            }
                        }
                        else{
                            num.append(((QString)t_strList2[t1]).toFloat());
                        }
                    }
                    bool isSame = true;
                    for(int t1=1;t1<num.count();t1++){
                        if(num[0]!=num[t1]){
                            isSame = false;
                            break;
                        }
                    }
                    if(oriValue != QVariant(isSame?"是":"否")){
                        var[i][j] = QVariant(isSame?"是":"否");
                        //Choose-apart
                        int index = strList1.indexOf(strList2[j]);
                        for(int k=1; k<varList1[i].count(); k++){
                            varList1[i][k][index] = var[i][j];
                        }
                    }
                }
            }
        }
    }
}
void OutPut::CheckDate(QStringList strList1, QStringList strList2, QStringList tableType1, QStringList tableType2,
                         QList<QList<QVariant>>& var1, QList<QList<QList<QVariant>>>& var2, QString date1, QString date2, int index){
    //Choose
    int start,end;
    if(index==-1){
        start=1;
        end=var1.count();
    }
    else{
        start=index;
        end=index+1;
    }
    int n2 = tableType2.indexOf("date");
    for(int i=start; i<end; i++){
        for(int j=0; j<strList1.count(); j++){
            int n1 = strList2.indexOf(strList1[j]);
            int k;
            if(tableType1[j] == "numS"){
                bool isExist=false;
                for(k=1;k<var2[i].count();k++){
                    QStringList dateList = var2[i][k][n2].toString().split('.');
                    QString date = QString("%1%2%3").arg(dateList[0].toInt(),4,10,
                            QChar('0')).arg(dateList[1].toInt(),2,10,QChar('0')).arg(dateList[2].toInt(),2,10,QChar('0'));
                    if(date1<=date && date<=date2){
                        isExist=true;
                        break;
                    }
                }
                if(isExist)
                    var1[i][j] = var2[i][k][n1];
                else
                    var1[i][j] = QVariant(0);
            }
            else if(tableType1[j] == "numE"){
                bool isExist=false;
                for(k=1;k<var2[i].count();k++){
                    QStringList dateList = var2[i][k][n2].toString().split('.');
                    QString date = QString("%1%2%3").arg(dateList[0].toInt(),4,10,
                            QChar('0')).arg(dateList[1].toInt(),2,10,QChar('0')).arg(dateList[2].toInt(),2,10,QChar('0'));
                    if(!isExist){
                        if(date1<=date && date<=date2){
                            isExist=true;
                            continue;
                        }
                    }
                    else{
                        if(!(date1<=date && date<=date2))
                            break;
                    }
                }
                if(isExist){
                    k--;
                    var1[i][j] = var2[i][k][n1];
                }
                else
                    var1[i][j] = QVariant(0);
            }
            else if(tableType1[j] == "num"){
                if(n1==-1){
                    //vars7
                    float sum=0;
                    switch(j){
                    case 7:
                        //应收未收
                        if(m_typeList.at(i-1)==3){
                            sum=vars3[m_typeIndexList.at(i-1)][7].toFloat()-var1[i][4].toFloat();
                            var1[i][j] = QVariant(sum);
                        }
                        else
                            var1[i][j] = QVariant(0);
                        break;
                    case 8:
                        //应付未付
                        if(m_typeList.at(i-1)==1){
                            sum=vars1[m_typeIndexList.at(i-1)][8].toFloat()-var1[i][5].toFloat();
                            var1[i][j] = QVariant(sum);
                        }
                        else
                            var1[i][j] = QVariant(0);
                        break;
                    case 9:
                        //利润
                        sum=var1[i][4].toFloat()-var1[i][5].toFloat();
                        var1[i][j] = QVariant(sum);
                        break;
                    }
                }
                else{
                    bool isExist=false;
                    float sum=0;
                    for(k=1;k<var2[i].count();k++){
                        QStringList dateList = var2[i][k][n2].toString().split('.');
                        QString date = QString("%1%2%3").arg(dateList[0].toInt(),4,10,
                                QChar('0')).arg(dateList[1].toInt(),2,10,QChar('0')).arg(dateList[2].toInt(),2,10,QChar('0'));
                        if(!isExist){
                            if(date1<=date && date<=date2){
                                isExist=true;
                                sum+=var2[i][k][n1].toFloat();
                                continue;
                            }
                        }
                        else{
                            if(!(date1<=date && date<=date2))
                                break;
                            else
                                sum+=var2[i][k][n1].toFloat();
                        }
                    }
                    if(isExist)
                        var1[i][j] = sum;
                    else
                        var1[i][j] = QVariant(0);
                }
            }
            else if(tableType1[j] == "int"){
                bool isExist=false;
                int sum=0;
                for(k=1;k<var2[i].count();k++){
                    QStringList dateList = var2[i][k][n2].toString().split('.');
                    QString date = QString("%1%2%3").arg(dateList[0].toInt(),4,10,
                            QChar('0')).arg(dateList[1].toInt(),2,10,QChar('0')).arg(dateList[2].toInt(),2,10,QChar('0'));
                    if(!isExist){
                        if(date1<=date && date<=date2){
                            isExist=true;
                            sum+=var2[i][k][n1].toInt();
                            continue;
                        }
                    }
                    else{
                        if(!(date1<=date && date<=date2))
                            break;
                        else
                            sum+=var2[i][k][n1].toInt();
                    }
                }
                if(isExist)
                    var1[i][j] = sum;
                else
                    var1[i][j] = QVariant(0);
            }
        }
    }
}
void OutPut::Add78(){
    //Init
    vars7.clear();
    vars8.clear();
    //init
    QList<QList<QVariant>> List;
    QList<QVariant> list;
    list.clear();
    for(int j=0;j<m_headerLabels7.count();j++)
        list.append(QVariant(m_headerLabels7.at(j)));
    vars7.append(list);
    vars8.append(QList<QList<QVariant>>());
    m_indexList.clear();
    m_typeList.clear();
    m_typeIndexList.clear();
    //vars6
    for(int i1=1;i1<vars6.count();i1++){
        for(int j1=1;j1<vars6[i1].count();j1++){
            QString id=vars6[i1][j1][7].toString();
            if(m_indexList.keys().contains(id)){
                //exsit
                int index=m_indexList.value(id);
                int type=m_typeList.at(index-1);
                int sum=vars8[index][vars8[index].count()-1][7].toFloat();
                switch(type){
                case 1:{
                    for(int i2=1;i2<vars1.count();i2++){
                        if(vars1[i2][2].toString()==id){
                            type=1;
                            list.clear();
                            list.append(vars6[i1][j1][0]);
                            list.append(vars1[i2][2]);
                            list.append(vars1[i2][1]);
                            //4
                            list.append(vars6[i1][j1][1]);
                            //5
                            list.append(QVariant(sum));
                            //6
                            list.append(vars6[i1][j1][3]);
                            sum+=vars6[i1][j1][3].toFloat();
                            //7
                            list.append(vars6[i1][j1][4]);
                            sum-=vars6[i1][j1][4].toFloat();
                            //8
                            list.append(QVariant(sum));
                            break;
                        }
                    }
                    break;
                }
                case 3:{
                    for(int i2=1;i2<vars3.count();i2++){
                        if(vars3[i2][2].toString()==id){
                            list.clear();
                            list.append(vars6[i1][j1][0]);
                            list.append(vars3[i2][3]);
                            list.append(vars3[i2][2]);
                            //4
                            list.append(vars6[i1][j1][1]);
                            //5
                            list.append(QVariant(sum));
                            //6
                            list.append(vars6[i1][j1][3]);
                            sum+=vars6[i1][j1][3].toFloat();
                            //7
                            list.append(vars6[i1][j1][4]);
                            sum-=vars6[i1][j1][4].toFloat();
                            //8
                            list.append(QVariant(sum));
                            break;
                        }
                    }
                    break;
                }
                default:{
                    list.clear();
                    list.append(vars6[i1][j1][0]);
                    list.append(QVariant(""));
                    list.append(QVariant(""));
                    //4
                    list.append(vars6[i1][j1][1]);
                    //5
                    list.append(QVariant(sum));
                    //6
                    list.append(vars6[i1][j1][3]);
                    sum+=vars6[i1][j1][3].toFloat();
                    //7
                    list.append(vars6[i1][j1][4]);
                    sum-=vars6[i1][j1][4].toFloat();
                    //8
                    list.append(QVariant(sum));
                    break;
                }
                }
                vars8[index].append(list);
            }
            else{
                //don't exsit
                List.clear();
                int type=0;
                int sum=0;
                //header
                list.clear();
                for(int i2=0;i2<m_headerLabels8.count();i2++)
                    list.append(QVariant(m_headerLabels8.at(i2)));
                List.append(list);
                //list-vars1
                for(int i2=1;i2<vars1.count();i2++){
                    if(vars1[i2][2].toString()==id){
                        type=1;
                        list.clear();
                        list.append(vars6[i1][j1][0]);
                        list.append(vars1[i2][2]);
                        list.append(vars1[i2][1]);
                        //4
                        list.append(vars6[i1][j1][1]);
                        //5
                        list.append(QVariant(sum));
                        //6
                        list.append(vars6[i1][j1][3]);
                        sum+=vars6[i1][j1][3].toFloat();
                        //7
                        list.append(vars6[i1][j1][4]);
                        sum-=vars6[i1][j1][4].toFloat();
                        //8
                        list.append(QVariant(sum));
                        List.append(list);
                        m_typeIndexList.append(i2);
                        break;
                    }
                }
                //list-vars3
                if(type==0){
                    type=3;
                    for(int i2=1;i2<vars3.count();i2++){
                        if(vars3[i2][3].toString()==id){
                            list.clear();
                            list.append(vars6[i1][j1][0]);
                            list.append(vars3[i2][3]);
                            list.append(vars3[i2][2]);
                            //4
                            list.append(vars6[i1][j1][1]);
                            //5
                            list.append(QVariant(sum));
                            //6
                            list.append(vars6[i1][j1][3]);
                            sum+=vars6[i1][j1][3].toFloat();
                            //7
                            list.append(vars6[i1][j1][4]);
                            sum-=vars6[i1][j1][4].toFloat();
                            //8
                            list.append(QVariant(sum));
                            List.append(list);
                            m_typeIndexList.append(i2);
                            break;
                        }
                    }
                }
                //empty
                if(type==0){
                    list.clear();
                    list.append(vars6[i1][j1][0]);
                    list.append(QVariant(""));
                    list.append(QVariant(""));
                    //4
                    list.append(vars6[i1][j1][1]);
                    //5
                    list.append(QVariant(sum));
                    //6
                    list.append(vars6[i1][j1][3]);
                    sum+=vars6[i1][j1][3].toFloat();
                    //7
                    list.append(vars6[i1][j1][4]);
                    sum-=vars6[i1][j1][4].toFloat();
                    //8
                    list.append(QVariant(sum));
                    List.append(list);
                    m_typeIndexList.append(-1);
                }
                if(List.count()>=2){
                    m_typeList.append(type);
                    m_indexList.insert(id,vars8.count());
                    vars8.append(List);
                }
            }
        }
    }
    for(int i=1;i<vars8.count();i++){
        list.clear();
        for(int j=0;j<m_headerLabels7.count();j++){
            int k=m_headerLabels8.indexOf(m_headerLabels7.at(j));
            if(k!=-1){
                if(m_tableType7.at(j)=="date")
                    list.append(vars8[i][vars8[i].count()-1][k]);
                else if(m_tableType7.at(j)=="numS")
                    list.append(vars8[i][1][k]);
                else if(m_tableType7.at(j)=="numE")
                    list.append(vars8[i][vars8[i].count()-1][k]);
                else if(m_tableType7.at(j)=="num"){
                    float sum=0;
                    for(int l=1;l<vars8[i].count();l++){
                        sum+=vars8[i][l][k].toFloat();
                    }
                    list.append(QVariant(sum));
                }
                else
                    list.append(QVariant(vars8[i][1][k]));
            }
            else{
                float sum=0;
                switch(j){
                case 7:
                    //应收未收
                    if(m_typeList.at(i-1)==3){
                        sum=vars3[m_typeIndexList.at(i-1)][7].toFloat()-list[4].toFloat();
                        list.append(QVariant(sum));
                    }
                    else
                        list.append(QVariant(0));
                    break;
                case 8:
                    //应付未付
                    if(m_typeList.at(i-1)==1){
                        sum=vars1[m_typeIndexList.at(i-1)][8].toFloat()-list[5].toFloat();
                        list.append(QVariant(sum));
                    }
                    else
                        list.append(QVariant(0));
                    break;
                case 9:
                    //利润
                    sum=list[4].toFloat()-list[5].toFloat();
                    list.append(QVariant(sum));
                    break;
                }
            }
        }
        vars7.append(list);
    }
}
//excel.ReadDataToTable(tableWidget); //导入到widget中
bool OutPut::SortByStringList(QList<QList<QVariant>> &list, QStringList sortList){
    for (int i = 0; i < list[0].count(); i++)
    {
        for (int j = i + 1; j < list[0].count(); j++){
            if (sortList.indexOf(list[0][i].toString()) > sortList.indexOf(list[0][j].toString())){
                for(int t=0;t<list.count();t++){
                    list[t].swap(i, j);
                }
            }
        }
    }
    return true;
}
bool OutPut::SortByDate(QList<QList<QVariant>> &list, int index){
    for (int i = 1; i < list.count(); i++)
    {
        for (int j = i + 1; j < list.count(); j++){
            if (QDate::fromString(list[i][index].toString(),"yyyy.M.d").toString("yyyyMMdd") > QDate::fromString(list[j][index].toString(),"yyyy.M.d").toString("yyyyMMdd")){
                list.swap(i, j);
            }
        }
    }
    return true;
}
bool OutPut::SortByCol(QTableWidget* table, int index, QList<int> &indexList, Qt::SortOrder order){
    int row = indexList.count()-1;
    int col = table->columnCount()-1;
    QString itemStr;
    int t;
    if(order == Qt::AscendingOrder){
        for (int i = 0; i < row; i++)
        {
            for (int j = i + 1; j < row; j++){
                if (table->item(i,index)->text() > table->item(j,index)->text()){
                    for(int k=0;k<col;k++){
                        itemStr = table->item(i,k)->text();
                        table->item(i,k)->setText(table->item(j,k)->text());
                        table->item(j,k)->setText(itemStr);
                    }
                    t = indexList.at(i+1);
                    indexList[i+1]=indexList.at(j+1);
                    indexList[j+1]=t;
                }
            }
        }
    }
    else if(order == Qt::DescendingOrder){
        for (int i = 0; i < row; i++)
        {
            for (int j = i + 1; j < row; j++){
                if (table->item(i,index)->text() < table->item(j,index)->text()){
                    for(int k=0;k<col;k++){
                        itemStr = table->item(i,k)->text();
                        table->item(i,k)->setText(table->item(j,k)->text());
                        table->item(j,k)->setText(itemStr);
                    }
                    t = indexList.at(i+1);
                    indexList[i+1]=indexList.at(j+1);
                    indexList[j+1]=t;
                }
            }
        }
    }
    return true;
}
int OutPut::VarToTable(QList<QList<QVariant>>& var, QTableWidget *tableWidget, QStringList strList, int maxRow){
    //先把table的内容清空
    int tableRow = tableWidget->rowCount();
    //tableWidget->clear();
    for (int n=0; n<tableRow; n++)
    {
        tableWidget->removeRow(0);
    }
    //插入新数据
    QList<QString> list;
    for(int i=0;i<tableWidget->columnCount();i++)
        list.append(tableWidget->horizontalHeaderItem(i)->text());
    if(var.count()>1){
        for(int i=1;i<var.count();i++){
            tableWidget->insertRow(i-1); //插入新行
            for(int j=0,k=0;j<var[i].count();j++){
                if(!list.contains(var[0][j].toString()))
                    continue;
                QTableWidgetItem *item = new QTableWidgetItem;
                if(strList.at(j)=="int"){
                    item->setData(Qt::EditRole, QVariant(var[i][j].toInt()));
                }
                else if(strList.at(j)=="num" || strList.at(j)=="numC" || strList.at(j)=="numS" || strList.at(j)=="numE"){
                    item->setData(Qt::EditRole, QVariant(QString::number(var[i][j].toFloat(), 'f', 2)));
                }else{
                    item->setData(Qt::EditRole, QVariant(var[i][j].toString()));
                }
                item->setTextAlignment(Qt::AlignCenter);
                item->setFont(QFont("宋体",10));
                tableWidget->setItem(i-1,k,item);
                k++;
            }
        }
    }
    int count = tableWidget->rowCount();
    for(int i=tableWidget->rowCount();i<maxRow;i++){
        tableWidget->insertRow(i); //插入新行
    }
    tableWidget->resizeColumnsToContents();
    return count;
}

//弹框
void OutPut::MessageHit(const QString &text){
    QMessageBox message(QMessageBox::Information, "Tip", text, QMessageBox::Ok);
    message.exec();
}
void OutPut::MessageHit(const QString &text,int msec){
    QMessageBox message(QMessageBox::Information, "提示", text, QMessageBox::Ok);
    if(msec!=0){
        message.show();
        QTimer::singleShot(msec,&message,&QMessageBox::close);
    }
    message.exec();
}

bool OutPut::MessageQuestion(const QString &text){
    QMessageBox box(QMessageBox::Question,"提示",text);
    box.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    box.setButtonText(QMessageBox::Ok,"是");
    box.setButtonText(QMessageBox::Cancel,"否");
    if(box.exec()==QMessageBox::Ok)
        return true;
    return false;

}

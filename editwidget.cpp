//窗口
#include "editwidget.h"
//布局
#include <QVBoxLayout>
//控件
#include <QLabel>
#include "uline.h"
#include "ubutton.h"
#include "udatebox.h"
#include "uradio.h"
//辅助
#include <QVariant>
#include <QDate>
#include "output.h"

//EditWidget
EditWidget::EditWidget(OutPut *m_output, WingWidget *m_parent)
{
    setAttribute(Qt::WA_QuitOnClose, false);
    this->m_layout = new QVBoxLayout(this);
    this->m_output = m_output;
    this->m_parent = m_parent;
    this->m_index1 = -1;
    this->m_index2 = -1;
    this->m_var1 = NULL;
    this->m_var2 = NULL;
}
EditWidget::~EditWidget()
{
    QMutableHashIterator<QString, ULine *> i1(m_lineHash);
    while (i1.hasNext()) {
        i1.next();
        delete i1.value();
    }
    QMutableHashIterator<QString, UButton *> i2(m_btnHash);
    while (i2.hasNext()) {
        i2.next();
        delete i2.value();
    }
    QMutableHashIterator<QString, UDateBox *> i3(m_dateHash);
    while (i3.hasNext()) {
        i3.next();
        delete i3.value();
    }
    QMutableHashIterator<QString, QLabel *> i4(m_labelHash);
    while (i4.hasNext()) {
        i4.next();
        delete i4.value();
    }
    QMutableHashIterator<QString, URadio *> i5(m_radioHash);
    while (i5.hasNext()) {
        i5.next();
        delete i5.value();
    }
    delete m_btnLayout;
    delete m_layout;
}
void EditWidget::SetType(WidgetType type){
    if(m_index2==-1){
        QList<QString> strList;
        for(int i=0;i<m_headerLabels1.count();i++){
            if(m_tagMap.keys().contains(m_headerLabels1[i])){
                if(m_typeMap.value(m_headerLabels1[i]) == "Text")
                    AddLine(EditLine(m_headerLabels1[i], m_tagMap.value(m_headerLabels1[i]), EditType::Text,""));
                else if(m_typeMap.value(m_headerLabels1[i]) == "Number")
                    AddLine(EditLine(m_headerLabels1[i], m_tagMap.value(m_headerLabels1[i]), EditType::Number,""));
                else if(m_typeMap.value(m_headerLabels1[i]) == "Int")
                    AddLine(EditLine(m_headerLabels1[i], m_tagMap.value(m_headerLabels1[i]), EditType::Int,""));
                else if(m_typeMap.value(m_headerLabels1[i]) == "ComboBox")
                    AddLine(EditLine(m_headerLabels1[i], m_tagMap.value(m_headerLabels1[i]), EditType::ComboBox,""));
                else if(m_typeMap.value(m_headerLabels1[i]) == "Date")
                    AddLine(EditLine(m_headerLabels1[i], m_tagMap.value(m_headerLabels1[i]), EditType::Date,""));
            }
            if(m_tableAuto1[i] == "3:"){
                strList.append("是否"+m_headerLabels1[i]);
            }
        }
        QString name = m_typeMap.key("Radio");
        if(name!="" && strList.count()>0){
            AddLine(EditLine(name, m_tagMap.value(name), EditType::Radio,"",strList));
        }
    }
    else{
        for(int i=0;i<m_headerLabels2.count();i++){
            if(m_tagMap.keys().contains(m_headerLabels2[i])){
                if(m_typeMap.value(m_headerLabels2[i]) == "Text")
                    AddLine(EditLine(m_headerLabels2[i], m_tagMap.value(m_headerLabels2[i]), EditType::Text,""));
                else if(m_typeMap.value(m_headerLabels2[i]) == "Number")
                    AddLine(EditLine(m_headerLabels2[i], m_tagMap.value(m_headerLabels2[i]), EditType::Number,""));
                else if(m_typeMap.value(m_headerLabels2[i]) == "Int")
                    AddLine(EditLine(m_headerLabels2[i], m_tagMap.value(m_headerLabels2[i]), EditType::Int,""));
                else if(m_typeMap.value(m_headerLabels2[i]) == "ComboBox")
                    AddLine(EditLine(m_headerLabels2[i], m_tagMap.value(m_headerLabels2[i]), EditType::ComboBox,""));
                else if(m_typeMap.value(m_headerLabels2[i]) == "Date")
                    AddLine(EditLine(m_headerLabels2[i], m_tagMap.value(m_headerLabels2[i]), EditType::Date,""));
            }
        }
    }
    switch(type){
        case EditWidget::Add:{
            AddButton(EditWidget::Add);
            connect(m_btnHash["OK"],&QPushButton::clicked,[=](){
                this->BtnAdd();
            });
            connect(m_btnHash["ESC"],&QPushButton::clicked,[=](){
                this->close();
            });
            break;
        }
        case EditWidget::Edit:{
            AddButton(EditWidget::Edit);
            connect(m_btnHash["EDIT"],&QPushButton::clicked,[=](){
                this->BtnEdit();
            });
            connect(m_btnHash["ESC"],&QPushButton::clicked,[=](){
                this->close();
            });
            break;
        }
        default:{
            AddButton(EditWidget::Info);
            connect(m_btnHash["OK"],&QPushButton::clicked,[=](){
                this->close();
            });
            break;
        }
    }
}
void EditWidget::SetIndex(int index1, int index2, bool isDetails){
    if(isDetails){
        m_index1 = index1;
        if(index2==-1)
            m_index2 = (*m_var2)[m_index1].count()-1;
        else
            m_index2 = index2;
    }
    else{
        if(index1==-1)
            m_index1 = m_var1->count();
        else
            m_index1 = index1;
        m_index2 = -1;
    }
}
void EditWidget::BtnAdd(){
    if(!Check() && m_var1!=NULL && m_var2!=NULL)
        return;
    if(m_index2==-1){
        //var1
        QList<QVariant> list;
        int radioNum = 0;
        for(int i=0;i<m_headerLabels1.count();i++){
            if(m_tagMap.keys().contains(m_headerLabels1.at(i))){
                if(m_tableType1.at(i)=="date")
                    list.append(QVariant(m_dateHash[m_tagMap.value(m_headerLabels1.at(i))]->GetData()));
                else
                    list.append(QVariant(m_lineHash[m_tagMap.value(m_headerLabels1.at(i))]->GetValue()));
            }
            else{
                QStringList strList1=((QString)m_tableAuto1[i]).split(':');
                QStringList strList2;
                switch(((QString)strList1[0]).toInt()){
                case 1:{
                    if(m_tableType1.at(i)=="text")
                        list.append(QVariant(""));
                    else if(m_tableType1.at(i)=="int")
                        list.append(QVariant(0));
                    else if(m_tableType1.at(i)=="num"||m_tableType1.at(i)=="numC"||m_tableType1.at(i)=="numS"||m_tableType1.at(i)=="numE")
                        list.append(QVariant(0.00f));
                    break;
                }
                case 2:{
                    strList2=((QString)strList1[1]).split(',');
                    float sum = 0;
                    for(int n=0;n<strList2.count();n++){
                        int index=((QString)strList2[n]).toInt();
                        if(index>0)
                            sum += list[index-1].toFloat();
                        else if(index<0)
                            sum -= list[-index-1].toFloat();
                    }
                    list.append(QVariant(sum));
                    break;
                }
                case 3:{
                    if(strList1[1]=="")
                        list.append(QVariant(m_radioHash[m_tagMap.value("状态")]->GetValue(++radioNum)?"是":"否"));
                    else
                        list.append(QVariant("否"));
                    break;
                }
                case 4:{
                    strList2=((QString)strList1[1]).split(',');
                    float sum = 1;
                    for(int n=0;n<strList2.count();n++){
                        int index=((QString)strList2[n]).toInt();
                        if(index>0)
                            sum *= list[index-1].toFloat();
                        else if(index<0)
                            sum /= list[-index-1].toFloat();
                    }
                    list.append(QVariant(sum));
                    break;
                }
                case 5:{
                    if(m_tableType1.at(i)=="text")
                        list.append(QVariant(""));
                    else if(m_tableType1.at(i)=="int")
                        list.append(QVariant(0));
                    else if(m_tableType1.at(i)=="num"||m_tableType1.at(i)=="numC"||m_tableType1.at(i)=="numS"||m_tableType1.at(i)=="numE")
                        list.append(QVariant(0.00f));
                    break;
                }
                }
            }
        }
        m_var1->append(list);
        //var2
        QList<QList<QVariant>> t_list1;
        QList<QVariant> t_list2;
        for(int i=0;i<m_headerLabels2.count();i++)
            t_list2.append(QVariant(m_headerLabels2[i]));
        t_list1.append(t_list2);
        (*m_var2).append(t_list1);
    }
    else{
        //var2
        QList<QVariant> list;
        for(int i=0;i<m_headerLabels2.count();i++){
            if(m_tagMap.keys().contains(m_headerLabels2.at(i))){
                if(m_tableType2.at(i)=="date")
                    list.append(QVariant(m_dateHash[m_tagMap.value(m_headerLabels2.at(i))]->GetData()));
                else if(m_tableType2.at(i)=="text"||m_tableType2.at(i)=="int"||m_tableType2.at(i)=="num"||m_tableType2.at(i)=="numC"||m_tableType2.at(i)=="numS"||m_tableType2.at(i)=="numE"){
                    list.append(QVariant(m_lineHash[m_tagMap.value(m_headerLabels2.at(i))]->GetValue()));
                }
            }
            else{
                QStringList strList1=((QString)m_tableAuto2[i]).split(':');
                QStringList strList2;
                switch(((QString)strList1[0]).toInt()){
                case 1:{
                    int index = m_headerLabels1.indexOf(m_headerLabels2.at(i));
                    list.append((*m_var1)[m_index1][index]);
                    break;
                }
                case 2:{
                    int rows = (*m_var2)[m_index1].count();
                    strList2=((QString)strList1[1]).split(',');
                    float sum;
                    if(m_tableType2.at(i)=="numE"){
                        if(rows==0)
                            sum = 0;
                        else
                            sum = (*m_var2)[m_index1][rows-1][i].toFloat();
                    }
                    else
                        sum = 0;
                    for(int n=0;n<strList2.count();n++){
                        int index=((QString)strList2[n]).toInt();
                        if(index>0)
                            sum += list[index-1].toFloat();
                        else if(index<0)
                            sum -= list[-index-1].toFloat();
                    }
                    list.append(QVariant(sum));
                    break;
                }
                case 3:{
                    int index = m_headerLabels1.indexOf(m_headerLabels2.at(i));
                    list.append((*m_var1)[m_index1][index]);
                    break;
                }
                case 4:{
                    int rows = (*m_var2)[m_index1].count();
                    strList2=((QString)strList1[1]).split(',');
                    float sum;
                    if(m_tableType2.at(i)=="numE"){
                        if(rows==0)
                            sum = 1;
                        else
                            sum = (*m_var2)[m_index1][rows-1][i].toFloat();
                    }
                    else
                        sum = 1;
                    for(int n=0;n<strList2.count();n++){
                        int index=((QString)strList2[n]).toInt();
                        if(index>0)
                            sum *= list[index-1].toFloat();
                        else if(index<0)
                            sum /= list[-index-1].toFloat();
                    }
                    list.append(QVariant(sum));
                    break;
                }
                case 5:{
                    QVariant value;
                    if(((QString)strList1[1]).contains('$')){
                        int rows = (*m_var2)[m_index1].count();
                        strList2=((QString)((QString)strList1[1]).remove('$')).split('/');
                        if(strList2.count()==2){
                            int n1 = ((QString)strList2[0]).toInt();
                            int n2 = ((QString)strList2[1]).toInt();
                            if(n1>0)
                                value = (*m_var2)[m_index1][n1][n2-1];
                            else{
                                if(rows+n1>1)
                                    value = (*m_var2)[m_index1][rows+n1][n2-1];
                                else
                                    value = 0;
                            }
                        }
                    }
                    list.append(value);
                    break;
                }
                }
            }
        }
        (*m_var2)[m_index1].append(list);
        //var1
        for(int i=0;i<m_headerLabels2.count();i++){
            if(m_headerLabels1.indexOf(m_headerLabels2[i])!=-1){
            if(m_tableType2[i]=="int")
                (*m_var1)[m_index1][m_headerLabels1.indexOf(m_headerLabels2[i])] = QVariant((*m_var1)[m_index1][m_headerLabels1.indexOf(m_headerLabels2[i])].toInt() + list[i].toInt());
            else if(m_tableType2[i]=="num")
                (*m_var1)[m_index1][m_headerLabels1.indexOf(m_headerLabels2[i])] = QVariant((*m_var1)[m_index1][m_headerLabels1.indexOf(m_headerLabels2[i])].toFloat() + list[i].toFloat());
            else if(m_tableType2[i]=="numE")
                (*m_var1)[m_index1][m_headerLabels1.indexOf(m_headerLabels2[i])] = QVariant(list[i].toFloat());
            }
        }
    }
    m_output->MessageHit("已添加");
    BtnCal();
    BtnFlash();
    this->close();
}
void EditWidget::BtnEdit(){
    if(!Check() && m_var1!=NULL && m_var2!=NULL)
        return;
    //sum
    if(m_index2==-1){
        //var1
        int radioNum = 0;
        for(int i=0;i<m_headerLabels1.count();i++){
            if(m_tagMap.keys().contains(m_headerLabels1.at(i))){
                if(m_tableType1.at(i)=="date")
                    (*m_var1)[m_index1][i] = QVariant(m_dateHash[m_tagMap.value(m_headerLabels1.at(i))]->GetData());
                else if(m_tableType1.at(i)=="text")
                    (*m_var1)[m_index1][i] = QVariant(m_lineHash[m_tagMap.value(m_headerLabels1.at(i))]->GetValue());
                else if(m_tableType1.at(i)=="int")
                    (*m_var1)[m_index1][i] = QVariant(m_lineHash[m_tagMap.value(m_headerLabels1.at(i))]->GetValue().toInt());
                else if(m_tableType1.at(i)=="num"||m_tableType1.at(i)=="numC"||m_tableType1.at(i)=="numS"||m_tableType1.at(i)=="numE")
                    (*m_var1)[m_index1][i] = QVariant(m_lineHash[m_tagMap.value(m_headerLabels1.at(i))]->GetValue().toDouble());
            }
            else{
                QStringList strList1=((QString)m_tableAuto1[i]).split(':');
                QStringList strList2;
                switch(((QString)strList1[0]).toInt()){
                case 2:{
                    strList2=((QString)strList1[1]).split(',');
                    float sum = 0;
                    for(int n=0;n<strList2.count();n++){
                        int index=((QString)strList2[n]).toInt();
                        if(index>0)
                            sum += (*m_var1)[m_index1][index-1].toFloat();
                        else if(index<0)
                            sum -= (*m_var1)[m_index1][-index-1].toFloat();
                    }
                    (*m_var1)[m_index1][i] = QVariant(sum);
                    break;
                }
                case 3:{
                    (*m_var1)[m_index1][i] = QVariant(m_radioHash[m_tagMap.value("状态")]->GetValue(++radioNum)?"是":"否");
                    break;
                }
                case 4:{
                    strList2=((QString)strList1[1]).split(',');
                    float sum = 1;
                    for(int n=0;n<strList2.count();n++){
                        int index=((QString)strList2[n]).toInt();
                        if(index>0)
                            sum *= (*m_var1)[m_index1][index-1].toFloat();
                        else if(index<0)
                            sum /= (*m_var1)[m_index1][-index-1].toFloat();
                    }
                    (*m_var1)[m_index1][i] = QVariant(sum);
                    break;
                }
                }
            }
        }
        //var2-get
        for(int i=0;i<m_headerLabels1.count();i++){
            if(m_tagMap.keys().contains(m_headerLabels1.at(i))){
                if(m_headerLabels2.contains(m_headerLabels1.at(i))){
                    int k = m_headerLabels2.indexOf(m_headerLabels1.at(i));
                    QStringList strList1=((QString)m_tableAuto2[k]).split(':');
                    switch(((QString)strList1[0]).toInt()){
                    case 1:
                    case 3:{
                        for(int j=1;j<(*m_var2)[m_index1].count();j++){
                            (*m_var2)[m_index1][j][k] = (*m_var1)[m_index1][i];
                        }
                        break;
                    }
                    }

                }
            }
        }
        //var2-cal
        for(int j=1;j<(*m_var2)[m_index1].count();j++){
            for(int i=0;i<m_headerLabels2.count();i++){
                QStringList strList1=((QString)m_tableAuto2[i]).split(':');
                QStringList strList2;
                switch(((QString)strList1[0]).toInt()){
                case 2:{
                    strList2=((QString)strList1[1]).split(',');
                    float sum;
                    if(m_tableType2.at(i)=="numE"){
                        if(j==1)
                            sum = 0;
                        else
                            sum = (*m_var2)[m_index1][j-1][i].toFloat();
                    }
                    else
                        sum = 0;
                    for(int n=0;n<strList2.count();n++){
                        int index=((QString)strList2[n]).toInt();
                        if(index>0)
                            sum += (*m_var2)[m_index1][j][index-1].toFloat();
                        else if(index<0)
                            sum -= (*m_var2)[m_index1][j][-index-1].toFloat();
                    }
                    (*m_var2)[m_index1][j][i] = QVariant(sum);
                    break;
                }
                case 4:{
                    strList2=((QString)strList1[1]).split(',');
                    float sum;
                    if(m_tableType2.at(i)=="numE"){
                        if(j==1)
                            sum = 1;
                        else
                            sum = (*m_var2)[m_index1][j-1][i].toFloat();
                    }
                    else
                        sum = 1;
                    for(int n=0;n<strList2.count();n++){
                        int index=((QString)strList2[n]).toInt();
                        if(index>0)
                            sum *= (*m_var2)[m_index1][j][index-1].toFloat();
                        else if(index<0)
                            sum /= (*m_var2)[m_index1][j][-index-1].toFloat();
                    }
                    (*m_var2)[m_index1][j][i] = QVariant(sum);
                    break;
                }
                case 5:{
                    QVariant value;
                    if(((QString)strList1[1]).contains('$')){
                        strList2=((QString)((QString)strList1[1]).remove('$')).split('/');
                        if(strList2.count()==2){
                            int n1 = ((QString)strList2[0]).toInt();
                            int n2 = ((QString)strList2[1]).toInt();
                            if(n1>0)
                                value = (*m_var2)[m_index1][n1][n2-1];
                            else{
                                if(j+n1>1)
                                    value = (*m_var2)[m_index1][j+n1][n2-1];
                                else
                                    value = 0;
                            }
                        }
                    }
                    (*m_var2)[m_index1][j][i] = value;
                    break;
                }
                }
            }
    }
    }
    //details
    else{
        //var1
        for(int i=0;i<m_headerLabels1.count();i++){
            int index = m_headerLabels2.indexOf(m_headerLabels1[i]);
            if(index!=-1){
            if(m_tableType2[index]=="int")
                (*m_var1)[m_index1][i] = QVariant((*m_var1)[m_index1][i].toInt() - (*m_var2)[m_index1][m_index2][index].toInt());
            else if(m_tableType2[index]=="num")
                (*m_var1)[m_index1][i] = QVariant((*m_var1)[m_index1][i].toFloat() - (*m_var2)[m_index1][m_index2][index].toFloat());
            }
        }
        //var2-get
        for(int i=0;i<m_headerLabels2.count();i++){
            if(m_tagMap.keys().contains(m_headerLabels2.at(i))){
                if(m_tableType2.at(i)=="date")
                    (*m_var2)[m_index1][m_index2][i] = QVariant(m_dateHash[m_tagMap.value(m_headerLabels2.at(i))]->GetData());
                else if(m_tableType2.at(i)=="text")
                    (*m_var2)[m_index1][m_index2][i] = QVariant(m_lineHash[m_tagMap.value(m_headerLabels2.at(i))]->GetValue());
                else if(m_tableType2.at(i)=="int")
                    (*m_var2)[m_index1][m_index2][i] = QVariant(m_lineHash[m_tagMap.value(m_headerLabels2.at(i))]->GetValue().toInt());
                else if(m_tableType2.at(i)=="num"||m_tableType2.at(i)=="numC"||m_tableType2.at(i)=="numS"||m_tableType2.at(i)=="numE")
                    (*m_var2)[m_index1][m_index2][i] = QVariant(m_lineHash[m_tagMap.value(m_headerLabels2.at(i))]->GetValue().toDouble());
            }
        }
        //var2-cal
        for(int j=m_index2;j<(*m_var2)[m_index1].count();j++){
            for(int i=0;i<m_headerLabels2.count();i++){
                QStringList strList1=((QString)m_tableAuto2[i]).split(':');
                QStringList strList2;
                switch(((QString)strList1[0]).toInt()){
                case 2:{
                    strList2=((QString)strList1[1]).split(',');
                    float sum;
                    if(m_tableType2.at(i)=="numE"){
                        if(j==1)
                            sum = 0;
                        else
                            sum = (*m_var2)[m_index1][j-1][i].toFloat();
                    }
                    else
                        sum = 0;
                    for(int n=0;n<strList2.count();n++){
                        int index=((QString)strList2[n]).toInt();
                        if(index>0)
                            sum += (*m_var2)[m_index1][j][index-1].toFloat();
                        else if(index<0)
                            sum -= (*m_var2)[m_index1][j][-index-1].toFloat();
                    }
                    (*m_var2)[m_index1][j][i] = QVariant(sum);
                    break;
                }
                case 4:{
                    strList2=((QString)strList1[1]).split(',');
                    float sum;
                    if(m_tableType2.at(i)=="numE"){
                        if(j==1)
                            sum = 1;
                        else
                            sum = (*m_var2)[m_index1][j-1][i].toFloat();
                    }
                    else
                        sum = 1;
                    for(int n=0;n<strList2.count();n++){
                        int index=((QString)strList2[n]).toInt();
                        if(index>0)
                            sum *= (*m_var2)[m_index1][j][index-1].toFloat();
                        else if(index<0)
                            sum /= (*m_var2)[m_index1][j][-index-1].toFloat();
                    }
                    (*m_var2)[m_index1][j][i] = QVariant(sum);
                    break;
                }
                case 5:{
                    QVariant value;
                    if(((QString)strList1[1]).contains('$')){
                        int rows = (*m_var2)[m_index1].count();
                        strList2=((QString)((QString)strList1[1]).remove('$')).split('/');
                        if(strList2.count()==2){
                            int n1 = ((QString)strList2[0]).toInt();
                            int n2 = ((QString)strList2[1]).toInt();
                            if(n1>0)
                                value = (*m_var2)[m_index1][n1][n2-1];
                            else{
                                if(rows+n1>1)
                                    value = (*m_var2)[m_index1][rows+n1][n2-1];
                                else
                                    value = 0;
                            }
                        }
                    }
                    (*m_var2)[m_index1][j][i] = value;
                    break;
                }
                }
            }
        }
        //var1
        for(int i=0;i<m_headerLabels1.count();i++){
            int index = m_headerLabels2.indexOf(m_headerLabels1[i]);
            if(index!=-1){
            if(m_tableType2[index]=="int")
                (*m_var1)[m_index1][i] = QVariant((*m_var1)[m_index1][i].toInt() + (*m_var2)[m_index1][m_index2][index].toInt());
            else if(m_tableType2[index]=="num")
                (*m_var1)[m_index1][i] = QVariant((*m_var1)[m_index1][i].toFloat() + (*m_var2)[m_index1][m_index2][index].toFloat());
            else if(m_tableType2[index]=="numE")
                (*m_var1)[m_index1][i] = QVariant((*m_var2)[m_index1][(*m_var2)[m_index1].count()-1][index].toFloat());
            else if(m_tableType2[index]=="numS")
                (*m_var1)[m_index1][i] = QVariant((*m_var2)[m_index1][1][index].toFloat());
            }
        }
    }
    m_output->MessageHit("已修改");
    BtnCal();
    BtnFlash();
    this->close();
}
void EditWidget::BtnFlash(){}
void EditWidget::BtnCal(){}
bool EditWidget::Check(){
    return true;
}
void EditWidget::Loading(){
    if(m_index2==-1){
        QList<QVariant> list = (*m_var1)[m_index1];
        QStringList strList;
        for(int i=0;i<m_headerLabels1.count();i++){
            if(m_tagMap.keys().contains(m_headerLabels1[i])){
                if(m_typeMap.value(m_headerLabels1[i]) == "Text")
                    m_lineHash[m_tagMap.value(m_headerLabels1[i])]->SetValue(list[i].toString());
                else if(m_typeMap.value(m_headerLabels1[i]) == "Number")
                    m_lineHash[m_tagMap.value(m_headerLabels1[i])]->SetValue(list[i].toFloat());
                else if(m_typeMap.value(m_headerLabels1[i]) == "Int")
                    m_lineHash[m_tagMap.value(m_headerLabels1[i])]->SetValue(list[i].toInt());
                else if(m_typeMap.value(m_headerLabels1[i]) == "ComboBox"){
                }
                else if(m_typeMap.value(m_headerLabels1[i]) == "Date"){
                    QDate date = QDate::fromString(list[i].toString(), "yyyy.M.d");
                    m_dateHash[m_tagMap.value(m_headerLabels1[i])]->Update(date.toString("yyyyMMdd"));
                }
            }
            if(m_tableAuto1[i]=="3:"){
                strList.append(m_headerLabels1[i]);
            }
        }
        QString name = m_typeMap.key("Radio");
        if(name != "" && strList.count()>0){
            for(int i=0;i<strList.count();i++){
                m_radioHash[m_tagMap.value(name)]->SetValue(i+1, list[m_headerLabels1.indexOf(strList[i])].toString()=="是");
            }
        }
    }
    else{
        QList<QVariant> list = (*m_var2)[m_index1][m_index2];
        for(int i=0;i<m_headerLabels2.count();i++){
            if(m_tagMap.keys().contains(m_headerLabels2[i]) || m_typeMap.value(m_headerLabels2[i]) == "Radio"){
                if(m_typeMap.value(m_headerLabels2[i]) == "Text")
                    m_lineHash[m_tagMap.value(m_headerLabels2[i])]->SetValue(list[i].toString());
                else if(m_typeMap.value(m_headerLabels2[i]) == "Number")
                    m_lineHash[m_tagMap.value(m_headerLabels2[i])]->SetValue(list[i].toFloat());
                else if(m_typeMap.value(m_headerLabels2[i]) == "Int")
                    m_lineHash[m_tagMap.value(m_headerLabels2[i])]->SetValue(list[i].toInt());
                else if(m_typeMap.value(m_headerLabels2[i]) == "ComboBox"){
                }
                else if(m_typeMap.value(m_headerLabels2[i]) == "Date"){
                    QDate date = QDate::fromString(list[i].toString(), "yyyy.M.d");
                    m_dateHash[m_tagMap.value(m_headerLabels2[i])]->Update(date.toString("yyyyMMdd"));
                }
            }
        }
    }
}
void EditWidget::AddLine(EditLine line)
{
    switch(line.type){
    case EditType::Text:{
        ULine *uline = new ULine(line.name, line.tip);
        m_layout->addLayout(uline);
        m_lineHash.insert(line.tag, uline);
        break;
    }
    case EditType::Number:{
        ULine *uline = new ULine(line.name, line.tip);
        uline->SetDouble(2,999999999);
        uline->SetValue(0.00f);
        m_layout->addLayout(uline);
        m_lineHash.insert(line.tag, uline);
        break;
    }
    case EditType::Int:{
        ULine *uline = new ULine(line.name, line.tip);
        uline->SetInt(999999999,-999999999);
        uline->SetValue((int)0);
        m_layout->addLayout(uline);
        m_lineHash.insert(line.tag, uline);
        break;
    }
    case EditType::ComboBox:{
        break;
    }
    case EditType::Date:{
        m_dateLayout = new QHBoxLayout();
        QLabel *label = new QLabel();
        label->setText(line.name);
        label->setMaximumSize(80,25);
        m_labelHash.insert(line.tag, label);
        m_dateLayout->addWidget(label);
        m_dateLayout->addSpacing(55);
        UDateBox *udate = new UDateBox(1);
        m_dateLayout->addWidget(udate);
        m_dateHash.insert(line.tag, udate);
        m_layout->addLayout(m_dateLayout);
        break;
    }
    case EditType::Radio:{
        if(line.list.count()<=2){
            URadio *uRadio;
            if(line.list.count()==1)
                uRadio = new URadio(line.name,line.list[0]);
            else
                uRadio = new URadio(line.name,line.list[0],line.list[1]);
            m_layout->addLayout(uRadio);
            m_radioHash.insert(line.tag, uRadio);
        }
        break;
    }
    default:{
        break;
    }
    }
}
void EditWidget::AddButton(WidgetType type)
{
    m_btnLayout = new QHBoxLayout();
    m_layout->addLayout(m_btnLayout);
    switch(type){
    case WidgetType::Add:{
        UButton *ubtn = new UButton("添加", "Return", 80, 30, m_btnLayout);
        m_btnHash.insert("OK", ubtn);
        ubtn = new UButton("取消", "Esc", 80, 30, m_btnLayout);
        m_btnHash.insert("ESC", ubtn);
        break;
    }
    case WidgetType::Edit:{
        UButton *ubtn = new UButton("修改", "Return", 80, 30, m_btnLayout);
        m_btnHash.insert("EDIT", ubtn);
        ubtn = new UButton("返回", "Esc", 80, 30, m_btnLayout);
        m_btnHash.insert("ESC", ubtn);
        break;
    }
    default:{
        UButton *ubtn = new UButton("好的", "Return", 80, 30, m_btnLayout);
        m_btnHash.insert("OK", ubtn);
        break;
    }
    }
}
//EditLine
EditWidget::EditLine::EditLine(){
}
EditWidget::EditLine::EditLine(QString name, QString tag, EditType type, QString tip)
{
    this->name = name;
    this->tag = tag;
    this->type = type;
    this->tip = tip;
}
EditWidget::EditLine::EditLine(QString name, QString tag, EditType type, QString tip, QList<QString> list)
{
    this->name = name;
    this->tag = tag;
    this->type = type;
    this->tip = tip;
    this->list = list;
}

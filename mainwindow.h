#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>

class QGridLayout;
class UButton;

class QTabWidget;
class IniData;
class OutPut;
class ULoading;

class WidgetPurchase;
class WidgetSell;
class WidgetBank;
class WidgetIncome;
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(IniData *ini, QWidget *parent = 0);
    ~MainWindow();
    void keyPress(QKeyEvent *);
    void mouseMove(QMouseEvent *);
    void mousePress(QMouseEvent *);
    void mouseRelease(QMouseEvent *);
public:
    IniData *m_ini;
    OutPut *m_output;
public slots:
    void OpenLayer1();
    void OpenLayer2();
    void OpenLayer3();
    void OpenLayer4();
    void OpenLayer5();
    void OpenLayer6();
private:
    //创建
    void Loading();
    void CreateWidget();     //创建窗口
    void createMenus();     //创建菜单
    void createActions();   //创建动作
    QWidget *m_centerWindow;
    QGridLayout *m_layout;
    UButton *m_btn1, *m_btn2, *m_btn3, *m_btn4, *m_btn5, *m_btn6;

    WidgetPurchase *m_purchaseWidget;
    WidgetSell *m_sellWidget;
    WidgetBank *m_bankWidget;
    WidgetIncome *m_incomeWidget;
};

#endif // MAINWINDOW_H

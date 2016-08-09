#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setRowCount(2);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"sex"<<"name"<<"age");

    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);  //整行选中的方式
/* 设置单元格行选模式
 * QAbstractItemView.SelectionBehavior枚举还有如下类型
QAbstractItemView.SelectItems	0	Selecting single items.	选中单个单元格
QAbstractItemView.SelectRows	1	Selecting only rows.	选中一行
QAbstractItemView.SelectColumns	2	Selecting only columns.	选中一列
*/

    ui->tableWidget->setEditTriggers(QAbstractItemView::AnyKeyPressed | QAbstractItemView::DoubleClicked);  //双击修改或者按任意键修改

/*
 *  设置表格的编辑模式
    在默认情况下，表格里的字符是可以更改的，比如双击一个单元格，就可以修改原来的内容，如果想禁止用户的这种操作，让这个表格对用户只读，可以这样：
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QAbstractItemView.NoEditTriggers是QAbstractItemView.EditTrigger枚举中的一个，都是触发修改单元格内容的条件：

QAbstractItemView.NoEditTriggers	0	No editing possible. 									不能对表格内容进行修改
QAbstractItemView.CurrentChanged	1	Editing start whenever current item changes.			任何时候都能对单元格修改
QAbstractItemView.DoubleClicked		2	Editing starts when an item is double clicked.			双击单元格
QAbstractItemView.SelectedClicked	4	Editing starts when clicking on an already selected item.单击已选中的内容
QAbstractItemView.EditKeyPressed	8	Editing starts when the platform edit key has been pressed over an item.
QAbstractItemView.AnyKeyPressed		16	Editing starts when any key is pressed over an item.		按下任意键就能修改
QAbstractItemView.AllEditTriggers	31	Editing starts for all above actions.					以上条件全包括
*/
    ui->tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);  //设置为可以选中单个
/*
 单个选中和多个选中的设置：
tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);  //设置为可以选中多个目标
该函数的参数还可以是：
QAbstractItemView.NoSelection      不能选择
QAbstractItemView.SingleSelection  选中单个目标
QAbstractItemView.MultiSelection    选中多个目标
QAbstractItemView.ExtendedSelection 和 QAbstractItemView.ContiguousSelection 的区别不明显，主要功能是正常情况下是单选，但按下Ctrl或Shift键后，可以多选
*/
    ui->tableWidget->setItem(0,1,new QTableWidgetItem("zhangsan"));
    ui->tableWidget->setItem(0,2,new QTableWidgetItem("1"));

    ui->tableWidget->verticalHeader()->setVisible(false);   //隐藏列表头
/*
 * 表格表头的显示与隐藏
对于水平或垂直方法的表头，可以用以下方式进行 隐藏/显示 的设置：
tableWidget->verticalHeader()->setVisible(false);   //隐藏列表头
tableWidget->horizontalHeader()->setVisible(false); //隐藏行表头
*/
    QTableWidgetItem *columnHeaderItem0 = ui->tableWidget->horizontalHeaderItem(1); //获得水平方向表头的Item对象
    columnHeaderItem0->setFont(QFont("Helvetica")); //设置字体
    columnHeaderItem0->setBackgroundColor(QColor(0,60,10)); //设置单元格背景颜色
    columnHeaderItem0->setTextColor(QColor(200,111,30)); //设置文字颜色
//在单元格里加入控件
//QTableWidget不仅允许把文字加到单元格，还允许把控件也放到单元格中。比如，把一个下拉框加入单元格，可以这么做：
    QComboBox *comBox = new QComboBox();
    comBox->addItem("Boy");
    comBox->addItem("Girl");
    ui->tableWidget->setCellWidget(0,0,comBox); //设置控件
    //读取控件值
    QWidget * widget=ui->tableWidget->cellWidget(0,0);//获得widget
    QComboBox *combox=(QComboBox*)widget;//强制转化为QComboBox
    QString string=combox->currentText();
    qDebug()<<string;

    //对所有的单元格的字体进行设置，则可以使用
    //ui->tableWidget->setFont(QFont("Helvetica"));


    //设置单个单元格的字体颜色和背景颜色及字体字符
    QTableWidgetItem *item = new QTableWidgetItem("Apple");
    item->setBackgroundColor(QColor(0,60,10));
    item->setTextColor(QColor(200,111,100));
    item->setFont(QFont("Helvetica"));
    ui->tableWidget->setItem(1,0,item);

    //设置单元格内文字的对齐方式
/*
这个比较简单，使用newItem.setTextAlignment()函数即可，该函数的参数为单元格内的对齐方式，和字符输入顺序是自左相右还是自右向左。
水平对齐方式有：
Qt::AlignLeft	0x0001	Aligns with the left edge.
Qt::AlignRight	0x0002	Aligns with the right edge.
Qt::AlignHCenter	0x0004	Centers horizontally in the available space.
Qt::AlignJustify	0x0008	Justifies the text in the available space.
垂直对齐方式：
Qt::AlignTop		0x0020	Aligns with the top.
Qt::AlignBottom	0x0040	Aligns with the bottom.
Qt::AlignVCenter	0x0080	Centers vertically in the available space.
如果两种都要设置，只要用 Qt.AlignHCenter |  Qt.AlignVCenter 的方式即可
*/
    QTableWidgetItem *item2 = new QTableWidgetItem("Cat");
    item2->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    ui->tableWidget->setItem(1,1,item2);

    ui->tableWidget->selectRow(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tableWidget_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous)
{

    if(previous!=Q_NULLPTR)
    {
        previous->setBackgroundColor(Qt::transparent);
    }
    if(current==Q_NULLPTR)return;
    current->setBackgroundColor(Qt::blue);
}

void MainWindow::on_btn_Add_clicked()
{
//    QAbstractItemModel *model = ui->tableWidget->model();
//     model->insertRow(model->rowCount());
    int cols=ui->tableWidget->columnCount();
    int rows=ui->tableWidget->rowCount();
    qDebug()<<rows;
    ui->tableWidget->insertRow(rows);
    for(int i=0;i<cols;i++)
    {
        ui->tableWidget->setItem(rows,i,new QTableWidgetItem("new"+QString::number(rows)));
    }
    ui->tableWidget->selectRow(rows);
}

void MainWindow::on_btn_Del_clicked()
{
    QTableWidgetItem * item = ui->tableWidget->currentItem();
    if(item==Q_NULLPTR)return;
    ui->tableWidget->removeRow(item->row());
}

void MainWindow::on_btn_Modify_clicked()
{
    QModelIndex index =  ui->tableWidget->currentIndex();
    QList<QTableWidgetItem *> listItem = ui->tableWidget->selectedItems();
    if(listItem.count()==0)return;
    foreach (QTableWidgetItem * item, listItem) {
        item->setText("modify");
    }
//    QTableWidgetItem * item = ui->tableWidget->currentItem();
//    if(item==Q_NULLPTR)return;
//    item->setText("modify");
}


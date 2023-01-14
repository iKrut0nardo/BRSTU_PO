#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->myListWidget->addItem("Minsk");
    ui->myListWidget->insertItem(1, "Moscow");
    connect(ui->buttonDelete, SIGNAL(clicked()), this, SLOT(deleteListItem( )));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::deleteListItem()
{
    qDebug() << "Button deleted is pressed!" ;
    int row = ui->myListWidget->currentRow();
    qDebug() << "Current: " << row ;
    if( row >= 0 && row < ui->myListWidget->count()) {
        ui->myListWidget->takeItem(row);

    } else {
        qDebug() << "Wrong item index: " << row ;
    }
}

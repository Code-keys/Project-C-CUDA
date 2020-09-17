#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "darknet.h"
#include <iostream>

#include<opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#include "cuda_runtime.h"


// FUNCTION COMPLEMENT
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	this->move(QPoint((1960 - this->rect().width()) / 2, (1024 - this->rect().height()) / 2));
    setWindowIcon(QIcon(":/resources/cut.png"));
    
    _work_thr = new wkThread;
	work_thr = new wkThread;
    
    Scene_L = new QGraphicsScene;//图像显示
    Scene_R = new QGraphicsScene;//图像显示

    qRegisterMetaType<mdata>("mdata");// 元类型可zai不同线程之间通信
    qRegisterMetaType<statue>("statue");// 元类型可zai不同线程之间通信


    connect(ui->BN_1,SIGNAL(clicked()),this,SLOT(FileDialogBN()));
    
    connect(ui->BN_2,SIGNAL(clicked()),this,SLOT(sendMsgSlot()));
    connect(this,SIGNAL(sigMsg_plugin(mdata)),this,SLOT(sigASlot(mdata)), Qt::QueuedConnection);

    connect(ui->BN_3,SIGNAL(clicked()),this,SLOT(sender_metadata(mdata)));
    connect(this, SIGNAL(sender_data(mdata)), work_thr, SLOT(pro_data(mdata)), Qt::QueuedConnection);
    connect(work_thr, SIGNAL(send_metadata(mdata)), this, SLOT(process_metadata(mdata)), Qt::QueuedConnection);

    connect(ui->action_Open_weight,SIGNAL(triggered()),this,SLOT(FileDialogBN()));
    connect(ui->action_Open_class,SIGNAL(triggered()),this,SLOT(FileDialogBN()));
    connect(ui->action_Open_cfg,SIGNAL(triggered()),this,SLOT(FileDialogBN()));
    connect(ui->action_pic,SIGNAL(triggered()),this,SLOT(imshow()));
    connect(ui->action_video,SIGNAL(triggered()),this,SLOT(imshow()));  

    // connect(ui->action_Open_cfg,SIGNAL(triggered()),this,SLOT(FileDialog()));


}

void MainWindow::box(int a){
    switch (a)
    {
    case 1:
        QMessageBox::critical(NULL, "critical", "Content", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        break;
    case 2:
        QMessageBox::question(NULL, "question", "SOME THING NOT CONFIGURE !", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        break;
    case 3:
        QMessageBox::warning(NULL, "warning", "", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);     
        break;
    case 4:
        QMessageBox::about(NULL, "About", "About this application");
        break;
    default:
        break;
    }

};

void MainWindow::custum_box(){
    QMessageBox message(QMessageBox::NoIcon, "Title", "Content with icon."); 
    message.setIconPixmap(QPixmap("icon.png")); 
    message.exec();
}

void MainWindow::FileDialogBN(){
    QAction *Sender=qobject_cast<QAction *>(sender());
//定义文件对话框类
	QFileDialog *fileDialog = new QFileDialog(this);
	//定义文件对话框标题
	fileDialog->setWindowTitle(QStringLiteral("选择"));
	//设置文件过滤器
    if (Sender->text()=="Open_cfg")
            {fileDialog->setNameFilter(tr("File(*.cfg*)"));}
        else if (Sender->text()=="Open_weight")
            {fileDialog->setNameFilter(tr("File(*.weights*)"));}
        else if (Sender->text()=="Open_class")
            {fileDialog->setNameFilter(tr("File(*.*)"));};
	//设置可以选择多个文件,默认为只能选择一个文件QFileDialog::ExistingFiles
	fileDialog->setFileMode(QFileDialog::ExistingFiles);
	//设置视图模式
	fileDialog->setViewMode(QFileDialog::Detail);
	//打印所有选择的文件的路径
	if (fileDialog->exec()) {
        QStringList name = fileDialog->selectedFiles();
        if (Sender->text()=="Open_cfg")
            {cfg_name =  name;}
        else if (Sender->text()=="Open_weight")
            {weight_name =  name;}
        else if (Sender->text()=="Open_class")
            {class_name =  name;};
	};
    Sender->setCheckable(true);
    // qDebug() << Sender->text()<< cfg_name << weight_name<< class_name ;
};

void MainWindow::imshow(){
{ 
    QString filename = QFileDialog::getOpenFileName(this,tr("选择图像"),"",tr("Images(*.png *.bmp *.jpg *.tif *.gif);;AllFiles(*.*)"));
    if(filename.isEmpty())
    {
	    if (_img.isNull()){return;}
	    else{
		   return;
	    }
    }
    else
    {
        if (filename.endsWith("jpeg")||filename.endsWith("png")||filename.endsWith("tif")||filename.endsWith("jpg")||filename.endsWith("bmp"))    
        {
                cv::Mat image;
                image = cv::imread(filename.toUtf8().data());// toLatin1().data()
                if(!(_img.load(filename)))//加载图像
                {
                        QMessageBox::information(this, tr("打开图像失败"),tr("打开图像失败!"));
                        return ;
                }

               
                Scene_L->addPixmap(QPixmap::fromImage(_img));
                ui->graphicsView_L->setScene(Scene_L);
                ui->graphicsView_L->show();
        }
        

          //ui->label->setPixmap(QPixmap::fromImage(disImage.scaled(ui->label->size(), Qt::KeepAspectRatio)));
//        ui->graphicsView_UR->setPixmap(QPixmap::fromImage(img));
    }    }
//        ui->lb_Screen->setScaledContents(true);

}

MainWindow::~MainWindow()
{
    delete ui;
    cfg_name.empty();
    delete Scene_L;
    delete Scene_R;
}


wkThread::wkThread() : QThread()
{
    // qRegisterMetaType<mdata>("mdata");// 元类型可zai不同线程之间通信
}
void wkThread::run()
{
    while(true)
    {
        qDebug("Thread processing ...........");
        metaData.Fname = "hello";
        emit send_data(metaData); // 多线程间的通信 将i的值发送到主线程中
        this->msleep(1000);

    }
}
void wkThread::pro_data(mdata metaData){

}
wkThread::~wkThread(){delete &metaData;};
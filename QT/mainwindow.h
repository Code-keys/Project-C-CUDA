#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "darknet.h"
#include <vector>
// signal  plugin.
#include <QtGui/QtGui>
#include <QtCore/QtCore>
#include <QtCore/QVariant>
#include <QtCore/QMetaType>  
#include <QtCore/QThread>

#include <QtWidgets/QWidget>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QDesktopWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>

typedef struct _boxCC {
    float x, y, w, h ,cls, conf;
} boxCC;
typedef struct _mdata
{
    QImage img;
    QString Fname;           //mac
    int  type;             //类型
    std::vector<boxCC> boxes;
}mdata;  //元数据
typedef struct _process_statue
{
    int  sta;             //类型
}statue;  //元数据

namespace Ui {
class MainWindow;
class wkThread;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void box(int a);
    void custum_box();
    void FileDialogBN();
    wkThread* _work_thr;
    wkThread* work_thr;

 signals: // 
        void sigMsg_plugin(mdata);
        void file_open_sigMsg_plugin(int type);
        void sender_data(mdata);

public slots:
        void sendMsgSlot(){
                mdata m_info;
                m_info.Fname = "4E:3F:3D:48";//  里面可　ｇｅｔ　ｕｉ的返回信息
                m_info.type = 1;
                emit sigMsg_plugin(m_info);// emit 传递特定的信息　来供给他人（）处理的　（可用来传输　参数设置的内容　或者更新界面参数）
};
        void sigASlot(mdata info){qDebug()<<"sigMsg_plugin.file name:"<<info.Fname;};//　接受特定的信息　进行处理

private slots:
        void sender_metadata(){emit sender_data(data);};
private:
    void imshow();

    mdata data;
    Ui::MainWindow *ui;
    QStringList cfg_name;
    QStringList weight_name;
    QStringList class_name;
    QStringList pic_name;
    QStringList video_name;

    QImage _img ;
    QGraphicsScene *Scene_L;
    QGraphicsScene *Scene_R;
};

class wkThread :public QThread
{
    Q_OBJECT
public:
        explicit wkThread();
        ~wkThread();
signals:
        void send_data(mdata); // 直接使用emit进行数据的发送
public slots:
        void pro_data(mdata);
protected:
        void run();
private :
        mdata metaData;
        statue FT;
};

/*
//Plugin　　｜特定信号　+　特定槽｜　链接　使用
        signal:
            void sigMsg_plugin(DeviceInfo info);
        public slots:
                void sendMsgSlot(){
                        DeviceInfo m_info;
                        m_info.Mac = "4E:3F:3D:48";　　//  里面可　ｇｅｔ　ｕｉ的返回信息
                        m_info.type = 1;
                        emit sigMsg_plugin(m_info);　　　// emit 传递特定的信息　来供给他人（）处理的　（可用来传输　参数设置的内容　或者更新界面参数）
                };
                void sigASlot(DeviceInfo info){qDebug()<<"sigMsg_plugin.Mac:"<<info.Mac;};　　//　接受特定的信息　进行处理

                //***方法1：引入头文件#include < QMetaType>，使用 qRegisterMetaType<>()进行元类型注册
                //　构造函数里的　注册加上　signal -->> SLOT　的链接
                qRegisterMetaType<DeviceInfo>("DeviceInfo");
                connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(sendMsgSlot()));
                connect(this,SIGNAL(sigMsg_plugin(DeviceInfo)),this,SLOT(sigASlot(DeviceInfo)));

                **方法2：使用connect函数的第5个参数Qt::DirectConnection
                connect(objA,SIGNAL(sig(customType)),objB,SLOT(sigSLOT(customType)),Qt::DirectConnection);

                **方法3：如果需要一个信号发送很多数据类型，这个时候就需要一种通用的数据处理方式。这个时候可以利用QVariant
                                    使用这种方式首先要在数据声明下面使用宏声明Q_DECLARE_METATYPE(DeviceInfo)
                void VARTest::sendMsgSlot()
{
    DeviceInfo m_info;
    m_info.Mac = "4E:3F:3D:48";
    m_info.type = 1;
    QVariant values1;
    values1.setValue(m_info);
    emit sigMsg_B(1,values1);

    int m_value = 999;
    QVariant values2;
    values2.setValue(m_value);
    emit sigMsg_B(2,values2);

    QString str("真有意思！");
    QVariant values3;
    values3.setValue(str);
    emit sigMsg_B(3,values3);

}

void VARTest::sigBSlot(int id,QVariant values)
{switch (id) {
    case 1:
    {   DeviceInfo m_info = values.value<DeviceInfo>();
        qDebug()<<"sigB Mac:"<<m_info.Mac;
        break;
    }
    case 2:
    {   qDebug()<<"sigB int:"<<values.toInt();
        break;
    }
    case 3:
    {   qDebug()<<"sigB QString:"<<values.toString();
        break;
    }
    default:
        break;
    }
}


*/

#endif // MAINWINDOW_H
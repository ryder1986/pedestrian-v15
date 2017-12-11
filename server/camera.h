#ifndef TEST_H
#define TEST_H
#include <iostream>
#include <cstdio>
#include <chrono>
#include <thread>
#include <ctime>
#include <cstring>
#include <mutex>
#include <thread>
#include <bitset>
#include <QtCore>
#include <QUdpSocket>
#include <QNetworkInterface>
#include <list>
#include "tools.h"
using namespace std;

//void fun()
//{

//    try {
//        throw std::invalid_argument("test  error!");
//    }
//    catch (const invalid_argument& ia) {
//        std::cerr << "Invalid argument: " << ia.what() << '\n';
//    }
//}
//#include <mutex>
//using namespace std;
//#include <windows.h>


class TestThread{

    static void thread_fun1()
    {

        //      this_thread::sleep_for(chrono::seconds(10));
        while(1) {

            //        Sleep(1000);
            this_thread::sleep_for(chrono::microseconds(1));
            //  lk.lock();
            prt(info,"thread fun11 ");
            // lk.unlock();
            // cout<<"1"<<endl;
        }

    }
    static void thread_fun2()
    {
        //      this_thread::sleep_for(chrono::seconds(10));


        while(1) {
            //  Sleep(1000);
            this_thread::sleep_for(chrono::microseconds(1));
            //    this_thread::sleep_for(chrono::seconds(1));
            //  lk.lock();
            prt(info,"thread fun22 ");
            // lk.unlock();
            // cout<<"1"<<endl;
        }

    }
public:
    TestThread(){

        //        while(1)
        //        {
        //           //   this_thread::sleep_for(chrono::milliseconds(1000));
        //            Sleep(1000);
        //            cout<<"aa"<<endl;

        //        }
        thread tmp1(thread_fun1);
        thread tmp2(thread_fun2);
        //   tmp.detach();
        //   this_thread::sleep_for(chrono::seconds(1));
        tmp1.join();
        tmp2.join();
    }
    ~TestThread(){}
};


class TestThread1{
public:
    void fun()
    {
        while(1)
        {
            this_thread::sleep_for(chrono::milliseconds(1000));
            //    Sleep(1000);
            cout<<t<<endl;

        }
    }

public:
    TestThread1():t(12){



    }

    int t;
};
class PrintNum1{
public:
    PrintNum1():start(17){}
    void fun()
    {
        while(1)
        {
            this_thread::sleep_for(chrono::milliseconds(1000));
            cout<<start++<<endl;
        }
    }
    void start_thread()
    {
        t=new thread(std::mem_fn(&PrintNum1::fun),*this);
    }
    void stop_thread()
    {
        t->join();
    }
private:
    int start;
    // thread t(std::mem_fn(&PrintNum1::fun),*(PrintNum1 *)obj);
    thread *t;
};
class AThread{
public:
    AThread()
    {

    }

};
class AbstructThread{
public:

    AbstructThread(thread *th):t(th){
        thread_started=1;
        cout<<thread_started<<endl;

        //sss=11;
    }
    //virtual void fun()=0;
    ~AbstructThread()
    {
        //    t->join();
    }
    int is_started()
    {
        cout<<thread_started<<endl;
        return thread_started;
    }

    void start_thread()
    {
        cout<<"thread_started"<<endl;
        thread_started=1;
    }
    void stop_thread()
    {
        cout<<"stoping thread"<<endl;
        thread_started=0;
    }
    void ter()
    {
        t->join();

    }
private:
    // thread t(std::mem_fn(&PrintNum1::fun),*(PrintNum1 *)obj);
    thread *t;
    int thread_started;

    //void *obj;
    //   / int num;
};

class Thread1{
public:
    Thread1(){
        // th=new AbstructThread(  thread(std::mem_fn(&Thread1::fun),*(Thread1*)obj));
        ttt=10;

        // p_thread=new thread(std::mem_fn(&Thread1::fun),*(Thread1*)obj);
        p_thread_fun1=THREAD_DEF(Thread1,fun1);
        p_thread_fun1->detach();
        p_thread_fun2=THREAD_DEF(Thread1,fun2);
        p_thread_fun2->detach();
    }
    void fun1()
    {
        while(1){
            if(1)
            {
                this_thread::sleep_for(std::chrono::milliseconds(10)); //休眠三秒
                cout<<__FUNCTION__<<endl;

            }
            else{
                this_thread::sleep_for(std::chrono::seconds(1)); //休眠三秒
            }
        }
    }
    void fun2()
    {
        while(1){
            if(1)
            {
                this_thread::sleep_for(std::chrono::milliseconds(10)); //休眠三秒
                cout<<__FUNCTION__<<endl;

            }
            else{
                this_thread::sleep_for(std::chrono::seconds(1)); //休眠三秒
            }
        }
    }
    thread *p_thread_fun1;
    thread *p_thread_fun2;
    //    AbstructThread *th;
    int ttt;
};



//#include <sys/socket.h>
//#include <arpa/inet.h>
//#include <netinet/in.h>
//#include <string.h>
//#include <sys/ioctl.h>
//#include <net/if.h>
//#include <fcntl.h>
//#include <stdlib.h>
//#include <stdio.h>
//#include <unistd.h>
//#include <linux/netlink.h>
//#include <linux/rtnetlink.h>
//#include <errno.h>
////#include <tcp.h>
//#include <sys/ioctl.h>
#define BROADCAST_STR "pedestrian"
/*
    ServerInfoReporter:check port 12348  per sec. if string "pedestrian" recived , send string "ssssss" to the port 12347 of incoming ip
*/

//#include "common.h"
//#include "protocol.h"


class ServerInfoReporter : public QObject{
    Q_OBJECT
public:
    ServerInfoReporter(){
        timer=new QTimer();
        connect(timer,SIGNAL(timeout()),this,SLOT(check_client()));//TODO:maybe replace with readReady signal
        udp_skt = new QUdpSocket(this);
        udp_skt->bind(Protocol::SERVER_REPORTER_PORT,QUdpSocket::ShareAddress);
       // timer->start(1000);
    }
    ~ServerInfoReporter()
    {
        disconnect(timer);
        delete timer;
        delete udp_skt;
    }
    void start()
    {
        timer->start(1000);
    }

    void stop()
    {
        timer->stop();
    }

public  slots:
    void check_client()
    {
        QByteArray client_msg;
        char *msg;
        if(udp_skt->hasPendingDatagrams())
        {
            client_msg.resize((udp_skt->pendingDatagramSize()));
            udp_skt->readDatagram(client_msg.data(),client_msg.size());
            prt(info,"msg :%s",msg=client_msg.data());
            if(!strcmp(msg,"pedestrian"))
                send_buffer_to_client();
            //   udp_skt->flush();
        }else{
            //prt(debug,"searching client on port %d",Protocol::SERVER_REPORTER_PORT)
        }
    }

    void send_buffer_to_client()
    {
        QByteArray datagram;
        datagram.clear();
        QList <QNetworkInterface>list_interface=QNetworkInterface::allInterfaces();
        foreach (QNetworkInterface i, list_interface) {
            if(i.name()!="lo"){
                QList<QNetworkAddressEntry> list_entry=i.addressEntries();
                foreach (QNetworkAddressEntry e, list_entry) {
                    if(e.ip().protocol()==QAbstractSocket::IPv4Protocol)
                    {
                        datagram.append(QString(e.ip().toString())).append(QString(",")).\
                                append(QString(e.netmask().toString())).append(QString(",")).append(QString(e.broadcast().toString()));
                    }

                }
            }
        }
        udp_skt->writeDatagram(datagram.data(), datagram.size(),
                               QHostAddress::Broadcast, Protocol::CLIENT_REPORTER_PORT);
    }
private:
    QTimer *timer;
    QUdpSocket *udp_skt;
};


#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QTextStream>
class FileDataBase{
    QByteArray data;
    QString config_filename;
public:
    FileDataBase(QString name):config_filename(name)
    {
        load_config_from_file(config_filename);
    }
    ~FileDataBase()
    {

    }
    QByteArray get()
    {
        return data;
    }
    void set(const QByteArray &d)
    {
        data=d;
        save_config_to_file();
    }


private:
    int load_config_from_file()
    {

        QFile *f=new QFile(config_filename);
        bool ret = f->open(QIODevice::ReadOnly);
        if(!ret){
            delete f;
            return 0;
        }
        data=f->readAll();
        f->close();
        return 1;
    }
    int load_config_from_file(QString file_name)
    {

        QFile *f=new QFile(file_name);
        bool ret = f->open(QIODevice::ReadOnly);
        if(!ret){
            delete f;
            return 0;
        }
        data=f->readAll();
        f->close();
        return 1;
    }
    void save_config_to_file()
    {
        QFile *f=new QFile(config_filename);
        bool ret = f->open(QIODevice::ReadWrite|QIODevice::Truncate);
        if(!ret){
            prt(info,"fail to open %s",config_filename.toStdString().data());
            delete f;
        }
        f->write(data);
        f->close();
    }
    void save_config_to_file(QString file_name)
    {
        QFile *f=new QFile(file_name);
        bool ret = f->open(QIODevice::ReadWrite|QIODevice::Truncate);
        if(!ret){
            prt(info,"fail to open %s",file_name.toStdString().data());
            delete f;
        }
        f->write(data);
        f->close();
    }
};
class CameraConfiguration{
public:
    /*
        config save in cfg(config_t),which is load from p_database(FileDatabase).
    */
    FileDataBase *p_database;
    typedef struct camera_config{
        QString ip;
        int port;
    }camera_config_t;
    typedef struct config{
        int camera_amount;
        QList<camera_config_t> camera;
    }config_t;
    config_t cfg;

    CameraConfiguration(QString name)
    {
        p_database=new FileDataBase(name);
        reload_cfg();
        //        QByteArray b=p_database->get();
        //        cfg=decode_from_json(b);
    }
    ~CameraConfiguration()
    {
        delete p_database;
    }
    //    int add_camera(int index,QString url,int port)
    //    {
    //        if(index<0||index > Protocol::camera_max_num)
    //            return -1;
    //        camera_config_t cam;
    //        cam.ip=url;
    //        cam.port=port;
    //        cfg.camera.insert(index,cam);
    //        cfg.camera_amount++;
    //        save();
    //        return 0;
    //    }

    //    int del_camera(int index)
    //    {
    //        if(index<0||index > Protocol::camera_max_num)
    //            return -1;
    //        cfg.camera.removeAt(index-1);
    //        cfg.camera_amount--;
    //        save();
    //        return 0;
    //    }
    //    void mod_camera()
    //    {

    //    }
    void set_config(QByteArray &ba)
    {
        p_database->set(ba);
        reload_cfg();
    }

    void set_config(const char *buf)
    {
        QByteArray ba;
        ba.clear();
        ba.append(buf);
        p_database->set(ba);
        reload_cfg();
    }
    //    camera_config_t get_camera_config(int index)
    //    {
    //        if(index>0&&index<=cfg.camera_amount)
    //          return cfg.camera[index-1];

    //    }
    //    camera_config_t get_camera_config()
    //    {
    //        if(0<cfg.camera_amount)
    //          return cfg.camera[cfg.camera_amount-1];
    //        else
    //            return NULL;
    //    }
private:
    void reload_cfg()
    {
        QByteArray b=p_database->get();
        cfg=decode_from_json(b);
    }

    void save()
    {
        p_database->set(encode_to_json(cfg));
    }
    /*
        parse structure from data
    */
    config_t decode_from_json(QByteArray &json_src)
    {
        QJsonDocument json_doc=QJsonDocument::fromJson(json_src);
        QJsonObject root_obj=json_doc.object();
        config_t data;
        data.camera.clear();
        data.camera_amount=get_int(root_obj,"camera_total_number");
        QJsonArray cams=get_child_array(root_obj,"camera");

        foreach (QJsonValue v, cams) {
            QJsonObject obj=v.toObject();
            camera_config_t t;
            t.ip=get_string(obj,"ip");
            t.port=get_int(obj,"port");
            data.camera.append(t);
        }
        return data;
    }
    /*
        pack data from structure
    */
    QByteArray encode_to_json(config_t data)
    {
        QJsonDocument json_doc_new;
        QJsonObject root_obj;

        root_obj["camera_total_number"]=data.camera_amount;
        QJsonArray cams;

        for(int i=0;i<data.camera_amount;i++)
        {
            QJsonObject o;
            o["ip"]=data.camera[i].ip;
            o["port"]=data.camera[i].port;
            cams.append(o);
        }
        root_obj["camera"]=cams;
        json_doc_new.setObject(root_obj);
        return json_doc_new.toJson();

    }

    inline int get_int(QJsonObject obj,const char *member_name)
    {
        return obj[member_name].toInt();
    }
    inline QString get_string(QJsonObject obj,const char *member_name)
    {
        return obj[member_name].toString();
    }
    inline bool get_bool(QJsonObject obj,const char *member_name)
    {
        return obj[member_name].toBool();
    }
    inline QJsonObject get_child_obj(QJsonObject obj,const char *member_name)
    {
        return obj[member_name].toObject();
    }
    inline QJsonArray get_child_array(QJsonObject obj,const char *member_name)
    {
        return obj[member_name].toArray();
    }
};

class Config
{
    typedef struct camera_data{
        QString ip;
        int port;
    }camera_data_t;
    typedef struct data{
        int camera_amount;
        QList<camera_data_t> camera;
    }data_t;
public:

    Config(char *name)
    {
        config_filename.clear();
        config_filename.append(name);
        load_config_from_file();
    }
    ~Config()
    {

    }




    //    void set_ba(QByteArray ba){
    //        decode_from_json(ba);
    //        save_config_to_file();
    //    }
    //    QByteArray get_ba(){
    //        return encode_to_json();
    //    }
    //    void save(){
    //        save_config_to_file();
    //    }
    //    void append_camera(QString url,int port)
    //    {
    //        camera_data_t cam;
    //        cam.ip=url;
    //        cam.port=port;
    //        data.camera.append(cam);
    //        data.camera_amount++;
    //        save();
    //    }
    //    void del_camera(int index)
    //    {
    //        data.camera.removeAt(index-1);
    //        data.camera_amount--;
    //        save();
    //    }




    int load_config_from_file()
    {

        QFile *f=new QFile(config_filename);
        bool ret = f->open(QIODevice::ReadOnly);
        if(!ret){
            delete f;
            return 0;
        }
        QByteArray json_data;
        json_data=f->readAll();
        decode_from_json(json_data);
        f->close();
        return 1;
    }
    int load_config_from_file(QString file_name)
    {

        QFile *f=new QFile(file_name);
        bool ret = f->open(QIODevice::ReadOnly);
        if(!ret){
            delete f;
            return 0;
        }
        QByteArray json_data;
        json_data=f->readAll();
        decode_from_json(json_data);
        f->close();
        return 1;
    }
    void save_config_to_file()
    {
        QFile *f=new QFile(config_filename);
        bool ret = f->open(QIODevice::ReadWrite|QIODevice::Truncate);
        if(!ret){
            prt(info,"fail to open %s",config_filename.toStdString().data());
            delete f;
        }
        f->write(encode_to_json());
        f->close();
    }
    void save_config_to_file(QString file_name)
    {
        QFile *f=new QFile(file_name);
        bool ret = f->open(QIODevice::ReadWrite|QIODevice::Truncate);
        if(!ret){
            prt(info,"fail to open %s",file_name.toStdString().data());
            delete f;
        }
        f->write(encode_to_json());
        f->close();
    }


private:
    /*
        parse structure from data
    */
    void decode_from_json(QByteArray &json_src)
    {
        QJsonDocument json_doc=QJsonDocument::fromJson(json_src);
        QJsonObject root_obj=json_doc.object();

        data.camera.clear();
        data.camera_amount=get_int(root_obj,"camera_total_number");
        QJsonArray cams=get_child_array(root_obj,"camera");

        foreach (QJsonValue v, cams) {
            QJsonObject obj=v.toObject();
            camera_data_t t;
            t.ip=get_string(obj,"ip");
            t.port=get_int(obj,"port");
            data.camera.append(t);
        }
    }
    QByteArray encode_to_json()
    {
        QJsonDocument json_doc_new;
        QJsonObject root_obj;

        root_obj["camera_total_number"]=data.camera_amount;
        QJsonArray cams;

        for(int i=0;i<data.camera_amount;i++)
        {
            QJsonObject o;
            o["ip"]=data.camera[i].ip;
            o["port"]=data.camera[i].port;
            cams.append(o);
        }
        root_obj["camera"]=cams;
        json_doc_new.setObject(root_obj);
        return json_doc_new.toJson();

    }

    inline int get_int(QJsonObject obj,const char *member_name)
    {
        return obj[member_name].toInt();
    }
    inline QString get_string(QJsonObject obj,const char *member_name)
    {
        return obj[member_name].toString();
    }
    inline bool get_bool(QJsonObject obj,const char *member_name)
    {
        return obj[member_name].toBool();
    }
    inline QJsonObject get_child_obj(QJsonObject obj,const char *member_name)
    {
        return obj[member_name].toObject();
    }
    inline QJsonArray get_child_array(QJsonObject obj,const char *member_name)
    {
        return obj[member_name].toArray();
    }
    QString config_filename;
    data_t data;
};

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/objdetect/objdetect.hpp>

#include <QObject>
using namespace cv;
using namespace std;
class  VideoSrc:public QObject{
    Q_OBJECT
public:
    bool video_connected_flag;
    VideoSrc(QString path):p_cap(NULL)
    {

        video_connected_flag=true;
        memset(url,0,Tools::PATH_LENGTH);
        strcpy(url,path.toStdString().data());
        p_cap= cvCreateFileCapture(url);  //create video source
        width=cvGetCaptureProperty(p_cap,CV_CAP_PROP_FRAME_WIDTH);
        height=cvGetCaptureProperty(p_cap,CV_CAP_PROP_FRAME_HEIGHT);
        //    prt(info,"video widtbh %d  ",ret);
        if(p_cap==NULL){
            prt(info,"video src start  %s err  ",url);
            video_connected_flag=false;
        }
        else {
            prt(info,"video src  start %s ok  ",url);
        }
        //        if(p_cap==NULL)
        //            emit video_disconnected();
        //        else
        //            emit video_connected();




        //    timer=new QTimer();
        //  tmr->singleShot(1000,this,SLOT(time_up()));

        //    prt(info," shot afer 100 ms")
        // QTimer::singleShot(1000,this,SLOT(time_up()));
        //   connect(timer,SIGNAL(timeout()),this,SLOT(time_up()));
        //   timer->start(wait_duration);
    }
    ~VideoSrc()
    {
        //   cap_lock.lock();
        // timer->stop();
        //  disconnect(timer,SIGNAL(timeout()),this,SLOT(time_up()));
        //   delete timer;
        //     QThread::sleep(1);
        //   prt(info," delete src");
        //    disconnect(tmr,SIGNAL(timeout()),this,SLOT(time_up()));
        cvReleaseCapture(&p_cap);
        p_cap=NULL;
        //    cap_lock.unlock();
        //   delete tmr;
        //   delete p_cap;
    }
    Mat *get_frame()
    {

        //     tmr->singleShot(10,this,SLOT(time_up()));
        int err=0;
        if(p_cap==NULL){
            video_connected_flag=false;
            err=1;
            //   emit video_disconnected();
        }
        IplImage *ret_img;

        //            prt(info,"try to grb");
        //        int tmp= cvGrabFrame(p_cap);
        //             prt(info,"grub source url:%s ret %d (%p)",url,tmp,p_cap);
        //        ret_img= cvRetrieveFrame(p_cap);
        //   prt(info,"try to query");
        //    CV_CAP_PROP_XI_TIMEOUT
        //CV_CAP_PROP_FRAME_WIDTH
        //    int ret=cvSetCaptureProperty(p_cap,CV_CAP_PROP_XI_TIMEOUT,999);
        // double pro=cvGetCaptureProperty(p_cap,CV_CAP_PROP_XI_TIMEOUT);
        //  prt(info," set %d ,opecv time out %d",ret ,pro);
        //      CV_CAP_PROP_XI_TIMEOUT
        //prt(info,"  start query 1 frame ");
        ret_img=cvQueryFrame(p_cap);
        Mat(ret_img).copyTo(mat_rst);
        if(ret_img==NULL){
            err=1;
            //     std::this_thread::sleep_for(chrono::milliseconds(1000));
            //    QThread::sleep(1);
            if(video_connected_flag==true)
            {
                //    prt(info,"%s disconnected",url);
                video_connected_flag=false;
            }
        }else{
            if(video_connected_flag==false)
            {
                //     prt(info,"%s connected",url);
                video_connected_flag=true;
            }
        }
        if(err)
            return NULL;
        else
            return &mat_rst;

    }
    char *get_url(){
        return url;
    }
public slots:

signals:
private:
    CvCapture *p_cap;
    char url[Tools::PATH_LENGTH];
    int width;
    int height;
    Mat mat_rst;
};
using namespace cv;
using namespace std;

class VideoHandler{

public:
    IplImage * frame_ori;
    string video_path;
    VideoHandler(string url)
    {
            video_path=url;
    }
    ~VideoHandler()
    {

    }
    void set_frame( Mat * frame)
    {
        frame_mat=frame;
    }
    void set_null_frame( )
    {
        Mat frame;
        frame.resize(0);
        frame_mat=&frame;
    }
    //  bool work(QByteArray &rst_ba)
    bool work()
    {
        QByteArray rst_ba;
        int min_win_width = 64;	// 48, 64, 96, 128, 160, 192, 224
        int max_win_width = 256;
        bool ret=false;
        CascadeClassifier cascade;
        vector<Rect> objs;
        //string cascade_name = "../Hog_Adaboost_Pedestrian_Detect\\hogcascade_pedestrians.xml";
         string cascade_name = "hogcascade_pedestrians.xml";

  //      const string cascade_name = "E:\\projects\\repo-github\\reswin32\\hogcascade_pedestrians.xml";
//E:\projects\repo-github\reswin32\hogcascade_pedestrians.xml
        if (!cascade.load(cascade_name))
        {
            prt(info,"can't load cascade");
            // cout << "can't load cascade!" << endl;
            //return -1;
        }
#if 1



        // while (1)
        {
            //   frame_ori = cvQueryFrame(p_cap);
            //   frame.create(frame_ori->height,frame_ori->width,CV_8U);
            //   memcpy(frame.data,frame_ori->imageData,frame_ori->imageSize);
            // Mat frame(frame_ori);


            // int test=  waitKey(1);
            //     printf("%d\n",test);
            Mat frame(*frame_mat);
//#ifdef DISPLAY_VIDEO

//            imshow(video_path,frame);
//         waitKey(2);
//#endif
         //   this_thread::sleep_for(chrono::milliseconds(100));
            //  cv::namedWindow("1111")
//            if(!frame.empty())
//                imshow("url",frame);
//                 waitKey(20);
 //             imwrite("test.yuv", frame);

            //  return true;
            //     waitKey(25);
            //    QThread::msleep(1);

            //   return 0;
            if (!frame.empty())
            {
                frame_num++;
                if (frame_num % 100 == 0)
                {
                    cout << "Processed " << frame_num << " frames!" << endl;
                }

                //   if (frame_num % 3 == 0)
                if (1)
                {
                    resize(frame,frame,Size(frame.cols / 2, frame.rows / 2),CV_INTER_LINEAR);
                    //resize(frame,frame,Size(704, 576),CV_INTER_LINEAR);
                    cvtColor(frame, gray_frame, CV_BGR2GRAY);
                    //  gray_frame=frame;
                    //Rect rect;
                    //rect.x = 275;
                    //rect.y = 325;
                    //rect.width = 600;
                    //rect.height = 215;

                    //Mat detect_area = gray_frame(rect);
                    //cascade.detectMultiScale(detect_area,objs,1.1,3);
                    cascade.detectMultiScale(gray_frame, objs, 1.1, 3);


                    vector<Rect>::iterator it = objs.begin();
                    while (it != objs.end() && objs.size() != 0)
                    {
                        pedestrian_num++;
                        pedestrians = frame(*it);

                        Rect rct = *it;
                        if (rct.width >= min_win_width && rct.width < max_win_width)
                        {
                            //   sprintf(file_name, "%d.jpg", pedestrian_num);
                            //  imwrite(file_name, pedestrians);

                            //rct.x += rect.x;
                            //rct.y += rect.y;

                            int test=12345;
                            rectangle(frame, rct, Scalar(0, 255, 0), 2);

                            QString x_str=QString::number(rct.x);
                            QString y_str=QString::number(rct.y);
                            QString test_str=QString::number(test);

                            rst_ba.append(x_str.toStdString().data());
                            rst_ba.append(",");
                            rst_ba.append(y_str.toStdString().data());
                            //prt(info,"%d %d",rct.x,rct.y);
                            prt(info,"%d",rct.x);
                            ret=true;
                            break;//TODO, now we get first one
                        }

                        //  rst_ba.append(";");
                        //  rst_ba.append(rct.x);
                        it++;
                    }
#if 0
                    imshow("result", frame);
                    QThread::msleep(1);


#endif
                    //                    waitKey(1);

                    //   rectangle(frame,rect,Scalar(0,255,0),2);
                    //   imshow("result", frame);
                    //outputVideo << frame;
                    //   waitKey(1);

#ifdef DISPLAY_VIDEO

            imshow(video_path,frame);
         waitKey(2);
#endif
                    objs.clear();
                }
            }
            else
            {
                prt(info,"opencv handle frame error !");
            }
        }
#endif
        if(ret==true){
            //   emit send_rst(rst_ba);
        }
        return ret;
    }


private:
    Mat gray_frame;
    Mat pedestrians;
    Mat *frame_mat;
    QList <Mat> frame_list;
    int pedestrian_num = 0;
    int frame_num = 0;

};
class Camera{
    typedef CameraConfiguration::camera_config_t camera_config;
public:
    int test_flg;
    typedef struct data{
        bool quit_flag;
        bool quit_flag_src;
        bool quit_flag_sink;
        thread *video_src_thread;
        thread *video_sink_thread;
        thread *record_thread;
        camera_config cfg;
        VideoSrc *p_src;
        VideoHandler * p_handler;
        Mat* p_mt;
        deque <Mat> frame_list;
        deque <int> int_list;
        mutex *p_lock;
        int testflg;
        int duration;
    }data_t;
    data_t d;
    Camera( camera_config config)
    {
        d.quit_flag=false;
        d.duration=100;
        d.testflg=12;
        d.p_lock=new mutex();
        d.p_src=new VideoSrc(config.ip);
        string tmp(config.ip.toStdString());
        d.p_handler=new VideoHandler(tmp);
        d.video_src_thread=new thread(get_frame,&d);
        d.record_thread=new thread(record_fun,&d);
        d.video_sink_thread=new thread(process_frame,&d);

    }
    ~Camera()
    {
        d.quit_flag=true;
        d.video_sink_thread->join();
        d.video_src_thread->join();
        d.record_thread->join();
        delete d.video_sink_thread;
        delete d.video_src_thread;
        delete d.record_thread;
        delete d.p_handler;
        delete d.p_src;
    }

    void restart(camera_config new_cfg)
    {
        //        quit_flag=true;
        //        video_src_thread->join();
        //        video_sink_thread->join();
        //        cfg=new_cfg;
        //   video_src_thread=THREAD_DEF(Camera,get_frame);
        //   video_sink_thread=THREAD_DEF(Camera,process_frame);
    }
    int try_restart(camera_config new_cfg)//experinmental
    {
        //        quit_flag=true;
        //        if(video_src_thread->joinable())
        //            video_src_thread->detach();
        //        if(video_sink_thread->joinable())
        //            video_sink_thread->detach();
        //        cfg=new_cfg;
        //        this_thread::sleep_for(chrono::seconds(1));

        //        if(quit_flag==true&&quit_flag_src==true&&quit_flag_sink==true){
        //            quit_flag=false;
        //            quit_flag_sink=false;
        //            quit_flag_src=false;
        //     //       video_src_thread=THREAD_DEF(Camera,get_frame);
        //      //      video_sink_thread=THREAD_DEF(Camera,process_frame);
        //            return 0;
        //        }else{
        //            return 1;
        //        }
    }
private:
    static void record_fun(data_t *data)
    {
        while(!data->quit_flag)
        {
            this_thread::sleep_for(chrono::milliseconds(1000));
            prt(info,"recording");
        }
    }

    static void get_frame(data_t *data)
    {

        while(!data->quit_flag){
            //    prt(info,"get frame start ");
            data->p_lock->lock();

            data->frame_list.push_back(*data->p_src->get_frame());

//            data->p_handler->set_frame(&(*data->frame_list.begin()));
//            data->p_handler->work();

            data->p_lock->unlock();
         //       prt(info,"get frame end ");
            this_thread::sleep_for(chrono::milliseconds(data->duration));
        }
    }
    static void process_frame(data_t *data)
    {

        while(!data->quit_flag){
            data->p_lock->lock();
            if(data->frame_list.size()>0){
          //  prt(info,"size : %d",data->frame_list.size());
                data->p_handler->set_frame(&(*data->frame_list.begin()));
                data->p_handler->work();
                data->frame_list.pop_front();
            }
            else{
             //    prt(info,"size : %d",data->frame_list.size());
            }
            data->p_lock->unlock();
            this_thread::sleep_for(chrono::milliseconds(data->duration));
        }

    }

};
#ifdef DISPLAY_VIDEO
#ifdef IS_UNIX
#include <X11/Xlib.h>
#endif
#endif

class CameraManager{

public:
    CameraManager()
    {
#ifdef DISPLAY_VIDEO
#ifdef IS_UNIX
       XInitThreads();
#endif
#endif

        p_cfg=new CameraConfiguration("config.json-server");
        start_all();
    }
    ~CameraManager()
    {
        stop_all();
        delete p_cfg;

    }
    void start_all()
    {
        foreach (CameraConfiguration::camera_config_t tmp, p_cfg->cfg.camera) {
            Camera *c=new Camera(tmp);
            cameras.push_back(c);
        }
    }
    void stop_all()
    {
        foreach (Camera *tmp, cameras) {
            delete tmp;
            cameras.removeOne(tmp);
        }
    }

    void add_camera(const char *cfg_buf)
    {
        p_cfg->set_config(cfg_buf);
        Camera *c=new Camera(p_cfg->cfg.camera[p_cfg->cfg.camera_amount-1]);
        cameras.push_back(c);
    }
    void del_camera(const char *cfg_buf,const int index)
    {
        p_cfg->set_config(cfg_buf);
        delete cameras[index-1];
        cameras.removeAt(index-1);
    }
    void mod_camera(const char *cfg_buf,const int index)
    {
        p_cfg->set_config(cfg_buf);
        while(true){
            if(0==cameras[index-1]->try_restart(p_cfg->cfg.camera[p_cfg->cfg.camera_amount-1]))
                break;
            else
            {
                prt(info,"restarting camera %d",index);
            }
        }
    }

private:
    CameraConfiguration *p_cfg;
    QList<Camera *> cameras;

};
class NetServer{
public:
    NetServer(const NetServer&)
    {

    }
    NetServer()
    {
        cmd_list_lock=new mutex;
    }
    ~NetServer()
    {

    }
    void get_cmd()
    {
    }
private:
    void set_cmd()
    {
    }
    mutex *cmd_list_lock;
    mutex ccmd_list_lock;
};
int test();
class abc123{
public:
    abc123(const abc123 &){

    }

    mutex ccmd_list_lock;
    abc123()
    {

    }

};

class Test
{
    NetServer server;
    CameraManager *p_cam_manager;
    //   std::thread *fetch_cmd_thread;
    //  abc123 aaa;
    //
public:
    //
    //    Test(const Test&){//this is need by std:move sometimes(ex:keep every  member in class  can be move )

    //    }

    //   explicit
    Test() {

        ServerInfoReporter *r=new    ServerInfoReporter ;
        //        Config cfg("/root/repo-github/pedestrian-v12/server/config.json");
        //        cfg.save_config_to_file(QString("/root/repo-github/pedestrian-v12/server/config.json-test"));
        p_cam_manager=new CameraManager();
        //  c.start();
        //  Camera c;
        //        fetch_cmd_thread=THREAD_DEF(Test,fetch_cmd);

        //        fetch_cmd_thread->detach();
        // fetch_cmd_thread=new std::thread(std::mem_fn(&Test::fetch_cmd),*this);
        //   fetch_cmd_thread=new std::thread(test);
    }
    ~Test()
    {
        //   delete fetch_cmd_thread;
        delete p_cam_manager;
    }
    void process_net_cmd()
    {
        int cmd;
        char *config_buf;
        switch(cmd){
        case Protocol::ADD_CAMERA:
            p_cam_manager->add_camera(config_buf);
            break;
        case Protocol::DEL_CAMERA:
            p_cam_manager->del_camera(config_buf,1);
            break;
        default:break;
        }

    }
    void fun111()
    {



        //    abcd::test_fun();
        //Tools::aaaa=4;
        //        cout<<Tools::BCD<<endl;
        //        cout<<Tools::sss::ABC<<endl;
        // Tools::prt_time();
        //   http://blog.csdn.net/qq_31175231/article/details/77923212
        //        chrono::milliseconds ms{3};


        //        using namespace std::chrono;
        //        typedef duration<int,std::ratio<60*60*24*356>> days_type;
        //        time_point<system_clock,days_type> today = time_point_cast<days_type>(system_clock::now());
        //        std::cout << today.time_since_epoch().count() << " days since epoch" << std::endl;

        //cout<< Tools::FIXED_VALUE::BUF_LENGTH;
        //   TestThread t;
        //        TestThread1 t1;
        //        thread t(std::mem_fn(&TestThread1::fun),t1);
        //        t.join();

        //        PrintNum p;
        //        p.start_thread(&p);
        //        cout<<"ok1"<<endl;
        //         p.stop_thread();

        //         PrintNum1 p;
        //         p.start_thread();
        //         cout<<"ok1"<<endl;
        //         p.stop_thread();

        //    Thread1 t1;

        //   t1.start_thread();
        //   t1.stop_thread();
        //  this_thread::sleep_for(std::chrono::seconds(3)); //休眠三秒
        //   cout<<"done"<<endl;
        //   t1.stop_thread();


        //    while(1)
        //        ;
        //     ThreadTool1 t1;
        //       t1.start_thread();
        //    cout<<"ok2"<<endl;
        // t1.stop_thread();

        //   Tools::init("aa");
        //  this_thread::sleep_for(std::chrono::seconds(3)); //休眠三秒
        //   prt(info,"the name is %d %s",11,"FDASFASDF" );
    }
private:
    void fetch_cmd()
    {
        while(1)
        {
            prt(info,"fecthing cmd");
            this_thread::sleep_for(chrono::seconds(1));
        }
    }


};





#endif

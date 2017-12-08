//#include "test.h"
#include <QCoreApplication>
#include "tools.h"
#include "camera.h"
void test_fun()
{
  prt(info,"test_fun running");
}
void test_fun1(void * data)
{
    int *p= (int *)data;
  prt(info,"test_fun running %d",*p);
}

int main(int argc, char *argv[])
{
     QCoreApplication a(argc, argv);
    prt(info,"start main");



    ServerInfoReporter *reportor=new ServerInfoReporter();
    CameraManager *mgr=new CameraManager();
    reportor->start();
    this_thread::sleep_for(chrono::seconds(3));
    delete mgr;


 //   Timer t(test_fun,100);
//    int tmp=123;
//    Timer t(test_fun1,(void *)&tmp,100);
//   t.start();
//    this_thread::sleep_for(chrono::seconds(1));
//    t.stop();
//       prt(info,"pause  main for a while");
//    this_thread::sleep_for(chrono::seconds(1));
//    t.start();
//    prt(info,"end main");
//    while(1)
//        ;
    return a.exec();
}

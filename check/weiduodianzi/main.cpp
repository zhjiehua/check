/*
	DATE			VERSION		DESCRIPTION							AUTHER
	2016-08-11		V0.90		许可证控件不能保存首位是0的数字		zhjiehua
	2016-08-12		V0.91		修改GLP页面（生产日期、安装日期等）	zhjiehua
	2016-08-17		V0.92		解决模拟口的bug						zhjiehua
	2016-09-01		V0.93		添加灯源密码，调整灯源记录表格式
								修正Clarity协议的上传频率bug		zhjiehua
	2016-10-17		V0.94		去掉电池检测						zhjiehua
	2016-11-17		V0.95		Clarity协议流程修改：开机后要PC修改完上传频率才开始上传Au值
																	zhjiehua
	2016-11-17		V0.96		Clarity协议的时间跟上传频率无关		zhjiehua
	2017-03-17		V0.97		将保存数据和更新数据按钮从信息页面移到管理员页面
																	zhjiehua
	2017-08-15		V0.98		将超级管理员的密码由111111改成173895    
																	zhjiehua
	2017-11-07		V0.99		添加上位机模拟检测器的宏 INIT_SUCCESS_SIMULATE；
								使用debug页面。						zhjiehua
	2017-12-12		V1.00		修复色谱柱效低的bug(数据滤波太严重)	zhjiehua
	2018-01-06		V1.01		修复超级页面保存数据文件不存在的bug	zhjiehua
	2018-02-08		V1.02		修复死机bug,数据库中range字段超出combo的index导致
																	zhjiehua
	2018-07-08		V1.03		将时间常数参数改成修改数据缓冲区大小功能
																	zhjiehua
	2018-09-05		V1.04		当参比板上传的数据是0或无上传数据时，核心板依然上传AU值给PC
																	zhjiehua
	2019-04-24		V1.05		解决双波长时，双波长和单波长一样反应的bug，原因在发个PC的时候，都是发波长1的au值给PC，在LogicThread.cpp的uploadAuToPc()函数里。
																	zhjiehua
	2019-06-20		V1.06		模拟口同时输出模拟信号和串口数字信号。
																	zhjiehua


    2024-04-21		V1.09		添加通道1样本-参比值上传到工作站
                                                                    zhjiehua

根据《UV3000检测器计算机反控通讯命令格式》文件，上传给工作站的的吸光度命令为
    通道1：SM xxxx
    通道2：Sm xxxx
现在添加上传样本值和参比值的命令
    通道1样本值：SN xxxx
    通道1参比值：Sn xxxx
    通道2样本值：SO xxxx
    通道2参比值：So xxxx

注意，目前通道2的样本值和参比值不支持，
    因为根据波特率9600bps算，吸光度上传周期为50ms上传一次的话，
    如果是双通道，一次需要上传SM Sm SN Sn SO So 6条指令，其中每条指令长度10字节，1/9600*10*10*6 = 62.5ms > 50ms，实际会更大。
    如果是单通道，上传SM SN SN Sn 4条指令， 1/9600*10*10*4 = 41.7ms < 50ms

    所以如果要解决这个问题，需要把波特率提高
*/

#include "baseMainPage.h"
//#if QT_VERSION >= 0x050000
//#include <QtWidgets/QApplication>
//#else
//#include <QtGui/QApplication>
//#endif
#include <QApplication>

#include <QFont>
#include <QTextCodec>
#include "Common.h"
#include <QDebug>
#include <QString>
#include <QFontDatabase>
#include "QDesktopWidget"

int g_nActScreenX;
int g_nActScreenY;

int main(int argc, char *argv[])
{
#if QT_VERSION >= 0x050000
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));
#endif
	QApplication a(argc, argv);

	QDesktopWidget* desktopWidget = QApplication::desktop();
	//获取可用桌面大小
	//QRect deskRect = desktopWidget->availableGeometry();
	//获取设备屏幕大小
	QRect screenRect = desktopWidget->screenGeometry();
	g_nActScreenX = screenRect.width();
	g_nActScreenY = screenRect.height();

	qDebug() << "m_nActScreenX = " << g_nActScreenX;
	qDebug() << "m_nActScreenY = " << g_nActScreenY;

	//QTextCodec::setCodecForTr(QTextCodec::codecForName("gb18030"));
	QFont font;
	if(g_nActScreenX < 420)
		font.setPointSize(8);
	else
	{
#ifdef linux
		font.setPointSize(12);
#else
		font.setPointSize(8);
#endif
	}

#if QT_VERSION < 0x050000
	QTextCodec::setCodecForTr(QTextCodec::codecForName("gb18030"));
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("gb18030"));
#endif

	//QFont font;
	//font.setPointSize(8);
	//font.setFamily(("黑体"));
	QFontDatabase database;
	//qDebug()<<database.families();
	a.setFont(font);
	BaseMainPage w("UV3000U");
	w.resize(SCREEN_WIDTH, SCREEN_HEIGH);

#ifdef linux
	QApplication::setOverrideCursor(Qt::BlankCursor);//隐藏鼠标
	w.setWindowFlags(Qt::FramelessWindowHint);
	w.showFullScreen ();
#else
	//w.setWindowFlags(Qt::FramelessWindowHint);
	w.show();
#endif
	return a.exec();
}

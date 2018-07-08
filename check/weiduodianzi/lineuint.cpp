#include "lineuint.h"
#include <QDebug>
#include <math.h>

LineUint::LineUint(QObject *parent)
	: QObject(parent)
{

}

LineUint::LineUint(const LineUint &line )
{
	x1 = line.x1;
	y1 = line.y1;
	x2 = line.x2;
	y2 = line.y2;
	k = line.k;
	str = line.str;
}

LineUint::~LineUint()
{

}

void LineUint::setRange( double x1, double y1, double x2, double y2 ,QString disp)
{
	this->x1 = x1;
	this->x2 = x2;
	this->y1 = y1;
	this->y2 = y2;
	//qDebug()<<x1<<" "<<x2<<"---"<<y1<<" "<<y2;
	//����kֵ;
	if(x1 > x2)
	{
		//qDebug()<<"LineUint::setRange x1 > x2!Please Check!";
		k = 0;
		return;
	}
	else
	{
		k = (double)(y2-y1)/(double)(x2-x1);
		//qDebug()<<k;
	}
	str = disp;
}

bool LineUint::inStep(double x ) const
{

	if(x == x1)
		return true;
	else 
		return false;
}

void LineUint::printOut() const
{
	qDebug()<<"----------------------";
	qDebug()<<x1;
	qDebug()<<x2;
	qDebug()<<y1;
	qDebug()<<y2;
}

double LineUint::getStepValueByX( double x)const
{
	return y1;
}

QString LineUint::getFlowStr() const
{
	return str;
}

bool LineUint::inRange( double x ) const
{
	if(x>=x1 && x<x2)
		return true;
	else
		return false;
}

double LineUint::getValueByXAndK( double x, LineUint::DIR dir) const
{
	
	double ret = 0; 
	if (dir == LEFT)
	{
		ret = x*y1/x1;
	}
	else if(dir == MIDDLE)
	{
		ret = (x-x1)*k+y1;
	}
	else
	{
		ret = x*y2/x2;
	}
	
	return ret;
}

bool LineUint::bOutOfStep(double x, DIR dir) const
{
	if( dir == LEFT )
		return (x < x1);
	else
		return (x > x2);
}



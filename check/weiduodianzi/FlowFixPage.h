#ifndef SETUPMENUPAGE_H
#define SETUPMENUPAGE_H

#include "BasePage.h"
#include "ui_FlowFixPage.h"
#include "baseMainPage.h"

class FlowFixPage : public CBasePage
{
	Q_OBJECT
public:
	FlowFixPage(QWidget *parent = 0, quint8 index = 0, quint8 previndex = 0, quint32 add = 0);
	~FlowFixPage(void);
	static CBasePage* getInstance(QWidget *parent, quint8 index, quint8 previndex, quint32 add);

protected:
	void initFocusList();

private:
	Ui::FlowFixPageClass ui;
	bool tFlag;
	int whichMode;
	void initDisplay();
	void saveWaveMode();
	void restoreWaveMode();

private slots:
	void getOutTableFocus(int dir);
	void on_saveBtn_clicked();
	void on_backBtn_clicked();
	void updateFlowList();
	void waveLenChanged(QString);

};

#endif // SETUPMENUPAGE_H
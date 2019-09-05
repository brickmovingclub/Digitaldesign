#pragma once
#include <qwidget.h>
#include "ui_Territory.h"

class CTerritoryWidget :
	public QWidget
{
	Q_OBJECT
public:
	CTerritoryWidget(QWidget *parent = Q_NULLPTR);
	~CTerritoryWidget();
private:
	Ui::Territory ui;
signals:
	void TerritoryChanged(long &num, long &step);
private slots:
	void OnClickPushButtonAffirm();
	void OnClickPushButtonCancel();
};


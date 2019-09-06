#include "stdafx.h"
#include "CTerritoryWidget.h"


CTerritoryWidget::CTerritoryWidget(QWidget *parent):QWidget(parent)
{
	ui.setupUi(this);

}


CTerritoryWidget::~CTerritoryWidget()
{
}

void CTerritoryWidget::OnClickPushButtonAffirm()
{
	if (ui.lineEdit_SearchPoint->text().isEmpty() || ui.lineEdit_N->text().isEmpty())
		return;
	long num = ui.lineEdit_SearchPoint->text().toUInt();
	long j = ui.lineEdit_N->text().toInt();

	emit TerritoryChanged(num, j);
	this->close();

}
void CTerritoryWidget::OnClickPushButtonCancel()
{
	this->close();

}
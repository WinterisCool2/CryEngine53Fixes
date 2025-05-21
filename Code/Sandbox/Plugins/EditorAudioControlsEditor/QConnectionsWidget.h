// Copyright 2001-2016 Crytek GmbH / Crytek Group. All rights reserved.

#pragma once

#include "ATLControlsModel.h"

#include <QWidget>
#include <QListWidget>
#include <QColor>

class QVBoxLayout;
class QFrame;
class QPropertyTree;
class QAdvancedTreeView;

namespace ACE
{
class CATLControl;
class QConnectionModel;

class QConnectionsWidget : public QWidget, public IATLControlModelListener
{
public:
	QConnectionsWidget(QWidget* pParent = nullptr);
	~QConnectionsWidget();
	void Init();
	void SetControl(CATLControl* pControl);
	void Reload();

private:
	bool eventFilter(QObject* pObject, QEvent* pEvent) override;
	void RemoveSelectedConnection();
	void RefreshConnectionProperties();

	//////////////////////////////////////////////////////////
	// IAudioSystemEditor implementation
	/////////////////////////////////////////////////////////
	virtual void OnConnectionRemoved(CATLControl* pControl, IAudioSystemItem* pMiddlewareControl) override;
	//////////////////////////////////////////////////////////

	CATLControl*       m_pControl;
	QFrame*            m_pConnectionPropertiesFrame;
	QPropertyTree*     m_pConnectionProperties;
	QConnectionModel*  m_pConnectionModel;
	QAdvancedTreeView* m_pConnectionsView;
};
}

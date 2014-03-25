/**
********************************************************************************
\file   NodeStatusDock.cpp

\brief  Implements the node status dock and updates the status of the available
		CN node id's.

\author Ramakrishnan Periyakaruppan

\copyright (c) 2014, Kalycito Infotech Private Limited
					 All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
	* Redistributions of source code must retain the above copyright
	  notice, this list of conditions and the following disclaimer.
	* Redistributions in binary form must reproduce the above copyright
	  notice, this list of conditions and the following disclaimer in the
	  documentation and/or other materials provided with the distribution.
	* Neither the name of the copyright holders nor the
	  names of its contributors may be used to endorse or promote products
	  derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/

/*******************************************************************************
* INCLUDES
*******************************************************************************/
#include "NodeStatusDock.h"
#include "api/OplkQtApi.h"

#include <oplk/debugstr.h>

const UINT kMaxCnNodes = 239;

NodeStatusDock::NodeStatusDock(QWidget *parent) :
	QDockWidget(parent)
{
	this->ui.setupUi(this);

	NodeUi *nodeUi = NULL;
	for (UINT i = 0; i < kMaxCnNodes; ++i)
	{
		nodeUi = new NodeUi(i + 1);
		nodeUi->hide();
		this->nodelists.push_back(nodeUi);
		this->ui.verticalLayout->addWidget(nodeUi);
	}

	int index = this->metaObject()->indexOfMethod(
					QMetaObject::normalizedSignature(
					"HandleNodeStateChanged(const int, tNmtState)").constData());
	Q_ASSERT(index != -1);
	// If asserted check for the Function name

	// TODO Handle return values
	bool ret = OplkQtApi::RegisterNodeStateChangedEventHandler(*(this),
							this->metaObject()->method(index));


	// TODO Handle return values
	index = this->metaObject()->indexOfMethod(
					QMetaObject::normalizedSignature(
					"HandleNodeFound(const int)").constData());
	Q_ASSERT(index != -1);
	// If asserted check for the Function name

	// TODO Handle return values
	ret = OplkQtApi::RegisterNodeFoundEventHandler(*(this),
							this->metaObject()->method(index));

	index = this->metaObject()->indexOfMethod(
					QMetaObject::normalizedSignature(
						"HandleMnStateChanged(tNmtState)").constData());
	Q_ASSERT(index != -1);
	// If asserted check for the Function name

// TODO Handle return values
	ret = OplkQtApi::RegisterLocalNodeStateChangedEventHandler(*(this),
							this->metaObject()->method(index));

}

void NodeStatusDock::HandleMnStateChanged(tNmtState nmtState)
{
	// Change all CN states for Stack shutdown / MN dead.
	if ((nmtState == kNmtGsOff) || (nmtState < kNmtMsOperational))
	{
		for (QList<NodeUi*>::iterator it = this->nodelists.begin();
			 it != this->nodelists.end(); ++it)
		{
			(*it)->hide();
			// this->HandleNodeStateChanged((*it)->GetNodeId(), kNmtCsNotActive);
		}
	}
}

void NodeStatusDock::HandleNodeStateChanged(const int nodeId, tNmtState nmtState)
{
	// qDebug("HandleN %d %s", nodeId, debugstr_getNmtStateStr(nmtState));
	if ((nodeId > 0) && (nodeId <= kMaxCnNodes))
	{
		if ((this->nodelists.at(nodeId - 1)))
		{
			this->nodelists.at(nodeId - 1)->HandleNodeStateChanged(nmtState);
			// Hide CN for Loss of PRes
//			if (nmtState == kNmtCsNotActive)
//			{
//				this->nodelists.at(nodeId - 1)->hide();
//			}
		}
	}
}

void NodeStatusDock::HandleNodeFound(const int nodeId)
{
	// qDebug(" F %d ", nodeId);
	if ((nodeId > 0) && (nodeId <= kMaxCnNodes))
	{
		if (this->nodelists.at(nodeId - 1))
		{
			this->nodelists.at(nodeId - 1)->show();
		}
	}
}

QStringList NodeStatusDock::GetAvailableCnList()
{
	QStringList cnList;
//TODO
//	for (UINT i = 1; i <= kMaxCnNodes; ++i)
//	{
//		if ((this->nodelist[i]))
//		{
//			cnList << QString("0x%1").arg(i, 2, 16);
//		}
//	}
	return cnList;
}

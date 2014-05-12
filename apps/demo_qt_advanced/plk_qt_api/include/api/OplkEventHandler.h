/**
********************************************************************************
\file   OplkEventHandler.h

\brief  Design of a event handler that uses QThread to
		communicate openPOWERLINK asynchronous callback events via QT signals

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

#ifndef _OPLK_EVENTHANDLER_H_
#define _OPLK_EVENTHANDLER_H_

/*******************************************************************************
* INCLUDES
*******************************************************************************/
#include <QThread>
#include <QWaitCondition>
#include <QMutex>

#include <oplk/oplk.h>
#include <oplk/nmt.h>
#include <oplkcfg.h>

#include "api/ReceiverContext.h"
#include "user/SdoTransferResult.h"

/**
 * \brief Thread used to receive openPOWERLINK-Stack asynchronous callback events.
 *
 * Class provides the interface to the OplkQtApi to handle openPOWERLINK stack events via Qt Signals
 *
 * \note This class is intended to _only_ be used by OplkQtApi
 * \note The signals can be received by registering through the OplkQtApi::Register***() functions
 */
class OplkEventHandler : public QThread
{
	Q_OBJECT

public:

	/**
	 * \brief   Waits until the NMT state NMT_GS_OFF is reached
	 */
	void AwaitNmtGsOff();

	/**
	 * \return Returns the address of event callback function
	 */
	tOplkApiCbEvent GetEventCbFunc(void);

	virtual void run();

private:

	friend class OplkQtApi;

	OplkEventHandler();
	OplkEventHandler(const OplkEventHandler& eventHandler);
	OplkEventHandler& operator=(const OplkEventHandler& eventHandler);

	QMutex          mutex;
	QWaitCondition  nmtGsOffCondition;

	/**
	 * \return Returns the instance of the class
	 */
	static OplkEventHandler& GetInstance();

	/**
	 * \brief   The main event callback function
	 *          Accessed as a function pointer from the stack.
	 * \param[in] eventType  Type of the event
	 * \param[in] eventArg   Pointer to union which describes the event in detail
	 * \param[in] userArg    User specific argument
	 * \return Returns a tOplkError error code.
	 */
	static tOplkError AppCbEvent(tOplkApiEventType eventType,
								 tOplkApiEventArg* eventArg,
								 void* userArg);

	/**
	 * \brief   Process the NMT state change events of the local node.
	 *
	 * \param[in] nmtStateChange  Details of the NMT state changes
	 * \param[in] userArg         User specific argument
	 * \return Returns a tOplkError error code.
	 */
	tOplkError ProcessNmtStateChangeEvent(tEventNmtStateChange* nmtStateChange,
										  void* userArg);

	/**
	 * \brief   Process critical error events of the stack.
	 *
	 * \param[in] internalError  Details of the critical error events.
	 * \param[in] userArg        User specific argument.
	 * \return Returns a tOplkError error code.
	 */
	tOplkError ProcessCriticalErrorEvent(tEventError* internalError,
										 void* userArg);

	/**
	 * \brief   Process warning events of the stack.
	 *
	 * \param[in] internalError  Details of the warning events.
	 * \param[in] userArg        User specific argument.
	 * \return Returns a tOplkError error code.
	 */
	tOplkError ProcessWarningEvent(tEventError* internalError, void* userArg);

	/**
	 * \brief   Process history events generated by the stack.
	 *
	 * \param[in] historyEntry  Details of the history events
	 * \param[in] userArg       User specific argument
	 * \return Returns a tOplkError error code.
	 */
	tOplkError ProcessHistoryEvent(tErrHistoryEntry* historyEntry,
								   void* userArg);

	/**
	 * \brief   Process events generated by the stack with respect to the remote nodes.
	 *
	 * \param[in] nodeEvent  Details of the node events.
	 * \param[in] userArg    User specific argument.
	 * \return Returns a tOplkError error code.
	 */
	tOplkError ProcessNodeEvent(tOplkApiEventNode* nodeEvent, void* userArg);

	/**
	 * \brief   Process the events generated during the SDO transfer
	 *
	 * \note The sdoEvent->pUserArg will contain the data sent in the userArg in the SDO calling function.
	 * \param[in] sdoEvent  Details of the SDO events occurred.
	 * \param[in] userArg   User specific argument
	 * \return Returns a tOplkError error code.
	 */
	tOplkError ProcessSdoEvent(tSdoComFinished* sdoEvent, void* userArg);

	/**
	 * \brief   Process CFM progress events
	 *
	 * \param[in] cfmProgress  Details of the CFM progress events.
	 * \param[in] userArg      User specific argument.
	 * \return Returns a tOplkError error code.
	 */
	tOplkError ProcessCfmProgressEvent(tCfmEventCnProgress* cfmProgress,
									   void* userArg);

	/**
	 * \brief   Process CFM result events
	 *
	 * \param[in] cfmResult  Result of the CFM event occurred.
	 * \param[in] userArg    User specific argument.
	 * \return Returns a tOplkError error code.
	 */
	tOplkError ProcessCfmResultEvent(tOplkApiEventCfmResult* cfmResult,
									 void* userArg);

	/**
	 * \brief[in] Process the PDO change events.
	 *
	 * \param[in] pdoChange Details of the PDO change event.
	 * \param[in] userArg      User specific argument.
	 * \return Returns a tOplkError error code.
	 */
	tOplkError ProcessPdoChangeEvent(tOplkApiEventPdoChange* pdoChange,
									void* userArg);

	/**
	 * \brief   Triggers a signal OplkEventHandler::SignalLocalNodeStateChanged
	 * when there is a change of the state of local node.
	 *
	 * \param[in] nmtState  The new state to which the local node has changed to.
	 */
	void TriggerLocalNodeStateChanged(tNmtState nmtState);

	/**
	 * \brief   Triggers a signal OplkEventHandler::SignalNodeFound when
	 * the remote node with the nodeId starts communicating with the local node.
	 *
	 * \param[in] nodeId  The node id of the respective node
	 */
	void TriggerNodeFound(const int nodeId);

	/**
	 * \brief   Triggers a signal OplkEventHandler::SignalNodeStateChanged when
	 *  there is a change in the state of the remote node.
	 *
	 * \param[in] nodeId    The node id of the respective node
	 * \param[in] nmtState  The changed state of the respective node
	 */
	void TriggerNodeStateChanged(const int nodeId, tNmtState nmtState);

	/**
	 * \brief   Triggers a signal OplkEventHandler::SignalPrintLog with the
	 *  log message for all the events occured.
	 *
	 * \param[in] logStr  Formatted log message.
	 */
	void TriggerPrintLog(const QString logStr);

	/**
	 * \brief   Triggers a signal OplkEventHandler::SignalSdoTransferFinished
	 *  when SDO transfer to the remote node has finished.
	 *
	 * \param[in] result               The result of the SDO transfer.
	 * \param[in,out] receiverContext  The details of the receiver object.
	 */
	void TriggerSdoTransferFinished(const tSdoComFinished& result,
									const ReceiverContext* receiverContext);

	/**
	 * \brief Triggers a signal OplkEventHandler::SignalCriticalError to the
	 * application
	 *
	 * \param[in] errorMessage Detailed message about the error occured.
	 */
	void TriggerCriticalError(const QString errorMessage);

signals:
	/**
	 * \brief   This signal is emitted when the NMT state of the local node changes.
	 *
	 * \param[in] nmtState  The new NMT state to which it has changed.
	 */
	void SignalLocalNodeStateChanged(tNmtState nmtState);

	/**
	 * \brief   This signal is emitted when the remote node is found in the network.
	 *
	 * \param[in] nodeId  Node id of the node.
	 */
	void SignalNodeFound(const int nodeId);

	/**
	 * \brief   This signal is emitted when the NMT state of the remote node has changed.
	 *
	 * \param[in] nodeId    Node id of the node.
	 * \param[in] nmtState  The new NMT state to which it has changed.
	 */
	void SignalNodeStateChanged(const int nodeId, tNmtState nmtState);

	/**
	 * \brief   This signal is emmited whenever there is an event occured in the stack.
	 *
	 * \param[in] logStr  Detailed message about the event.
	 */
	void SignalPrintLog(const QString &logStr);

	/**
	 * \brief   This signal is emitted when the SDO transfer has happened/aborted.
	 *
	 * \param[in] result  Result of the SDO transfer query.
	 */
	void SignalSdoTransferFinished(const SdoTransferResult result);

	/**
	 * \brief This signal is emmited when there is a critical error in the stack occurred.
	 *
	 * \param[in] errorMessage Detailed information about the error.
	 */
	void SignalCriticalError(const QString& errorMessage);

};

#endif // _OPLK_EVENTHANDLER_H_

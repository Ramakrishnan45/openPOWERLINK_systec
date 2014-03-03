/**
********************************************************************************
\file   ConsoleReader.h

\brief  Console input reader thread.
*******************************************************************************/

#ifndef _CONSOLEREADER_H_
#define _CONSOLEREADER_H_

//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------
#include <QThread>

#include "console/console.h"
#include "api/OplkQtApi.h"
#include "user/processimage/ProcessImageParser.h"

#include "../include/Receiver.h"

/**
 * \brief Class to read the inputs from the console window.
 */
class ConsoleReader : public QThread
{
public:
	ConsoleReader();
	void run();
	ULONG GetSdoReadData();
	ULONG GetSdoWriteData();

private:
	ULONG *sdoReadData;
	ULONG *sdoWriteData;
	SdoTransferJob *sdoReadTransferJob;
	SdoTransferJob *sdoWriteTransferJob;
	Receiver receiver;

	std::string inputChannelName;
	std::string outputChannelName;
	UINT nodeId;
	std::string devName;

	std::string xapFileName;
};

#endif // _CONSOLEREADER_H_
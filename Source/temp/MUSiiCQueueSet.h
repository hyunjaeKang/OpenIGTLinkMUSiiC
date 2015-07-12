/***************************************************************************
Copyright Dec/2010
MUSiiC Laboratory
Hyun-Jae Kang, Emad M Boctor
Johns Hopkins Medical Institutions
Department of Radiology, Division of Medical Imaging Physics

For commercial use/licensing, please contact Emad Boctor, Ph.D. at eboctor@jhmi.edu.

***************************************************************************/
#ifndef __MUSICC_QUEUESET_
#define __MUSICC_QUEUESET_

/// MUSiiCQueue :: Concurrent Queue for multi-threaded programming
#include "MUSiiCQueue."

/// OpenIGTLinkMUSiiC :: Messages
#include "igtlUSMessage.h"
#include "igtlEIMessage.h"
#include "igtlArgMessage.h"
#include "igtlGenMessage.h"
#include "igtlFileMessage.h"

/// OpenIGTLink (Ver 1) :: Messages
#include <igtlTransformMessage.h>
#include <igtlImageMessage.h>
#include <igtlPointMessage.h>
#include <igtlPositionMessage.h>
#include <igtlStatusMessage.h>

/// OpenIGTLink (Ver 2) :: Messages
#include <igtlBindMessage.h>
#include <igtlColorTableMessage.h>
#include <igtlImageMetaMessage.h>
#include <igtlNDArrayMessage.h>
#include <igtlTrajectoryMessage.h>
#include <igtlTrackingDataMessage.h>
#include <igtlLabelMetaMessage.h>
#include <igtlQuaternionTrackingDataMessage.h>
#include <igtlSensorMessage.h>
#include <igtlStringMessage.h>

namespace igtl
{

class IGTLCommon_EXPORT MUSiiCQueueSet : public LightObject
{
	public:
			typedef MUSiiCQueueSet					Self;
			typedef LightObject						Superclass;
			typedef SmartPointer<Self>				Pointer;
			typedef SmartPointer<const Self>		ConstPointer;
			
			/** Method for creation through the object factory. */
			igtlTypeMacro(igtl::MUSiiCQueueSet, igtl::LightObject)
			
			/** Run-time type information (and related methods). */
			igtlNewMacro(igtl::MUSiiCQueueSet);
	public:

};
} //end of namespace
#endif
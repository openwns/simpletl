/*******************************************************************************
 * This file is part of openWNS (open Wireless Network Simulator)
 * _____________________________________________________________________________
 *
 * Copyright (C) 2004-2007
 * Chair of Communication Networks (ComNets)
 * Kopernikusstr. 16, D-52074 Aachen, Germany
 * phone: ++49-241-80-27910,
 * fax: ++49-241-80-22242
 * email: info@openwns.org
 * www: http://www.openwns.org
 * _____________________________________________________________________________
 *
 * openWNS is free software; you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License version 2 as published by the
 * Free Software Foundation;
 *
 * openWNS is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ******************************************************************************/

#include <SIMPLETL/service/Connection.hpp>
#include <SIMPLETL/SimpleTL.hpp>
#include <SIMPLETL/events/DataInd.hpp>
#include <SIMPLETL/Medium.hpp>
#include <SIMPLETL/PCI.hpp>
#include <SIMPLETL/PDU.hpp>
#include <WNS/module/Module.hpp>
#include <WNS/logger/Master.hpp>
#include <WNS/osi/PDU.hpp>
#include <WNS/service/tl/DataHandler.hpp>
#include <WNS/Assure.hpp>


using namespace simpletl;

Connection::Connection(wns::service::tl::ConnectionHandler* ch, wns::service::tl::FlowID _flowID,
					   Bit _headerSize)
	:
	datahandler(NULL),
	connectionhandler(ch),
	peer(NULL),
	flowID(_flowID),
	headerSize(_headerSize),
	eventscheduler(wns::simulator::getEventScheduler()),
	logger("SimpleTL", "Connection", wns::simulator::getMasterLogger())
{
	wns::pyconfig::View pyco = wns::module::Module<SimpleTL>::getPyConfigView().getView("channel");
	channelcapacity = pyco.get<double>("capacity");
}

Connection::~Connection()
{
	delete datahandler;
	datahandler = NULL;
	peer = NULL;
	connectionhandler = NULL;
}

void Connection::registerDataHandler(wns::service::tl::DataHandler* _dh)
{
	datahandler = _dh;
}

void Connection::sendData(const wns::osi::PDUPtr& _pdu)
{
	Bit payloadSize = _pdu->getLengthInBits();
	assure(payloadSize, "Trying to send an empty PDU!");

	simpletl::PCI* pci = new simpletl::PCI(PCI::unknown, headerSize, payloadSize, flowID);
	simpletl::PDUPtr pdu(new simpletl::PDU(pci, _pdu));

	simTimeType delay = (double)(headerSize+payloadSize) / (1000*channelcapacity);

	Medium::send(DataInd(getPeer(), pdu), delay);
}

void Connection::receiveData(const simpletl::PDUPtr& _pdu)
{
	assureType(_pdu.getPtr()->getPCI(), simpletl::PCI*);

	if (static_cast<simpletl::PCI*>(_pdu.getPtr()->getPCI())->flowID == swappedFlowID())
	{
		// If the data handler is not available, this indicates that the connection has not been
		// established yet.
		if (datahandler)
		{
			MESSAGE_SINGLE(NORMAL, logger, "Received packet with flow ID: "
						   << static_cast<simpletl::PCI*>(_pdu.getPtr()->getPCI())->flowID);
			datahandler->onData(wns::osi::PDUPtr(_pdu.getPtr()->getUserData()));
		}
		else
		{
			MESSAGE_SINGLE(NORMAL, logger, "Opening connection for flow ID: "
						   << static_cast<simpletl::PCI*>(_pdu.getPtr()->getPCI())->flowID);
			connectionhandler->onConnectionEstablished(
				static_cast<simpletl::PCI*>(_pdu.getPtr()->getPCI())->flowID.srcAddress, this);
			assure(datahandler, "No data handler available although connection established!");
						   datahandler->onData(wns::osi::PDUPtr(_pdu.getPtr()->getUserData()));
		}
	}
	// Packet belongs to an old session. It will be discarded.
	else
	{
		MESSAGE_BEGIN(NORMAL, logger, m, "Discarding packet. It belongs to an old session with flow ID: ");
		m << static_cast<simpletl::PCI*>(_pdu.getPtr()->getPCI())->flowID;
        m << " This connection has flow ID: " << swappedFlowID();
		MESSAGE_END();
	}
}

wns::service::tl::ConnectionHandler* Connection::getConnectionHandler()
{
	assure(connectionhandler, "Connection handler not available!");
	return connectionhandler;
}

void Connection::setPeer(Connection* connection)
{
	peer = connection;
}

Connection* Connection::getPeer()
{
	assure(peer, "Peer entity not available!");
	return peer;
}

wns::service::tl::FlowID Connection::getFlowID()
{
	return flowID;
}

wns::service::tl::FlowID Connection::swappedFlowID()
{
	wns::service::tl::FlowID _flowID(flowID.dstAddress, flowID.dstPort, flowID.srcAddress, flowID.srcPort);
	return _flowID;
}

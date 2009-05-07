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

#include <SIMPLETL/service/TCP.hpp>
#include <SIMPLETL/SimpleTL.hpp>
#include <SIMPLETL/service/Connection.hpp>
#include <SIMPLETL/Routing.hpp>
#include <SIMPLETL/events/ConInd.hpp>
#include <SIMPLETL/events/DisconInd.hpp>
#include <SIMPLETL/Medium.hpp>
#include <WNS/service/tl/FlowID.hpp>
#include <WNS/service/qos/QoSClasses.hpp>
#include <WNS/module/Module.hpp>
#include <WNS/logger/Master.hpp>

using namespace simpletl;

TCP::TCP(const wns::pyconfig::View& _pyco)
	: pyco(_pyco),
	  eventscheduler(wns::simulator::getEventScheduler()),
	  registered(false),
	  logger("SimpleTL", "TCP",
			 wns::simulator::getMasterLogger())
{
	portPool = new wns::service::tl::PortPool(pyco.get<simTimeType>("portUnbindDelay"));

	wns::pyconfig::View pyco =
		wns::module::Module<SimpleTL>::getPyConfigView().getView("channel");
	channelcapacity = pyco.get<double>("capacity");
}

TCP::~TCP()
{
	delete portPool;
}

void TCP::openConnection(wns::service::tl::Port _port,
						 wns::service::nl::FQDN _source,
						 wns::service::nl::FQDN _peerInstance,
						 wns::service::qos::QoSClass /*_qosClass*/,
						 wns::service::tl::ConnectionHandler* _ch)
{
	wns::service::tl::ConnectionHandler* peerconnectionhandler =
		Routing::getService(_peerInstance, _port);

	wns::service::tl::Port sourcePort = portPool->suggestPort();
	portPool->bind(sourcePort);

	wns::service::tl::FlowID flowID ( wns::service::nl::Address(_source), sourcePort, wns::service::nl::Address(_peerInstance),_port );
	// TCP-Header: 20 Byte, IP-Header: 20 Byte -> 320 Bit
	Bit headerLength = 320;

	Connection* local = new Connection(_ch, flowID, headerLength);
	Connection* peer = new Connection(peerconnectionhandler, local->swappedFlowID(), headerLength);

	MESSAGE_SINGLE(NORMAL, logger, "Opening connection for flow ID: " << flowID);

	local->setPeer(peer);
	peer->setPeer(local);

	simTimeType delay = (double)headerLength / (1000*channelcapacity);

	Medium::send(ConInd(local), delay);
}

void TCP::closeConnection(wns::service::tl::Connection* _connection)
{
	assureType(_connection, Connection*);
	Connection* local = static_cast<Connection*>(_connection);

	// TCP-Header: 20 Byte, IP-Header: 20 Byte -> 320 Bit
	Bit headerLength = 320;
	simTimeType delay = (double)headerLength / (1000*channelcapacity);

	assure(local->getPeer(), "Peer entity not available!");
	Medium::send(DisconInd(local), delay);
}

void TCP::listenOnPort(wns::service::tl::Port _port, wns::service::tl::ConnectionHandler* _ch)
{
	wns::service::nl::FQDN domainName =
		wns::service::nl::FQDN(pyco.get<std::string>("domainName"));

	if (!registered)
	{
		Routing::registerIP(domainName);
		registered = true;
	}
	Routing::setService(domainName, _port, _ch);
}

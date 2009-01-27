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

#include <SIMPLETL/service/UDP.hpp>
#include <SIMPLETL/service/Connection.hpp>
#include <SIMPLETL/Routing.hpp>
#include <SIMPLETL/SimpleTL.hpp>
#include <WNS/service/tl/FlowID.hpp>
#include <WNS/service/qos/QoSClasses.hpp>
#include <WNS/module/Module.hpp>
#include <WNS/logger/Master.hpp>

using namespace simpletl;

UDP::UDP(const wns::pyconfig::View& _pyco)
	: pyco(_pyco),
	  eventscheduler(wns::simulator::getEventScheduler()),
	  registered(false),
	  logger("SimpleTL", "UDP",
			 wns::simulator::getMasterLogger())
{
	portPool = new wns::service::tl::PortPool(pyco.get<simTimeType>("portUnbindDelay"));
}

UDP::~UDP()
{
	delete portPool;
}

void UDP::openConnection(int _port,
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
	// UDP-Header: 8 Byte, IP-Header: 20 Byte -> 224 Bit
	Bit headerLength = 224;

	Connection* local = new Connection(_ch, flowID, headerLength);
	Connection* peer = new Connection(peerconnectionhandler, local->swappedFlowID(), headerLength);

	local->setPeer(peer);
	peer->setPeer(local);

	MESSAGE_SINGLE(NORMAL, logger, "Opening connection for flow ID: " << flowID);

	_ch->onConnectionEstablished(wns::service::nl::Address(_source), local);
}

void UDP::closeConnection(wns::service::tl::Connection* _connection)
{
	assureType(_connection, Connection*);
	Connection* local = static_cast<Connection*>(_connection);

	local->getConnectionHandler()->onConnectionClosed(_connection);

	assureType(_connection, Connection*);
	MESSAGE_SINGLE(NORMAL, logger, "Closing connection for flowID: "
				   << static_cast<Connection*>(_connection)->getFlowID());
	delete _connection;
}

void UDP::listenOnPort(int _port, wns::service::tl::ConnectionHandler* _ch)
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

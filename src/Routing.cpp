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

#include <SIMPLETL/Routing.hpp>
#include <WNS/Assure.hpp>

using namespace simpletl;

Routing::ServerPorts Routing::serverports = Routing::ServerPorts();

void Routing::registerIP(wns::service::nl::FQDN domainName)
{
	serverports[domainName] = Routing::ServerServices();
}

void Routing::setService(wns::service::nl::FQDN domainName, int port,
						 wns::service::tl::ConnectionHandler* ch)
{
	serverports[domainName][port] = ch;
}

wns::service::tl::ConnectionHandler*
Routing::getService(wns::service::nl::FQDN domainName, int port)
{
	assure(serverports[domainName][port],
		   "No server with given IP address is listening on given port!");
	return serverports[domainName][port];
}

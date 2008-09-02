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

#include <SIMPLETL/events/DisconInd.hpp>
#include <SIMPLETL/service/Connection.hpp>
#include <SIMPLETL/Medium.hpp>

using namespace simpletl;

DisconInd::DisconInd(Connection* _sender) :
	  sender(_sender)
{}

DisconInd::~DisconInd()
{}

void DisconInd::operator()()
{
	assure(sender, "Sender not available!");

	sender->getPeer()->getConnectionHandler()->onConnectionClosedByPeer(sender->getPeer());
	sender->getConnectionHandler()->onConnectionClosed(sender);

	delete sender->getPeer();
	delete sender;

	Medium::setFree();
}

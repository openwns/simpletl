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

#include <SIMPLETL/node/component/Component.hpp>
#include <SIMPLETL/service/TCP.hpp>
#include <SIMPLETL/service/UDP.hpp>
#include <SIMPLETL/Routing.hpp>

using namespace simpletl;

STATIC_FACTORY_REGISTER_WITH_CREATOR(Component, wns::node::component::Interface,
									 "simpleTL.Component",
									 wns::node::component::ConfigCreator);

Component::Component(
	wns::node::Interface* node,
	const wns::pyconfig::View& pyco) :

	wns::node::component::Component(node, pyco),
	tcp(new TCP(pyco)),
	udp(new UDP(pyco)),
	logger(pyco.get("logger"))
{
}

void
Component::doStartup()
{
	wns::pyconfig::View pyco = this->getConfig();
	addService(pyco.get<std::string>("tcpServiceName"), tcp);
	addService(pyco.get<std::string>("udpServiceName"), udp);
}

Component::~Component()
{
	delete tcp;
	delete udp;
}

void
Component::onNodeCreated()
{}

void
Component::onWorldCreated()
{}

void
Component::onShutdown()
{}

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

#ifndef SIMPLETL_COMPONENT_HPP
#define SIMPLETL_COMPONENT_HPP

#include <WNS/node/component/Component.hpp>
#include <WNS/logger/Logger.hpp>
#include <SIMPLETL/service/UDP.hpp>
#include <SIMPLETL/service/TCP.hpp>


namespace simpletl {

    /**
    * @brief The SimpleTL component registers two implementation of the
    * transport layer service wns::service::tl::Service. A TCP and a UDP
    * model. The TCP service delays connection setup while the UDP connection
    * is set up immediately.
    */
	class Component : public wns::node::component::Component
	{
	public:
		Component(wns::node::Interface* node, const wns::pyconfig::View& pyco);

		virtual
		~Component();

		virtual void
		onNodeCreated();

		virtual void
		onWorldCreated();

		virtual void
		onShutdown();
	private:
        /**
        * @brief Registers the TCP and UDP service at the node wide service
        * registry.
        */
		virtual void
		doStartup();

		TCP* tcp;
		UDP* udp;
		wns::logger::Logger logger;
	};
}
#endif // SIMPLETL_COMPONENT_HPP

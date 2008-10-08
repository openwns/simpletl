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

#ifndef SIMPLETL_ROUTING_HPP
#define SIMPLETL_ROUTING_HPP

#include <WNS/service/tl/ConnectionHandler.hpp>
#include <WNS/service/nl/Address.hpp>
#include <map>

namespace simpletl {

    /**
    * @brief This class and its static methods help nodes
    * to magically communicate with each other. Every SimpleTL layer 
    * in a node can use this class to obtain a pointer to the 
    * ConnectionHandler of a port in another node.
    * The ConnectionHandler can then be used to open and close
    * connections. 
    */
	class Routing
	{
	public:
        /**
        * @brief Each node has to register with its domain name
        * before it can register a ConnectionHandler for a port 
        * number. This is usually done on the first call of
        * TCP::listenOnPort() or UDP::listenOnPort().
        */
		static void 
        registerIP(wns::service::nl::FQDN);

        /**
        * @brief Registers a ConnectionHandler for a domain name and port
        * pair. The domain name must be previously registered using 
        * registerIP()
        */
		static void
		setService(wns::service::nl::FQDN, int, wns::service::tl::ConnectionHandler*);

        /**
        * @brief Returns the ConnectionHandler for the domain name / port pair.
        * exits with error (assure) if no handler registered.
        */
		static 
        wns::service::tl::ConnectionHandler* getService(wns::service::nl::FQDN, int);
	private:
		typedef std::map<int, wns::service::tl::ConnectionHandler*> ServerServices;
		typedef std::map<wns::service::nl::FQDN, ServerServices> ServerPorts;
		static ServerPorts serverports;
	};
}

#endif // SIMPLETL_ROUTING_HPP

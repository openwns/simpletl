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

#ifndef SIMPLETL_TCP_HPP
#define SIMPLETL_TCP_HPP

#include <WNS/service/tl/Service.hpp>
#include <WNS/service/nl/Address.hpp>
#include <WNS/service/tl/PortPool.hpp>
#include <WNS/logger/Logger.hpp>


namespace simpletl {

    /**
    * @brief This simple TCP service delays connection establishment and
    * release by the time it takes to transmit 320 bit. 320 bit correspond to
    * an TCP/IP PDU with no payload. 
    */
	class TCP : public wns::service::tl::Service
	{
	public:
		TCP(const wns::pyconfig::View&);
		virtual ~TCP();

        /**
        * @brief Called by higher layer to establish a connection to a peer
        * node. 
        * An ConInd event is scheduled which will inform the local and peer
        * connection handler when the connection is established. Establishment
        * takes the duration of transmitting 320 bit. If the Medium is busy
        * connection establishment is delayed.
        * @see Connection
        * @see Medium
        */
		virtual void openConnection(int _port,
									wns::service::nl::FQDN _source,
									wns::service::nl::FQDN _peerInstance,
									wns::service::tl::ConnectionHandler* _ch);

        /**
        * @brief Called by higher layer to release a connection to a peer
        * node. 
        * An DisconInd event is scheduled which will inform the local and peer
        * connection handler when the connection is released. Releasing
        * takes the duration of transmitting 320 bit. 
        * @see Connection
        */
		virtual void closeConnection(wns::service::tl::Connection* _connection);

        /**
        * @brief Called by higher layer to open a port for incoming connections.
        * The provided connection handler is stored at the global Routing instance
        * for the local IP address and the provided port. On first call the node
        * IP address is #registered at the Routing instance.
        */
		virtual void listenOnPort(int _port,
								  wns::service::tl::ConnectionHandler* _ch);
	private:
        /**
        * @brief The Python configuration
        **/
		wns::pyconfig::View pyco;
        
        /**
        * @brief The global event scheduler used to schedule the %PDU
        * transmission end events
        **/
		wns::events::scheduler::Interface* eventscheduler;
		
        /**
        * @brief The data rate in bit per second of our connection
        **/
        double channelcapacity;

        /** @brief Flag determining if node already
        * registered its IP address at the global Routing instance
        **/
		bool registered;

        /**
        * @brief The pool of ports used to draw a port for a new outgoing connection 
        **/
		wns::service::tl::PortPool* portPool;

        /**
        * @brief The logger for debug output
        **/
		wns::logger::Logger logger;
	};
}

#endif // SIMPLETL_TCP_HPP

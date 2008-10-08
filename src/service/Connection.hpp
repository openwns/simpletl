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

#ifndef SIMPLETL_CONNECTION_HPP
#define SIMPLETL_CONNECTION_HPP

#include <SIMPLETL/PDU.hpp>
#include <WNS/service/tl/Connection.hpp>
#include <WNS/service/tl/ConnectionHandler.hpp>
#include <WNS/service/nl/Address.hpp>
#include <WNS/service/tl/FlowID.hpp>
#include <WNS/logger/Logger.hpp>


namespace simpletl {

    /**
     * @brief The connection between two communicating nodes
     * identified by a FlowID. Each connection has a defined 
     * capacity (data rate). There is a connection instance at
     * both communicating nodes. 
     */
	class Connection : public wns::service::tl::Connection
	{
	public:
		Connection(wns::service::tl::ConnectionHandler*, wns::service::tl::FlowID, Bit);
		~Connection();

        /**
        * @brief Called by next higher layer to register the class that will
        * receive incomming PDUs. This is usually called after the connection 
        * has been established.
        **/
		virtual void registerDataHandler(wns::service::tl::DataHandler* _dh);

        /**
        * @brief Called by next higher layer to transmit a %PDU. A %PCI of 
        * #headerSize is attached. The transmission duration is calculated
        * using the #channelcapacity variable. 
        **/
		virtual void sendData(const wns::osi::PDUPtr&);

        /**
        * @brief Called when a PDU is received. The %PDU is passed
        * to the next higher layer. The layer above is informed
        * about connection establishment when first %PDU is received.
        **/
		void receiveData(const simpletl::PDUPtr&);

        /**
        * @brief Returns the connection handler.
        **/
		wns::service::tl::ConnectionHandler* getConnectionHandler();

        /**
        * @brief Sets the peer Connection instance.
        **/
		void setPeer(Connection*);

        /**
        * @brief Returns the peer Connection instance.
        **/
		Connection* getPeer();

        /**
        * @brief Returns the FlowID of this connection
        **/
		wns::service::tl::FlowID getFlowID();

        /**
        * @brief Returns the FlowID of this connection with swapped
        * sender and receiver IP addresses and ports.
        **/
		wns::service::tl::FlowID swappedFlowID();

	private:
        /**
        * @brief Service from layer above that receives incoming PDUs
        **/
		wns::service::tl::DataHandler* datahandler;

        /**
        * @brief Service from layer above informed about establishment of
        * connection
        **/
		wns::service::tl::ConnectionHandler* connectionhandler;

        /**
        * @brief The peer connection instance
        **/
		Connection* peer;

        /**
        * @brief The FlowID consisting of source and target IP addresses and port
        * numbers
        **/
		wns::service::tl::FlowID flowID;

        /**
        * @brief Header overhead in bit added to the payload size
        **/
		Bit headerSize;

        /**
        * @brief The global event scheduler used to schedule the %PDU
        * transmission end events
        **/
		wns::events::scheduler::Interface* eventscheduler;

        /**
        * @brief The data rate in bit per second of our connection
        **/
		double channelcapacity;

        /**
        * @brief The logger for debug output
        **/
		wns::logger::Logger logger;
	};
}

#endif // SIMPLETL_CONNECTION_HPP

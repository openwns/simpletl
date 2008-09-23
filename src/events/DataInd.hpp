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

#ifndef SIMPELTL_DATAIND_HPP
#define SIMPLETL_DATAIND_HPP

#include <SIMPLETL/PDU.hpp>
#include <WNS/SmartPtr.hpp>
#include <WNS/RefCountable.hpp>

namespace simpletl
{
	class Connection;

    /**
    * @brief Used to schedule the transmission
    * end of a PDU on the medium.
    */
	class DataInd :
        public wns::RefCountable
	{
	public:
		DataInd(Connection*, const simpletl::PDUPtr&);
		virtual ~DataInd();

        /**
        * @brief Informs the #receiver of this transmitted #pdu that
        * the complete PDU was transmitted and passes it to to it
        * using the Connection::receiveData() method.
        */
		virtual void operator()();

	private:
		Connection* receiver;
		simpletl::PDUPtr pdu;
	};
    typedef wns::SmartPtr<DataInd> DataIndPtr;
}

#endif // SIMPLETL_DATAIND_HPP

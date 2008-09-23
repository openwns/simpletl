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

#ifndef SIMPELTL_DISCONIND_HPP
#define SIMPLETL_DISCONIND_HPP

#include <WNS/SmartPtr.hpp>
#include <WNS/RefCountable.hpp>

namespace simpletl
{
	class Connection;

    /**
    * @brief Used by TCP to schedule the event of connection
    * release. 
    */
	class DisconInd :
        public wns::RefCountable
	{
	public:
		DisconInd(Connection*);
		virtual ~DisconInd();

        /**
        * @brief When executed by the event scheduler this method
        * tells the ConnectionHandler of the sender and receiver
        * that the connection has been released.
        */
		virtual void operator()();

	private:
		Connection* sender;
	};
    typedef wns::SmartPtr<DisconInd> DisconIndPtr;
}

#endif // SIMPLETL_DISCONIND_HPP

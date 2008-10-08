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

#ifndef SIMPLETL_PCI_HPP
#define SIMPLETL_PCI_HPP

#include <WNS/service/tl/FlowID.hpp>
#include <WNS/osi/PCI.hpp>
#include <WNS/simulator/Bit.hpp>

namespace simpletl {
    /**
    * @brief This class holds the protocol header information
    * of the SimpleTL layer. These are the #headerSize and the #flowID.
    */
	class PCI :
		public wns::osi::PCI
	{
	public:
		PCI(wns::osi::pduType, const Bit, const Bit, wns::service::tl::FlowID);

        /**
        * @return The PCI (header) size in bit
        */
   		virtual Bit getSize() const;

        /**
        * @brief The flow ID consists of source and destination
        * IP address and the source and destination port number
        */
		wns::service::tl::FlowID flowID;
	private:
        /**
        * @brief The PCI (header) size in bit
        */
		Bit headerSize;
	};
}

#endif // SIMPLETL_PCI_HPP

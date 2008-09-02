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

#ifndef SIMPLETL_PDU_HPP
#define SIMPLETL_PDU_HPP

#include <WNS/osi/PDU.hpp>

namespace simpletl {
	class PCI;

    /**
    * @brief This class holds the protocol data unit (%PDU)
    * of the SimpleTL layer. It implements doGetLengthInBits()
    * to return the %PDU size.
    */
	class PDU :
		public wns::osi::PDU
	{
	public:
		PDU(simpletl::PCI*, const wns::osi::PDUPtr&);

	private:
        /**
        * @return The size of the %PDU in bit which is the sum of
        * the %PCI returned by PCI::getSize() and the size uf the user
        * data (SDU) from the layer above.
        */
		virtual Bit doGetLengthInBits() const;
	};

    /**
    * @brief Type definition for smart pointers to SimpleTL PDUs. A PDU this
    * smart pointer points to is automatically deleted when nobody references 
    * it any more. 
    */
	typedef wns::SmartPtr<simpletl::PDU> PDUPtr;
}
#endif // SIMPLETL_PDU_HPP

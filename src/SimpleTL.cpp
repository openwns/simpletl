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

#include <SIMPLETL/SimpleTL.hpp>
#include <SIMPLETL/bversion.hpp>

using namespace simpletl;

STATIC_FACTORY_REGISTER_WITH_CREATOR(SimpleTL, wns::module::Base, "simpleTL", wns::PyConfigViewCreator);

SimpleTL::SimpleTL(const wns::pyconfig::View& _pyConfigView)
	: wns::module::Module<SimpleTL>(_pyConfigView)
{
	version = wns::module::VersionInformation(BUILDVINFO);
}

void SimpleTL::configure()
{}

void SimpleTL::startUp()
{}

void SimpleTL::shutDown()
{}

/*
  Local Variables:
  mode: c++
  fill-column: 80
  c-basic-offset: 4
  c-tab-always-indent: t
  indent-tabs-mode: t
  tab-width: 4
  End:
*/

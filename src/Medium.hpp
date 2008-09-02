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

#ifndef SIMPLETL_MEDIUM_HPP
#define SIMPLETL_MEDIUM_HPP


#include <WNS/events/scheduler/Callable.hpp>
#include <WNS/events/scheduler/Interface.hpp>
#include <WNS/simulator/Time.hpp>
#include <WNS/simulator/ISimulator.hpp>
#include <map>
#include <queue>

namespace simpletl {
     /**
     * @brief The static methods of this class
     * assure that there is always just one ongoing
     * transmission. If there is an ongoing transmissions
     * later transmissions will be queued and served in
     * FIFO order.
     */
	class Medium
	{
	public:
        /**
        * @brief Will schedule the operator() method of
        * object of type T for execution. The method will be executed 
        * at simulation time "delay" if the medium is busy. Else it will 
        * be queued and executed later.
        * The execution of the event corresponds to the end of an 
        * transmission. The passed object must call the setFree() method
        * in its operator() method when it has finished. 
        */
        template <typename T>
        static void send(T t, wns::simulator::Time delay)
        {
            if (busy)
            {
                // Medium is busy. Queue the event
                eventqueue.push(std::make_pair(t, delay));
            }
            else
            {
                // Medium was free. Now it is busy. Send the event.
                busy = true;
                wns::simulator::getEventScheduler()->scheduleDelay(t, delay);
            }
        }
        
        /**
        * @brief Called when the ongoing transmission is over by the current
        * transmission event. If queued the next transmission event is scheduled
        * for execution.
        */
		static void setFree();

	private:
        typedef std::pair<wns::events::scheduler::Callable, wns::simulator::Time> QEntry;
		typedef std::queue<QEntry> EventQueue;
		static bool busy;
		static EventQueue eventqueue;
	};
}

#endif // SIMPLETL_MEDIUM_HPP

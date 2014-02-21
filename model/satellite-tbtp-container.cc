/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2013 Magister Solutions Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Jani Puttonen <jani.puttonen@magister.fi>
 */

#include "ns3/mac48-address.h"
#include "ns3/uinteger.h"
#include "ns3/nstime.h"
#include "ns3/simulator.h"
#include "satellite-tbtp-container.h"
#include "satellite-control-message.h"


namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (SatTbtpContainer);

TypeId
SatTbtpContainer::GetTypeId (void)
{
    static TypeId tid = TypeId ("ns3::SatTbtpContainer")
      .SetParent<Object> ()
      .AddConstructor<SatTbtpContainer>()
      .AddAttribute ("MaxStoredTbtps",
                     "Maximum amount of stored TBTPs",
                     UintegerValue (10),
                     MakeUintegerAccessor (&SatTbtpContainer::m_maxStoredTbtps),
                     MakeUintegerChecker<uint32_t> ())
    ;
    return tid;
}

SatTbtpContainer::SatTbtpContainer ()
:m_address (),
 m_maxStoredTbtps (10),
 m_rcvdTbtps (0)
{

}

SatTbtpContainer::~SatTbtpContainer ()
{

}

void SatTbtpContainer::DoDispose ()
{
  m_tbtps.clear ();
  Object::DoDispose ();
}


void
SatTbtpContainer::SetMacAddress (Mac48Address address)
{
  m_address = address;
}

void
SatTbtpContainer::Add (Time startTime, Ptr<SatTbtpMessage> tbtp)
{
  ++m_rcvdTbtps;

  m_tbtps.insert (std::make_pair<Time, Ptr<SatTbtpMessage> > (startTime, tbtp));

  // If there are too many TBTPs in the container, erase the first
  if (m_tbtps.size () > m_maxStoredTbtps)
    {
      m_tbtps.erase (m_tbtps.begin ());
    }
}


bool
SatTbtpContainer::HasScheduledTimeSlots () const
{
  if (m_tbtps.empty ())
    {
      return false;
    }
  else
    {
      /**
       * Go through the TBTP container in reverse order, until we
       * are in the first TBTP with earlier start time than Now!
       * If there are at least one time slot scheduled, return true.
       * Otherwise return false.
       */
      SatTbtpMessage::DaTimeSlotInfoContainer_t slots;
      for (TbtpMap_t::const_reverse_iterator it = m_tbtps.rbegin ();
          it != m_tbtps.rend ();
          ++it)
        {
          // TBTP in the future
          if (it->first > Simulator::Now ())
            {
              slots = it->second->GetDaTimeslots (m_address);
              if (!slots.empty ())
                {
                  return true;
                }
            }
          // it->first <= Simulator::Now ()
          // TBTP in the past or Now()
          else
            {
              slots = it->second->GetDaTimeslots (m_address);
              if (!slots.empty ())
                {
                  return true;
                }
              return false;
            }
        }
    }
  return false;
}


} // namespace


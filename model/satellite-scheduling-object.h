/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2013 Magister Solutions Ltd
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


#ifndef SATELLITE_SCHEDULING_OBJECT_H_
#define SATELLITE_SCHEDULING_OBJECT_H_

#include "ns3/simple-ref-count.h"
#include "ns3/nstime.h"

namespace ns3 {

/**
 * \ingroup satellite
 * \brief Base Llc class for Sat Net Devices.
 *
 */
class SatSchedulingObject :  public SimpleRefCount<SatSchedulingObject>
{
public:

  /**
   * Default constructor
   */
  SatSchedulingObject ();

  /**
   * Default constructor
   */
  SatSchedulingObject (Mac48Address addr, uint32_t bytes, uint32_t minTxOpportunity, Time holDelay, uint32_t priority);

  /**
   * Destructor
   */
  virtual ~SatSchedulingObject ();

  /**
   * Get the MAC address of this object
   * \return MAC address
   */
  Mac48Address GetMacAddress () const;

  /**
   * Get buffered bytes of this object
   * \return buffered bytes
   */
  uint32_t GetBufferedBytes () const;

  /**
   * Get minimum tx opportunity in bytes
   * \return minimum Tx opportunity in bytes
   */
  uint32_t GetMinTxOpportunityInBytes () const;

  /**
   * Get the priority of the object
   * \return Priority of the object
   */
  uint32_t GetPriority () const;

  /**
   * Get HOL delay of the object.
   *
   * \return HOL delay of the object.
   */
  Time GetHolDelay () const;

private:

  Mac48Address m_macAddress;
  uint32_t m_bufferedBytes;
  uint32_t m_minTxOpportunity;
  Time m_holDelay;
  uint32_t m_priority;

};



} // namespace ns3


#endif /* SATELLITE_SCHEDULING_OBJECT_H_ */

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

#include <sstream>
#include "ns3/log.h"
#include "satellite-channel-fading-trace-container.h"

NS_LOG_COMPONENT_DEFINE ("SatChannelFadingTraceContainer");

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (SatChannelFadingTraceContainer);

TypeId
SatChannelFadingTraceContainer::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::SatChannelFadingTraceContainer")
    .SetParent<Object> ()
    .AddConstructor<SatChannelFadingTraceContainer> ()
  ;
  return tid;
}

SatChannelFadingTraceContainer::SatChannelFadingTraceContainer ()
{
  NS_ASSERT (true);
}

SatChannelFadingTraceContainer::SatChannelFadingTraceContainer (uint32_t numUts, uint32_t numGws)
{
  NS_LOG_FUNCTION (this << numUts << numGws);

  // Create the fading traces
  CreateUtFadingTraces (numUts);
  CreateGwFadingTraces (numGws);
}


SatChannelFadingTraceContainer::~SatChannelFadingTraceContainer ()
{
  NS_LOG_FUNCTION (this);
}

void SatChannelFadingTraceContainer::CreateUtFadingTraces (uint32_t numUts)
{
  NS_LOG_FUNCTION (this << numUts);

  std::string path = "src/satellite/data/fadingtraces/";

  // UT identifiers start from 1
  for (uint32_t i = 1; i <= numUts; ++i)
    {
      std::stringstream ss;
      ss << i;

      std::string fwd = path + "term_ID" + ss.str () + "_fading_fwddwn.dat";
      std::string ret = path + "term_ID" + ss.str () + "_fading_rtnup.dat";

      Ptr<SatChannelFadingTrace> ftRet = CreateObject<SatChannelFadingTrace> (SatChannelFadingTrace::FT_TWO_COLUMN, ret);
      Ptr<SatChannelFadingTrace> ftFwd = CreateObject<SatChannelFadingTrace> (SatChannelFadingTrace::FT_THREE_COLUMN, fwd);

      // First = RETURN_USER
      // Second = FORWARD_USER
      m_utFadingMap.insert (std::make_pair (i, std::make_pair (ftRet, ftFwd)));
    }
}

void SatChannelFadingTraceContainer::CreateGwFadingTraces (uint32_t numGws)
{
  NS_LOG_FUNCTION (this << numGws);

  std::string path = "src/satellite/data/fadingtraces/";

  // GW identifiers start from 1
  for (uint32_t i = 1; i <= numGws; ++i)
    {
      std::stringstream ss;
      ss << i;

      std::string fwd = path + "GW_ID" + ss.str () + "_fading_fwdup.dat";
      std::string ret = path + "GW_ID" + ss.str () + "_fading_rtndwn.dat";

      Ptr<SatChannelFadingTrace> ftRet = CreateObject<SatChannelFadingTrace> (SatChannelFadingTrace::FT_TWO_COLUMN, ret);
      Ptr<SatChannelFadingTrace> ftFwd = CreateObject<SatChannelFadingTrace> (SatChannelFadingTrace::FT_TWO_COLUMN, fwd);

      // First = RETURN_FEEDER
      // Second = FORWARD_FEEDR
      m_gwFadingMap.insert (std::make_pair (i, std::make_pair (ftRet, ftFwd)));
    }
}


Ptr<SatChannelFadingTrace>
SatChannelFadingTraceContainer::GetFadingTrace (uint32_t nodeId, SatChannel::ChannelType_t channelType) const
{
  NS_LOG_FUNCTION (this << nodeId);
  NS_ASSERT (!m_utFadingMap.empty ());
  NS_ASSERT (!m_gwFadingMap.empty ());

  Ptr<SatChannelFadingTrace> ft;
  switch (channelType)
  {
    case SatChannel::FORWARD_USER_CH:
      ft = m_utFadingMap.at(nodeId).second;
      break;
    case SatChannel::RETURN_USER_CH:
      ft = m_utFadingMap.at(nodeId).first;
      break;

    case SatChannel::FORWARD_FEEDER_CH:
      ft = m_gwFadingMap.at(nodeId).second;
      break;

    case SatChannel::RETURN_FEEDER_CH:
      ft = m_gwFadingMap.at(nodeId).first;
      break;

    default:
      NS_LOG_ERROR (this << " not valid channel type!");

      break;
  }
  return ft;
}


bool SatChannelFadingTraceContainer::TestFadingTraces () const
{
  NS_LOG_FUNCTION (this);
  NS_ASSERT (!m_utFadingMap.empty ());
  NS_ASSERT (!m_gwFadingMap.empty ());

  // Go through all the created fading trace class as
  // test each one of those. If even one test fails,
  // return false.

  // Test UT fading traces
  std::map< uint32_t, ChannelTracePair_t>::const_iterator cit;
  for (cit = m_utFadingMap.begin (); cit != m_utFadingMap.end (); ++cit)
    {
      if (!cit->second.first->TestFadingTrace ())
        {
          return false;
        }
      if (!cit->second.second->TestFadingTrace ())
        {
          return false;
        }
    }

  // Test GW fading traces
  for (cit = m_gwFadingMap.begin (); cit != m_gwFadingMap.end (); ++cit)
    {
      if (!cit->second.first->TestFadingTrace ())
        {
          return false;
        }
      if (!cit->second.second->TestFadingTrace ())
        {
          return false;
        }
    }

  // All tests succeeded
  return true;
}

} // namespace ns3

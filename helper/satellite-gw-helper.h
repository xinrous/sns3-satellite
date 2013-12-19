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
 * Author: Sami Rantanen <sami.rantanen@magister.fi>
 */

#ifndef SATELLITE_GW_HELPER_H
#define SATELLITE_GW_HELPER_H

#include <string>

#include "ns3/object-factory.h"
#include "ns3/net-device-container.h"
#include "ns3/node-container.h"
#include "ns3/traced-callback.h"
#include "ns3/satellite-channel.h"
#include "ns3/satellite-ncc.h"
#include "ns3/satellite-link-results.h"

namespace ns3 {

/**
 * \brief Build a set of SatNetDevice objects
 *
 */
class SatGwHelper : public Object
{
public:
  typedef SatPhyRxCarrierConf::CarrierBandwidthConverter CarrierBandwidthConverter;

  static TypeId GetTypeId (void);
  TypeId GetInstanceTypeId (void) const;

  SatGwHelper ();
  /**
   * Create a SatGwHelper to make life easier when creating Satellite point to
   * point network connections.
   */
  SatGwHelper (CarrierBandwidthConverter carrierBandwidthConverter, uint32_t fwdLinkCarrierCount);

  virtual ~SatGwHelper () {}

  /*
   * Initializes the GW helper based on attributes
   */
  void Initialize ();

  /**
   * Each point to point net device must have a queue to pass packets through.
   * This method allows one to set the type of the queue that is automatically
   * created when the device is created and attached to a node.
   *
   * \param type the type of queue
   * \param n1 the name of the attribute to set on the queue
   * \param v1 the value of the attribute to set on the queue
   * \param n2 the name of the attribute to set on the queue
   * \param v2 the value of the attribute to set on the queue
   * \param n3 the name of the attribute to set on the queue
   * \param v3 the value of the attribute to set on the queue
   * \param n4 the name of the attribute to set on the queue
   * \param v4 the value of the attribute to set on the queue
   *
   * Set the type of queue to create and associated to each
   * SatNetDevice created through SatGwHelper::Install.
   */
  void SetQueue (std::string type,
                 std::string n1 = "", const AttributeValue &v1 = EmptyAttributeValue (),
                 std::string n2 = "", const AttributeValue &v2 = EmptyAttributeValue (),
                 std::string n3 = "", const AttributeValue &v3 = EmptyAttributeValue (),
                 std::string n4 = "", const AttributeValue &v4 = EmptyAttributeValue ());

  /**
   * Set an attribute value to be propagated to each NetDevice created by the
   * helper.
   *
   * \param name the name of the attribute to set
   * \param value the value of the attribute to set
   *
   * Set these attributes on each ns3::SatNetDevice created
   * by SatGwHelper::Install
   */
  void SetDeviceAttribute (std::string name, const AttributeValue &value);

  /**
   * Set an attribute value to be propagated to each Channel created by the
   * helper.
   *
   * \param name the name of the attribute to set
   * \param value the value of the attribute to set
   *
   * Set these attribute on each ns3::SatChannel created
   * by SatGwHelper::Install
   */
  void SetChannelAttribute (std::string name, const AttributeValue &value);

  /**
   * Set an attribute value to be propagated to each Phy created by the helper.
   *
   * \param name the name of the attribute to set
   * \param value the value of the attribute to set
   *
   * Set these attributes on each ns3::SatNetDevice created
   * by SatGwHelper::Install
   */
  void SetPhyAttribute (std::string name, const AttributeValue &value);

  /**
   * \param c a set of nodes
   * \param gwId  id of the gw
   * \param beamId  id of the beam
   * \param fCh forward channel
   * \param rCh return channel
   * \param ncc NCC (Network Control Center)
   *
   * This method creates a ns3::SatChannel with the
   * attributes configured by SatGwHelper::SetChannelAttribute,
   * then, for each node in the input container, we create a 
   * ns3::SatNetDevice with the requested attributes,
   * a queue for this ns3::SatNetDevice, and associate the resulting
   * ns3::SatNetDevice with the ns3::Node and ns3::SatChannel.
   */
  NetDeviceContainer Install (NodeContainer c, uint32_t gwId, uint32_t beamId, Ptr<SatChannel> fCh, Ptr<SatChannel> rCh, Ptr<SatNcc> ncc );

  /**
   * \param n node
   * \param gwId  id of the gw
   * \param beamId  id of the beam
   * \param fCh forward channel
   * \param rCh return channel
   * \param ncc NCC (Network Control Center)
   *
   * Saves you from having to construct a temporary NodeContainer.
   */
  Ptr<NetDevice> Install (Ptr<Node> n, uint32_t gwId, uint32_t beamId, Ptr<SatChannel> fCh, Ptr<SatChannel> rCh, Ptr<SatNcc> ncc );

  /**
   * \param aName Name of the node
   * \param gwId  id of the gw
   * \param beamId  id of the beam
   * \param fCh forward channel
   * \param rCh return channel
   * \param ncc NCC (Network Control Center)
   *
   * Saves you from having to construct a temporary NodeContainer.
   */
  Ptr<NetDevice> Install (std::string aName, uint32_t gwId, uint32_t beamId, Ptr<SatChannel> fCh, Ptr<SatChannel> rCh, Ptr<SatNcc> ncc );

  /**
   * Enables creation traces to be written in given file
   * \param stream  stream for creation trace outputs
   * \param cb  callback to connect traces
   */
  void EnableCreationTraces(Ptr<OutputStreamWrapper> stream, CallbackBase &cb);

private:
  CarrierBandwidthConverter  m_carrierBandwidthConverter;
  int32_t m_rtnLinkCarrierCount;

  ObjectFactory m_queueFactory;
  ObjectFactory m_channelFactory;
  ObjectFactory m_deviceFactory;

  /*
   * Configured interference model for the return link. Set as an attribute.
   */
  SatPhy::InterferenceModel m_interferenceModel;

  /*
   * Configured error model for the return link. Set as an attribute.
   */
  SatPhy::ErrorModel m_errorModel;

  /*
   * Return channel link results (DVB-RCS2) are created if ErrorModel
   * is configured to be AVI. Note, that only one instance of the
   * link results is needed for all GWs.
   */
  Ptr<SatLinkResults> m_linkResults;

  /**
   * \brief Trace callback for creation traces
   */
  TracedCallback<std::string> m_creation;
};

} // namespace ns3

#endif /* SATELLITE_GW_HELPER_H */

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
 * Author: Frans Laakso <frans.laakso@magister.fi>
 */
#ifndef SATELLITE_INTERFERENCE_OUTPUT_TRACE_CONTAINER_H
#define SATELLITE_INTERFERENCE_OUTPUT_TRACE_CONTAINER_H

#include "satellite-base-trace-container.h"
#include "ns3/satellite-output-fstream-double-container.h"
#include "satellite-enums.h"
#include "ns3/mac48-address.h"

namespace ns3 {

/**
 * \ingroup satellite
 *
 * \brief Class for interference output trace container
 */
class SatInterferenceOutputTraceContainer : public SatBaseTraceContainer
{
public:

  /**
   * \brief typedef for map key
   */
  typedef std::pair<Address,SatEnums::ChannelType_t> key_t;

  /**
   * \brief typedef for map of containers
   */
  typedef std::map <key_t, Ptr<SatOutputFileStreamDoubleContainer> > container_t;

  /**
   * \brief Constructor
   */
  SatInterferenceOutputTraceContainer ();

  /**
   * \brief Destructor
   */
  ~SatInterferenceOutputTraceContainer ();

  /**
   * \brief NS-3 type id function
   * \return type id
   */
  static TypeId GetTypeId (void);

  /**
   *  \brief Do needed dispose actions.
   */
  void DoDispose ();

  /**
   * \brief Add the vector containing the values to container matching the key
   * \param key key
   * \param newItem vector of values
   */
  void AddToContainer (key_t key, std::vector<double> newItem);

private:

  /**
   * \brief Function for resetting the variables
   */
  void Reset ();

  /**
   * \brief Function for adding the node to the map
   * \param key key
   * \return pointer to the added container
   */
  Ptr<SatOutputFileStreamDoubleContainer> AddNode (std::pair<Address,SatEnums::ChannelType_t> key);

  /**
   * \brief Function for finding the container matching the key
   * \param key key
   * \return matching container
   */
  Ptr<SatOutputFileStreamDoubleContainer> FindNode (key_t key);

  /**
   * \brief Write the contents of a container matching to the key into a file
   */
  void WriteToFile ();

  /**
   * \brief Map for containers
   */
  container_t m_container;

  /**
   * \brief Path to current working directory
   */
  std::string m_currentWorkingDirectory;
};

} // namespace ns3

#endif /* SATELLITE_INTERFERENCE_OUTPUT_TRACE_CONTAINER_H */

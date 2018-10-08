/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2011 Centre Tecnologic de Telecomunicacions de Catalunya (CTTC)
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
 * Author: Gaurav Sathe <gaurav.sathe@tcs.com>
 */

#include "ns3/lte-helper.h"
#include "ns3/epc-helper.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/lte-module.h"
#include "ns3/applications-module.h"
#include "ns3/point-to-point-helper.h"
#include "ns3/config-store.h"
//#include "ns3/gtk-config-store.h"
//FlowMonitor
#include "ns3/flow-monitor-module.h"


using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("BearerDeactivateExample");
int
main (int argc, char *argv[])
{

  uint16_t numberOfNodes = 1;
  uint16_t numberOfUeNodes = 6;
  double simTime = 1.1;
  int distance = 300;
  double interPacketInterval = 20;

  // Command line arguments
  CommandLine cmd;
  cmd.AddValue ("numberOfNodes", "Number of eNodeBs + UE pairs", numberOfNodes);
  cmd.AddValue ("simTime", "Total duration of the simulation [s])", simTime);
  cmd.AddValue ("distance", "Distance between eNBs [m]", distance);
  cmd.AddValue ("interPacketInterval", "Inter packet interval [ms])", interPacketInterval);
  cmd.Parse (argc, argv);

/********************************Setting EPCandLTE Helper and  system parameters from input.txt*********************************/

  Ptr<LteHelper> lteHelper = CreateObject<LteHelper> ();
  Ptr<PointToPointEpcHelper>  epcHelper = CreateObject<PointToPointEpcHelper> ();
  lteHelper->SetEpcHelper (epcHelper);

  ConfigStore inputConfig;
  inputConfig.ConfigureDefaults ();

  // parse again so you can override default values from the command line
  cmd.Parse (argc, argv);

  Ptr<Node> pgw = epcHelper->GetPgwNode ();

/********************************Setting LOG*********************************/
  // Enable Logging
  LogLevel logLevel = (LogLevel)(LOG_PREFIX_FUNC | LOG_PREFIX_TIME | LOG_LEVEL_ALL);

  LogComponentEnable ("BearerDeactivateExample", LOG_LEVEL_ALL);
  LogComponentEnable ("LteHelper", logLevel);
  LogComponentEnable ("EpcHelper", logLevel);
  LogComponentEnable ("EpcEnbApplication", logLevel);
  LogComponentEnable ("EpcSgwPgwApplication", logLevel);
  LogComponentEnable ("EpcMme", logLevel);
  LogComponentEnable ("LteEnbRrc", logLevel);
  LogComponentEnable ("LteUeRrc", logLevel);
  // LogComponentEnable ("LteUeMac", logLevel);
  LogComponentEnable ("LtePdcp", logLevel);
  LogComponentEnable ("LteRlc", logLevel);
  LogComponentEnable ("LteRlcUm", logLevel);
  // LogComponentEnable ("LteEnbMac", logLevel);
  // LogComponentEnable ("CqaFfMacScheduler", logLevel);
  LogComponentEnable ("UdpClient", logLevel);
  LogComponentEnable ("UdpServer", logLevel);
  /********************************Setting LOG END*********************************/


  // Create a single RemoteHost
  NodeContainer remoteHostContainer;
  remoteHostContainer.Create (1);
  Ptr<Node> remoteHost = remoteHostContainer.Get (0);
  InternetStackHelper internet;
  internet.Install (remoteHostContainer);

  // Create the Internet
  PointToPointHelper p2ph;
  p2ph.SetDeviceAttribute ("DataRate", DataRateValue (DataRate ("100Gb/s")));
  p2ph.SetDeviceAttribute ("Mtu", UintegerValue (2000));
  p2ph.SetChannelAttribute ("Delay", TimeValue (Seconds (0.010)));
  NetDeviceContainer internetDevices = p2ph.Install (pgw, remoteHost);
  Ipv4AddressHelper ipv4h;
  ipv4h.SetBase ("1.0.0.0", "255.0.0.0");
  Ipv4InterfaceContainer internetIpIfaces = ipv4h.Assign (internetDevices);
  // interface 0 is localhost, 1 is the p2p device
  // Ipv4Address remoteHostAddr = internetIpIfaces.GetAddress (1);

  Ipv4StaticRoutingHelper ipv4RoutingHelper;
  Ptr<Ipv4StaticRouting> remoteHostStaticRouting = ipv4RoutingHelper.GetStaticRouting (remoteHost->GetObject<Ipv4> ());
  remoteHostStaticRouting->AddNetworkRouteTo (Ipv4Address ("7.0.0.0"), Ipv4Mask ("255.0.0.0"), 1);

  NodeContainer ueNodes;
  NodeContainer enbNodes;
  enbNodes.Create (numberOfNodes);
  ueNodes.Create (numberOfUeNodes);


/********************************Setting LTE parameters********************************/
  //MAC scheduling
  lteHelper->SetSchedulerType ("ns3::CqaFfMacScheduler");
  lteHelper->SetSchedulerAttribute("CqaMetric",StringValue ("CqaPf"));
  lteHelper->SetSchedulerAttribute("HarqEnabled",BooleanValue (false));

  //RLC mode
  Config::SetDefault ("ns3::LteEnbRrc::EpsBearerToRlcMapping",EnumValue(LteEnbRrc::RLC_UM_ALWAYS));

  //Pathloss/Fading Model
  lteHelper->SetAttribute ("PathlossModel", StringValue ("ns3::Cost231PropagationLossModel"));
  lteHelper->SetAttribute ("FadingModel", StringValue ("ns3::TraceFadingLossModel"));
  std::ifstream ifTraceFile;
  ifTraceFile.open ("../../src/lte/model/fading-traces/fading_trace_EPA_3kmph.fad", std::ifstream::in);
  if (ifTraceFile.good ())
    {
      // script launched by test.py
      lteHelper->SetFadingModelAttribute ("TraceFilename", StringValue ("../../src/lte/model/fading-traces/fading_trace_EPA_3kmph.fad"));
    }
  else
    {
      // script launched as an example
      lteHelper->SetFadingModelAttribute ("TraceFilename", StringValue ("src/lte/model/fading-traces/fading_trace_EPA_3kmph.fad"));
    }
    
  // these parameters have to setted only in case of the trace format 
  // differs from the standard one, that is
  // - 10 seconds length trace
  // - 10,000 samples
  // - 0.5 seconds for window size
  // - 100 RB
  lteHelper->SetFadingModelAttribute ("TraceLength", TimeValue (Seconds (10.0)));
  lteHelper->SetFadingModelAttribute ("SamplesNum", UintegerValue (10000));
  lteHelper->SetFadingModelAttribute ("WindowSize", TimeValue (Seconds (0.5)));
  lteHelper->SetFadingModelAttribute ("RbNum", UintegerValue (100));

  // Install Mobility Model
  Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();
  //创建随机数 均匀分布
  Ptr<UniformRandomVariable> randomUniform = CreateObject<UniformRandomVariable> ();
  for (uint16_t i = 0; i < numberOfUeNodes; i++)
    {
      int randomNumber = randomUniform->GetInteger(0,distance);
      positionAlloc->Add (Vector ((double)randomNumber, 0, 0));
    }
  MobilityHelper mobility;
  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobility.Install (enbNodes);
  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobility.SetPositionAllocator(positionAlloc);
  mobility.Install (ueNodes);

  // Install LTE Devices to the nodes
  NetDeviceContainer enbLteDevs = lteHelper->InstallEnbDevice (enbNodes);
  NetDeviceContainer ueLteDevs = lteHelper->InstallUeDevice (ueNodes);

  // Install the IP stack on the UEs
  internet.Install (ueNodes);
  Ipv4InterfaceContainer ueIpIface;
  ueIpIface = epcHelper->AssignUeIpv4Address (NetDeviceContainer (ueLteDevs));
  // Assign IP address to UEs, and install applications
  for (uint32_t u = 0; u < ueNodes.GetN (); ++u)
    {
      Ptr<Node> ueNode = ueNodes.Get (u);
      // Set the default gateway for the UE
      Ptr<Ipv4StaticRouting> ueStaticRouting = ipv4RoutingHelper.GetStaticRouting (ueNode->GetObject<Ipv4> ());
      ueStaticRouting->SetDefaultRoute (epcHelper->GetUeDefaultGatewayAddress (), 1);
    }

  // Attach a UE to a eNB  Attach时候多一个默认承载，所以之后的数据流有2个承载 对应2个逻辑信道
  lteHelper->Attach (ueLteDevs, enbLteDevs.Get (0));

  // Activate an EPS bearer on all UEs

  for (uint32_t u = 0; u < ueNodes.GetN (); ++u)
    {
      Ptr<NetDevice> ueDevice = ueLteDevs.Get (u);
      GbrQosInformation qos;
      qos.gbrDl = 132;  // bit/s, considering IP, UDP, RLC, PDCP header size
      qos.gbrUl = 132;
      qos.mbrDl = qos.gbrDl;
      qos.mbrUl = qos.gbrUl;
      enum EpsBearer::Qci q;
      q= EpsBearer::GBR_GAMING;
      EpsBearer bearer (q, qos);
      // bearer.arp.priorityLevel = 15 - (u + 1);
      // bearer.arp.preemptionCapability = true;
      // bearer.arp.preemptionVulnerability = true;
      std::cout<<"**********"<<bearer.GetPacketErrorLossRate()<<std::endl;
      std::cout<<"**********"<<bearer.GetPacketDelayBudgetMs()<<std::endl;
      std::cout<<"**********"<<+bearer.GetPriority()<<std::endl;
      lteHelper->ActivateDedicatedEpsBearer (ueDevice, bearer, EpcTft::Default ());
    }


  // Install and start applications on UEs and remote host
  uint16_t dlPort = 1234;
  // uint16_t ulPort = 2000;
  // uint16_t otherPort = 3000;
  ApplicationContainer clientApps;
  ApplicationContainer serverApps;
  for (uint32_t u = 0; u < ueNodes.GetN (); ++u)
    {
      // ++ulPort;
      // ++otherPort;
      PacketSinkHelper dlPacketSinkHelper ("ns3::UdpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), dlPort));
      // PacketSinkHelper ulPacketSinkHelper ("ns3::UdpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), ulPort));
      // PacketSinkHelper packetSinkHelper ("ns3::UdpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), otherPort));
      serverApps.Add (dlPacketSinkHelper.Install (ueNodes.Get (u)));
      // serverApps.Add (ulPacketSinkHelper.Install (remoteHost));
      // serverApps.Add (packetSinkHelper.Install (ueNodes.Get (u)));

      UdpClientHelper dlClient (ueIpIface.GetAddress (u), dlPort);
      dlClient.SetAttribute ("Interval", TimeValue (MilliSeconds (interPacketInterval)));
      dlClient.SetAttribute ("MaxPackets", UintegerValue (1000000));
      dlClient.SetAttribute ("PacketSize", UintegerValue (1500));

      // UdpClientHelper ulClient (remoteHostAddr, ulPort);
      // ulClient.SetAttribute ("Interval", TimeValue (MilliSeconds (interPacketInterval)));
      // ulClient.SetAttribute ("MaxPackets", UintegerValue (1000000));

      // UdpClientHelper client (ueIpIface.GetAddress (u), otherPort);
      // client.SetAttribute ("Interval", TimeValue (MilliSeconds (interPacketInterval)));
      // client.SetAttribute ("MaxPackets", UintegerValue (1000000));

      clientApps.Add (dlClient.Install (remoteHost));
      // clientApps.Add (ulClient.Install (ueNodes.Get (u)));
      // if (u + 1 < ueNodes.GetN ())
      //   {
      //     clientApps.Add (client.Install (ueNodes.Get (u + 1)));
      //   }
      // else
      //   {
      //     clientApps.Add (client.Install (ueNodes.Get (0)));
      //   }
    }

  serverApps.Start (Seconds (0.200));
  clientApps.Start (Seconds (0.200));

  double statsStartTime = 0.0; // need to allow for RRC connection establishment + SRS
  double statsDuration = 1.0;

  lteHelper->EnableMacTraces ();
  lteHelper->EnableRlcTraces ();
  Ptr<RadioBearerStatsCalculator> rlcStats = lteHelper->GetRlcStats ();
  rlcStats->SetAttribute ("StartTime", TimeValue (Seconds (statsStartTime)));
  rlcStats->SetAttribute ("EpochDuration", TimeValue (Seconds (statsDuration)));

  //get ue device pointer for UE-ID 0 IMSI 1 and enb device pointer
  Ptr<NetDevice> ueDevice = ueLteDevs.Get (0);
  Ptr<NetDevice> enbDevice = enbLteDevs.Get (0);

  /*
   *   Instantiate De-activation using Simulator::Schedule() method which will initiate bearer de-activation after deActivateTime
   *   Instantiate De-activation in sequence (Time const &time, MEM mem_ptr, OBJ obj, T1 a1, T2 a2, T3 a3)
   */
  // Time deActivateTime (Seconds (0.05));
  // Simulator::Schedule (deActivateTime, &LteHelper::DeActivateDedicatedEpsBearer, lteHelper, ueDevice, enbDevice, 2);


  FlowMonitorHelper flowmon;
  Ptr<FlowMonitor> monitor = flowmon.Install(ueNodes);
  flowmon.Install(enbNodes.Get(1));


  //stop simulation after 3 seconds
  Simulator::Stop (Seconds (2.0));

  Simulator::Run ();
  /*GtkConfigStore config;
  config.ConfigureAttributes();*/

  monitor->CheckForLostPackets (); 

  Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier> (flowmon.GetClassifier ());
  std::map<FlowId, FlowMonitor::FlowStats> stats = monitor->GetFlowStats ();

  double Throughput=0.0;

  for (std::map<FlowId, FlowMonitor::FlowStats>::const_iterator i = stats.begin (); i != stats.end (); ++i)
    {
    Ipv4FlowClassifier::FiveTuple t = classifier->FindFlow (i->first);

      std::cout << "Flow ID: " << i->first << " Src Addr " <<  t.sourceAddress << " Dst Addr " << t.destinationAddress << std::endl;
      std::cout << "Tx Packets = " << i->second.txPackets << std::endl;
      std::cout << "Rx Packets = " << i->second.rxPackets << std::endl;
      Throughput=i->second.rxBytes * 8.0 /(i->second.timeLastRxPacket.GetSeconds()-i->second.timeFirstTxPacket.GetSeconds())/ 1024;
      std::cout << "Throughput: " <<  Throughput << " Kbps" << std::endl;
    }

  Simulator::Destroy ();
  return 0;

}


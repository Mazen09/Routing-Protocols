/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
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
 */

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/netanim-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("FirstScriptExample");

int
main (int argc, char *argv[])
{
  CommandLine cmd;
  cmd.Parse (argc, argv);

    Time::SetResolution (Time::NS);
	LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
	LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);

	NodeContainer nodes;
	nodes.Create (6);

	InternetStackHelper stack;
	stack.Install (nodes);

	PointToPointHelper p0p1;
	p0p1.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
	p0p1.SetChannelAttribute ("Delay", StringValue ("2ms"));

	PointToPointHelper p0p2;
	p0p2.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
	p0p2.SetChannelAttribute ("Delay", StringValue ("2ms"));

	PointToPointHelper p1p2;
	p1p2.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
	p1p2.SetChannelAttribute ("Delay", StringValue ("2ms"));

	PointToPointHelper p1p3;
	p1p3.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
	p1p3.SetChannelAttribute ("Delay", StringValue ("2ms"));

	PointToPointHelper p1p4;
	p1p4.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
	p1p4.SetChannelAttribute ("Delay", StringValue ("2ms"));

	PointToPointHelper p2p4;
	p2p4.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
	p2p4.SetChannelAttribute ("Delay", StringValue ("2ms"));

	PointToPointHelper p3p4;
	p3p4.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
	p3p4.SetChannelAttribute ("Delay", StringValue ("2ms"));

	PointToPointHelper p4p5;
	p4p5.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
	p4p5.SetChannelAttribute ("Delay", StringValue ("2ms"));


	Ipv4AddressHelper address;
	address.SetBase ("10.1.1.0", "255.255.255.0");
	NetDeviceContainer devices;
	devices = p0p1.Install (nodes.Get (0), nodes.Get (1));
	Ipv4InterfaceContainer interfaces = address.Assign (devices);

	devices = p0p2.Install (nodes.Get (0), nodes.Get (2));
	address.SetBase ("10.1.2.0", "255.255.255.0");
	interfaces = address.Assign (devices);

	devices = p1p2.Install (nodes.Get (1), nodes.Get (2));
	address.SetBase ("10.1.3.0", "255.255.255.0");
	interfaces = address.Assign (devices);

	devices = p1p3.Install (nodes.Get (1), nodes.Get (3));
	address.SetBase ("10.1.4.0", "255.255.255.0");
	interfaces = address.Assign (devices);

	devices = p1p4.Install (nodes.Get (1), nodes.Get (4));
	address.SetBase ("10.1.5.0", "255.255.255.0");
	interfaces = address.Assign (devices);

	devices = p2p4.Install (nodes.Get (2), nodes.Get (4));
	address.SetBase ("10.1.6.0", "255.255.255.0");
	interfaces = address.Assign (devices);

	devices = p3p4.Install (nodes.Get (3), nodes.Get (4));
	address.SetBase ("10.1.7.0", "255.255.255.0");
	interfaces = address.Assign (devices);

	devices = p4p5.Install (nodes.Get (4), nodes.Get (5));
	address.SetBase ("10.1.8.0", "255.255.255.0");
	interfaces = address.Assign (devices);

	Ipv4GlobalRoutingHelper::PopulateRoutingTables ();
        

	OutputStreamWrapper wrapper = OutputStreamWrapper (&std::cout);
        Ipv4GlobalRoutingHelper::PrintRoutingTableAllAt(Time(), &wrapper, Time::NS);

	UdpEchoServerHelper echoServer (9);

	ApplicationContainer serverApps = echoServer.Install (nodes.Get (4));
	serverApps.Start (Seconds (1.0));
	serverApps.Stop (Seconds (10.0));

	UdpEchoClientHelper echoClient (interfaces.GetAddress (1), 9);
	echoClient.SetAttribute ("MaxPackets", UintegerValue (1));
	echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
	echoClient.SetAttribute ("PacketSize", UintegerValue (1024));

	ApplicationContainer clientApps = echoClient.Install (nodes.Get (0));
	clientApps.Start (Seconds (2.0));
	clientApps.Stop (Seconds (10.0));

  AnimationInterface anim ("test2.xml");
  anim.SetConstantPosition(nodes.Get(0),0.0,24.5);
  anim.SetConstantPosition(nodes.Get(1),24.5,0.0);
  anim.SetConstantPosition(nodes.Get(2),24.5,49.0);
  anim.SetConstantPosition(nodes.Get(3),73.5,0.0);
  anim.SetConstantPosition(nodes.Get(4),73.5,49.0);
  anim.SetConstantPosition(nodes.Get(5),98.0,49.0);

  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}

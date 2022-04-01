//SINGLE HOP

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/applications-module.h"
#include "ns3/netanim-module.h"
#include "ns3/wifi-module.h"
#include "ns3/mobility-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <math.h>
#include "ns3/random-variable.h"
#include "ns3/socket-factory.h"
#include "ns3/tcp-socket-factory.h"
#include "ns3/udp-socket-factory.h"
#include "ns3/nstime.h"
#include "ns3/olsr-helper.h"
#include "ns3/v4ping-helper.h"

#include "variables.h"
#include "functions.h"
#include "singlehopm1f.h"
#include "singlehopm2f.h"
#include "singlehopm3f.h"

using namespace ns3;
using namespace std;

NS_LOG_COMPONENT_DEFINE("singlehopprogram");
NodeContainer wifinodes;
Ipv4InterfaceContainer interface;
ApplicationContainer cbrApps1;

double Distance(double dX0, double dY0, double dX1, double dY1)
{
    return sqrt((dX1 - dX0)*(dX1 - dX0) + (dY1 - dY0)*(dY1 - dY0));
}

//---------------------FREQUENCY ALLOCATION----------------------------------

void frequency_allocation(int onehoparray[nWifi][nWifi], int twohoparray[nWifi][nWifi], int onehopcountarray[],int primary_user[], vector< vector<int> > nodefrequencies)
{
		int freq[nWifi];		//No longer required
		int attempt[nWifi];
		int onehopcountwopu[nWifi];
		for(int i=0;i<nWifi;i++)
		{
			freq[i]=0;
			attempt[i]=1;
		}

		int randomfreq;
		randomfreq = rand()%FREQUENCY; //Assigning frequency for node 0
		freq[0]=randomfreq;
		nodefrequencies[0].push_back(randomfreq);

		for(int i=1;i<nWifi;i++)
		{
			randomfreq = rand()%FREQUENCY;
			freq[i]=randomfreq;
			int flag=0;
			for(int a=0;a<i;a++)
			{
				if(onehoparray[i][a]==1 || twohoparray[i][a]==2)
				{
					if(freq[a]==freq[i])
					{
						flag=1;
						attempt[i]=attempt[i]+1;
						break;
					}
				}
			}
			if(flag==1)
			{
				i=i-1;
				continue;
			}
			nodefrequencies[i].push_back(randomfreq);
			
		}
		for(int i=0;i<nWifi;i++)
		{
//			std::cout<<"Frequency for node "<<i<<": "<<freq[i]<<"\n";
//			std::cout<<"Frequency for node "<<i<<": "<<nodefrequencies[i][0]<<"\n";
//			std::cout<<"Attempt for node "<<i<<": "<<attempt[i]<<"\n\n";
		}

//-------------------ONE HOP COUNT ARRAY WITHOUT PU--------------------------
		for(int i=0;i<nWifi;i++)
		{
			int onehopcount=0;
			for(int j=0;j<nWifi;j++)
			{
				if(onehoparray[i][j]==1)
				{
					int present=0;
					for(int k=0;k<pu;k++)
					{
						if(j==primary_user[k])
						{
							present=1;
							break;
						}
					}
					if(present==0)
					{
						onehopcount++;
					}
				}
			}
			onehopcountwopu[i]=onehopcount;
		}

//-------------------NODES WITHOUT PU------------------------------------------
		int nodes_without_pu[nWifi];
		int n=0;
		for(int i=0;i<nWifi;i++)
		{
			int present=0;
			for(int j=0;j<pu;j++)
			{
				if(i==primary_user[j])
				{
					present=1;
					break;
				}
			}
			if(present==0)
			{
				nodes_without_pu[n]=i;
				n++;
			}
		}

//-------------------SOURCE-DESTINATION--------------------------------------------
		int source;
		int destination;
		
		while(1)
		{
			while(1)
			{
				source=rand()% nWifi;
				std::cout<<"\nSource: "<<source;
				int present=0;
				for(int i=0;i<pu;i++)
				{
					if(source==primary_user[i])
					{
						present=1;
						break;
					}
				}
				if(present==1)
					continue;
				else
					break;
			}

			if(onehopcountarray[source]>0)
			{
				if(onehopcountwopu[source]>0) //If src has atleast one node in its one hop WITHOUT PU then go for dest
				{
					int destpresent=0;
					while(1)
					{
						int position=rand()%nWifi;
						if(onehoparray[source][position]==1)
						{
							int present=0;
							for(int i=0;i<n;i++)
							{
								if(position==nodes_without_pu[i])
								{
									present=1;
									break;
								}
							}
							if(present==1)
							{
								destination=position;
								destpresent=1;
								std::cout<<"\nDestination: "<<destination;
								break;
							}
							else
								continue;
						}
						else
							continue;
					}
					if(destpresent==1)
						break;
				}
				else
					continue;
			}
			else
			{
				continue;
			}
		}
		

		Ptr<Node> node2 = wifinodes.Get(source);
		Ptr<MobilityModel> mob2 = node2->GetObject<MobilityModel> ();
		Vector pos2 = mob2->GetPosition ();
	
		Ptr<Node> node3 = wifinodes.Get(destination);
		Ptr<MobilityModel> mob3 = node3->GetObject<MobilityModel> ();
		Vector pos3 = mob3->GetPosition ();

		dis_s_d=Distance(pos2.x, pos2.y, pos3.x, pos3.y);
		cout<<"Distance between Source and Destination="<< dis_s_d;




		faulty_node1(onehopcountarray,onehoparray,freq,source,destination,primary_user,pu,onehopcountwopu,nodefrequencies);
		faulty_node2(onehopcountarray,onehoparray,freq,source,destination,primary_user,pu,onehopcountwopu,nodefrequencies);
		faulty_node3(onehopcountarray,onehoparray,freq,source,destination,primary_user,pu,onehopcountwopu,nodefrequencies);

}//---------------FREQUENCY ALLOCATION ENDS-------------------------------------

int main(int argc, char *argv[])
{
	srand ( (unsigned)time ( NULL ) );
	std::string phyMode ("DsssRate1Mbps");
	bool verbose = false;

	CommandLine cmd;
	cmd.AddValue ("phyMode", "Wifi Phy mode", phyMode);
	//cmd.AddValue("nWifi", "number of extra wifi nodes", nWifi);
	cmd.AddValue ("verbose", "turn on all WifiNetDevice log components", verbose);
	cmd.AddValue("range","Range:",range);
	cmd.AddValue("datatype","Data Type:",datatype);
	cmd.AddValue("FREQUENCY","No. of Frequencies:",FREQUENCY);
	cmd.AddValue("MAX_ATTEMPT","Max. Attempts:",MAX_ATTEMPT);
	cmd.Parse(argc,argv);
	data_size(datatype);	
	wifinodes.Create(nWifi);

	//PHY layer implementation
	YansWifiPhyHelper phy= YansWifiPhyHelper::Default();
	phy.Set ("RxGain", DoubleValue (0) );
	phy.SetPcapDataLinkType (YansWifiPhyHelper::DLT_IEEE802_11_RADIO);

	YansWifiChannelHelper channel= YansWifiChannelHelper::Default();
	channel.SetPropagationDelay ("ns3::ConstantSpeedPropagationDelayModel");
	channel.AddPropagationLoss ("ns3::FixedRssLossModel","Rss",DoubleValue (-80));

	phy.SetChannel(channel.Create());

	WifiHelper wifi;
	if (verbose)
	{
		wifi.EnableLogComponents ();  // Turn on all Wifi logging
	}
	wifi.SetStandard (WIFI_PHY_STANDARD_80211b);
	wifi.SetRemoteStationManager("ns3::ConstantRateWifiManager", "DataMode",StringValue (phyMode), "ControlMode",StringValue (phyMode)); //src/wifi/model

	//MAC layer implementation
	NqosWifiMacHelper wifimac= NqosWifiMacHelper::Default();
	wifimac.SetType("ns3::AdhocWifiMac"); //wifinodes

	NetDeviceContainer wifidevice= wifi.Install(phy,wifimac,wifinodes);

	MobilityHelper mobility;
	mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
	mobility.Install(wifinodes);

	OlsrHelper olsr;
	Ipv4ListRoutingHelper list;
	list.Add (olsr, 10);

	InternetStackHelper stack;
	stack.SetRoutingHelper(list);
	stack.Install(wifinodes);

	Ipv4AddressHelper address;
	address.SetBase("10.1.1.0","255.255.255.0");
	interface= address.Assign(wifidevice);

	AnimationInterface anim("allmajorityvotinganim.xml");

//-----------------------------------------------------------
	for(run=0;run<5;run++)
	{
		cout<<"RUN---------------------------------------------------------------:"<<run<<endl;
		int onehoparray[nWifi][nWifi];
		int twohoparray[nWifi][nWifi];
		int onehopcountarray[nWifi];
		int twohopcountarray[nWifi];
		vector< vector<int> > nodefrequencies(nWifi);

		tsum=0,tsum1=0,tmd_sum=0,tmd_sum1=0,tfa_sum=0,tfa_sum1=0;//SINGLEHOPM1
		tsum2=0,tsum3=0,tmd_sum2=0,tmd_sum3=0,tfa_sum2=0,tfa_sum3=0;//SINGLEHOPM2
		tsum4=0,tsum5=0,tmd_sum4=0,tmd_sum5=0,tfa_sum4=0,tfa_sum5=0;//SINGLEHOPM3


		//POSITION
		for(int i=0;i<nWifi;i++)
		{
			int x= rand() % 100;
			int y= rand() % 100;
			anim.SetConstantPosition(wifinodes.Get(i),x,y,0);
		}

//-------------------PRIMARY NODE ASSIGNMENT--------------------------
		int primary_user[pu];
		for(int i=0;i<pu;i++)
		{
			int present=0;
			int a= rand() % nWifi;
			for(int j=0;j<i;j++)
			{
				if(a==primary_user[j])
				{
					present=1;
					break;
				}
			}
			if(present==1)
			{
				i=i-1;
				continue;
			}
			else
			{
				primary_user[i]=a;
			}
		}

		cout<<"\nPrimary Users: ";
		for(int i=0;i<pu;i++)
		{
			cout<<primary_user[i]<<" ";
		}


		//INITIALIZING ONE HOP MATRIX AND TWO HOP MATRIX 0
		for(int i=0;i<nWifi;i++)
		{
			onehopcountarray[i]=0;
			twohopcountarray[i]=0;
			for(int j=0;j<nWifi;j++)
			{
				onehoparray[i][j]=0;
				twohoparray[i][j]=0;
			}
		}

		//ONE-HOP
		for(int i=0; i<nWifi; i++)
		{
			Ptr<Node> node = wifinodes.Get(i);
			Ptr<MobilityModel> mob = node->GetObject<MobilityModel> ();
			Vector pos = mob->GetPosition ();

			for(int j=0; j<nWifi; j++)
			{
				Ptr<Node> node1 = wifinodes.Get(j);
				Ptr<MobilityModel> mob1 = node1->GetObject<MobilityModel> ();
				Vector pos1 = mob1->GetPosition ();
				double dist=Distance(pos.x, pos.y, pos1.x, pos1.y);

				if(dist<=range && dist>0.00) //range
					onehoparray[i][j]=1;
			}

		} //ONE HOP ENDS

		//ONE HOP PRINTING
		cout<<"\nOne Hop Array:\n";
		for(int i=0;i<nWifi;i++)
		{
			int onehopcount=0;
//			cout<<"For node "<<i<<": ";
			for(int j=0;j<nWifi;j++)
			{
				if(onehoparray[i][j]==1)
				{
//					cout<<j<<" ";
					onehopcount++;
				}
			}
			onehopcountarray[i]=onehopcount; //storing the one hop node count in an array
//			cout<<"\n";
		}
//--------------------------------------------------------------------------------------------

		//TWO HOP MATRIX CALCULATION
		for(int i=0;i<nWifi;i++)
		{
			for(int j=0;j<nWifi;j++)
			{
				if(onehoparray[i][j]==1)
				{
					for(int k=0;k<nWifi;k++)
					{
						if(onehoparray[j][k]==1 && k!=i && onehoparray[i][k]!=1)
						{
							twohoparray[i][k]=2;
						}
					}
				}
			}
		}

		cout<<"Two Hop Array:\n";
		for(int i=0;i<nWifi;i++)
		{
			int twohopcount=0;
//			cout<<"For node "<<i<<": ";
			for(int j=0;j<nWifi;j++)
			{
				if(twohoparray[i][j]==2)
				{
//					cout<<j<<" ";
					twohopcount++;
				}
			}
			twohopcountarray[i]=twohopcount;
//			cout<<"\n";
		}

//------------CALCULATING MAX NEIGHBOR NODES IN THE NETWORK------------------
		for(int i=0;i<nWifi;i++)
		{
			int temp=onehopcountarray[i]+twohopcountarray[i];
			if(temp>temp2)
			{
				temp2=temp;
			}
		}

//-------------FREQUENCY ALLOCATION METHOD CALLED----------------------------
		frequency_allocation(onehoparray,twohoparray,onehopcountarray,primary_user,nodefrequencies);
//------------------------------PING-----------------------------------------
		for(int i=0;i<nWifi;i++)
		{
			for(int j=0;j<nWifi;j++)
			{
				if(onehoparray[i][j]==1)
				{
					V4PingHelper ping= V4PingHelper(interface.GetAddress(j));
					cbrApps1=ping.Install(wifinodes.Get(i));
				}
			}
		}

		cout<<"\nRun "<<run<<" completed.";

	} //-------------FOR LOOP ENDS----------------


	cout<<endl<<endl<<endl;
	cout<<endl<<"Faulty 1, Majority\n";
	cout<<"Avg Total Attempt : "<<((float)AAT[0]/run)<<endl;
	cout<<"Avg Miss Detection : "<<((float)MD[0]/run)<<endl;
	cout<<"Avg False Alarm : "<<((float)FA[0]/run)<<endl;
	cout<<"Avg Delay : "<<((float)D[0]/run)<<endl;
	cout<<"Success Percent : "<<((float)S[0]/run)<<endl;

	cout<<endl<<"Faulty 1, Existing\n";
	cout<<"Avg Total Attempt : "<<((float)AAT[1]/run)<<endl;
	cout<<"Avg Miss Detection : "<<((float)MD[1]/run)<<endl;
	cout<<"Avg False Alarm : "<<((float)FA[1]/run)<<endl;
	cout<<"Avg Delay : "<<((float)D[1]/run)<<endl;
	cout<<"Success Percent : "<<((float)S[1]/run)<<endl;

	cout<<endl<<"Faulty 2, Majority\n";
	cout<<"Avg Total Attempt : "<<((float)AAT[2]/run)<<endl;
	cout<<"Avg Miss Detection : "<<((float)MD[2]/run)<<endl;
	cout<<"Avg False Alarm : "<<((float)FA[2]/run)<<endl;
	cout<<"Avg Delay : "<<((float)D[2]/run)<<endl;
	cout<<"Success Percent : "<<((float)S[2]/run)<<endl;

	cout<<endl<<"Faulty 2, Existing\n";
	cout<<"Avg Total Attempt : "<<((float)AAT[3]/run)<<endl;
	cout<<"Avg Miss Detection : "<<((float)MD[3]/run)<<endl;
	cout<<"Avg False Alarm : "<<((float)FA[3]/run)<<endl;
	cout<<"Avg Delay : "<<((float)D[3]/run)<<endl;
	cout<<"Success Percent : "<<((float)S[3]/run)<<endl;

	cout<<endl<<"Faulty 3, Majority\n";
	cout<<"Avg Total Attempt : "<<((float)AAT[4]/run)<<endl;
	cout<<"Avg Miss Detection : "<<((float)MD[4]/run)<<endl;
	cout<<"Avg False Alarm : "<<((float)FA[4]/run)<<endl;
	cout<<"Avg Delay : "<<((float)D[4]/run)<<endl;
	cout<<"Success Percent : "<<((float)S[4]/run)<<endl;

	cout<<endl<<"Faulty 3, Existing\n";
	cout<<"Avg Total Attempt : "<<((float)AAT[5]/run)<<endl;
	cout<<"Avg Miss Detection : "<<((float)MD[5]/run)<<endl;
	cout<<"Avg False Alarm : "<<((float)FA[5]/run)<<endl;
	cout<<"Avg Delay : "<<((float)D[5]/run)<<endl;
	cout<<"Success Percent : "<<((float)S[5]/run)<<endl;


	exit(0);
	cbrApps1.Start(Seconds (1.0));
	cbrApps1.Stop(Seconds (10.0));

	//Ipv4GlobalRoutingHelper::PopulateRoutingTables();
	Simulator::Stop(Seconds(10.0));

	phy.EnablePcap("singlehop",wifidevice);
	anim.EnablePacketMetadata(true);

	Simulator::Run();
	Simulator::Destroy();


	print();
	cout<<"*************"<< packets << " " << requiredfrequency <<"***************\n";



	return 0;
}

//MAIN ENDS



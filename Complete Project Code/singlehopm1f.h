#ifndef SCRATCH_SINGLEHOPM1_H_
#define SCRATCH_SINGLEHOPM1_H_


void faulty_node1(int onehopcountarray[],int onehoparray[nWifi][nWifi],int freq[],int source,int destination,int primary_user[],int pu,int onehopcountwopu[], vector< vector<int> > nodefrequencies)
{
	int n1=onehopcountwopu[source]; //NUMBER OF NODES IN ONE HOP WITHOUT PU
	int n2=onehopcountwopu[destination];
	int srconehop[n1]; //without PU
	int destonehop[n2]; //without PU
	int sohsize=0;
	int dohsize=0;

//-------------------LOCK ALL THE NODES WHICH ARE IN THE LIST OF LESS THAN 3 NODES---------------
	lock=0;
	for(int i=0;i<nWifi;i++)
	{
		int y=onehopcountarray[i];
		if(y<=3)
		{
			for(int j=0;j<nWifi;j++)
			{
				if(onehoparray[i][j]==1)
				{
					int present=0;
					for(int k=0;k<lock;k++)
					{
						if(j==locked[k])
						{
							present=1;
							break;
						}
					}
					if(present==0)
					{
						locked[lock]=j;
						lock++;
					}
				}
			}
		}
	}

	std::cout<<"\nLocked Nodes:";
	for(int i=0;i<lock;i++)
	{
		std::cout<<locked[i]<<" ";
	}
//-------------REMOVE ALL THE LOCKED NODES AND PRIMARY NODES FROM SRC AND DEST ONE HOP---------
	for(int i=0;i<nWifi;i++)
	{
		if(onehoparray[source][i]==1)
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
				for(int j=0;j<lock;j++)
				{
					if(i==locked[j])
					{
						present=1;
						break;
					}
				}
				if(present==0)
				{
					srconehop[sohsize]=i;
					sohsize++;
				}
			}
		}

		if(onehoparray[destination][i]==1)
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
				for(int j=0;j<lock;j++)
				{
					if(i==locked[j])
					{
						present=1;
						break;
					}
				}
				if(present==0)
				{
					destonehop[dohsize]=i;
					dohsize++;
				}
			}
		}
	}
	std::cout<<"\nSource One Hop Nodes: ";
	for(int i=0;i<sohsize;i++)
	{
		std::cout<<srconehop[i]<<" ";
	}

	std::cout<<"\nDestination One Hop Nodes: ";
	for(int i=0;i<dohsize;i++)
	{
		std::cout<<destonehop[i]<<" ";
	}

	int n3=onehopcountarray[source]; //NUMBER OF NODES IN ONE HOP
	int n4=onehopcountarray[destination];
	int srconehop2[n3]; //with PU
	int destonehop2[n4]; //with PU
	int sohsize2=0;
	int dohsize2=0;

	for(int i=0;i<nWifi;i++)
	{
		if(onehoparray[source][i]==1)
		{
			srconehop2[sohsize2]=i;
			sohsize2++;
		}

		if(onehoparray[destination][i]==1)
		{
			destonehop2[dohsize2]=i;
			dohsize2++;
		}
	}
	std::cout<<"\nSource One Hop Nodes-2: ";
	for(int i=0;i<n3;i++)
	{
		std::cout<<srconehop2[i]<<" ";
	}

	std::cout<<"\nDestination One Hop Nodes-2: ";
	for(int i=0;i<n4;i++)
	{
		std::cout<<destonehop2[i]<<" ";
	}

	output0=0;
	output1=1;

//------------------COMMON NODES--SRCLEFTOVER NODES--DESTLEFTOVER NODES------------------------
	int commonnodes[nWifi];
	int cnsize=0;
	for(int i=0;i<sohsize;i++)
	{
		for(int j=0;j<dohsize;j++)
		{
			if(srconehop[i]==destonehop[j])
			{
				commonnodes[cnsize]=srconehop[i];
				cnsize++;
			}
		}
	}
	std::cout<<"\nCommon Nodes: ";
	for(int i=0;i<cnsize;i++)
	{
		std::cout<<commonnodes[i]<<" ";
	}

	int srcleftover[nWifi];
	int destleftover[nWifi];
	int slosize=0;
	int dlosize=0;

	for(int i=0;i<sohsize;i++)
	{
		int flag=0;
		for(int j=0;j<cnsize;j++)
		{
			if(srconehop[i]==commonnodes[j])
			{
				flag=1;
			}
		}
		if(flag==0)
		{
			srcleftover[slosize]=srconehop[i];
			slosize++;
		}
	}

	for(int i=0;i<dohsize;i++)
	{
		int flag=0;
		for(int j=0;j<cnsize;j++)
		{
			if(destonehop[i]==commonnodes[j])
			{
				flag=1;
			}
		}
		if(flag==0)
		{
			destleftover[dlosize]=destonehop[i];
			dlosize++;
		}
	}

	std::cout<<"\nSource Left Over Nodes: ";
	for(int i=0;i<slosize;i++)
	{
		std::cout<<srcleftover[i]<<" ";
	}
	std::cout<<"\nDestination Left Over Nodes: ";
	for(int i=0;i<dlosize;i++)
	{
		std::cout<<destleftover[i]<<" ";
	}

	int no_of_faulty_nodes;
	int srcfaultynode[nWifi];
	int destfaultynode[nWifi];

//-----------------FAULTY NODE ASSIGNMENT---------------------------------
	if(sohsize<=dohsize)
	{
		no_of_faulty_nodes=floor(((sohsize-1)/3));
		std::cout<<"\nSource floor: "<<no_of_faulty_nodes;
		if(no_of_faulty_nodes!=0)
		{
			if(no_of_faulty_nodes<cnsize)
			{
				for(int i=0;i<no_of_faulty_nodes;i++)
				{
					int random=rand()%(cnsize);
					int flag=0;
					for(int k=0;k<i;k++)
					{
						if(commonnodes[random]==srcfaultynode[k])//if already present
						{
							flag=1;
							break;
						}
					}
					if(flag==1)
					{
						i=i-1;
						continue;
					}
					else
					{
						srcfaultynode[i]=commonnodes[random];
						destfaultynode[i]=commonnodes[random];
					}
				}
			}
			if(no_of_faulty_nodes==cnsize)
			{
				for(int i=0;i<cnsize;i++)
				{
					srcfaultynode[i]=commonnodes[i];
					destfaultynode[i]=commonnodes[i];
				}
			}
			if(no_of_faulty_nodes>cnsize)
			{
				int i;
				for(i=0;i<cnsize;i++)
				{
					srcfaultynode[i]=commonnodes[i];
					destfaultynode[i]=commonnodes[i];
				}
				int j=i;
				while(i<no_of_faulty_nodes)
				{
					int flag=0;
					int random1=rand()%(slosize);
					for(int k=0;k<i;k++)
					{
						if(srcleftover[random1]==srcfaultynode[k])
						{
							flag=1;
							break;
						}
					}
					if(flag==1)
					{
						continue;
					}
					else if(srcleftover[random1]!=destination)
					{
						srcfaultynode[i]=srcleftover[random1];
						i++;
					}
					else
						continue;
				}

				while(j<no_of_faulty_nodes)
				{
					int flag=0;
					int random2=rand()%(dlosize);
					for(int k=0;k<j;k++)
					{
						if(destleftover[random2]==destfaultynode[k])
						{
							flag=1;
							break;
						}
					}
					if(flag==1)
					{
						continue;
					}
					else if(destleftover[random2]!=source)
					{
						destfaultynode[j]=destleftover[random2];
						j++;
					}
					else
						continue;
				}
			}
		}
		std::cout<<"\nSource Faulty Nodes: ";
		for(int i=0;i<no_of_faulty_nodes;i++)
		{
			std::cout<<srcfaultynode[i]<<" ";
		}
		std::cout<<"\nDestination Faulty Nodes: ";
		for(int i=0;i<no_of_faulty_nodes;i++)
		{
			std::cout<<destfaultynode[i]<<" ";
		}
	}
	else
	{
		no_of_faulty_nodes=floor(((dohsize-1)/3));
		std::cout<<"\nDestination floor: "<<no_of_faulty_nodes;
		if(no_of_faulty_nodes!=0)
		{
			if(no_of_faulty_nodes<cnsize)
			{
				for(int i=0;i<no_of_faulty_nodes;i++)
				{
					int random=rand()%(cnsize);
					int flag=0;
					for(int k=0;k<i;k++)
					{
						if(commonnodes[random]==srcfaultynode[k])
						{
							flag=1;
							break;
						}
					}
					if(flag==1)
					{
						i=i-1;
						continue;
					}
					else
					{
						srcfaultynode[i]=commonnodes[random];
						destfaultynode[i]=commonnodes[random];
					}
				}
			}
		if(no_of_faulty_nodes==cnsize)
		{
			for(int i=0;i<cnsize;i++)
			{
				srcfaultynode[i]=commonnodes[i];
				destfaultynode[i]=commonnodes[i];
			}
		}
		if(no_of_faulty_nodes>cnsize)
		{
			int i;
			for(i=0;i<cnsize;i++)
			{
				srcfaultynode[i]=commonnodes[i];
				destfaultynode[i]=commonnodes[i];
			}
			int j=i;
			while(i<no_of_faulty_nodes)
			{
				int flag=0;
				int random1=rand()%(slosize);
				for(int k=0;k<i;k++)
				{
					if(srcleftover[random1]==srcfaultynode[k])
					{
						flag=1;
						break;
					}
				}
				if(flag==1)
				{
					continue;
				}
				else if(srcleftover[random1]!=destination)
				{
					srcfaultynode[i]=srcleftover[random1];
					i++;
				}
				else
					continue;
			}

			while(j<no_of_faulty_nodes)
			{
				int flag=0;
				int random2=rand()%(dlosize);
				for(int k=0;k<j;k++)
				{
					if(destleftover[random2]==destfaultynode[k])
					{
						flag=1;
						break;
					}
				}
				if(flag==1)
				{
					continue;
				}
				else if(destleftover[random2]!=source)
				{
					destfaultynode[j]=destleftover[random2];
					j++;
				}
				else
					continue;
			}
		}
	}
	std::cout<<"\nSource Faulty Nodes: ";
	for(int i=0;i<no_of_faulty_nodes;i++)
	{
		std::cout<<srcfaultynode[i]<<" ";
	}
	std::cout<<"\nDestination Faulty Nodes: ";
	for(int i=0;i<no_of_faulty_nodes;i++)
	{
		std::cout<<destfaultynode[i]<<" ";
	}

	}
	cout<<"\nFaulty Node 1, Majority :\n";
	majority_voting_func(1,freq,onehoparray,no_of_faulty_nodes,srcfaultynode,destfaultynode,destonehop2,srconehop2,source,destination,primary_user,pu,nodefrequencies);
	
	cout<<"\nFaulty Node 1, Existing :\n";
	existing_func(1,freq,source,destination,onehoparray,no_of_faulty_nodes,srcfaultynode,destfaultynode,destonehop2,srconehop2,primary_user,pu,nodefrequencies);
}

//--------------------FAULTY NODES END--------------------------------------


#endif /* SCRATCH_SINGLEHOPM1_H_ */

#ifndef SCRATCH_ALLL_H_
#define SCRATCH_ALLL_H_

void faulty_node2(int onehopcountarray[],int onehoparray[nWifi][nWifi],int freq[],int source,int destination,int primary_user[],int pu,int onehopcountwopu[], vector< vector<int> > nodefrequencies)
{
	int no_of_faulty_nodes;
	int actualnodes=nWifi-pu;
	no_of_faulty_nodes=floor(((actualnodes-1)/3));
	int faultynode[no_of_faulty_nodes];

	for(int i=0;i<no_of_faulty_nodes;i++)
	{
		int present=0;
		int random=rand()%nWifi;
		for(int k=0;k<i;k++)
		{
			if(random==faultynode[k])
			{
				present=1;
				break;
			}
		}
		if(present==0)
		{
			for(int k=0;k<pu;k++)
			{
				if(random==primary_user[k])
				{
					present=1;
					break;
				}
			}
		}
		if(present==1 || random==source || random==destination)
		{
			i=i-1;
			continue;
		}
		else
			faultynode[i]=random;
	}

	int srcfaultynode[nWifi],destfaultynode[nWifi],k=0,l=0;

	std::cout<<"\nFaulty Nodes: ";
	for(int i=0;i<no_of_faulty_nodes;i++)
	{
		std::cout<<faultynode[i]<<" ";
	
		if(onehoparray[source][faultynode[i]]==1) 
			srcfaultynode[k++]=faultynode[i];

		if(onehoparray[destination][faultynode[i]]==1) 
			destfaultynode[l++]=faultynode[i];
	}

	std::cout<<"\nSource Faulty Nodes: ";
	for(int i=0;i<k;i++)
	{
		std::cout<<srcfaultynode[i]<<" ";
	}

	std::cout<<"\nDestination Faulty Nodes: ";
	for(int i=0;i<l;i++)
	{
		std::cout<<destfaultynode[i]<<" ";
	}


	int n1=onehopcountarray[source]; //NUMBER OF NODES IN ONE HOP
	int n2=onehopcountarray[destination];
	int srconehop[n1];
	int destonehop[n2];
	int sohsize=0;
	int dohsize=0;

	for(int i=0;i<nWifi;i++)
	{
		if(onehoparray[source][i]==1)
		{
			srconehop[sohsize]=i;
			sohsize++;
		}

		if(onehoparray[destination][i]==1)
		{
			destonehop[dohsize]=i;
			dohsize++;
		}
	}
	std::cout<<"\nSource One Hop Nodes: ";
	for(int i=0;i<n1;i++)
	{
		std::cout<<srconehop[i]<<" ";
	}

	std::cout<<"\nDestination One Hop Nodes: ";
	for(int i=0;i<n2;i++)
	{
		std::cout<<destonehop[i]<<" ";
	}

	output0=0;
	output1=1;

	cout<<"\nFaulty Node 2, Majority :\n";
	majority_voting_func(2,freq,onehoparray,no_of_faulty_nodes,srcfaultynode,destfaultynode,destonehop,srconehop,source,destination,primary_user,pu,nodefrequencies);
	cout<<"\nFaulty Node 2, Existing :\n";
	existing_func(2,freq,source,destination,onehoparray,no_of_faulty_nodes,srcfaultynode,destfaultynode,destonehop,srconehop,primary_user,pu,nodefrequencies);
}



#endif /* SCRATCH_SINGLEHOPM2_H_ */

#ifndef SCRATCH_ALLLL_H_
#define SCRATCH_ALLLL_H_

void faulty_node3(int onehopcountarray[],int onehoparray[nWifi][nWifi],int freq[],
				  int source,int destination,int primary_user[],int pu,int onehopcountwopu[],vector< vector<int> > nodefrequencies)
{
	int no_of_faulty_nodes;
	int faultynode[nWifi];
	int cntfn=0;

	for(int i=0;i<nWifi;i++)
	{
		int e=onehopcountwopu[i];
		no_of_faulty_nodes=floor(((e-1)/3));

		if(no_of_faulty_nodes>0)
		{
			for(int j=0;j<no_of_faulty_nodes;j++)
			{
				int random=rand()%nWifi;
				int fnpresent1=0;
				if(onehoparray[i][random]!=1)
				{
					j=j-1;
					continue;
				}
				if(onehoparray[i][random]==1)
				{
					for(int k=0;k<cntfn;k++)
					{
						if(random==faultynode[k])
						{
//							std::cout<<"\nFor "<<i<<"-"<<random<<" already present.";
							fnpresent1=1;
							break;
						}
					}
					if(fnpresent1==1)
					{
						continue;
					}
					else
					{
						if(random!=source && random!=destination)
						{
							int present=0;
							for(int k=0;k<pu;k++)
							{
								if(random==primary_user[k])
								{
									present=1;
									break;
								}
							}
							if(present==0)
							{
//								std::cout<<"\n Faulty node for "<<i<<" is: "<<random;
								faultynode[cntfn]=random;
								cntfn++;
							}
							else
							{
								j=j-1;
								continue;
							}
						}
						else
						{
							j=j-1;
							continue;
						}
					}
				}
			}
		}
	}
	std::cout<<"\n\nTotal Faulty Nodes in the network: ";
	for(int i=0;i<cntfn;i++)
	{
		std::cout<<faultynode[i]<<" ";
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

	int srcfaultynode[nWifi],destfaultynode[nWifi],k=0,l=0;

	for(int i=0;i<cntfn;i++)
	{
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

	cout<<"\nFaulty Node 3, Majority :\n";
	majority_voting_func(3,freq,onehoparray,cntfn,srcfaultynode,destfaultynode,destonehop,srconehop,source,destination,primary_user,pu,nodefrequencies);
	cout<<"\nFaulty Node 3, Existing :\n";
	existing_func(3,freq,source,destination,onehoparray,cntfn,srcfaultynode,destfaultynode,destonehop,srconehop,primary_user,pu,nodefrequencies);

}


#endif /* SCRATCH_SINGLEHOPM3_H_ */


bool can_be_selected(int currentchoice, vector<int> usedfrequencies,int node, int primary_user[])
{
	for(int i=0;i<pu;i++){
		if(node == primary_user[i]){		
			int puactivity = rand()%2;
			if(puactivity == 0){
				return true;
			}
		}
	}

	int s = usedfrequencies.size();
	for(int i=0;i<s;i++){
		if(currentchoice == usedfrequencies[i])
			return false;	
	}
	return true;
}

void data_size(string datatype)
{
	if(datatype == "text"){
		requiredfrequency = 1;
		packets = 100;
	}

	if(datatype == "image"){
		requiredfrequency = 2;
		packets = 500;
	}

	if(datatype == "audio"){
		requiredfrequency = 4;
		packets = 1000;
	}

	if(datatype == "video"){
		requiredfrequency = 8;
		packets = 2500;
	}
}


bool sourceOneHop(int currentFreq, int source, int onehoparray[nWifi][nWifi], int freq[], int primary_user[], vector< vector<int> > nodefrequencies){

	for(int i=0;i<nWifi;i++)
		{
		if(onehoparray[source][i]==1)
		{
			if(!can_be_selected(currentFreq,nodefrequencies[i],i,primary_user))
			{
				return false;
			}
		}
	}
	return true;
}

bool destinationOneHop(int currentFreq, int destination, int onehoparray[nWifi][nWifi], int freq[], int primary_user[], vector< vector<int> > nodefrequencies){

	for(int i=0;i<nWifi;i++)
	{
		if(onehoparray[destination][i]==1)
		{
			if(!can_be_selected(currentFreq,nodefrequencies[i],i,primary_user))
			{
				return false;
			}
		}
	}
	return true;
}

//method : 0-Majority, 1-existing
bool sourceTwoHop(int cf, bool method, int source, int destination, int currentFreq, int no_of_faulty_nodes, int srcfaultynode[], int primary_user[], int onehoparray[nWifi][nWifi], int freq[], vector< vector<int> > nodefrequencies){

	//cout<<cf;
	int sourcetwohop[nWifi];
	int count=0;
	int one=0;
	int zero=0;
	for(int i=0;i<nWifi;i++)//source one hop
	{
		int fnode=0;
		for(int k=0;k<no_of_faulty_nodes;k++)
		{
			if(i==srcfaultynode[k])
			{
				int Answer;
				if(cf==3 and method == 1){
					Answer = (rand()%10+1)>8;
				}else{
					Answer = rand()%2;
				}
				sourcetwohop[count]=Answer;
				count++;
				fnode=1;
				break;
			}
		}
		if(fnode==1)
			continue;


		if(onehoparray[source][i]==1)
		{
			int present=0;
			for(int k=0;k<pu;k++)
			{
				if(i==primary_user[k])
				{
					present=1;
					break;
				}
			}
			if(present==0)
			{
				int f3=0;
				for(int j=0;j<nWifi;j++)//src one hop one hop
				{
					if(onehoparray[i][j]==1 && j!=source && onehoparray[source][j]!=1 && j!=destination)
					{
						if(!can_be_selected(currentFreq,nodefrequencies[j],j,primary_user))
						{
							f3=1;
						}
					}
				}
				if(f3==1)
				{
					sourcetwohop[count]=1;
					count++;
				}
				else
				{
					sourcetwohop[count]=0;
					count++;
				}
			}
			else
			{
				sourcetwohop[count]=-1;
				count++;
			}
		}
	}

	for(int z=0;z<count;z++)
	{
		if(sourcetwohop[z]==1)
			one++;
		if(sourcetwohop[z]==0)
			zero++;
	}
	
	if(method==0)
		return (one < zero);
	else
		return (one==0);
}

//method : 0-Majority, 1-existing
bool destinationTwoHop(int cf, bool method, int source, int destination, int currentFreq, int no_of_faulty_nodes, int destfaultynode[], int primary_user[], int onehoparray[nWifi][nWifi], int freq[], vector< vector<int> > nodefrequencies){

	//cout<<cf;
	int destinationtwohop[nWifi];
	int count=0;
	int one=0;
	int zero=0;
	for(int i=0;i<nWifi;i++)//source one hop
	{
		int fnode=0;
		for(int k=0;k<no_of_faulty_nodes;k++)
		{
			if(i==destfaultynode[k])
			{
				int Answer;
				if(cf==3 and method == 1){
					Answer = (rand()%10+1)>8;
				}else{
					Answer = rand()%2;
				}
				destinationtwohop[count]=Answer;
				count++;
				fnode=1;
				break;
			}
		}
		if(fnode==1)
			continue;


		if(onehoparray[destination][i]==1)
		{
			int present=0;
			for(int k=0;k<pu;k++)
			{
				if(i==primary_user[k])
				{
					present=1;
					break;
				}
			}
			if(present==0)
			{
				int f3=0;
				for(int j=0;j<nWifi;j++)//src one hop one hop
				{
					if(onehoparray[i][j]==1 && j!=source && onehoparray[source][j]!=1 && j!=destination)
					{
						if(!can_be_selected(currentFreq,nodefrequencies[j],j,primary_user))
						{
							f3=1;
						}
					}
				}
				if(f3==1)
				{
					destinationtwohop[count]=1;
					count++;
				}
				else
				{
					destinationtwohop[count]=0;
					count++;
				}
			}
			else
			{
				destinationtwohop[count]=-1;
				count++;
			}
		}
	}

	for(int z=0;z<count;z++)
	{
		if(destinationtwohop[z]==1)
			one++;
		if(destinationtwohop[z]==0)
			zero++;
	}
	

	if(method==0)
		return (one < zero);
	else
		return (one==0);
}

bool checkIfValid(int source, int destination, int currentFreq, int onehoparray[nWifi][nWifi], int freq[]){

	for(int i=0;i<nWifi;i++)//source one hop
	{
		if(i==source || i==destination) continue;
		if(onehoparray[destination][i]==1 || onehoparray[source][i]==1)
		{
			if(currentFreq == freq[i]) return false;
		}
	}
	
	for(int i=0;i<nWifi;i++)//source one hop
	{
		if(onehoparray[destination][i]==0 && onehoparray[source][i]==0) continue;
		for (int j = 0; j < nWifi; j++)
		{
			if(j==source || j==destination) continue;
			if(onehoparray[i][j]==1)
			{
				if(currentFreq == freq[j]) return false;
			}
		}
	}

	return true;
}



void majority_voting_func(int cf, int freq[],int onehoparray[nWifi][nWifi],int no_of_faulty_nodes,
						  int srcfaultynode[],int destfaultynode[],int destonehop2[],int srconehop2[],
						  int source,int destination,int primary_user[],int pu,vector< vector<int> > nodefrequencies)
{
//	cout<<"Hello1 "<<requiredfrequency <<endl;
	bool flag[requiredfrequency]={};
	int freqAlloted[requiredfrequency]={};
	int tatolAttempts=0, missDetection=0, falseAlarm=0;
	for (int i = 0; i < requiredfrequency; ++i){
		freqAlloted[i]=-1;
	}
	srand(time(0));
	int packetsLeft=packets;
	int TotalIterations=0;
	while(packetsLeft>0){
		TotalIterations++;
		int localAttempts=0;
		for(int i=0;i<requiredfrequency;i++){
			int it=MAX_ATTEMPT;
			if(flag[i]==false){
				bool valid;
				while(it--){
					int currentFreq;
					while(true){
						currentFreq = rand()% FREQUENCY;
						bool valid = true;
						for(int j=0;j<requiredfrequency;j++){
							if(j<i){
								if(currentFreq == freqAlloted[j]){
									valid=false;
									break;
								}
							}
							else{
								if(flag[j]==true and  currentFreq == freqAlloted[j]){
									valid=false;
									break;
								}
							}
						}
						if(valid)
							break;
					}
					valid = true;
					valid = valid && sourceOneHop(currentFreq, source, onehoparray, freq, primary_user, nodefrequencies);
					valid = valid && destinationOneHop(currentFreq, destination, onehoparray, freq, primary_user, nodefrequencies);
					valid = valid && sourceTwoHop(cf, 0, source, destination, currentFreq, no_of_faulty_nodes, destfaultynode, primary_user, onehoparray, freq, nodefrequencies);
					valid = valid && destinationTwoHop(cf, 0, source, destination, currentFreq, no_of_faulty_nodes, destfaultynode, primary_user, onehoparray, freq, nodefrequencies);
					if(valid){
						freqAlloted[i]=currentFreq;
						break;
					}
					else{
						falseAlarm+=(checkIfValid(source, destination, currentFreq, onehoparray, freq)==true);
					}
				}
				if(valid == false){
					freqAlloted[i]=-1;
				}
			}
			localAttempts = max(localAttempts,MAX_ATTEMPT-it);
		}

		//bool allDone = true;
		tatolAttempts+=localAttempts;

		for(int i=0;i<requiredfrequency;i++){
			//cout<<freqAlloted[i]<<"\t";
			if(flag[i]==false){
				bool f;
				if(freqAlloted[i] == -1) f=false;	
				else{
					f = checkIfValid(source, destination, freqAlloted[i], onehoparray, freq);
					missDetection+=(f==false);
				}
				flag[i] = f;
				//allDone = allDone && f;
			}
			if(flag[i])
				packetsLeft--;
		}
		
	}
	
	PrT=rand()%8;
	PT=dis_s_d/Velocity;
	delay=PT+QT+PrT;
	delay+=tatolAttempts+packets*TT;

	AAT[2*cf-2]+=tatolAttempts;
	cout<<endl<<"Total Attempt : "<<tatolAttempts<<endl;	
	MD[2*cf-2]+=missDetection;
	cout<<"Miss Detection : "<<missDetection<<endl;
	FA[2*cf-2]+=falseAlarm;
	cout<<"False Alarm : "<<falseAlarm<<endl;
	D[2*cf-2]+=delay;
	cout<<"Delay : "<<delay<<endl;
	S[2*cf-2]+=((float)packets/(TotalIterations*requiredfrequency))*100;
	cout<<"Success Percentage : "<<((float)packets/(TotalIterations*requiredfrequency))*100<<endl;
}
//------------------MAJORITY VOTING ENDS------------------------------------------

//------------------EXISTING METHOD-----------------------------------------

void existing_func(int cf, int freq[],int source,int destination,int onehoparray[nWifi][nWifi],
				   int no_of_faulty_nodes,int srcfaultynode[],int destfaultynode[],int destonehop2[],
				   int srconehop2[],int primary_user[],int pu,vector< vector<int> > nodefrequencies)
{
//	cout<<"Hello2 "<<requiredfrequency <<endl;
	bool flag[requiredfrequency]={};
	int freqAlloted[requiredfrequency]={};
	int tatolAttempts=0, missDetection=0, falseAlarm=0;
	for (int i = 0; i < requiredfrequency; ++i){
		freqAlloted[i]=-1;
	}
	srand(time(0));
	int packetsLeft=packets;
	int TotalIterations=0;
	while(packetsLeft>0){
		TotalIterations++;
		int localAttempts=0;
		for(int i=0;i<requiredfrequency;i++){
			int it=MAX_ATTEMPT;
			if(flag[i]==false){
				bool valid;
				while(it--){
					int currentFreq;
					while(true){
						currentFreq = rand()% FREQUENCY;
						bool valid = true;
						for(int j=0;j<requiredfrequency;j++){
							if(j<i){
								if(currentFreq == freqAlloted[j]){
									valid=false;
									break;
								}
							}
							else{
								if(flag[j]==true and  currentFreq == freqAlloted[j]){
									valid=false;
									break;
								}
							}
						}
						if(valid)
							break;
					}
					valid = true;
					valid = valid && sourceOneHop(currentFreq, source, onehoparray, freq, primary_user, nodefrequencies);
					valid = valid && destinationOneHop(currentFreq, destination, onehoparray, freq, primary_user, nodefrequencies);
					valid = valid && sourceTwoHop(cf, 1, source, destination, currentFreq, no_of_faulty_nodes, destfaultynode, primary_user, onehoparray, freq, nodefrequencies);
					valid = valid && destinationTwoHop(cf, 1, source, destination, currentFreq, no_of_faulty_nodes, destfaultynode, primary_user, onehoparray, freq, nodefrequencies);
					//cout<<currentFreq<<",";
					if(valid){
						freqAlloted[i]=currentFreq;
						//cout<<"\t";
						break;
					}
					else{
						falseAlarm+=(checkIfValid(source, destination, currentFreq, onehoparray, freq)==true);
					}

				}
				if(valid == false){
					//cout<<"-1,\t";
					freqAlloted[i]=-1;
				}
			}
			localAttempts = max(localAttempts,MAX_ATTEMPT-it);
		}
		//cout<<endl;
		//bool allDone = true;
		tatolAttempts+=localAttempts;

	//	if (tatolAttempts>50) return;

		for(int i=0;i<requiredfrequency;i++){
			//cout<<freqAlloted[i]<<"\t";
			if(flag[i]==false){
				bool f;
				if(freqAlloted[i] == -1) f=false;	
				else{
					f = checkIfValid(source, destination, freqAlloted[i], onehoparray, freq);
					missDetection+=(f==false);
				}
				flag[i] = f;
				//allDone = allDone && f;
			}
			if(flag[i])
				packetsLeft--;
		}
	}

	PrT=rand()%8;
	PT=dis_s_d/Velocity;
	delay=PT+QT+PrT;
	delay+=tatolAttempts+packets*TT;

	AAT[2*cf-1]+=tatolAttempts;
	cout<<endl<<"Total Attempt : "<<tatolAttempts<<endl;
	MD[2*cf-1]+=missDetection;
	cout<<"Miss Detection : "<<missDetection<<endl;
	FA[2*cf-1]+=falseAlarm;
	cout<<"False Alarm : "<<falseAlarm<<endl;
	D[2*cf-1]+=delay;
	cout<<"Delay : "<<delay<<endl;
	S[2*cf-1]+=((float)packets/(TotalIterations*requiredfrequency))*100;
	cout<<"Success Percentage : "<<((float)packets/(TotalIterations*requiredfrequency))*100<<endl;
}


#define nWifi 110
#define Velocity 299792458
#define TT 1
#define MAX_PACKET_ATTEMPT 10000

using namespace std;

int FA[6]={};
int MD[6]={};
int AAT[6]={};
int D[6]={};
int S[6]={};

int FREQUENCY = 25;
int MAX_ATTEMPT = 15;

double dis_s_d=0,QT=0;
double PT,PrT,delay;

double range;
string datatype;
int packets;
int datasize;
int temp2=0;
int pu=nWifi / 10;
int requiredfrequency;

int run,totrun=0;
int sum=0,ss=0,md_sum=0,fa_sum=0;
int false_alarm_f1;
int sum1=0,ss1=0,md_sum1=0,fa_sum1=0;
int miss_detection,false_alarm;
int attempt2;
int a_success_status,b_success_status;
int output0;
int output1;
int tsum,tsum1,tmd_sum,tmd_sum1,tfa_sum,tfa_sum1;
int md_sum_all1=0,fa_sum_all1=0,md_sum_all2=0,fa_sum_all2=0;
int locked[nWifi];
int lock;

int packetattempt=0,packetattempt1=0,packetattempt2=0,packetattempt3=0,packetattempt4=0,packetattempt5=0;
int sentpackets=0,sentpackets1=0,sentpackets2=0,sentpackets3=0,sentpackets4=0,sentpackets5=0;

int sum2=0,ss2=0,md_sum2=0,fa_sum2=0;
int false_alarm_f;
int sum3=0,ss3=0,md_sum3=0,fa_sum3=0;
int tsum2,tsum3,tmd_sum2,tmd_sum3,tfa_sum2,tfa_sum3;
int c_success_status,d_success_status;
int md_sum_all3=0,fa_sum_all3=0,md_sum_all4=0,fa_sum_all4=0;

int sum4=0,ss4=0,md_sum4=0,fa_sum4=0;
int false_alarm_f2;
int sum5=0,ss5=0,md_sum5=0,fa_sum5=0;
int tsum4,tmd_sum4,tfa_sum4,tsum5,tmd_sum5,tfa_sum5;
int e_success_status,f_success_status;
int md_sum_all5=0,fa_sum_all5=0,md_sum_all6=0,fa_sum_all6=0;

void print()
{
	std::fstream myfile;
	
	if(datatype == "text"){
      myfile.open ("text.xlsx",std::fstream::app);
	}

	if(datatype == "image"){
      myfile.open ("image.xlsx",std::fstream::app);
	}

	if(datatype == "audio"){
      myfile.open ("audio.xlsx",std::fstream::app);
	}

	if(datatype == "video"){
      myfile.open ("video.xlsx",std::fstream::app);
	}	

	myfile << "\n";
	//myfile << "SU,PU,Success%,Avg.Attempt,Avg.Miss Detection,Avg.False Alarm,Delay,,";

	cout<<"\n\nRun: "<<run;
	int totalrun=run-totrun;
	cout<<"\n\nMax Nodes: "<<temp2;	

	cout<<"\n\nVersion 1:";
	PrT=rand()%8;
	PT=dis_s_d/Velocity;
	delay=PT+TT+QT+PrT;
	delay=delay + sum + (packetattempt-packets)*MAX_ATTEMPT;
	cout<<"\n--------------";
	cout<<"\nNumber of nodes: "<<nWifi;
	cout<<"\nPackets sent: "<<packets;
	cout<<"\nPacket Send Attempts: "<<packetattempt;
	cout<<"\nActual run: "<<totalrun;
	cout<<"\nSS(No. of success): "<<ss;

	float ssc=(float)sentpackets/packetattempt;
	float sscent=ssc*100;
	cout<<"\nSuccess Percentage: "<<sscent<<"%";

	cout<<"\nTotal Attempts (Successful Transmission): "<<sum;
	float avg_attempt=(float)sum/ss;
	cout<<"\nAverage Attempt: "<<avg_attempt;//<<ceil(avg_attempt);

	cout<<"\nMiss Detection (for all sent packets and selected frequencies ): "<<md_sum;
	float md=(float)md_sum/ss;
	//float mdcent=md*100;
	//cout<<"\nMiss Detection Percentage: "<<mdcent<<"%";
	cout<<"\nAverage Miss Detection (for all sent packets and selected frequencies ): "<<md;

	cout<<"\nFalse Alarm (for all sent packets and selected frequencies ): "<<fa_sum;
	float fa=(float)fa_sum/ss;
	cout<<"\nAverage False Alarm (for all sent packets and selected frequencies ): "<<fa;

	cout<<"\nMiss Detection All: "<<md_sum_all1;
	float md_all=(float)md_sum_all1/packetattempt;
	cout<<"\nAverage Miss Detection All: "<<md_all;

	cout<<"\nFalse Alarm All: "<<fa_sum_all1;
	float fa_all=(float)fa_sum_all1/packetattempt;
	cout<<"\nAverage False Alarm All: "<<fa_all;
	cout<<"\nDelay: "<<delay<<endl;

	myfile << FREQUENCY <<","<<MAX_ATTEMPT<<","<< range <<",,"<< nWifi-pu<<","<<pu<<","<<sscent<<","<<avg_attempt<<","<<md<<","<<fa<<","<<delay<<",,";

	//----------------------------------------------------------------

	cout<<"\n\nVersion 2:";
	PrT=rand()%8;
	PT=dis_s_d/Velocity;
	delay=PT+TT+QT+PrT;
	delay=delay + sum1 + (packetattempt1-packets)*MAX_ATTEMPT;
	cout<<"\n--------------";
	cout<<"\nNumber of nodes: "<<nWifi;
	cout<<"\nPackets sent: "<<packets;
	cout<<"\nPacket Send Attempts: "<<packetattempt1;
	cout<<"\nActual run: "<<totalrun;
	cout<<"\nSS1(No. of success): "<<ss1;

	float ssc1=(float)sentpackets1/packetattempt1;
	float sscent1=ssc1*100;
	cout<<"\nSuccess Percentage: "<<sscent1<<"%";

	cout<<"\nTotal Attempts (Successful Transmission): "<<sum1;
	float avg_attempt1=(float)sum1/ss1;
	cout<<"\nAverage Attempt: "<<avg_attempt1;//<<ceil(avg_attempt);

	cout<<"\nMiss Detection (for all sent packets and selected frequencies ): "<<md_sum1;
	float md1=(float)md_sum1/ss1;
		//float mdcent=md*100;
		//cout<<"\nMiss Detection Percentage: "<<mdcent<<"%";
	cout<<"\nAverage Miss Detection (for all sent packets and selected frequencies ): "<<md1;

	cout<<"\nFalse Alarm (for all sent packets and selected frequencies ): "<<fa_sum1;
	float fa1=(float)fa_sum1/ss1;
	cout<<"\nAverage False Alarm (for all sent packets and selected frequencies ): "<<fa1;

	cout<<"\nMiss Detection All: "<<md_sum_all2;
	float md_all1=(float)md_sum_all2/packetattempt1;
	cout<<"\nAverage Miss Detection All: "<<md_all1;

	cout<<"\nFalse Alarm All: "<<fa_sum_all2;
	float fa_all1=(float)fa_sum_all2/packetattempt1;
	cout<<"\nAverage False Alarm All: "<<fa_all1;

	cout<<"\nDelay: "<<delay<<endl;

	myfile << nWifi-pu<<","<<pu<<","<<sscent1<<","<<avg_attempt1<<","<<md1<<","<<fa1<<","<<delay<<",,";

	//----------------------------------------------------------------

	cout<<"\n\nVersion 3:";
	PrT=rand()%8;
	PT=dis_s_d/Velocity;
	delay=PT+TT+QT+PrT;
	delay=delay + sum2 + (packetattempt2-packets)*MAX_ATTEMPT;
	cout<<"\n--------------";
	cout<<"\nNumber of nodes: "<<nWifi;
	cout<<"\nPackets sent: "<<packets;
	cout<<"\nPacket Send Attempts: "<<packetattempt2;
	cout<<"\nActual run: "<<totalrun;
	cout<<"\nSS2(No. of success): "<<ss2;

	float ssc2=(float)sentpackets2/packetattempt2;
	float sscent2=ssc2*100;
	cout<<"\nSuccess Percentage: "<<sscent2<<"%";

	cout<<"\nTotal Attempts (Successful Transmission): "<<sum2;
	float avg_attempt2=(float)sum2/ss2;
	cout<<"\nAverage Attempt: "<<avg_attempt2;//<<ceil(avg_attempt);

	cout<<"\nMiss Detection (for all sent packets and selected frequencies ): "<<md_sum2;
	float md2=(float)md_sum2/ss2;
		//float mdcent=md*100;
		//cout<<"\nMiss Detection Percentage: "<<mdcent<<"%";
	cout<<"\nAverage Miss Detection (for all sent packets and selected frequencies ): "<<md2;

	cout<<"\nFalse Alarm (for all sent packets and selected frequencies ): "<<fa_sum2;
	float fa2=(float)fa_sum2/ss2;
	cout<<"\nAverage False Alarm (for all sent packets and selected frequencies ): "<<fa2;

	cout<<"\nMiss Detection All: "<<md_sum_all3;
	float md_all2=(float)md_sum_all3/packetattempt2;
	cout<<"\nAverage Miss Detection All: "<<md_all2;

	cout<<"\nFalse Alarm All: "<<fa_sum_all3;
	float fa_all2=(float)fa_sum_all3/packetattempt2;
	cout<<"\nAverage False Alarm All: "<<fa_all2;

	cout<<"\nDelay: "<<delay<<endl;

	myfile << nWifi-pu<<","<<pu<<","<<sscent2<<","<<avg_attempt2<<","<<md2<<","<<fa2<<","<<delay<<",,";

	//-----------------------------------------------------------

	cout<<"\n\nVersion 4:";
	PrT=rand()%8;
	PT=dis_s_d/Velocity;
	delay=PT+TT+QT+PrT;
	delay=delay + sum3 + (packetattempt3-packets)*MAX_ATTEMPT;
	cout<<"\n--------------";
	cout<<"\nNumber of nodes: "<<nWifi;
	cout<<"\nPackets sent: "<<packets;
	cout<<"\nPacket Send Attempts: "<<packetattempt3;
	cout<<"\nActual run: "<<totalrun;
	cout<<"\nSS3(No. of success): "<<ss3;

	float ssc3=(float)sentpackets3/packetattempt3;
	float sscent3=ssc3*100;
	cout<<"\nSuccess Percentage: "<<sscent3<<"%";

	cout<<"\nTotal Attempts (Successful Transmission): "<<sum3;
	float avg_attempt3=(float)sum3/ss3;
	cout<<"\nAverage Attempt: "<<avg_attempt3;//<<ceil(avg_attempt);

	cout<<"\nMiss Detection (for all sent packets and selected frequencies ): "<<md_sum3;
	float md3=(float)md_sum3/ss3;
			//float mdcent=md*100;
			//cout<<"\nMiss Detection Percentage: "<<mdcent<<"%";
	cout<<"\nAverage Miss Detection (for all sent packets and selected frequencies ): "<<md3;
	
	cout<<"\nFalse Alarm (for all sent packets and selected frequencies ): "<<fa_sum3;
	float fa3=(float)fa_sum3/ss3;
	cout<<"\nAverage False Alarm (for all sent packets and selected frequencies ): "<<fa3;

	cout<<"\nMiss Detection All: "<<md_sum_all4;
	float md_all3=(float)md_sum_all4/packetattempt3;
	cout<<"\nAverage Miss Detection All: "<<md_all3;

	cout<<"\nFalse Alarm All: "<<fa_sum_all4;
	float fa_all3=(float)fa_sum_all4/packetattempt3;
	cout<<"\nAverage False Alarm All: "<<fa_all3;

	cout<<"\nDelay: "<<delay<<endl;

	myfile << nWifi-pu<<","<<pu<<","<<sscent3<<","<<avg_attempt3<<","<<md3<<","<<fa3<<","<<delay<<",,";

	//--------------------------------------------------------

	cout<<"\n\nVersion 5:";
	PrT=rand()%8;
	PT=dis_s_d/Velocity;
	delay=PT+TT+QT+PrT;
	delay=delay + sum4 + (packetattempt4-packets)*MAX_ATTEMPT;
	cout<<"\n--------------";
	cout<<"\nNumber of nodes: "<<nWifi;
	cout<<"\nPackets sent: "<<packets;
	cout<<"\nPacket Send Attempts: "<<packetattempt4;
	cout<<"\nActual run: "<<totalrun;
	cout<<"\nSS4(No. of success): "<<ss4;

	float ssc4=(float)sentpackets4/packetattempt4;
	float sscent4=ssc4*100;
	cout<<"\nSuccess Percentage: "<<sscent4<<"%";

	cout<<"\nTotal Attempts (Successful Transmission): "<<sum4;
	float avg_attempt4=(float)sum4/ss4;
	cout<<"\nAverage Attempt: "<<avg_attempt4;//<<ceil(avg_attempt);

	cout<<"\nMiss Detection (for all sent packets and selected frequencies ): "<<md_sum4;
	float md4=(float)md_sum4/ss4;
			//float mdcent=md*100;
			//cout<<"\nMiss Detection Percentage: "<<mdcent<<"%";
	cout<<"\nAverage Miss Detection (for all sent packets and selected frequencies ): "<<md4;

	cout<<"\nFalse Alarm (for all sent packets and selected frequencies ): "<<fa_sum4;
	float fa4=(float)fa_sum4/ss4;
	cout<<"\nAverage False Alarm (for all sent packets and selected frequencies ): "<<fa4;

	cout<<"\nMiss Detection All: "<<md_sum_all5;
	float md_all4=(float)md_sum_all5/packetattempt4;
	cout<<"\nAverage Miss Detection All: "<<md_all4;

	cout<<"\nFalse Alarm All: "<<fa_sum_all5;
	float fa_all4=(float)fa_sum_all5/packetattempt4;
	cout<<"\nAverage False Alarm All: "<<fa_all4;

	cout<<"\nDelay: "<<delay<<endl;

	myfile << nWifi-pu<<","<<pu<<","<<sscent4<<","<<avg_attempt4<<","<<md4<<","<<fa4<<","<<delay<<",,";

	//-------------------------------------------------------------

	cout<<"\n\nVersion 6:";
	PrT=rand()%8;
	PT=dis_s_d/Velocity;
	delay=PT+TT+QT+PrT;
	delay=delay + sum5 + (packetattempt5-packets)*MAX_ATTEMPT;
	cout<<"\n--------------";
	cout<<"\nNumber of nodes: "<<nWifi;
	cout<<"\nPackets sent: "<<packets;
	cout<<"\nPacket Send Attempts: "<<packetattempt5;
	cout<<"\nActual run: "<<totalrun;
	cout<<"\nSS5(No. of success): "<<ss5;

	float ssc5=(float)sentpackets5/packetattempt5;
	float sscent5=ssc5*100;
	cout<<"\nSuccess Percentage: "<<sscent5<<"%";

	cout<<"\nTotal Attempts (Successful Transmission): "<<sum5;
	float avg_attempt5=(float)sum5/ss5;
	cout<<"\nAverage Attempt: "<<avg_attempt5;//<<ceil(avg_attempt);

	cout<<"\nMiss Detection (for all sent packets and selected frequencies ): "<<md_sum5;
	float md5=(float)md_sum5/ss5;
				//float mdcent=md*100;
				//cout<<"\nMiss Detection Percentage: "<<mdcent<<"%";
	cout<<"\nAverage Miss Detection (for all sent packets and selected frequencies ): "<<md5;

	cout<<"\nFalse Alarm (for all sent packets and selected frequencies ): "<<fa_sum5;
	float fa5=(float)fa_sum5/ss5;
	cout<<"\nAverage False Alarm (for all sent packets and selected frequencies ): "<<fa5;

	cout<<"\nMiss Detection All: "<<md_sum_all6;
	float md_all5=(float)md_sum_all6/packetattempt5;
	cout<<"\nAverage Miss Detection All: "<<md_all5;

	cout<<"\nFalse Alarm All: "<<fa_sum_all6;
	float fa_all5=(float)fa_sum_all6/packetattempt5;
	cout<<"\nAverage False Alarm All: "<<fa_all5;
	cout<<"\nDelay: "<<delay<<endl;

	myfile << nWifi-pu<<","<<pu<<","<<sscent5<<","<<avg_attempt5<<","<<md5<<","<<fa5<<","<<delay<<",,";

	cout<<"Range : "<<range<<endl;

	myfile.close();

}

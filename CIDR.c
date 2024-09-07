#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void get_data();
int verification_IP_Address(int num1, int num2, int num3, int num4, int MSR_value);
int *get_IP_bin (int num1, int num2, int num3, int num4);
int *get_netmask_bin (int MSR_value);
int *default_MSR (int *netmask_bin, int *IP_bin);
int *get_broadcast(int MSR_value, int *netmask_bin, int *IP_bin);
int *power ();
void *convertion(int *netmask_bin, int *IP_bin, int *network_address_bin, int *broadcast_bin, int *pow);

int main(){
    get_data();
    return 0;
}

                                    //prends l'adresse IP et le MSR 

void get_data(){
    char data[50],
        IP_Address[20]={0},
        MSR[10]={0},
        n1[10]={0},
        n2[10]={0},
        n3[10]={0},
        n4[10]={0};;
    
    int *broadcast_bin=NULL,
        *IP_bin=NULL,
        *netmask_bin=NULL,
        *network_address_bin=NULL,
        *pow=NULL,
        count=0,
        count1=0,
        count_char=0,
        i,
        data_length=0,
        MSR_value=0,
        num1=0,
        num2=0,
        num3=0,
        num4=0,
        true_value=0,
        true_count=0,
        verify=0;

    while(true_value!=1){
        printf("\tCIDR(Classess Inter-Domain Routing) \n");
        printf("Enter IP Address and netmask(0-32), e.g:xxx.xxx.xxx.xxx/x'\n");
        printf("=>"),
        scanf("%s", data);
        data_length=strlen(data);
        for(i=0; i<data_length; i++){
            if(data[i]=='.'){
                count++;
            }
        }
        for(i=0; i<data_length; i++){
            if(data[i]=='/'){
                count1++;
            }
        }
        for(i=0; i<data_length; i++){
            if((data[i]>='a' && data[i]<='z') || (data[i]>='A' && data[i]<='Z')){
                count_char=1;
            }
        }
        sscanf(data, "%99[^/]/%99s", IP_Address, MSR);
        sscanf(data, "%99[^.].%99[^.].%99[^.].%99s", n1, n2, n3, n4);
        
        num1=atoi(n1);
        num2=atoi(n2);
        num3=atoi(n3);
        num4=atoi(n4);
        MSR_value=atoi(MSR);

        //printf("%d.%d.%d.%d\n", num1, num2, num3, num4);----------teste---------------//
        
        verify=verification_IP_Address(num1, num2, num3, num4, MSR_value);
        
        if((data_length>=9 && data_length<=18) &&
            count==3 && 
            count1==1 && 
            verify==1 &&
            count_char==0){
            true_value=1;
        }else{
            true_value=0;
            count=0;
            count1=0;
            count_char=0;
            printf("\n");
        } 
    }

    IP_bin=get_IP_bin(num1, num2, num3, num4);
    netmask_bin=get_netmask_bin(MSR_value);
    network_address_bin=default_MSR(netmask_bin, IP_bin);
    broadcast_bin=get_broadcast(MSR_value, netmask_bin, IP_bin);
    pow=power();
    convertion(netmask_bin, IP_bin, network_address_bin, broadcast_bin, pow);


//----------------------------------teste----------------------------------------------//

    /*printf("IP Address :");
    for(i=0; i<32; i++){
        printf("%d", IP_bin[i]);
    }
    printf("\n__________________________________\n");
    printf("Netmask    :");
    for(i=0; i<32; i++){
        printf("%d", netmask_bin[i]);
    }
    printf("\n__________________________________\n");
    printf("True netmask:");
    for(i=0; i<32; i++){
        printf("%d", network_address_bin[i]);
    }
    printf("\n__________________________________\n");
    printf("Broadcast   :");
    for(i=0; i<32; i++){
        printf("%d", broadcast_bin[i]);
    }
    printf("\n__________________________________\n");

    printf("\n============================================\n");
    for(i=0; i<8; i++){
        printf("%d\n", pow[i]);
    }
    printf("\n============================================\n");

    convertion(netmask_bin, IP_bin, network_address_bin, broadcast_bin, pow);*/
//----------------------------------teste----------------------------------------------//

}

                                                //verification de l'adresse IP

int verification_IP_Address(int num1, int num2, int num3, int num4, int MSR_value){
    int verification=0;
    if((num1>=0 && num1<=255)&&
        (num2>=0 && num2<=255)&&
        (num3>=0 && num3<=255)&&
        (num4>=0 && num4<=255)&&
        (MSR_value>=0 && MSR_value<=32)){
            verification=1; //IP valid
    }else{
        verification=0; //IP invalid
    }
    return (verification);
}

                                                //convertion de l'adresse IP en binaire 
int *get_IP_bin (int num1, int num2, int num3, int num4){
    int *value1=NULL,
        *value2=NULL,
        *value3=NULL,
        *value4=NULL,
        i,
        j,
        k,
        *IP_ad=NULL,
        bin_IP1=0,
        bin_IP2=0,
        bin_IP3=0,
        bin_IP4=0,
        b=2,
        c=0;

    value1=(int *)malloc(8*sizeof(int));
    value2=(int *)malloc(8*sizeof(int));
    value3=(int *)malloc(8*sizeof(int));
    value4=(int *)malloc(8*sizeof(int));
    IP_ad=(int *)malloc(32*sizeof(int));

    for(i=0; num1!=0, num2!=0, num3!=0, num4!=0; i++){
        bin_IP1=num1/b;
        bin_IP2=num2/b;
        bin_IP3=num3/b;
        bin_IP4=num4/b;
        value1[i]=num1%b;
        value2[i]=num2%b;
        value3[i]=num3%b;
        value4[i]=num4%b;
        num1=bin_IP1;
        num2=bin_IP2;
        num3=bin_IP3;
        num4=bin_IP4;
    }
    i=8;
    //printf("IP_Address=");
    for(j=i-1, k=0; j>=0; j--, k++){
        IP_ad[k]=value1[j];
        //printf("%d", IP_ad[k]);
    }
    printf("\n");
    for(j=i-1, k=8; j>=0; j--, k++){
        //printf("%d", value2[j]);
        IP_ad[k]=value2[j];
    }
    //printf(".");
    for(j=i-1, k=16; j>=0; j--, k++){
        //printf("%d", value3[j]);
        IP_ad[k]=value3[j];
    }
    //printf(".");
    for(j=i-1, k=24; j>=0; j--, k++){
        //printf("%d", value4[j]);
        IP_ad[k]=value4[j];
    }
    return (IP_ad);
}

                                                //convertion du masque de sous réseaux en binaire

int *get_netmask_bin (int MSR_value){
    int *MSR_bin=NULL,
        i,
        j;
    MSR_bin=(int *)malloc(32*sizeof(int));
    for(i=0; i<32; i++){
        for(j=0; j<MSR_value; j++){
            MSR_bin[j]=1;
        }
        for(j=MSR_value; j<32; j++){
            MSR_bin[j]=0;
        }
    }
    /*for(i=0; i<8; i++){
        printf("%d", MSR_bin[i]);
    }
    printf(".");
    for(i=8; i<16; i++){
        printf("%d", MSR_bin[i]);
    }
    printf(".");
    for(i=16; i<24; i++){
        printf("%d", MSR_bin[i]);
    }
        printf(".");
    for(i=24; i<32; i++){
        printf("%d", MSR_bin[i]);
    }
    printf("\n________________________________________________________________________\n");
    for(i=0; i<32; i++){
        printf("%d", MSR_bin[i]);
    }
    printf("\n________________________________________________________________________\n");*/
    return (MSR_bin);
}

                                                //MSR par défaut

int *default_MSR (int *netmask_bin, int *IP_bin){
    int i,
        *buffer=NULL;
    buffer=(int *)malloc(32*sizeof(int));
    //printf("default MSR:");
    for(i=0; i<32; i++){
        buffer[i]=IP_bin[i]*netmask_bin[i];
        //printf("%d", buffer[i]);
    }
    //printf("\n");
    return (buffer);
}

int *get_broadcast(int MSR_value, int *netmask_bin, int *IP_bin){
    int *broadcast=NULL,
        i,
        j;
    broadcast=(int *)malloc(32*sizeof(int));
    for(i=0; i<32; i++){
        for(j=0; j<MSR_value; j++){
            broadcast[j]=IP_bin[j]*netmask_bin[j];
        }
        for(j=MSR_value; j<32; j++){
            broadcast[j]=1;
        }
    }
    return (broadcast);
}
                                                //prends les puissances de 0-7 de 2 et les stock à l'envers
int *power (){
    int i,
        j,
        k,
        c=1,
        *temp=NULL,
        *pow=NULL;
    temp=(int *)malloc(8*sizeof(int));
    pow=(int *)malloc(8*sizeof(int));
    temp[0]=1;
    for(i=0, j=1; i<7, j<8; i++, j++){
        c*=2;
        temp[j]=c;
    }
    for(i=j-1, k=0; i>=0; i--, k++){
        pow[k]=temp[i];
    }
    return (pow);
}

void *convertion(int *netmask_bin, int *IP_bin, int *network_address_bin, int *broadcast_bin, int *pow){
    int i,
        j,
        decimal_netmask_num1=0,
        decimal_netmask_num2=0,
        decimal_netmask_num3=0,
        decimal_netmask_num4=0,
        decimal_IP_num1=0,
        decimal_IP_num2=0,
        decimal_IP_num3=0,
        decimal_IP_num4=0,
        decimal_network_address_num1=0,
        decimal_network_address_num2=0,
        decimal_network_address_num3=0,
        decimal_network_address_num4=0,
        decimal_broadcast_num1=0,
        decimal_broadcast_num2=0,
        decimal_broadcast_num3=0,
        decimal_broadcast_num4=0;

    for(i=0; i<8; i++){
        decimal_netmask_num1+=(netmask_bin[i]*pow[i]);
        decimal_IP_num1+=(IP_bin[i]*pow[i]);
        decimal_network_address_num1+=(network_address_bin[i]*pow[i]);
        decimal_broadcast_num1+=(broadcast_bin[i]*pow[i]);
    }
    for(i=8, j=0; i<16; i++, j++){
        decimal_netmask_num2+=(netmask_bin[i]*pow[j]);
        decimal_IP_num2+=(IP_bin[i]*pow[j]);
        decimal_network_address_num2+=(network_address_bin[i]*pow[j]);
        decimal_broadcast_num2+=(broadcast_bin[i]*pow[j]);
    }
    for(i=16, j=0; i<24; i++, j++){
        decimal_netmask_num3+=(netmask_bin[i]*pow[j]);
        decimal_IP_num3+=(IP_bin[i]*pow[j]);
        decimal_network_address_num3+=(network_address_bin[i]*pow[j]);
        decimal_broadcast_num3+=(broadcast_bin[i]*pow[j]);
    }
    for(i=24, j=0; i<32; i++, j++){
        decimal_netmask_num4+=(netmask_bin[i]*pow[j]);
        decimal_IP_num4+=(IP_bin[i]*pow[j]);
        decimal_network_address_num4+=(network_address_bin[i]*pow[j]);
        decimal_broadcast_num4+=(broadcast_bin[i]*pow[j]);
    }
    printf("\n-------------------------------------------------------------\n");
    printf("IP_Address      => %d.%d.%d.%d\n", decimal_IP_num1, decimal_IP_num2, decimal_IP_num3, decimal_IP_num4);
    printf("network address => %d.%d.%d.%d\n", decimal_network_address_num1, decimal_network_address_num2, decimal_network_address_num3, decimal_network_address_num4);
    printf("netmask         => %d.%d.%d.%d\n", decimal_netmask_num1, decimal_netmask_num2, decimal_netmask_num3, decimal_netmask_num4);
    printf("Broadcast       => %d.%d.%d.%d\n", decimal_broadcast_num1, decimal_broadcast_num2, decimal_broadcast_num3, decimal_broadcast_num4);
    printf("-------------------------------------------------------------\n");

}

// 1 corveta
// 2 submarino
// 3 fragata
// 4 destroyer
// 5 cruzador
// 6 porta-aviões

// 1 corvetas      2 quadrdinhos
// 2 submarinos    3
// 2 fragatas      3
// 4 destroyer     4 quadradinhos
// 2 cruzador      3 quadradinhos
// 1 porta-aviões  2 quadradinhos
#include <conio.h>
#include <iostream>
#include <fstream>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <sstream>
#include <string>
#define ENTER 13
#define numLinhas 15
#define numColunas 22
using namespace std;

struct dadosNav
{
    string nomeNav;
    int quantNav;
    int codNav;
    int quantQuadrados;
    char simbNav;
};

struct dadosPlayer
{
    int  cursor_linha;
    int  cursor_coluna;
    int pontos;
    int tiros;
    int afundou[6];
    int acertos[6];
    string nome;
};

void mostrar_recordes();
string inter_to_string(int);
void recorde(string, int);
void inicializarStructMBN(void);
void inicializarMapa( vector<int>&);
void escolherMapa(vector<int>& , int, dadosPlayer&);
void menu();
void sorteioMapa(vector<int>&);
void  MBN ( vector<int>&,  dadosPlayer&, int );
void ganhou();
void perdeu();
void mostrar_mapa();
bool verifica3(vector<int>&, int, int, int);
void delay();


dadosPlayer *ptStruct;
vector<int> mapaSortP1(numLinhas*numColunas), mapaSortP2(numLinhas*numColunas);
vector<char> mapaP1 (numLinhas*numColunas),   mapaP2(numLinhas*numColunas);
int tecla,quantPlayer,tiros;
dadosNav dadosMBN[6];
dadosPlayer dadosP[2];
vector<dadosPlayer> players;



bool verifica3(vector<int>& mapaSort, int i,  int j, int number) {
	bool b;

	if( mapaSort[ (i+1)*numColunas+j] ==number  &&  mapaSort[(i+2)*numColunas+j] ==number)
   	b=true;	  
	else if(  mapaSort[  (i+1)*numColunas+j] ==number  && mapaSort[ (i-1)*numColunas+j] ==number)
	b=true;
	else if (mapaSort[ (i-1)*numColunas+j] ==number  &&  mapaSort[ (i-2)*numColunas+j] ==number)
	b=true;

	else if( mapaSort[ i*numColunas+j +1] ==number  &&  mapaSort[ i*numColunas+j +2] ==number )
	b=true;
	else if( mapaSort[ i*numColunas+j +1] ==number  &&  mapaSort[ i*numColunas+j-1] ==number )
	b=true;
	else if(mapaSort[ i*numColunas+j -1] ==number  &&  mapaSort[ (i)*numColunas+j -2] ==number)
	b=true;	
	
	else 
	b=false;
	inicializarMapa(mapaSort);
		return b;						
	}

bool verifica4(vector<int>& mapaSort, int i,  int j, int number) {
	bool b;
	
	if( mapaSort[ (i+1)*numColunas+j] ==number  &&  mapaSort[(i+2)*numColunas+j] ==number &&  mapaSort[ (i+3)*numColunas+j] ==number)
	b=true;

	else if(mapaSort[ (i-1)*numColunas+j] ==number  &&  mapaSort[ (i-2)*numColunas+j] ==number &&  mapaSort[ (i-3)*numColunas+j] ==number)
	b=true;	

	else if(  mapaSort[  (i+1)*numColunas+j] ==number  && mapaSort[ (i-1)*numColunas+j] ==number &&  mapaSort[ (i-2)*numColunas+j] ==number )
	b=true;

	else if (mapaSort[ (i+1)*numColunas+j] ==number  &&  mapaSort[ (i+2)*numColunas+j] ==number &&  mapaSort[ (i-1)*numColunas+j] ==number)
	b=true;

    
	else if( mapaSort[ i*numColunas+j +1] ==number  &&  mapaSort[ i*numColunas+j +2] ==number &&  mapaSort[ i*numColunas+j +3] ==number)
	b=true;
	
	else if( mapaSort[ i*numColunas+j -1] ==number  &&  mapaSort[ i*numColunas+j-2] ==number &&  mapaSort[i*numColunas+j -3] ==number)
	b=true;

	else if( mapaSort[ i*numColunas+j +1] ==number  &&  mapaSort[ i*numColunas+j+2] ==number &&  mapaSort[ (i)*numColunas+j-1] ==number)
	b=true;
	
	else if(mapaSort[ i*numColunas+j +1] ==number  &&  mapaSort[ (i)*numColunas+j -1] ==number &&  mapaSort[ (i)*numColunas+j -2] ==number)
	b=true;	
	else 
	b=false;
	inicializarMapa(mapaSort);

return b;	
}

bool verifica2(vector<int>& mapaSort, int i,  int j, int number) {
	bool b;
        if(mapaSort[ (i+1)*numColunas+j] !=1 &&mapaSort[ (i-1)*numColunas+j] !=1 &&mapaSort[ i*numColunas+j+1] !=1 &&mapaSort[ i*numColunas+j-1] !=1 )
       b=false;
       else{
       b=true;
       inicializarMapa(mapaSort);
        }
	return b;						
	}

void escolherMapa( vector<int>& mapaSort, int player, dadosPlayer&structP)
{
vector<int> mapaSort2(numLinhas*numColunas);
int cont,option,p,i,j;
bool b;
 do{
 	inicializarMapa(mapaSort2);
 	inicializarMapa(mapaSort);
 	tecla=0;
 	option=0;
    cont=1;
	b=true;
    do 
	{
      system("cls");
        tecla=0;
        if(cont<3)
            p=0;
        else if	(cont<9)
            p=1;
        else if	(cont<15)
            p=2;
        else if	(cont<31)
            p=3;
        else if	(cont<37)
            p=4;
        else if	(cont<39)
            p=5;
        cout<<"**************************************************************************************"<<endl;
        cout<<"********************************* MEGA BATALHA NAVAL *********************************"<<endl;
        cout<<"**************************************************************************************"<<endl;
        cout<<"Jogador"<<player<<" escolha onde deseja colocar os navios. Obedeça a regraabaixo "<<endl;
        cout<<"\t\t 1 corvetas     -    2 quadrdinhos"<<endl;
        cout<<"\t\t 2 submarinos   -    3 quadradinhos"<<endl;
        cout<<"\t\t 2 fragatas     -    3 quadradinhos"<<endl;
        cout<<"\t\t 4 destroyer    -    4 quadradinhos"<<endl;
        cout<<"\t\t 2 cruzador     -    3 quadradinhos"<<endl;
        cout<<"\t\t 1 porta-aviões -    2 quadradinhos "<<endl;
        cout<<"\n\n \t Escolha os quadrados do(s) \n"<<dadosMBN[p].quantNav<<" "<< dadosMBN[p].nomeNav<<endl;
        for(i=0; i<15; i++)
        {
            cout<<"\t\t\t   ";
            for(j=0; j<22; j++)
            {

                if ((i == structP.cursor_linha)&&(j == structP.cursor_coluna))
                    cout<<" X ";
                else
                {
                    switch(mapaSort[i*numColunas+j])
                    {
                    case 1:
                        cout<<" ¬ ";
                        break;
                    case 2:
                        cout<<" » ";
                        break;
                    case 3:
                        cout<<" £ ";
                        break;
                    case 4:
                        cout<<" $ ";
                        break;
                    case 5:
                        cout<<" © ";
                        break;
                    case 6:
                        cout<<" ð ";
                        break;
                    default:
                        cout<<" _ ";
                        break;
                    }
                }

            }
            cout<<"\n";
        }
         delay();
        tecla = getch();
        switch(tecla)
        {

        case 13:    // enter
            mapaSort[structP.cursor_linha*numColunas + structP.cursor_coluna] = dadosMBN[p].codNav;
		    mapaSort2[structP.cursor_linha*numColunas + structP.cursor_coluna] = dadosMBN[p].codNav;
			cont++;
        	 if(cont==3){ 
        		b=verifica2(mapaSort2, structP.cursor_linha,  structP.cursor_coluna,1);
			}
			else if(cont==6 || cont==9 ){ 
        		b=verifica3(mapaSort2, structP.cursor_linha,  structP.cursor_coluna,2);
			}
			else if(cont==12 || cont==15 ){ 
        		b=verifica3(mapaSort2, structP.cursor_linha,  structP.cursor_coluna,3);
			}
			else if(cont==19 ){ 
        		b=verifica4(mapaSort2, structP.cursor_linha,  structP.cursor_coluna,4);
			}
			else if(cont==22 || cont==25 ){ 
        		b=verifica3(mapaSort2, structP.cursor_linha,  structP.cursor_coluna,5);
			}
			else if(cont==27){ 
        		b=verifica3(mapaSort2, structP.cursor_linha,  structP.cursor_coluna,6);
			}
            break;
        case 72:
            if(structP.cursor_linha>0) //cima
                structP.cursor_linha--;
            break;
        case 75:
            if(structP.cursor_coluna>0)  //esquerda
                structP.cursor_coluna--;
            break;
        case 77:       //direita
            if(structP.cursor_coluna<21)
                structP.cursor_coluna++;
            break;
        case 80:     //baixo
            if(structP.cursor_linha<14)
                structP.cursor_linha++;
            break;
        default:
            break;
        }

    }while(cont!=39 &&b);
	
	if(!b){
	cout<<"mapa inválido!"<<endl;
	cout<<"Digite 1 se deseja tentar novamente ou qualquer outra tecla para retornar ao menu de opçoes"<<endl;
	cin>>option;
	if(option!=1)
	menu();
	else
	inicializarMapa(mapaSort);
	}
	
	}while(option==1);
} 

void mostrar_recordes()
{
    string linha;
    vector<string>vetorRecordeAtual;
    vector<string>::iterator it;
    int k,b=0;
    ifstream meuarquivo("recordes.txt");
    if(meuarquivo.is_open())
    {
        while(!meuarquivo.eof())
        {
            getline (meuarquivo,linha);
            if(linha!="")
            {
                vetorRecordeAtual.push_back(linha);
            }
        }
        meuarquivo.close();
    }
    cout<<"--------------------------------- RECORDES ---------------------------------"<<endl;
    cout<<"\n Nome                    Disparados efetuados"<<endl;
    for(it=vetorRecordeAtual.begin(); it!=vetorRecordeAtual.end(); it++)
    {
        cout<<"      | "<<*it<<" |         "<<endl;
    }
    cout<<"----------------------------------------------------------------------------"<<endl;
    system("pause");
    menu();
}

string inter_to_string(int a)
{
    stringstream resultado;
    resultado<<a;
    return (resultado.str());
}

bool verifica_int(string a)
{
    int c, cont=0;
    for(c=0; c<a.size(); c++)
    {
        if(isdigit(a[c]))
            cont++;
    }
    if( cont==a.size())
        return true;
    else
        return false;
}

void recorde(string nomeP, int tirosP)
{

    string linha, subs="";
    int i=0;
    vector<string>vetorRecordeAtual;
    vector<string>::iterator it, it2;
    vector<string>numbers;

    int k,b=0;
    ifstream meuarquivo("recordes.txt");
    if(meuarquivo.is_open())
    {
        while(!meuarquivo.eof())
        {
            getline (meuarquivo,linha);
            if(linha!="")
            {
                vetorRecordeAtual.push_back(linha);
                i++;
            }
        }

        meuarquivo.close();
    }
    if(i==0)
    {
        ofstream meu_arquivo ("recordes.txt");
        if (meu_arquivo.is_open())
        {
            meu_arquivo<<nomeP<<" ";
            meu_arquivo<<tirosP<<endl;
            meu_arquivo.close();
        }
    }
    else
    {
        for(k=0; k<i; k++)
        {
            istringstream iss(vetorRecordeAtual[k]);
            do
            {
                string sub;
                iss >> sub;
                if(verifica_int(sub) && sub!="")
                    numbers.push_back(sub);
            }
            while(iss);
        }
        k=0;
        b=1;
        it= vetorRecordeAtual.begin();
        it2= numbers.begin();
        do
        {
            if(tirosP< stoi(*it2))
            {
                subs=nomeP+" ";
                subs+= inter_to_string (tirosP);
                vetorRecordeAtual.insert(it,subs);
                b=0;
            }
            it++;
            it2++;
            k++;
        }
        while(b==1 && it2!=numbers.end());

        if( vetorRecordeAtual.size()>5)
            vetorRecordeAtual.pop_back();
        else if( b==1 && i<5)
        {
            subs=nomeP+" ";
            subs+= inter_to_string(tirosP);
            vetorRecordeAtual.push_back(subs);
        }
        ofstream meu_arquivo ("recordes.txt");
        if (meu_arquivo.is_open())
        {
            for(it=vetorRecordeAtual.begin(); it!=vetorRecordeAtual.end(); ++it)
                meu_arquivo<<*it<<endl;
            meu_arquivo.close();
        }
    }
}

void mostrar_mapa( vector<int>& mapaSort)
{
    system("cls");
    int i,j;
    for (i=0;  i<15; i++)
    {
        cout<<"\t\t\t   ";//manter no meio do prog
        for(j=0; j<22; j++)
        {
            cout<<mapaSort[numColunas*i +j];
        }
        cout<<"\n";
    }
}

void inicializarStructMBN(void)
{
    ptStruct = dadosP;
    int k, i;
    dadosMBN[0] = {"corveta",1,1,2,'¬'};
    dadosMBN[1] = {"submarino", 2,2,3,'»'};
    dadosMBN[2] = {"fragata",2,3,3,'£'};
    dadosMBN[3] = {"destroyer",4,4,4,'$'};
    dadosMBN[4] = {"cruzador",2,5,3,'©'};
    dadosMBN[5] = {"porta-aviões",1,6,2,'ð'};
    for(k=0; k<2; k++)
    {
        dadosP[k].cursor_linha=0;
        dadosP[k].cursor_coluna=0;
        dadosP[k].tiros=0;
        dadosP[k].pontos=0;
        for( i=0; i<6; i++)
        {
            dadosP[k].afundou[i]=0;
            dadosP[k].acertos[i]=0;
        }
    }
}

void inicializarMapa( vector<int>& mapaSort)
{
    int i, j;
    for (i=0; i<15; i++)
    {
        for(j=0; j<22; j++)
        {
            mapaSort[i*numColunas+j]=0;
        }
    }
}

void delay()
{
    int i=1000;
    while(i) i--;
}
int op, op2,op3;

void menu()
{
    string nome;
    //system("mode con:cols=240 lines=140");
    do
    {
        quantPlayer=0;
        cout<<"\t ______________________________________________________________________________"<<endl;
        cout<<"\t|                                                                     		|"<<endl;
        cout<<"\t|  &&&&&&&&&&&&&&&&&&&&&&&& MEGA BATALHA NAVAL &&&&&&&&&&&&&&&&&&&&&&&&       	|"<<endl;
        cout<<"\t|  										|"<<endl;
        cout<<"\t|                           1 - 1 Jogador                             		|"<<endl;
        cout<<"\t|                           2 - 2 Jogadores                           		|"<<endl;
        cout<<"\t|                           3 - Recordes                              		|"<<endl;
        cout<<"\t|                           4 - Ajuda                                 		|"<<endl;
        cout<<"\t|                           5 - Sair                                  		|"<<endl;
        cout<<"\t|_______________________________________________________________________________|"<<endl;

       cout<<"\tEscolha uma opção acima"<<endl;
        cin>>op;
        system ("cls");
    }
    while(op!=1 && op!=2 && op!=3 && op!=4 &&op!=5 );
    switch(op)
    {
    case 1:
        quantPlayer=1;
        inicializarMapa( mapaSortP1);
        cout<<"Jogador, digite o seu nome:"<<endl;
        getline(cin,nome);
	    getline(cin,nome);
        dadosP[0].nome=nome;
        sorteioMapa(mapaSortP1);
        //system("cls");
        cout<<" _________________________________________________________________________"<<endl;
        cout<<"|                              		                                      	 |"<<endl;
        cout<<"|  	 	&&&&&&&&&&&&&&&&&&&&&&& MEGA BATALHA NAVAL &&&&&&&&&&&&&&&&&&&&&&&   |"<<endl;
        cout<<"|  																		 	 |"<<endl;
        cout<<"|        		                   1 Fácil                                   |"<<endl;
        cout<<"|            		               2 Mécdio                                  |"<<endl;
        cout<<"|                		           3 Difícil                                 |"<<endl;
        cout<<"|_____________________________________________________________________________|"<<endl;
        cin>>op2;
        switch(op2)
        {
        case 1:
            tiros=180;
            break;
        case 2:
            tiros=120;
            break;
        case 3:
            tiros=100;
        default:
            break;
        }
        break;
    case 2:
        quantPlayer=2;
        inicializarMapa( mapaSortP1);
        inicializarMapa( mapaSortP2);
        do
        {
            system("cls");
            cout<<"Jogador 1, digite o seu nome:"<<endl;
            getline(cin,nome);
	        getline(cin,nome);
	        dadosP[0].nome=nome;
            cout<<" _____________________________________________________________________"<<endl;
            cout<<"|                                                                     |"<<endl;
            cout<<"| &&&&&&&&&&&&&&&&&&&&&&& MEGA BATALHA NAVAL &&&&&&&&&&&&&&&&&&&&&&&  |"<<endl;
            cout<<"|  																	 |"<<endl;
            cout<<"|                           1 Sortear tabuleiro                       |"<<endl;
            cout<<"|                           2 Escolher as posiçoes                    |"<<endl;
            cout<<"|_____________________________________________________________________|"<<endl;
            cout<<"Jogador 1 escolha uma opção acima"<<endl;
            cin>>op3;
            if (op3==1)
                sorteioMapa(mapaSortP1);
            else if(op3==2)
                escolherMapa (mapaSortP1,1,ptStruct[0]);
        }
        while(op3!=1 && op3!=2);
        do
        {
            system("cls");
            cout<<"Jogador 2, digite o seu nome:"<<endl;
            getline(cin,nome);
	        getline(cin,nome);
	        dadosP[1].nome=nome;
            cout<<" _____________________________________________________________________"<<endl;
            cout<<"|                                                                     |"<<endl;
            cout<<"| &&&&&&&&&&&&&&&&&&&&&&& MEGA BATALHA NAVAL &&&&&&&&&&&&&&&&&&&&&&&  |"<<endl;
            cout<<"|  																	 |"<<endl;
            cout<<"|                           1 Sortear tabuleiro                       |"<<endl;
            cout<<"|                           2 Escolher as posiçoes                    |"<<endl;
            cout<<"|_____________________________________________________________________|"<<endl;
            cout<<"Jogador 2 escolha uma opção acima"<<endl;
            cin>>op3;
            if (op3==1)
                sorteioMapa(mapaSortP2);
            else if(op3==2)
                escolherMapa ( mapaSortP2,2,ptStruct[1]);
        }
        while(op3!=1 && op3!=2);
        break;
    case 3:
        mostrar_recordes();
    default:
        break;
    }
}

void sorteioMapa(vector<int>& mapaSort)
{
    int op, op2,i, j,p, linha_x,coluna_y;
    //      0
    //1  x  2
    //   3
    int k;
    int flag;
    for(i=0; i<12; i++)
    {
        flag=0;
        //srand(time(NULL));
        linha_x=(rand()%15);     //entre 0 e 14 linhax
        coluna_y=(rand()%22);     // entre 0 e 21
        if(i<1)
            k=0;
        else if( i<3)
            k=1;
        else if( i<5)
            k=2;
        else if( i<9)
            k=3;
        else if( i<11)
            k=4;
        else if( i<12)
            k=5;
        if (mapaSort[linha_x*numColunas+coluna_y]==0 )
        {
            //     srand(time(NULL));
            op= (rand()%4);
            if(op==0)
            {
                for(j=1; j<dadosMBN[k].quantQuadrados; j++ )
                {
                    if( (mapaSort[ (linha_x-j)*numColunas+coluna_y] !=0) || (linha_x-j<0) )
                        flag=1;
                }
                if(flag!=1)
                {
                    for(j=0; j<dadosMBN[k].quantQuadrados; j++ )
                    {
                        mapaSort[ (linha_x-j)*numColunas+coluna_y] =dadosMBN[k].codNav;
                    }
                }
            }
            else if (op==1)
            {
                for(j=1; j<dadosMBN[k].quantQuadrados; j++ )
                {
                    if( (mapaSort[linha_x*numColunas+coluna_y-j] !=0) || (coluna_y-j<0 ))
                        flag=1;
                }
                if(flag!=1)
                {
                    for(j=0; j<dadosMBN[k].quantQuadrados; j++ )
                    {
                        mapaSort[linha_x*numColunas+coluna_y-j] =dadosMBN[k].codNav;
                    }
                }
            }
            else if (op==2)
            {
                for(j=1; j<dadosMBN[k].quantQuadrados; j++ )
                {
                    if( (mapaSort[linha_x*numColunas+coluna_y+j] !=0) || (coluna_y+j>21 ))
                        flag=1;
                }
                if(flag!=1)
                {
                    for(j=0; j<dadosMBN[k].quantQuadrados; j++ )
                    {
                        mapaSort[linha_x*numColunas+coluna_y+j] =dadosMBN[k].codNav;
                    }
                }
            }
            else if (op==3)
            {
                for(j=1; j<dadosMBN[k].quantQuadrados; j++ )
                {
                    if((mapaSort[(linha_x+j)*numColunas+coluna_y] !=0) || (linha_x+j>14 ))
                        flag=1;
                }
                if(flag!=1)
                {
                    for(j=0; j<dadosMBN[k].quantQuadrados; j++ )
                    {
                        mapaSort[(linha_x+j)*numColunas+coluna_y] =dadosMBN[k].codNav;
                    }
                }
            }
        }
        else
            flag=1;
        if(flag==1)
            i--;
    }

}

void  MBN ( vector<int>& mapaSort,  dadosPlayer &structP, int player )
{
    int i,flag=0,j;
    do
    {
        flag=0;
        tecla=0;
        system("cls");
        cout<<" ______________________________________________________________________________________________"<<endl;
        cout<<"|																						      | "<<endl;
        cout<<"| &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& MEGA BATALHA NAVAL &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& |"<<endl;
        cout<<"|					JOGADOR "<<player<<"                                     |"<<endl;
        cout<<"|______________________________________________________________________________________________|"<<endl;
        cout<<"Legendas Mapa:"<<endl;;
        cout<<" X : Posição do cursor"<<endl;
        cout<<" Ø : Quadradinho já foi atingido"<<endl;
        cout<<" _ : Quadradinho não foi atingido"<<endl;
        cout<<" ¬ : Corveta"<<endl;
        cout<<" » : Submarino"<<endl;
        cout<<" £ : Fragata"<<endl;
        cout<<" $ : Destroyer"<<endl;
        cout<<" © : Cruzador"<<endl;
        cout<<" ð : Porta-Aviões"<<endl;
        for (i=0; i<15; i++)
        {
            cout<<"\t\t\t ";
            for(j=0; j<22; j++)
            {
                if ((i == structP.cursor_linha)&&(j == structP.cursor_coluna))
                    cout<<" X ";
                else
                {
                    switch(mapaSort[i*numColunas+j])
                    {
                    case -1:
                        cout<<" Ø ";
                        break;
                    case 7:
                        cout<<" ¬ ";
                        break;
                    case 8:
                        cout<<" » ";
                        break;
                    case 9:
                        cout<<" £ ";
                        break;
                    case 10:
                        cout<<" $ ";
                        break;
                    case 11:
                        cout<<" © ";
                        break;
                    case 12:
                        cout<<" ð ";
                        break;
                    default:
                        cout<<" _ ";
                        break;
                    }
                }

            }
            cout<<"\n";
        }

        cout<<" STATUS :"<<endl; // Imprime as direcoes
        if(op==1)
            cout<<"   Tiros disparados/tiros totais:"<<structP.tiros<<"/"<<tiros<<"\n\n";
        else if(op==2)
            cout<<"   Tiros disparados:"<<structP.tiros<<"\n\n";
        cout<<"Pontuação: "<<structP.pontos<<"/38"<<endl;
        cout<<"Corveta: "<<structP.acertos[0] <<"/2 	 |\tAfundou: "<<structP.afundou[0]<<"/1"<<endl;
        cout<<"Submarino: "<<structP.acertos[1]<<"/3 	 |\tAfundou: "<<structP.afundou[1]<<"/2"<<endl;
        cout<<"Fragata: "<<structP.acertos[2]<<"/3 		 |\tAfundou: "<<structP.afundou[2]<<"/2"<<endl;
        cout<<"Destroyer: "<<structP.acertos[3]<<"/4 	 |\tAfundou: "<<structP.afundou[3]<<"/4"<<endl;
        cout<<"Cruzador: "<<structP.acertos[4]<<"/3 	 |\tAfundou: "<<structP.afundou[4]<<"/2"<<endl;
        cout<<"Porta-Aviões: "<<structP.acertos[5]<<"/2  |\tAfundou: "<<structP.afundou[5]<<"/1"<<endl;
        cout<<"\n";

        printf ("\n");

        tecla = getch();

        switch(tecla)
        {
        case 13:    // enter
            structP.tiros++;
            if (mapaSort[structP.cursor_linha*numColunas+ structP.cursor_coluna] == 0)
            {
                mapaSort[structP.cursor_linha*numColunas+ structP.cursor_coluna]=-1;
                printf("Tiro acertou a água");
                getch();
            }
            else if(mapaSort[structP.cursor_linha*numColunas+ structP.cursor_coluna]==1)
            {
                mapaSort[structP.cursor_linha*numColunas+ structP.cursor_coluna]=7;
                cout<<"Você acertou em uma Corveta!";
                structP.acertos[0]++;
                structP.pontos++;
                if (structP.acertos[0]==2)
                {
                    structP.afundou[0]++;
                    cout<< "\nVoce afundou uma Corveta!";
                }
                getch();//pausa
            }
            else if(mapaSort[structP.cursor_linha*numColunas+ structP.cursor_coluna]==2)
            {
                mapaSort[structP.cursor_linha*numColunas+ structP.cursor_coluna]=8;
                cout<<"Você acertou em um Submarino!";
                structP.acertos[1]++;
                structP.pontos++;
                if (structP.acertos[1]==3)
                {
                    structP.acertos[1]=0;
                    structP.afundou[1]++;
                    cout<< "Voce afundou um Submarino!";
                }
                if (structP.afundou[1]==3)
                    cout<< "Voce afundou todos os submarinos!";
                getch();//pausa
            }
            else if(mapaSort[structP.cursor_linha*numColunas+ structP.cursor_coluna]==3)
            {
                mapaSort[structP.cursor_linha*numColunas+ structP.cursor_coluna]=9;
                cout<<"Você acertou em uma Fragata!";
                structP.acertos[2]++;
                structP.pontos++;
                if (structP.acertos[2]==3)
                {
                    cout<< "Voce afundou uma Fragata!";

                    structP.acertos[2]=0;
                    structP.afundou[2]++;
                }
                if (structP.afundou[2]==2)
                    cout<< "Voce afundou todos as fragatas!";
                getch();//pausa
            }
            else if(mapaSort[structP.cursor_linha*numColunas+ structP.cursor_coluna]==4)
            {
                mapaSort[structP.cursor_linha*numColunas+ structP.cursor_coluna]=10;
                cout<<"Você acertou em um Destroyer!";
                structP.acertos[3]++;
                structP.pontos++;
                if (structP.acertos[3]==4)
                {
                    cout<<"Você afundou um Destroyer!";
                    structP.acertos[3]=0;
                    structP.afundou[3]++;
                }
                if (structP.afundou[3]==4)
                    cout<< "Voce afundou todos os Destroyer!";
                getch();//pausa
            }

            else if(mapaSort[structP.cursor_linha*numColunas+ structP.cursor_coluna]==5)
            {
                mapaSort[structP.cursor_linha*numColunas+ structP.cursor_coluna]=11;
                cout<<"Você acertou um Cruzador!";
                structP.acertos[4]++;
                structP.pontos++;
                if (structP.acertos[4]==3)
                {
                    cout<< "Voce afundou um Cruzador!";
                    structP.acertos[4]=0;
                    structP.afundou[4]++;
                }
                if (structP.afundou[4]==2)
                    cout<< "Voce afundou todos os Cruzador!";
                getch();//pausa
            }
            else if(mapaSort[structP.cursor_linha*numColunas+ structP.cursor_coluna]==6)
            {
                mapaSort[structP.cursor_linha*numColunas+ structP.cursor_coluna]=12;
                cout<<"Você acertou um Porta-Aviões!";
                structP.acertos[5]++;
                structP.pontos++;
                if (structP.acertos[5]==2)
                {
                    structP.afundou[5]++;
                    cout<< "Voce afundou todos os Porta-Aviões!";
                }
                getch();//pausa
            }
            else
            {
                structP.tiros--;
                cout<<"Você já acertou essa área!"<<endl;
                getch();
                flag=1;
            }

            break;
        case 27:
            //	main();
            break; //esc
        case 72:
            if (structP.cursor_linha>0) //cima
                structP.cursor_linha--;
            break;
        case 75:
            if(	structP.cursor_coluna>0)  //esquerda
                structP.cursor_coluna--;
            break;
        case 77:       //direita
            if(structP.cursor_coluna<21)
                structP.cursor_coluna++;
            break;
        case 80:     //baixo
            if(structP.cursor_linha<14)
                structP.cursor_linha++;
            break;

        default:
            break;
        }

    }
    while( tecla!=13 || flag==1);
    system("pause");
    if(structP.pontos==10)
    {
        ganhou();
        recorde(structP.nome, structP.tiros);
    }
    else if(op==1)
    {
        if( tiros-structP.tiros==0)
        {
            perdeu();
            mostrar_mapa(mapaSort);
        }
    }
}

void ganhou()
{
    cout<<"\nParabéns você ganhou!"<<endl;
    system("pause");

}

void perdeu()
{
    cout<<"\nInfelizmente você perdeu!"<<endl;
    system("pause");
}

int main()
{
    system("color 30");
    setlocale(LC_ALL, "Portuguese" );
    int opc;
    do
    {
        inicializarStructMBN();
        menu();
        int i,j;
        if (quantPlayer==1)
        {
            while (dadosP[0].pontos!=10 && tiros-dadosP[0].tiros>0 )
            {
                MBN( mapaSortP1, ptStruct[0],1);
            }
        }
        else if (quantPlayer==2)
        {
            while (dadosP[0].pontos!=38 && dadosP[1].pontos!=38 )
            {
                MBN(mapaSortP1, ptStruct[1],1);
                MBN(mapaSortP2, ptStruct[0],2);
            }
        }
        cout<<"digite 1 se deseja jogar novamente ";
        cin>>opc;
    }
    while(opc==1);
    return 0;

}

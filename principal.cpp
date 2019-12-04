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
#define W 176
#define POSICAO 15
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

void inicializarStructMBN(void);
void inicializarMapa(vector<char>&, vector<int>&);
void escolherMapa(vector<char>&, vector<int>& , int, dadosPlayer&);
void menu();
void sorteioMapa(vector<int>&);
void  MBN (vector<char>&, vector<int>&,  dadosPlayer&, int );
void ganhou();
void perdeu();
void mostrar_mapa();

dadosPlayer *ptStruct;
vector<int> mapaSortP1(numLinhas*numColunas), mapaSortP2(numLinhas*numColunas);
vector<char> mapaP1 (numLinhas*numColunas),   mapaP2(numLinhas*numColunas);
int tecla,quantPlayer,tiros;
dadosNav dadosMBN[6];
dadosPlayer dadosP[2];
vector<dadosPlayer> players;
/*
void recorde(){
	string linha;
	int i=0;
	vector<string>vetorRecordeAtual;
	iterator::string it;
	ifstream meuarquivo("recordes.txt");
	if(meuarquivo.is_open()){
		while(!meuarquivo.eof()){
     getline (meuarquivo,linha);
      vetorRecordeAtual.push_back(linha);
	  i++;
	 }
	     meuarquivo.close();
	}
	while(i){
		vetorRecordeAtual[i]
	}


	if(vetorRecordeAtual.size()<5){
		for(it=vetorRecordeAtual.begin();  it!=vetorRecordeAtual.end(); ++it)

	}

}
*/
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

void inicializarMapa(vector<char>& mapa, vector<int>& mapaSort)
{
    int i, j;
    for (i=0; i<15; i++)
    {
        for(j=0; j<22; j++)
        {
            mapa[i*numColunas+j]='_';
            mapaSort[i*numColunas+j]=0;
        }
    }
}

void escolherMapa(vector<char>& mapa, vector<int>& mapaSort, int player, dadosPlayer&structP)
{
    int p=0, linha,coluna,cont=1;
    while(cont!=39)
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
        for(linha=0; linha<15; linha++)
        {
            cout<<"\t\t\t   ";//manter no meio do prog
            for(coluna=0; coluna<22; coluna++)
            {
                if ((linha == structP.cursor_linha)&&(coluna == structP.cursor_coluna)&&(tecla!=ENTER))
                    printf("%c",POSICAO);
                else
                    printf("%c", mapa[linha*numColunas+ coluna]);
            }
            cout<<"\n";
        }
        tecla = getch();
        switch(tecla)
        {
        case 13:    // enter
            mapaSort[structP.cursor_linha*numColunas + structP.cursor_coluna] = dadosMBN[p].codNav;
            mapa[structP.cursor_linha*numColunas+ structP.cursor_coluna] = dadosMBN[p].simbNav;
            cont++;
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
            if(structP.cursor_coluna<20)
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
}
int op, op2,op3;

void menu()
{
	string nome;
	system("mode con:cols=240 lines=140");
    do
    {
        quantPlayer=0;
        cout<<" ________________________________________________________________________"<<endl;
        cout<<"|                                                                     	|"<<endl;
        cout<<"|  &&&&&&&&&&&&&&&&&&&&&&&& MEGA BATALHA NAVAL &&&&&&&&&&&&&&&&&&&&&&&&  |"<<endl;
        cout<<"|  																		|"<<endl;
        cout<<"|                           1 - 1 Jogador                             	|"<<endl;
        cout<<"|                           2 - 2 Jogadores                           	|"<<endl;
        cout<<"|                           3 - Recordes                              	|"<<endl;
        cout<<"|                           4 - Ajuda                                 	|"<<endl;
        cout<<"|                           5 - Sair                                  	|"<<endl;
        cout<<"|________________________________________________________________________|"<<endl;
        cout<<"Escolha uma opção acima"<<endl;
        cin>>op;
        system ("cls");
    }
    while(op!=1 && op!=2&& op!=3 &&op!=4 &&op!=5 );
    switch(op)
    {
    case 1:
        quantPlayer=1;
        inicializarMapa(mapaP1, mapaSortP1);
        cout<<"Jogador, digite o seu nome:"<<endl;
        cin>> nome;
        dadosP[0].nome=nome;
	    sorteioMapa(mapaSortP1);
        //system("cls");
        cout<<" _________________________________________________________________________"<<endl;
        cout<<"|                                                                    	 |"<<endl;
        cout<<"| 	&&&&&&&&&&&&&&&&&&&&&&& MEGA BATALHA NAVAL &&&&&&&&&&&&&&&&&&&&&&&   |"<<endl;
        cout<<"|  																	 	 |"<<endl;
        cout<<"|        	                   1 Fácil                                   |"<<endl;
        cout<<"|            	               2 Mécdio                                  |"<<endl;
        cout<<"|                	           3 Difícil                                 |"<<endl;
        cout<<"|_________________________________________________________________________|"<<endl;
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
        inicializarMapa(mapaP1, mapaSortP1);
        inicializarMapa(mapaP2, mapaSortP2);
        do
        {
            //system("cls");
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
                escolherMapa (mapaP1, mapaSortP1,1,ptStruct[0]);
        }
        while(op3!=1 && op3!=2);
        do
        {
            system("cls");
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
                escolherMapa (mapaP2, mapaSortP2,2,ptStruct[1]);
        }
        while(op3!=1 && op3!=2);
        break;
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


void  MBN (vector<char>& mapa, vector<int>& mapaSort,  dadosPlayer &structP, int player )
{
    int i,flag=0,j;
    do
    {
        flag=0;
        tecla=0;
        system("cls");
       // mostrar_mapa(mapaSort);
        cout<<" ______________________________________________________________________________________________"<<endl;
        cout<<"|																						      | "<<endl;
	    cout<<"| &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& MEGA BATALHA NAVAL &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& |"<<endl;
        cout<<"|					JOGADOR "<<player<<"                                     |"<<endl;
        cout<<"|______________________________________________________________________________________________|"<<endl;
        cout<<"Legendas Mapa:"<<endl;;
		cout<<" @ : Posição curso"<<endl;
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
                    cout<<" @ ";
                else
                     cout<<" "<<mapa[i*numColunas+j]<<" ";
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
                mapa[structP.cursor_linha*numColunas+ structP.cursor_coluna]='Ø';
                mapaSort[structP.cursor_linha*numColunas+ structP.cursor_coluna]=-1;
                printf("Tiro acertou a água");
                getch();
            }
            else if(mapaSort[structP.cursor_linha*numColunas+ structP.cursor_coluna]==1)
            {
                mapa[structP.cursor_linha*numColunas+ structP.cursor_coluna]=4;
                mapaSort[structP.cursor_linha*numColunas+ structP.cursor_coluna]=-1;
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
                mapa[structP.cursor_linha*numColunas+ structP.cursor_coluna]=205;
                mapaSort[structP.cursor_linha*numColunas+ structP.cursor_coluna]=-1;
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
                mapa[structP.cursor_linha*numColunas+ structP.cursor_coluna]=17;
                mapaSort[structP.cursor_linha*numColunas+ structP.cursor_coluna]=-1;
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
                mapa[structP.cursor_linha*numColunas+ structP.cursor_coluna]=254;
                mapaSort[structP.cursor_linha*numColunas+ structP.cursor_coluna]=-1;
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
                mapa[structP.cursor_linha*numColunas+ structP.cursor_coluna]='¶';
                mapaSort[structP.cursor_linha*numColunas+ structP.cursor_coluna]=-1;
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
                mapa[structP.cursor_linha*numColunas+ structP.cursor_coluna]='+';
                mapaSort[structP.cursor_linha*numColunas+ structP.cursor_coluna]=-1;
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
            else if(mapaSort[structP.cursor_linha*numColunas+ structP.cursor_coluna]==-1)
            {
                structP.tiros++;
                cout<<"Você já acertou essa área!"<<endl;
                getch();
                flag=1;
            }
            else
            {
                cout<<"\nbug "<<mapaSort[structP.cursor_linha*numColunas+ structP.cursor_coluna]<<endl;
                getch();

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
    cout<<"\nsaiu do while"<<endl;
    system("pause");
    if(structP.pontos==38)
    {
        ganhou();

    }
    else if(op==1){
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
    inicializarStructMBN();
    menu();
    int i,j;
    if (quantPlayer==1)
    {
        while (dadosP[0].pontos!=38 && tiros-dadosP[0].tiros>0 )
        {
            MBN(mapaP1, mapaSortP1, ptStruct[0],1);
        }
    }
    else if (quantPlayer==2)
    {
        while (dadosP[0].pontos!=38 && dadosP[1].pontos!=38 )
        {
            MBN(mapaP1, mapaSortP1, ptStruct[1],1);
            MBN(mapaP2, mapaSortP2, ptStruct[0],2);
        }
    }

    return 0;

}

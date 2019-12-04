
#include <iostream>
#include <fstream>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <sstream>
#include <string>
using namespace std;
 


string inter_to_string(int a){
		stringstream resultado;
		resultado<<a;		
		return (resultado.str());		
}


bool verifica_int(string a){
int c, cont=0;
 for(c=0;c<a.size();c++)
    {
    if(isdigit(a[c]))
	cont++;	
    }
    if( cont==a.size())
    return true;
    else 
    return false;
}

void recorde(string nomeP, int tirosP){
	
	string linha, subs="";
	int i=0;
	vector<string>vetorRecordeAtual;
	vector<string>::iterator it, it2;
	vector<string>numbers;
	
	int k,b=0;
	ifstream meuarquivo("recordes.txt");
	if(meuarquivo.is_open()){
		while(!meuarquivo.eof()){
     	  getline (meuarquivo,linha);
     	  	if(linha!=""){   
      			vetorRecordeAtual.push_back(linha);
	  			i++;
			 }
		}
	 	
      meuarquivo.close();
  }
  if(i==0){
  	ofstream meu_arquivo ("recordes.txt");
	if (meu_arquivo.is_open()){
		meu_arquivo<<nomeP<<" ";
		meu_arquivo<<tirosP<<endl;
	    meu_arquivo.close(); 	 		
    }
  }
  else{
		for(k=0;k<i;k++){
	 		istringstream iss(vetorRecordeAtual[k]);    
     		do{
     			string sub;
                iss >> sub;	
				if(verifica_int(sub) && sub!="")
    				numbers.push_back(sub);
     		}while(iss);
		}
		k=0;
		b=1;
		it= vetorRecordeAtual.begin();
		it2= numbers.begin();
		do{
			if(tirosP< stoi(*it2)) {
				subs=nomeP+" ";
	        	subs+= inter_to_string (tirosP);
				vetorRecordeAtual.insert(it,subs);
				b=0;
			}
			it++;
			it2++;
			k++; 
	 	} while(b==1 && it2!=numbers.end());
	  
		if( vetorRecordeAtual.size()>5)
  		vetorRecordeAtual.pop_back();
    	else if( b==1 && i<5){
     		subs=nomeP+" ";
	 		subs+= inter_to_string(tirosP);
	    	vetorRecordeAtual.push_back(subs);
		}
	ofstream meu_arquivo ("recordes.txt");
	if (meu_arquivo.is_open()){
	for(it=vetorRecordeAtual.begin();it!=vetorRecordeAtual.end();++it)
		meu_arquivo<<*it<<endl;
	    meu_arquivo.close(); 	 		
    }
	}
}

int main(void){
	recorde("marcelote",14);
	
	return 0;			  				  
}

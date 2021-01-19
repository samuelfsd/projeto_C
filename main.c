#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//estrutura de cadastro
typedef struct Cadastro{
  char nome[60];
  char telefone[15];
  int horas;
  int minutos;
  int horafinal;
  int minutofinal;
  char tipo_de_corte[60];
  struct Cadastro *prox;
}Cadastro;

// criando cadastro apontando para NULL
Cadastro *criar_cadastro(void){
  return NULL;
}

int verifica(Cadastro *lista, Cadastro *novo,int tempo){
  Cadastro *a = lista;
  int disponivel=1, tempo_novo,tempo_corte;
  if (a==NULL){
    disponivel=1;
  }
  else{
    int tempoinicial, tempofinal, novotempoinicial,novotempofinal;
  while(a!=NULL){
    tempoinicial=(a->horas * 60)+a->minutos;
    tempofinal=(a->horafinal * 60)+a->minutofinal;
    novotempoinicial=(novo->horas * 60)+novo->minutos;
    novotempofinal=(novo->horafinal * 60)+novo->minutofinal;
    if (novotempoinicial>=tempoinicial && novotempoinicial<=tempofinal){
      disponivel = 0;
    }if (novotempofinal>=tempoinicial && novotempofinal<=tempofinal){
      disponivel = 0;
    } 
    a=a->prox;
    }
  }
  return disponivel;
}

// criando função para inserir um cliente
Cadastro *insere_cliente(Cadastro *c){
  Cadastro *novo;
  novo =(Cadastro *) malloc(sizeof(Cadastro));
  int tempo;
  int tipo_de_corte,tent=0,disponivel=1,disp=1;
  printf("CADASTRANDO CLIENTE:\n");
  printf("---------------------------------\n");
  printf("NOME: ");
  setbuf(stdin,NULL);
  fgets(novo->nome,60,stdin);
  printf("TELEFONE: ");
  setbuf(stdin,NULL);
  fgets(novo->telefone,60,stdin);
  printf("ESCOLHA O TIPO DE CORTE:\n");
  printf("INFORME 1 - SOCIAL\n");
  printf("INFORME 2 - DEGRADÊ\n");
  printf("INFORME 3 - NAVALHADO\n");
  scanf("%d",&tipo_de_corte);
  do{
    //if (disponivel==0){
    disp=1;
    if (tent==1){
    printf("HORÁRIO INDISPONÍVEL, TENTE OUTRO.\n");}
    printf("ABERTO DAS 8:00 ÀS 17:00\n");
    printf("HORÁRIO(HORAS): "); 
    scanf("%d",&novo->horas);
    printf("HORÁRIO(MINUTO): ");
    scanf("%d",&novo->minutos);
    if (tipo_de_corte==1){
      tempo=25;
    strcpy(novo->tipo_de_corte,"SOCIAL\n");
    novo->horafinal=novo->horas;
    novo->minutofinal=novo->minutos+25;
    if (novo->minutofinal >= 60){
      novo->horafinal=novo->horafinal+1;
      novo->minutofinal=novo->minutofinal-60;
    }
  }else if(tipo_de_corte==2){
    tempo=45;
    strcpy(novo->tipo_de_corte,"DEGRADÊ\n");
    novo->horafinal=novo->horas;
    novo->minutofinal=novo->minutos+45;
    if (novo->minutofinal >= 60){
      novo->horafinal=novo->horafinal+1;
      novo->minutofinal=novo->minutofinal-60;
    }
  }else{
    tempo=55;
    strcpy(novo->tipo_de_corte,"NAVALHADO\n");
    novo->horafinal=novo->horas;
    novo->minutofinal=novo->minutos+55;
    if (novo->minutofinal >= 60){
      novo->horafinal=novo->horafinal+1;
      novo->minutofinal=novo->minutofinal-60;
    }
  }
    disponivel=verifica(c, novo,tempo);
    if (novo->horas<8 || novo->horas>=17){
      tent=1;
      disp=0;
    }
    if (disponivel==0){
      tent=1;
    }
 }while(disp==0 || disponivel==0);
  
  if(c == NULL){
		novo->prox = NULL;
		return novo;
	}else{
		Cadastro *p = c;
		while(p->prox!=NULL){
			p = p->prox;
		}
		novo->prox = NULL;
		p->prox = novo;
		return c;
	}
}
void exibir_horarios(Cadastro *c){
  Cadastro *p = c;
  if(p==NULL){
    printf("Sem horários marcados!\n");
  }else{
    while(p!=NULL){
      printf("Nome: %s|Horário: %dh%d - %dh%d",p->nome,p->horas,p->minutos,p->horafinal,p->minutofinal);
      printf("\n");
      p = p->prox;
    }
  }
}
Cadastro *busca_cliente(Cadastro *c){
  Cadastro *p = c;
  char busca[60];
  printf("Qual cliente deseja buscar:\n");
  setbuf(stdin,NULL);
  fgets(busca,60,stdin);
  if(p==NULL){
		return NULL;
	}
	while(p->prox!=NULL){
		if(strcmp(p->nome,busca) == 0){
			return p;
		}
		p= p->prox;
	}
	if(strcmp(p->nome,busca) == 0){
		return p;
	}
	return NULL;
}

//Transferindo de arquivo para lista:
  Cadastro* filetolista(Cadastro *c,FILE *arquivo,FILE *arquivo2){
  char buff[10],texto[60];
  int testando;
  Cadastro *novo;
  novo =(Cadastro *) malloc(sizeof(Cadastro));
  if(c == NULL){
    fgets(novo->nome,60,arquivo);
    fgets(novo->telefone,15,arquivo);
    fgets(buff,10,arquivo);
    novo->horas=atoi(buff);
    fgets(buff,10,arquivo);
    novo->minutos=atoi(buff);
    fgets(buff,10,arquivo);
    novo->horafinal=atoi(buff);
    fgets(buff,10,arquivo);
    novo->minutofinal=atoi(buff);
    fgets(novo->tipo_de_corte,60,arquivo);
    while(fgets(texto,60,arquivo)!=NULL){
      fprintf(arquivo2,"%s",texto);
    }
    remove("dados.txt");
    rename("atualiza.txt","dados.txt");
		novo->prox = NULL;
		return novo;
	}else{
		Cadastro *p = c;
		while(p->prox!=NULL){
			p = p->prox;
		}
    fgets(novo->nome,60,arquivo);
    fgets(novo->telefone,15,arquivo);
    fgets(buff,10,arquivo);
    novo->horas=atoi(buff);
    fgets(buff,10,arquivo);
    novo->minutos=atoi(buff);
    fgets(buff,10,arquivo);
    novo->horafinal=atoi(buff);
    fgets(buff,10,arquivo);
    novo->minutofinal=atoi(buff);
    fgets(novo->tipo_de_corte,60,arquivo);
    while(fgets(texto,60,arquivo)!=NULL){
      fprintf(arquivo2,"%s",texto);
    }
    remove("dados.txt");
    rename("atualiza.txt","dados.txt");
		novo->prox = NULL;
		p->prox = novo;
		return c;
	}
}

//Main: 

int main(void){
 
  Cadastro *cliente;
  cliente = criar_cadastro();
  Cadastro *busca;
 //Chamada da função errada:
  int conta=0, i;
  char teste[60];
  FILE *arq,*arq2;
  arq=fopen("dados.txt","r");
  if (arq){
    while (fgets(teste,60,arq)!=NULL){
    conta=conta+1;
    }
    fclose(arq);
    }
    conta=conta/7;
  
  for (i=0;i<conta;i++){
    arq=fopen("dados.txt","r");
    arq2=fopen("atualiza.txt","w");
    if(arq){
    cliente=filetolista(cliente, arq, arq2);
    fclose(arq);
    }
    fclose(arq2);
  }
  Cadastro *p=cliente;
  arq=fopen("dados.txt","w");
  while (p!=NULL){
    fprintf(arq,"%s",p->nome);
    fprintf(arq,"%s",p->telefone);
    fprintf(arq,"%d\n",p->horas);
    fprintf(arq,"%d\n",p->minutos);
    fprintf(arq,"%d\n",p->horafinal);
    fprintf(arq,"%d\n",p->minutofinal);
    fprintf(arq,"%s",p->tipo_de_corte);
    p=p->prox;
  }
  fclose(arq);
  //Continuação do programa normal
  
  int menu=99;

  while (menu!=0){
    printf("---------------------------------\n");
    printf("SALÃO DO BARBEIRO BOLADÃO\n\n");
    printf("Menu Principal\n");
    printf("INFORME 0- SAIR\n");
    printf("INFORME 1- CADASTRAR CLIENTE\n");
    printf("INFORME 2- EXIBIR HORARIOS\n");
    printf("INFORME 3- BUSCAR CLIENTE\n");
    scanf("%d",&menu);
    if (menu==1){
      cliente=insere_cliente(cliente);
    }
    if(menu==2){
      printf("EXIBINDO HORáRIOS:\n");
      printf("---------------------------------\n");
      printf("ABERTO DAS 8:00 ÀS 17:00\nHORÁRIOS JÁ OCUPADOS:\n");
      exibir_horarios(cliente);
    }
    if(menu==3){
      printf("BUSCANDO CLIENTE:\n");
      printf("---------------------------------\n");
      if(cliente==NULL){
        printf("NENHUM CLIENTE CADASTRADO!\n");
      }else{
        busca = busca_cliente(cliente);
        if(busca!=NULL){
          printf("O nome do cliente buscado é %s com horario marcado para %dh%d - %dh%d\n",busca->nome,busca->horas,busca->minutos,busca->horafinal,busca->minutofinal);
        }
      }
      
    }
  }
  
  //Coleta de dados da lista para o arquivo
  Cadastro *g=cliente;
  arq=fopen("dados.txt","w");
  while (g!=NULL){
    fprintf(arq,"%s",g->nome);
    fprintf(arq,"%s",g->telefone);
    fprintf(arq,"%d\n",g->horas);
    fprintf(arq,"%d\n",g->minutos);
    fprintf(arq,"%d\n",g->horafinal);
    fprintf(arq,"%d\n",g->minutofinal);
    fprintf(arq,"%s",g->tipo_de_corte);
    g=g->prox;
  }
  fclose(arq);
  
  return 0;
}

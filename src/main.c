#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h> // contien to lower()
#include <time.h>
#define BR "\n"
#define TB "\t"
#define LINE "\t-------------------------------------------------------------\n"
#define HLINE "\n\t                ---------------          \n\n"
#define MIDLINE "\t----------------------------------------------------\n"
#define LongLine "\t----------------------------------------------------------------------------\n"
typedef struct  Produits{
	char code[20];
	char nom[20];
	int quantite ;
	float prix;
}Produit;


typedef struct Statistics{
	char nomPrdVendu[20];
	char dateDAchat[20];
	float prix;
	float totalTTC;
}Statistics;


FILE *fp;
bool isExist(Produit *list,char code[20] ,char nom[],int index){
	bool exist=false;
	//printf("\ttest de %d \n",code);
	int i;
	for(i=0;i<index;i++){
	//	printf("\t--test de %d \n",code==list[i].code);
		if(strcmp(list[i].code,code)==0 || strcmp(list[i].nom,nom)==0){
			return true ;
			break;
		}
	}
	return exist;
	
}
float calculateTTC(float prix){
	//printf("ttc:%f",(prix + (float)(15/100)*prix));
	return (prix + ((float)15/(float)100)*prix);
}
char * toLowerCase(char *str){
	int i=0;
	for(i=0; i<strlen(str);i++){
		str[i]=tolower(str[i]);
	}
	return str;
}

void PrintTableInOrder(Produit *list,int *index,int indice){
	int i,j;
			printf(LINE);
			if(indice==3){
				 printf("\t    NOM            |       PRIX TTC      |      QUANTITE     \n");
			}
			else printf("\t    NOM            |        PRIX           |       PRIX TTC  \n");
			//printf("--%d\n",*index);
			for(i=0;i<*index;i++){
				
				for(j=i+1;j<*index;j++){
					int val;
					val = (indice==1) ? strcmp(toLowerCase(list[i].nom) , toLowerCase(list[j].nom)) :list[i].prix-list[j].prix;
					if(val>0){
						Produit temp=list[i];
						list[i]=list[j];
						list[j]=temp;
					}
				}
				if(indice==3){
				printf("\t     %s                   %.2f DH                 %d         \n",list[i].nom,calculateTTC(list[i].prix),list[i].quantite);
				}else{
				printf("\t     %s                   %.2f DH                %.2f DH       \n",list[i].nom,list[i].prix,calculateTTC(list[i].prix));
				}			
			}
			printf(LINE);
}
void ajouterUnProduit(Produit *list,int *index){
	bool valid,essai=0;
	do{
		valid=true;
		printf(HLINE);
		printf("\tVeullez remplire les informations necessaires %d :\n",*index);
		printf(BR);
		printf("\tNotez : Tous les champs sont requis pour valider la formule\n");
		printf(BR);
		printf("\t*CODE : ");
		scanf(" %s",list[*index].code);
		//gets(list[index].code);
		//getint(list[index].code);
		printf("\t*NOM : ");
		scanf(" %s",list[*index].nom);
		if(isExist(list,list[*index].code,list[*index].nom,*index)){
			printf(BR);
			printf(LINE);
			printf("\t  [error] :Code ou Nom de produit deja existe !\n");
			printf(LINE);
			printf(BR);
			valid=false;
			continue;
		}
		printf("\t*QUANTITE : ");
		scanf("%d",&list[*index].quantite);
		printf("\t*PRIX : ");
		scanf("%f",&list[*index].prix);
		if(list[*index].quantite==0 || list[*index].prix==0) {
			printf(BR);
			printf(LINE);
			printf("\t   [error] :la quantite ou le prix ne soit pas null !\n");
			printf(LINE);
			printf(BR);
			valid=false;
		}
		++essai;
		//printf("essai %d",essai);
		//printf("qua,tity is :%d\n",list[index].quantite);
		
	}while(!valid && essai<3);
	if(valid) {
		printf("\n\t--------   [Produit ajoute avec sucess]   -------\n\n");
		// add to file :
		printf("%s %s %.2f %d\n", list[*index].nom, list[*index].code, list[*index].prix, list[*index].quantite);
		fp = fopen("produits.txt","a+");
        fprintf(fp, "%s %s %f %d\n", list[*index].nom, list[*index].code, list[*index].prix, list[*index].quantite);
        	//if(getchar() == EOF) brea
		
		//printf("%s %s %f %d\n",name,code,price,qnt);
		fclose(fp);
		
		
		
		
		
		++*index;
	
	}else{
		printf("\t  [error] :coordonees invalid (%essai fois) !\n",essai);
	}	
}
void ajouterPlusieurPrd(Produit *list,int *index){
	int nombreDeProduit,i=0,choix;
	printf(BR);
	printf("\tEnter le nombre de produits a ajouter : ");
	scanf("%d",&nombreDeProduit);
	while(i<nombreDeProduit){
		ajouterUnProduit(list,index);
		//printf("%d",*index);
		i++;
	}
	printf(BR);
	printf(HLINE);
	printf("\t1 : Ajouter d autre produits .\n");
	printf("\t0 : retour au menu principal.\n");
	printf(BR);
	printf("\t| ");
	scanf("%d",&choix);
	if(choix==1) ajouterPlusieurPrd(list,index); 
	
}

void listerLesProduits(Produit *list,int *index){
	int choix,i,j ;
	printf(BR);
	printf(HLINE);
	printf("\t1 : Lister selon l'order alphabetique croissant de nom .\n");
	printf("\t2 : Lister selon l'order decroissant de prix .\n");
	printf(BR);
	printf("\t0 : retour au menu principal.\n");
	printf(BR);
	printf("\t| ");
	scanf("%d",&choix);
	printf(BR);
	switch(choix){
		case 1 :	
			PrintTableInOrder(list,index,1);
			break;
		case 2 :
			PrintTableInOrder(list,index,2);
			break;
		case 0 :
			break;
		default :
			printf("\tchoix invalid !\n\n");
			printf("\tretour au menu principale...\n\n");
		//	sleep(1);
			break;			
	}
	printf(BR);
	printf("\t1 : Lister a nouveau .\n");
	printf("\t0 : retour au menu \n");
	printf("\t | ");
	scanf("%d",&choix);
	if(choix==1)  listerLesProduits(list,index);
	printf(BR);
	printf("\n\tRetour au menu principal...\n\n");
	//sleep(1);
	
	
}

Produit chercheUnPrd(Produit *list ,int *index,char code[],int *prdIndex,char chercherPar[]){
	Produit t;
	int i;
	bool found=false;
	for(i=0;i<*index;i++){
		if(strcmp(chercherPar,"code")==0){
			if(strcmp(list[i].code,code)==0) {
			//	printf("inside");
			*prdIndex=i;
			found=true;
			return list[i];
			}
			
		}else if(strcmp(chercherPar,"quantite")==0) {
			if(list[i].quantite == atoi(code)) {
			*prdIndex=i;
			found=true;
			 return list[i];
			}
		}
		
	}
	if(!found){
		printf(BR);
		printf("\t-----------       [PAS DE RESULTATS]     ------------\n");
		return t;	
		}
	
}

void acheterUnPrd(Produit *list,int *index,Statistics *stst,int *indexOfstst){
	char code[20];
	int quantite,valider,rep;
	int prdIndex=0;
	printf(BR);
	printf(HLINE);
	printf("\tVeillez remplire les infos de produits a acheter :\n");
	printf("\t|code de produit :");
	scanf("%s",code);
	printf("\t|quantite  :");
	scanf("%d",&quantite);
	printf(BR);
	printf("\t PRODUIT DESIRE : \n");
	printf(BR);
	
	Produit prdDesire = chercheUnPrd(list,index,code,&prdIndex,"code");
	float totalTTC=calculateTTC(prdDesire.prix)*quantite;
	printf(LongLine);
	printf("\t NOM          |         PRIX TTC       |       Quantite  |    Total  \n");
	printf("\t %s                     %.2f DH                %d           %.2f DH     \n",prdDesire.nom,calculateTTC(prdDesire.prix),quantite,totalTTC);
	printf(LongLine);
	printf(BR);
	printf("\t1 : valider la commande \n");
	printf("\t2 : chercher un nouveau produit \n");
	printf("\t0 : retour au menu principal \n");
	printf(BR);
	printf("\t | ");
	scanf("%d",&valider);
	if(valider==1){
		//valider la commande
		if(prdDesire.quantite>=quantite){
			printf("\n\t--------   [Commande valide avec sucess]   -------\n\n");	
			time_t dateDachat;
			dateDachat = time(NULL);
			//printf("date :%s",ctime(&dateDachat));
			// ADDING SELL TO STATISTICS
			strcpy(stst[*indexOfstst].dateDAchat,ctime(&dateDachat));
			strcpy(stst[*indexOfstst].nomPrdVendu,list[prdIndex].nom);
			stst[*indexOfstst].totalTTC=totalTTC;
			stst[*indexOfstst].prix=list[prdIndex].prix;
			++*indexOfstst;
			// INCREASING QUANTITY AFTER SELL
			list[prdIndex].quantite-=quantite;
			printf("\t1 : acheter un nouveau produit \n");
			printf("\t0 : retour au menu principal \n");
			printf("\t | ");
			scanf("%d",&rep);
			(rep==1) ? acheterUnPrd(list,index,stst,indexOfstst) : printf("\n\tRetour au menu principal...\n\n");
		}else{
			printf(BR);
			printf("\t  [error] :stock insufisant ( %d unitee restant ) !\n",prdDesire.quantite);
			printf(BR);
			printf(HLINE);
			printf("\t1 : acheter a moin quantite produit / changer le produit \n");
			printf("\t0 : retour au menu principal \n");
			printf("\t | ");
			scanf("%d",&rep);
			(rep==1) ? acheterUnPrd(list,index,stst,indexOfstst) : printf("\n\tRetour au menu principal...\n\n");
			printf(BR);
		}
	}else if(valider==2){
		acheterUnPrd(list,index,stst,indexOfstst);
	}else printf("\n\tRetour au menu principal...\n\n"); ;
	
	
}
void afficherLesStatistic(Statistics *stst,int *indexOfstst){
	int i,retour;
	float totalttc=0.0,max=0.0,min=0.0;
	printf(BR);
	printf(HLINE);
	printf(BR);
	printf("\t                  LES STATISTICS                \n");
	printf(BR);
	printf(LongLine);
	printf("\t    NOM          |      Total TTC    |                   Date            \n");
	for(i=0;i<*indexOfstst;i++){
		totalttc+=stst[i].totalTTC;
		if(stst[i].totalTTC>=max)  max=stst[i].totalTTC;
		if(stst[i].totalTTC<=stst[i+1].totalTTC) min = stst[i].totalTTC;
		printf("\t   %s                 %.2f                 %s                \n",stst[i].nomPrdVendu,stst[i].totalTTC,stst[i].dateDAchat);
	}
	printf(LongLine);
	printf(BR);
	printf("\tTotal des prix des produits vendus en journee courante : ");
	printf("%.2f DH\n",totalttc);
	printf("\tMoyenne des prix des produits vendus en journee courante : ");
	printf("%.2f DH\n",totalttc/(float)i);
	printf("\tMax des prix des produits vendus en journee courante : ");
	printf("%.2f DH\n",max);
	printf("\tMin des prix des produits vendus en journee courante : ");
	printf("%.2f DH\n",min);
	printf(BR);
	printf("\t0 : retour au menu principal \n");
	printf("\t | ");
	scanf("%d",&retour);
	printf("\n\tRetour au menu principal...\n\n");
	//sleep(1);
	
}
void printSearchedPrd(Produit *list ,int *index,int *prdIndex){
	int choix,qntEntre;
	char codeEntre[20];
	Produit returnedPrd ;
	printf(HLINE);
	printf("\t             CHERCHER UN PRODUIT              \n");
	printf(BR);
	printf("\t1 : chercher par code \n");
	printf("\t2 : chercher par quantite \n");
	printf("\t0 : retour au menu \n");
	printf("\t | ");
	scanf("%d",&choix);
	if(choix==1){
		printf("\t | CODE : ");
		scanf("%s",codeEntre);
		 //chercheUnPrd(Produit *list ,int *index,int code,int *prdIndex,char chercherPar[]){
		returnedPrd = chercheUnPrd(list ,index,codeEntre,prdIndex,"code");
		//(strcmp(returnedPrd.nom,NULL)==0) ? printSearchedPrd(list,index,prdIndex) : printf("\t-----------       [RESULTATS]     ------------\n");
				
	}else if(choix==2){
		printf("\t | QUANTITE : ");
		scanf("%d",&qntEntre);
		returnedPrd = chercheUnPrd(list ,index,qntEntre,prdIndex,"quantite");
	}
	else{
		printf("\n\tRetour au menu principal...\n\n");
	}
	
	printf(LINE);
	printf("\t    NOM            |        PRIX           |       PRIX TTC  \n");
	printf("\t     %s                  %.2f DH                %.2f DH       \n",returnedPrd.nom,returnedPrd.prix,calculateTTC(returnedPrd.prix));
	printf(LINE);
	printf(BR);
	printf("\t1 : chercher autre \n");
	printf("\t0 : retour au menu \n");
	printf("\t | ");
	scanf("%d",&choix);
	(choix==1) ? printSearchedPrd(list,index,prdIndex) : printf("\n\tRetour au menu principal...\n\n");
	sleep(1);
	
}
void afficherEtatDeStock(Produit *list,int *index){
	int i,tabIndex,j=0,choix;
	Produit tab[100];
	printf(HLINE);
	printf("\t              ETAT DE STOCK              \n");
	printf(BR);
	for(i=0;i<*index;i++){
		if(list[i].quantite<=3){
			tab[j]=list[i];
			j++;
		}
	}
	PrintTableInOrder(tab,&j,3);
	printf(BR);
	printf("\t0 : retour au menu \n");
	printf("\t | ");
	scanf("%d",&choix);
	printf(BR);
	printf("\n\tRetour au menu principal...\n\n");
	sleep(1);
	
}
void alimenterLeStock(Produit *list,int *index){
	char code[20];
	int i,qntEntre,choix;
	printf("\t             ALIMENTATION DE STOCK              \n");
	printf(BR);
	printf("\tCode de produit a alimenter : ");
	scanf("%s",code);
	printf("\tQuantite a alimenter : ");
	scanf("%d",&qntEntre);
	for(i=0;i<*index;i++){
		if(strcmp(list[i].code,code)==0){
			list[i].quantite+=qntEntre;
		}
	}
	printf("\n\t--------   [alimentation faite avec sucess]   -------\n\n");
	printf(BR);
	printf("\t1 : alimenter autre produit \n");
	printf("\t0 : retour au menu \n");
	printf("\t | ");
	scanf("%d",&choix);
	if(choix==1) alimenterLeStock(list,index);
	
}
void supprimerUnProduit(Produit *list ,int *index){
	char code[20];
	int i,j,position=0;
	printf("\t           SUPPRIMER UN PRODUIT              \n");
	printf(BR);
	printf("\tCode de produit  | ");
	scanf("%s",code);
	Produit prd =chercheUnPrd(list ,index,code,&position,"code");
	//printf("%d",position);
	//printf(list[position].nom);
	if(list[position].quantite==0){
		printf(BR);
		printf(LINE);
		printf("\t  [error] :code ne correspond pas a un produit declare  !\n");
		printf(LINE);
		supprimerUnProduit(list,index);
	}else{
		if(position==0&&*index==0) {
			list[position] = list[position+1]; 
			--*index;
		}
		else{
			for (i = position; i < *index; i++)  
	        {  
	            list[i] = list[i+1]; 
	        }
			--*index;	
		}
		
    	printf("\n\t--------   [supprission faite avec sucess]   -------\n\n");
    	printf(BR);
	}
	
	
}
int main() {
	
	// variable declaration aria 
	int choix,num=-1,indexStst=0,i;
	Produit listDesProduits[1000];
	Statistics statisticsDeVentes[1000];

	// files 
	  	char c;
 		char name[20],code[20];
 		float price;
 		int qnt;
 		FILE *fp;
        fp = fopen("produits.txt","r");
        while(1){
        	if(feof(fp)){
        		break;
			}
        	fscanf(fp, "%s %s %f %d", listDesProduits[num].nom, listDesProduits[num].code, &listDesProduits[num].prix, &listDesProduits[num].quantite);
        	num++;
        	
        	//if(getchar() == EOF) break;
		}
		
		//printf("%s %s %f %d\n",name,code,price,qnt);
		fclose(fp);
         
	
	
	
	
	// app introdution 
	printf(BR);
	printf(MIDLINE);
	printf("\t|            GESTION DE PHARMACIE                  |\n");
	printf("\t|                                                  |\n");
	printf("\t|                  By mounir                       |\n");
	printf(MIDLINE);
	printf(BR);
	do{
		//printf("num :%d",num);
		printf(BR);
		printf("\t----------------- MENU PRINCIPAL -------------------\n");
		printf(BR);
		printf("\t1  : Ajouter un nouveau produit.\n");
		printf("\t2  : Ajouter plusieurs nouveaux produits.\n");
		printf("\t3  : Lister les produits.\n");
		printf("\t4  : Acheter un produit.\n");
		printf("\t5  : Chercher un produit.\n");
		printf("\t6  : Etat de stock.\n");
		printf("\t7  : Alimenter le stock.\n");
		printf("\t8  : Supprimer un produit.\n");
		printf("\t9  : Afficher les statistiques de vente.\n\n");
		printf("\t0  : Sortir de program.\n");
		printf(BR);
		printf(MIDLINE);
		printf(BR);
		printf("\tVeulliez selectionez un choix pour continuer... : ");
		scanf("%d",&choix);
		printf(BR);
		
		switch(choix){
			case 1 :
				ajouterUnProduit(listDesProduits,&num);	
				break;
			case 2 :
				
				ajouterPlusieurPrd(listDesProduits,&num);
				break;
			case 3 :
				listerLesProduits(listDesProduits,&num);
				break;
			case 4 :
				acheterUnPrd(listDesProduits,&num,statisticsDeVentes,&indexStst);
				break;
			case 5 :
				printSearchedPrd(listDesProduits,&num,&i);
				break;
			case 6 :
				afficherEtatDeStock(listDesProduits,&num);
				break;
			case 7 :
				alimenterLeStock(listDesProduits,&num);
				break;
			case 8 :
				supprimerUnProduit(listDesProduits,&num);
				break;
			case 9 :
				afficherLesStatistic(statisticsDeVentes,&indexStst);
				break;
				
			case 0 :
				printf(BR);
				printf("\tfermeture de program..");
				sleep(1);
				printf(BR);printf(BR);
				printf("\t------------------ PROGRAM FERME ------------------\n");
				printf("\t|");
				printf("\t                                           |\n");
				printf("\t|              Hope you enjoy usig it              |\n");
				printf("\t|");
				printf("\t                                           |\n");
				printf(MIDLINE);
				break;
			default:
				printf("\tchoix invalid !\n\n");
				printf("\tretour au menu principale...\n\n");
				sleep(1);
				break;
				
		}	
	}while(choix!=0);
	
	return 0;
}

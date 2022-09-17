#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define BR "\n"
#define TB "\t"
#define LINE "\t---------------------------------------------------\n"
#define HLINE "\t            ----          \n"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
typedef struct  Produits{
	int code ;
	char nom[20];
	int quantite ;
	float prix;
}Produit;
bool isExist(Produit *list,int code ,char nom[],int index){
	bool exist=false;
	//printf("\ttest de %d \n",code);
	int i;
	for(i=0;i<index;i++){
	//	printf("\t--test de %d \n",code==list[i].code);
		if(list[i].code==code || strcmp(list[i].nom,nom)==0){
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
void ajouterUnProduit(Produit *list,int *index){
	bool valid;
	do{
		valid=true;
		printf(HLINE);
		printf("\tVeullez remplire les informations necessaires %d :\n",*index);
		printf(BR);
		printf("\tNotez : Tous les champs sont requis pour valider la formule\n");
		printf(BR);
		printf("\t*CODE : ");
		scanf(" %d",&list[*index].code);
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
		scanf(" %d",&list[*index].quantite);
		printf("\t*PRIX : ");
		scanf(" %f",&list[*index].prix);
		if(list[*index].quantite==0 || list[*index].prix==0) {
			printf(BR);
			printf(LINE);
			printf("\t[error] :la quantite ou le prix ne soit pas null !\n\n");
			printf(LINE);
			printf(BR);
			valid=false;
		}
		//printf("qua,tity is :%d\n",list[index].quantite);
		
	}while(!valid);
	if(valid) {
		printf("\n\t----[Produit ajoute avec sucess]----\n\n");
		++*index;
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
			//printf("`\t prd 1 code : %d\n",list[0].code);
			//printf("`\t prd 2 code : %d\n",list[1].code);
			printf(LINE);
			printf("\t NOM        |       PRIX         |       PRIX TTC\n");
			//printf("--%d\n",*index);
			for(i=0;i<*index;i++){
				
				for(j=i+1;j<*index;j++){
					//printf("---j=%d\n",j);
					int cmpInASCII = strcmp(list[i].nom,list[j].nom);
					//printf("cmpInASCII :%d",cmpInASCII);
					if(cmpInASCII>0){
						Produit temp=list[i];
						list[i]=list[j];
						list[j]=temp;
					}
				}
				printf("\t  %s         |      %.2f DH      |       %.2f DH     \n",list[i].nom,list[i].prix,calculateTTC(list[i].prix));
				
			}
			printf(LINE);
			
			
			
			
			
	}
	
}

int main() {
	
	// variable declaration aria 
	int choix,num=0;
	Produit listDesProduits[1000];
	//int *a = malloc(sizeof(Produit) * n); //pour avoir une taille de list elastique
	
	// app introdution 
	printf(BR);
	printf(LINE);
	printf("\t|            GESTION DE PHARMACIE                  |\n");
	printf(LINE);
	printf(BR);
	do{
		//printf("num :%d",num);
		printf(BR);
		printf("\t1  : Ajouter un nouveau produit.\n");
		printf("\t2  : Ajouter plusieurs nouveaux produits.\n");
		printf("\t3  : Lister les produits.\n");
		printf("\t4  : Acheter un produit.\n");
		printf("\t5  : Chercher un produit.\n");
		printf("\t6  : Etat de stock.\n");
		printf("\t7  : Alimenter le stock.\n");
		printf("\t8  : Supprimer un produit.\n");
		printf("\t9  : Ajouter un produit\n");
		printf("\t10 : Afficher les statistiques de vente.\n");
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
				break;
			case 5 :
				break;
			case 6 :
				break;
			case 7 :
				break;
			case 8 :
				break;
			case 9 :
				break;
			case 10 :
				break;
			case 0 :
				printf(BR);
				printf("\tfermeture de program..");
				sleep(1);
				printf(BR);
				printf("\t---------------- 	PROGRAM FERME -----------------\n"); 
			default:
				printf(BR);
				printf("\tchoix non trouvé !\n");
				break;
				
		}
		
		
	}while(choix!=0);
	
/*	for(details_t* it = emp_details; (*it).name != NULL; it++)
//  { printf("..", (*it).name, (*it).data); }*/
	return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct Elemento{
    struct Elemento*sx;
    struct Elemento*dx;
    struct Elemento*genitore;
    int distanza; 
    int numero_macchine;
    int macchine[512];
}Nodo;

typedef Nodo* stazione; 

typedef struct lista{
    int distanza;
    struct lista*next;
}t_node;

typedef struct catena{
    int distanza;
    struct catena*next;
    int differenza;
}charm;

typedef charm*chain;

typedef t_node*listina;
chain percorso(stazione alberone, int partenza,int arrivo);
stazione nuovo(int dist,int num, int v[]);
stazione elimina_nodo(stazione s, stazione new);
stazione inserisci(stazione s, stazione nodo); 
int ricerca(stazione s, int dist);
listina insintesta(listina l, int dist);
void aggiungi_auto(stazione s,int dist,int car);
void elimina_auto(stazione s,int dist, int car);
int max_array(int v[]);
chain insincoda(chain c, int distanza, int diff);
chain insdavanti(chain c, int distanza, int diff);
stazione successore(stazione radice,int distanza);
stazione minimo(stazione s);
listina insinfondo(listina l, int distanza);
int percorso_possibile (stazione s, int partenza, int arrivo);
stazione ricerca_nodo(stazione s, int dist);
stazione massimo(stazione s);
stazione predecessore(stazione radice,int distanza);
listina percorso_diretto(stazione s, int partenza, int arrivo);
void stampaPercorso(listina l);
void stampa(chain c);
chain rovescia(chain c);
int main(){
    char comando[20];
    int distanza, numero;
    int autonomie[512];
    int autonomia;
    int partenza, arrivo;
    stazione alberone=NULL;
   
    FILE* fp=stdin;

    while(fscanf(fp,"%s",comando)!=EOF){
        if(strcmp(comando, "aggiungi-stazione")==0){
            if(fscanf(fp,"%d %d", &distanza, &numero)!=EOF){
                int k;
                for(k=0; k<512; k++){
                    autonomie[k]=0;
                }
                if(numero==0){
                    if(fscanf(fp,"%d", &autonomie[0])!=EOF){
                    }
                }
                else{
                for(int i=0; i<numero; i++){
                if(fscanf(fp,"%d",&autonomie[i])!=EOF){
                }
                }
                }
                  
            }
                if(ricerca(alberone,distanza)==1){
                    printf("non aggiunta\n");
                }
                else{
                stazione new=nuovo(distanza, numero, autonomie);
                alberone=inserisci(alberone,new); 
                printf("aggiunta\n");
                
                }
               
        }
         
        if(strcmp(comando, "demolisci-stazione")==0){
            if(fscanf(fp,"%d", &distanza)!=EOF){
              
                if((ricerca(alberone, distanza))==1){
                    alberone= elimina_nodo(alberone, ricerca_nodo(alberone,distanza));
                    printf("demolita\n");
                }
                else{
                    printf("non demolita\n");
                }
               
            }
           
            
        }
           
        
        if(strcmp(comando, "aggiungi-auto")==0){
           
            if(fscanf(fp, "%d",&distanza)!=EOF){
                if(fscanf(fp, "%d", &autonomia)!=EOF){
             aggiungi_auto(alberone, distanza,autonomia);
    
            }
            }
            
            
        }
            if(strcmp(comando, "rottama-auto")==0){
           
            if(fscanf(fp, "%d %d", &distanza, &autonomia)!=EOF){
              elimina_auto(alberone,distanza,autonomia);
    
            } 
            
            
                  
        }
        
        
        if(strcmp(comando,"pianifica-percorso")==0){
            if(fscanf(fp, "%d %d", &partenza, &arrivo)!=EOF){
                if(partenza==arrivo){
                        printf("%d\n",partenza);
                    }
                    else if(partenza!=arrivo){
                if(percorso_possibile(alberone,partenza,arrivo)){
                    if(partenza<arrivo){
                        listina listus=percorso_diretto(alberone, partenza,arrivo);
                        stampaPercorso(listus);
                       
                    }
                     if(partenza>arrivo){                    
                    chain l=percorso(alberone,partenza,arrivo);
                    stampa(l);
               
                    }
                    
                }
                else{
                    printf("nessun percorso\n");
                }
            }
            
        } 
        
        
    }
    }
    
    



    
 
fclose(fp);

return 0;
    
}

stazione nuovo(int dist,int num, int v[]){
    stazione s=(stazione)malloc(sizeof(Nodo));
    s->sx=NULL;
    s->dx=NULL;
    s->genitore=NULL;
    s->distanza=dist;
    s->numero_macchine=num;
    for(int i=0; i<512;i++){
    s->macchine[i]=v[i];
}
return s;

}
stazione inserisci(stazione s, stazione z){
    stazione y=NULL;
    stazione x=s;
    if(s==NULL){
        return z;
    }
    while(x!=NULL){
        y=x;
        if(z->distanza<x->distanza){
            x=x->sx;
        }
        else{
            x=x->dx;
        }
    }
    z->genitore=y;
    if(y==NULL){
        s=z;
    }
    else if(z->distanza<y->distanza){
        y->sx=z;
    }
    else{
        y->dx=z;
    }
    return s;
  

}

stazione elimina_nodo(stazione s, stazione z){
    stazione y=NULL;
    stazione x=NULL;
    if(z->sx==NULL || z->dx==NULL){
        y=z;

    }
    else{
        y=successore(s,z->distanza);
    }
    if(y->sx!=NULL){
        x=y->sx;
    }
    else{
       x=y->dx;
    }
    if(x!=NULL){
        x->genitore=y->genitore;
    }
    if(y->genitore==NULL){
        s=x;
    }
    else if(y==y->genitore->sx){
        y->genitore->sx=x;
    }
    else{
        y->genitore->dx=x;
    }
    if(y->distanza!=z->distanza){
        z->distanza=y->distanza;
        z->numero_macchine=y->numero_macchine;
            for(int i=0; i<512; i++){
                z->macchine[i]=y->macchine[i];
            }

    }
    free(y);
    return s;


}



int ricerca(stazione s, int dist){
    if(s==NULL){
        return 0;
    }
    if(s->distanza==dist){
        return 1;
    }
    if(s->distanza<dist){
        return ricerca(s->dx,dist);
    }
   
    return ricerca(s->sx,dist);
}

void aggiungi_auto(stazione s,int dist, int car){
    int i;
    if(s==NULL){
        printf("non aggiunta\n");
        return;
    }
    if(s->distanza==dist){
        if(s->numero_macchine<512){
        for(i=0; i<512; i++){
            if(s->macchine[i]==0){
                s->macchine[i]=car;
                s->numero_macchine++;
                printf("aggiunta\n");
                return;
            }
        }
        }
        else{
            printf("non aggiunta\n");
            return;
        }
    }
    else if(s->distanza<dist){
        aggiungi_auto(s->dx,dist,car);
        return;
    }
    else{
    aggiungi_auto(s->sx,dist,car);
    return;
    }

}


void elimina_auto(stazione s,int dist, int car){
    if(s==NULL){
       printf("non rottamata\n");
        return;
    }
    if(s->distanza==dist){
            for(int i=0; i<512;i++){
                if(s->macchine[i]==car){
                    s->macchine[i]=0;
                    (s->numero_macchine)--;
                    printf("rottamata\n");
                    return;
                }
            }
            printf("non rottamata\n");
            return;
    }
    if(s->distanza<dist){
        elimina_auto(s->dx,dist,car);
        return;
    }
    elimina_auto(s->sx,dist,car);
    return;
    
}
int max_array(int a[]){
    int tmp=a[0];
    for(int i=1; i<512;i++){
        if(a[i]>tmp){
            tmp=a[i];
        }
    }
    return tmp;
}
stazione successore(stazione radice,int chiave){
 stazione x=ricerca_nodo(radice,chiave);
 if(x->dx!=NULL){
    return minimo(x->dx);
 }
 stazione y=x->genitore;
 while(y!=NULL && x==y->dx){
 x=y;
 y=y->genitore;

}
return y;

}
stazione minimo(stazione s){
    while((s->sx)!=NULL){
        s=s->sx;
    }
    return s;
}
stazione massimo(stazione s){
    while(s->dx!=NULL){
        s=s->dx;
    }
    return s;
}


int percorso_possibile (stazione s, int partenza, int arrivo){
    //per ogni stazione che considero trovo il massimo//
    stazione back=NULL;
    back=ricerca_nodo(s, partenza);
    stazione destinazione=ricerca_nodo(s, arrivo);
    if((back!=NULL) && (destinazione!=NULL)){
        //caso in cui arrivo è maggiore della stazione di partenza//
        if(destinazione->distanza>back->distanza){
        while(back->distanza!=arrivo){
         //trovo il massimo della stazione di partenza//
        int max1=max_array(back->macchine);
        int distanza_attuale=back->distanza;
        //trovo stazione successiva//
        back=successore(s,back->distanza);
        //adesso ho la stazione successiva in back a quella iniziale//
        if(max1<((back->distanza)-distanza_attuale)){
            return 0; 
        }  
    }
    return 1;
        }
       else if(destinazione->distanza<back->distanza){
            //cioè se devo andare per esempio dalla stazione 50 alla 20//
            while(back->distanza!=arrivo){ //in back distanza ho 50 e in arrivo ho 20//
            int max1=max_array(back->macchine); //ho la macchina max della stazione 50//
            int distanza_attuale=back->distanza; //=50//
            back=predecessore(s,back->distanza); //ora ho per esempio 40//
            if(max1<(distanza_attuale-back->distanza)){
                return 0;
            }

            }
            return 1;

        }
    
    }
    else{
    return 0;
    }
    return 1;
}
stazione ricerca_nodo(stazione s, int dist){
    if(s==NULL){
        return s;
    }
    if(s->distanza==dist){
        return s;
    }
    if(s->distanza<dist){
        return ricerca_nodo(s->dx,dist);
    }
   
    return ricerca_nodo(s->sx,dist);
}
stazione predecessore(stazione radice,int chiave){
    stazione x=ricerca_nodo(radice,chiave);
    if(x->sx!=NULL){
        return massimo(x->sx);
    }
    stazione y=x->genitore;
    while(y!=NULL && x==y->sx){
        x=y;
        y=y->genitore;
    }
    return y;
}

listina insinfondo(listina l, int distanza){
    if(l==NULL){
        return insintesta(l, distanza);
    }
    l->next=insinfondo(l->next, distanza);
    return l;
}

listina insintesta(listina l, int dist){
    listina punt;
    punt=(listina)malloc(sizeof(t_node));
    punt->distanza=dist;
    punt->next=l;
    return punt;


}
chain insdavanti(chain c, int distanza, int diff){
    chain ch;
    ch=(chain)malloc(sizeof(charm));
    ch->distanza=distanza;
    ch->differenza=diff;
    ch->next=c;
    return ch;
}
chain insincoda(chain c, int distanza, int diff){
    if(c==NULL){
        return insdavanti(c,distanza,diff);
    }
    c->next=insincoda(c->next, distanza, diff);
    return c;
}
listina percorso_diretto(stazione s, int partenza, int arrivo){
    stazione t=ricerca_nodo(s,arrivo);
    //ora in t ho il nodo di arrivo//
    listina l=NULL;
    //scorro albero dalla partenza finchè non trovo il primo nodo che mi porta all'arrivo direttamente//
    //per farlo faccio somma distanza e autonomia massima, la prima volta che trovo un valore >=196 mi fermo//
    stazione p=ricerca_nodo(s,partenza);
    stazione backup=p;
while(t->distanza!=p->distanza){
    while(backup->distanza+max_array(backup->macchine)<t->distanza){
        backup=successore(s,backup->distanza);
        
    }
    //sono uscita e ho trovato 178
    l=insintesta(l,backup->distanza);
    t=backup;
    backup=p;
}
l=insinfondo(l, arrivo);
return l;
}
void stampaPercorso(listina l) {
    while (l != NULL) {
        printf("%d ",l->distanza);
        l = l->next;
    }
    printf("\n");
}
void stampa(chain c){
    while(c!=NULL){
        printf("%d ",c->distanza);
        c=c->next;
    }
    printf("\n");
}

chain percorso(stazione alberone, int partenza,int arrivo){
    chain l=NULL;
    stazione s=ricerca_nodo(alberone, arrivo);
    //creo lista che mi da il minor numero di tappe che posso fare//

    //devo trovare la prima dal fondo che arrivi a una stazione precedente indicata//
    stazione t=ricerca_nodo(alberone,partenza);
    stazione b=t; //b parte dalla partenza che è più lontana//
    //temp parte dall'arrivo//
    //scorro i nodi da b per trovare il maggiore che abbia distanza-max_array <= di b//
    stazione temp=s;
    while(temp->distanza!=partenza){
        
        while((b->distanza-max_array(b->macchine))>temp->distanza){
          b=predecessore(alberone,b->distanza);


        }
        
        l=insdavanti(l, b->distanza, b->distanza-max_array(b->macchine));
        //printf("%d\n", b->distanza);
        temp=b;
        b=t;
    
    }
    
    l=insincoda(l, arrivo, 0);
  



    //confronto il 263 con il 258 e controllo che arrivi al 235, se trovo un minore comune che arrivi a 
    //235 allora lo metto al posto di 258//
   chain h=l;
    chain speranza=h->next;

    while(speranza->distanza!=arrivo){
            //confronto h con speranza//
            if(h->differenza>=speranza->differenza){
                //scorro tutti quelli a cui 811 arriva e tengo traccia di quello che percorre più spazio//
                stazione k=ricerca_nodo(alberone, h->distanza);
                stazione temp=predecessore(alberone,k->distanza);
                //ora temp punta al predecessore di k, lo salvo come minimo di differenza//
                int minimo_distanza=temp->distanza; 
                int minimo_differenza=temp->distanza-max_array(temp->macchine);
                k=temp;
                while(h->differenza<=temp->distanza){
                    if(minimo_differenza>=temp->distanza-max_array(temp->macchine)){
                        minimo_distanza=temp->distanza;
                        minimo_differenza=temp->distanza-max_array(temp->macchine);
                    }
                    temp=predecessore(alberone,temp->distanza);
                }
                speranza->distanza=minimo_distanza;
                speranza->differenza=minimo_differenza;
                h=speranza;
                speranza=speranza->next;

                
            }
            else if(speranza->differenza>h->differenza){
                stazione k=ricerca_nodo(alberone, speranza->distanza);
                stazione temp=predecessore(alberone,k->distanza);
                 int minimo_distanza=temp->distanza; 
                int minimo_differenza=temp->distanza-max_array(temp->macchine);
                k=temp;
                while(speranza->differenza<=temp->distanza){
                    if(minimo_differenza>=temp->distanza-max_array(temp->macchine)){
                        minimo_distanza=temp->distanza;
                        minimo_differenza=temp->distanza-max_array(temp->macchine);
                    }
                    temp=predecessore(alberone,temp->distanza);
                }
                speranza->distanza=minimo_distanza;
                speranza->differenza=minimo_differenza;
                h=speranza;
                speranza=speranza->next;

            }

    }
 
    l=rovescia(l);

    
    
   chain c=l;
   chain te=c->next;
   chain he=te->next;
   while(te->distanza!=partenza){
    //voglio sapere se esiste una stazione minore di 39 che arriva a 19, a cui arrivo da 209//
    stazione s=ricerca_nodo(alberone, te->distanza);
    int minimo_distanza=s->distanza;
    int minimo_differenza=te->differenza;
    while(s->distanza>=he->differenza){
        if((minimo_distanza>s->distanza)&&(s->distanza-max_array(s->macchine)<=c->distanza)){
                minimo_distanza=s->distanza;
                minimo_differenza=s->distanza-max_array(s->macchine);
        }
        s=predecessore(alberone, s->distanza);
    }
    te->distanza=minimo_distanza;
    te->differenza=minimo_differenza;
    c=te;
    te=he;
    he=he->next;
   }
   l=rovescia(l);

return l; 

}

chain rovescia(chain c){
    chain sec, coda, tmp;
    coda=c;
    sec=c->next;
    coda->next=NULL;
    tmp=coda;
    while(sec!=NULL){
        coda=sec;
        sec=sec->next;
        coda->next=tmp;
        tmp=coda;
    }
    return coda;
}
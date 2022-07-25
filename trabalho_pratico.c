#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>



typedef struct {
    int id;
    int duracao; //segundos
    char titulo[200];
    char artista[200];
    char album[200];
}musica;

typedef struct musica_no {
    musica *musica;
    struct musica_no *prox;
    struct musica_no *ant;
}musica_no;

typedef struct playlist_no{
    musica *musica;
    struct playlist_no *prox;
}playlist_no;

typedef struct lplaylist_no{
    int id;
    char nome[200];
    playlist_no *musicas;
    struct lplaylist_no *prox;
}lplaylist_no;




musica* search_music(musica_no* node, int id_music);
void registerMusic(musica_no *node, int id );
void printMusic( musica_no *node);
void createLpPlaylist(lplaylist_no *lp_node, musica_no *node);
void search_playlist(lplaylist_no *lp_node);
void printPlaylist(playlist_no *node);
void deleteMusic(musica_no *node, lplaylist_no *lp_node);
void deleteMusicFromPlaylist(int id_music, playlist_no *node);
void deleteMusicFromList(musica_no *node);


musica_no *cria_lista_mus() {
    musica_no *cabeca;
    cabeca = malloc(sizeof(musica_no));
    cabeca->ant = NULL;
    cabeca->prox = NULL;
    return cabeca;
}

lplaylist_no *cria_lista_playlist(){ //função que cria um nó de uma lista de playlist
    lplaylist_no *cabeca = malloc(sizeof(lplaylist_no));
    cabeca->prox = NULL;
    return cabeca;
}

playlist_no * cria_playlist(){
    playlist_no *novo = malloc(sizeof(playlist_no));  
    novo->prox = novo;
    return novo;
}



int main()
{
    int opc, id;
    musica_no *listamusicas = cria_lista_mus(); //cria lista vazia...
    // playlist_no *playlist = cria_playlist();
    lplaylist_no *listaplaylist = cria_lista_playlist();



    for (;;)
    {
        printf(
               "*-----------------------*\n"
               " (1) - ADICIONAR MUSICA \n"
               " (2) - IMPRIMIR LISTA \n"
               " (3) - CRIAR PLAYLIST \n"
               " (4) - IMPRIMIR PLAYLIST  \n "
               " (5) - DELETAR MUSICA  \n "
               "*-----------------------*\n");

               printf(" > "); 
               scanf("%d",&opc);
               system("cls");

               switch(opc)
               {
                   default:
                       fprintf(stdout,"\n comando invalido \n");
                       break;
                   case 1:
                        printf("\n Informe o id: "); 
               		    scanf("%d", &id);
                        system("cls");
                        registerMusic(listamusicas, id);
                       break;
                   case 2:
                        printMusic(listamusicas);
                        break;
                   case 3:
                        createLpPlaylist(listaplaylist ,listamusicas);
                        break;

                    case 4:
                        search_playlist(listaplaylist);
                        break;

                    case 5: 
                        deleteMusic(listamusicas, listaplaylist);
                        break;
                        
               }
               if (opc == 0) {
                   break;}
    }
    return ( 0 );
}

void registerMusic(musica_no *node, int id)
{
   
    musica *new_pointer = malloc(sizeof(musica));

    if (!new_pointer) { 
        return;
    }
    char alb[200];
    char artista[200];
    char title[200];

    new_pointer->id = id;
    
    printf("\n Informe o titulo: "); 
    scanf(" %[^\n]",title);
    system("cls");
    printf("\n Informe o artista: ");
    scanf(" %[^\n]",artista);
    system("cls");
    printf("\n Informe o album: "); 
    scanf(" %[^\n]",alb);
    system("cls");
    printf("\n Informe a duracao da musica: "); 
    scanf("%d",&(new_pointer->duracao));

    strcpy(new_pointer->album,alb);
    strcpy(new_pointer->artista,artista);
    strcpy(new_pointer->titulo,title);

    musica_no* novamusica = (musica_no*)malloc(sizeof(musica_no));
    
	novamusica->musica = new_pointer;
	
	novamusica->prox = node->prox;
    novamusica->ant= node;
    if (node->prox !=NULL) {
        node->prox->ant = novamusica;
    }
    node->prox = novamusica;

    

}





void printMusic( musica_no *node)
{
    musica_no *pointer;

    int h;
    int m;
    int s;


    for (pointer = (node)->prox ; pointer != NULL; pointer=pointer->prox)
    {
        h = (pointer->musica->duracao / 3600);
        m = (pointer->musica->duracao - (3600 * h)) / 60;
        s = (pointer->musica->duracao - (3600 * h) - (m * 60));

        printf(
               "ID: %d \n"
               "TITULO : %s \n"
               "ARTISTA: %s \n"
               "ALBUM: %s \n"
               "DURACAO: %d: %d : %d \n",
               pointer->musica->id,
               pointer->musica->titulo,
               pointer->musica->artista,
               pointer->musica->album,h,m,s);

    }
}






musica* search_music (musica_no* node, int id_music){
    musica_no *musicAux = node->prox;
    
    while (musicAux){
        if(musicAux->musica->id == id_music){
            return musicAux->musica;
        }
        musicAux = musicAux->prox;
    }
    return NULL;

}


void createLpPlaylist (lplaylist_no *lp_node,musica_no *node_2 ){
    playlist_no *playlist = cria_playlist();
    playlist_no *playlistAux = cria_playlist(); 
    lplaylist_no *listaplaylistAux = cria_lista_playlist();
    musica* musica;
    char ids [300];
    char *idMusicList = NULL;
    int idPlaylist;
    


    printf("\n Informe os IDs das Musicas: "); 
    setbuf(stdin, NULL); 
    fgets(ids, 400, stdin);
    printf("\n Informe o ID da playlist: ");
    scanf("%d",&idPlaylist);
    
    printf("\n Informe o nome da playlist: ");
    setbuf(stdin, NULL);
   
    fgets(listaplaylistAux->nome, 200, stdin);

    idMusicList = strtok(ids, " ");

    musica = search_music(node_2, atoi(idMusicList));
    playlistAux->musica = musica;
    playlistAux->prox = playlist;
    playlist->prox = playlistAux;

    while(idMusicList != NULL){
        playlist_no *playlistAux2 = cria_playlist(); 
        musica = search_music(node_2, atoi(idMusicList));
        playlistAux2->musica = musica;
        playlistAux2->prox = playlistAux;
        playlist->prox = playlistAux2;
        
        idMusicList = strtok(NULL, " ");

    }

    listaplaylistAux->id = idPlaylist;
    listaplaylistAux->musicas = playlist;
    if(listaplaylistAux->prox != NULL){
        listaplaylistAux->prox = lp_node->prox;
    }else{
        listaplaylistAux->prox = NULL;
    }

    lp_node->prox = listaplaylistAux;

    printf("\nPlaylist com ID %d criada com sucesso!\n", idPlaylist);

  


    
    }

void search_playlist(lplaylist_no *lp_node){
    lplaylist_no *listaplaylistAux;
    int idPlaylist;
    int flag;
    printf("\n Informe o ID da Playlist:");
    setbuf(stdin, NULL);
    scanf("%d", &idPlaylist);

    listaplaylistAux = lp_node->prox;
    while(listaplaylistAux){
        if(listaplaylistAux->id == idPlaylist){
            flag = 1;
            printf("Nome da Playlist: %s\n", listaplaylistAux->nome);
            printPlaylist(listaplaylistAux->musicas);
            break;
        }else{
            flag= 0;
        }
        listaplaylistAux = listaplaylistAux->prox;
    }
    if(flag == 0){
        printf("\n Playlist não encontrada !");
    }

}





void printPlaylist (playlist_no *node){
    
    playlist_no *playlistAux = node->prox;
    printf("entrouu!!!");
    if(!playlistAux){
        printf("\n Nenhuma musica encontrada");
    }
    do{
        printf("ID da musica: %d\n", playlistAux->musica->id);
        printf("Titulo: %s\n", playlistAux->musica->titulo);
        printf("Artista: %s\n", playlistAux->musica->artista);
        printf("Album: %s\n", playlistAux->musica->album);
        playlistAux = playlistAux->prox;
    }while(playlistAux != node);



    

    }


void deleteMusic(musica_no* node, lplaylist_no *lp_node){
    int idMusic;
    lplaylist_no *playlistAux = lp_node->prox;
    musica_no *musicListAux = node->prox;
    
    printf("\nREMOVER MUSICA");
    printf("\nDigite o ID da musica: ");
    setbuf(stdin, NULL);
    scanf("%d", &idMusic);

    while(playlistAux){
        deleteMusicFromPlaylist(idMusic, playlistAux->musicas);
        playlistAux = playlistAux->prox;
    }


      while(musicListAux){
         if (musicListAux->musica->id == idMusic) {
             deleteMusicFromList(musicListAux);
             break;
         }
         musicListAux = musicListAux->prox;
     }



    printf("\nMusica removida !");


}


void deleteMusicFromPlaylist(int id_music, playlist_no* playlist){
    playlist_no *playlistAux, *playlistAnt;
    playlistAux = playlist->prox;
    playlistAnt = playlist;
    while (playlistAux != playlist) {
        if (playlistAux->musica->id == id_music) {
            playlistAnt->prox = playlistAux->prox;
            free(playlistAux);
            break;
        }
        playlistAnt = playlistAux;
        playlistAux = playlistAux->prox;
    } 



    // playlist_no *playlistAux, *playlistAnt;
    // if(!playlist){
    //     return;
    // }
    // playlistAux = playlist->prox;
    // playlistAnt = playlist;

    // while(playlistAux != playlist && playlistAnt->musica->id != id_music){
    //     playlistAnt = playlistAux;
    //     playlistAux = playlistAux->prox;

    //     if(playlistAux == playlist->prox){
    //         return;
    //     }else{
    //         playlistAnt->prox = playlistAux->prox;
    //         if(playlistAux == playlist) playlist = playlistAnt;
    //         free(playlistAux);
    //     }
    // }

    
}


void deleteMusicFromList(musica_no *node){
    musica_no* musicAux = node->ant;
    musicAux->prox = node->prox;
    if(node->prox){
        node->prox->ant = musicAux;
    }
    free(node);


}
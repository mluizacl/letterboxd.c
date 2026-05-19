#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>


//-------------------------------------------------------------------------------
struct Filme {
	char titulo[100];
	char diretor[100];
	int ano;
	char genero[50];
	char sinopse[300];
	int estrelas;
	char avaliacao[300];
	
};

//-------------------------------------------------------------------------------
void mostrarWatchlist(struct Filme watchlist[], int qtd){
	int i;
	printf("=============================");
	printf("\n-------- WATCHLIST --------\n");
	
	if (qtd > 0) {
		for(i = 0; i < qtd; i++) {
			printf("%s (%d)\n", watchlist[i].titulo, watchlist[i].ano);
		}
	} else {
		printf("Sua lista est� vazia! Adicione filmes que deseja assistir!\n");
	}
	printf("\n");
}

void mostrarFilmesDisponiveis(struct Filme filmes[], int total){
	int i;
	printf("===========================");
	printf("\n---- FILMES DISPON�VEIS ----\n");
	for (i = 0; i < total; i++) {
		printf("%d. %s (%d)\n", i+1, filmes[i].titulo, filmes[i].ano);
	}
}

void adicionarFilme(struct Filme **watchlist, int *qtd, struct Filme movie) {
	int i;
	for(i = 0; i < *qtd; i++){
		if(strcmp((*watchlist)[i].titulo, movie.titulo) == 0) {
			printf("\n'%s' j� est� na lista!\n", movie.titulo);
			getch();
			return;
		}
	}
	
	(*qtd)++;
	*watchlist = realloc(*watchlist, (*qtd) * sizeof(struct Filme));
	
	(*watchlist)[(*qtd) - 1]  = movie;
	
	printf("'%s' foi adicionado � sua watchlist!\n", movie.titulo);
	getch();
}

int compararTitulos(const char *a, const char *b) {
    while (*a && *b) {
    	int ca = tolower((unsigned char)*a);
        int cb = tolower((unsigned char)*b);
        if (ca != cb) {
        	return ca - cb;
		}
        a++;
        b++;
    }
    return tolower((unsigned char)*a) - tolower((unsigned char)*b);
}

void removerFilme(struct Filme **watchlist, int *qtd, char titulo[]){
	if((*qtd) == 0) {
		printf("Sua lista est� vazia!\n");
		getch();
		return;
	}
	
	int i, j;
	for(i = 0; i < *qtd; i++) {
		if(compararTitulos((*watchlist)[i].titulo, titulo) == 0) {
			for(j = i; j < *qtd - 1; j++) {
				(*watchlist)[j] = (*watchlist)[j+1];
			}
			
			(*qtd)--;
			*watchlist = realloc(*watchlist, (*qtd) * sizeof (struct Filme));
			
			printf("'%s' foi removido da sua watchlist!\n", titulo);
			getch();
			return;
		}
	}
	printf("'%s' n�o foi encontrado na sua lista!\n", titulo);
	getch();
}

void ordenarFilmes(struct Filme filmes[], int total){
    int x, y, min;
    struct Filme aux;
    
    for(x = 0; x < total-1; x++) {
    	min = x;
    	for(y = x+1; y < total; y++) {
            if (strcmp(filmes[y].titulo, filmes[min].titulo) < 0) {
                min = y;
            }
        }
        if(min != x) {
            aux = filmes[x];
            filmes[x] = filmes[min];
            filmes[min] = aux;
        }
        
    }
}

int buscarFilme(struct Filme filmes[], int total, char nome[]) {
    int inicio = 0, fim = total-1, meio;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        int c = compararTitulos(nome, filmes[meio].titulo);

        if (c == 0) {
            return meio;
        } else if (c > 0) {
            inicio = meio + 1; 
        } else {
            fim = meio - 1; 
        }
    }
    return -1; 
}

void avaliarFilme(struct Filme *movie) {
    do {
        printf("D� uma nota de 0 a 5 estrelas para \"%s\": ", movie->titulo);
        scanf("%d", &movie->estrelas);
        if (movie->estrelas < 0 || movie->estrelas > 5)
            printf("Nota inv�lida! Digite um n�mero entre 0 e 5.\n");
    } while (movie->estrelas < 0 || movie->estrelas > 5);

    printf("\nVoc� avaliou \"%s\" com %d estrela(s)!\n", movie->titulo, movie->estrelas);
    getch();
}

void reviewFilme(struct Filme *movie) {
    printf("\nEscreva sua avalia��o sobre \"%s\":\n", movie->titulo);
    getchar();
    fgets(movie->avaliacao, 300, stdin);
    movie->avaliacao[strcspn(movie->avaliacao, "\n")] = '\0';

    printf("\n Avalia��o realizada! \n");
    printf("-----------------------------------------\n");
    printf("Filme: %s\n", movie->titulo);
    printf("Avalia��o: %s\n", movie->avaliacao);
    printf("-----------------------------------------\n");
    getch();
}


//-------------------------------------------------------------------------------
int main () {
	setlocale(LC_ALL, "Portuguese");

	struct Filme filmesDisponiveis[12] = {
    {"O Labirinto do Fauno", "Guilherme del Toro", 2006, "Fantasia",
    "Durante a guerra civil espanhola, uma menina encontra um misterioso labirinto e um fauno que muda seu destino.", -1, ""},
    {"Matrix", "Lana Wachowski e Lilly Wachowski", 1999, "A��o/Fic��o Cient�fica",
    "Um hacker descobre que o mundo � uma simula��o e luta contra m�quinas que controlam a humanidade.", -1, ""},
    {"Clube dos Cinco", "John Hughes", 1985, "Com�dia/Drama",
    "Cinco estudantes de perfis diferentes cumprem deten��o e descobrem que t�m mais em comum do que pensam.", -1, ""},
    {"A hora do Pesadelo", "Wes Craven", 1984, "Terror",
    "Um assassino invade os sonhos de adolescentes e os mata enquanto dormem.", -1, ""},
    {"Interestelar", "Christopher Nolan", 2014, "Fic��o Cient�fica/Aventura",
    "Astronautas viajam por um buraco de minhoca em busca de um novo lar para a humanidade.", -1, ""},
    {"Stardust: O Mist�rio da Estrela", "Matthew Vaughn", 2007, "Fantasia",
    "Um jovem cruza um muro m�gico para buscar uma estrela cadente e encontra bruxas e reis em disputa.", -1, ""},
    {"A Escolha Perfeita", "Jason Moore", 2012, "Com�dia/Romance",
    "Uma jovem entra em um grupo de canto a capella e descobre amizade e amor atrav�s da m�sica.", -1, ""},
    {"O Fant�stico Sr. Raposo", "Wes Anderson", 2009, "Infantil/Com�dia",
    "Um raposo tenta roubar fazendeiros vizinhos e coloca sua fam�lia e amigos em perigo.", -1, ""},
    {"Possess�o", "Andrzej Zulawski", 1981, "Terror/Fantasia",
    "Ap�s o fim de seu casamento, uma mulher entra em colapso e revela um segredo sobrenatural.", -1, ""},
    {"Duna", "Denis Villeneuve", 2021, "Fic��o Cient�fica/Aventura",
    "O jovem Paul Atreides enfrenta intrigas e batalhas em um planeta des�rtico onde h� uma subst�ncia poderosa.", -1, ""},
    {"Clube da Luta", "David Fincher", 1999, "A��o/Crime",
    "Um homem insone e desiludido conhece o carism�tico Tyler Durden e juntos fundam um clube secreto de lutas.", -1, ""},
    {"Um Sonho de Liberdade", "Frank Darabont", 1994, "Thriller/Fic��o Policial",
    "Um banqueiro � preso injustamente e encontra esperan�a e amizade ao longo dos anos na pris�o.", -1, ""}
};

	
	struct Filme *watchlist = NULL;
	
	int qtdWatchlist = 0, totalFilmes = 12;
	int opcao, subopcao, escolha;
	char tituloFilme[100];

	
	do {
		printf("==============================");
		printf("\n----------- MENU ------------");
		printf("\n1. Acessar watchlist \n2. Buscar filme \n3. Avaliar filme \n4. Mostrar filmes dispon�veis \n0. Sair");
		
		printf("\n\nSelecione uma op��o: ");
		scanf("%d", &opcao);
		
		switch(opcao) {
//1. mostrar watchlist----------------------------------------------------------------------
			case 1:
				do {
					system("cls");
					mostrarWatchlist(watchlist, qtdWatchlist);
					printf("\n1. Adicionar filme \n2. Remover filme \n3. Avaliar filme \n4. Voltar ao menu");
					printf("\n\nSelecione uma op��o: ");
					scanf("%d", &subopcao);
					
					switch (subopcao) {
	//1. adicionar filme---------------------------------------------------------------------
						case 1: 
							mostrarFilmesDisponiveis(filmesDisponiveis, totalFilmes);
							printf("\n\nQual o n�mero do filme que deseja adicionar na lista? ");
							scanf("%d", &escolha);	
							
							if (escolha > 0 && escolha <= totalFilmes) {
								adicionarFilme(&watchlist, &qtdWatchlist, filmesDisponiveis[escolha - 1]);
							} else {
								printf("Op��o inv�lida!");
							}
							break;

	//2. remover filme------------------------------------------------------------------------	
						case 2:
							printf("\n\nQual o nome do filme deseja remover da lista? ");
							getchar();
							fgets(tituloFilme, sizeof(tituloFilme), stdin);
							tituloFilme[strcspn(tituloFilme, "\n")] = '\0';
							
							removerFilme(&watchlist, &qtdWatchlist, tituloFilme);
							break;

	//3. chama funcao avaliar filme-----------------------------------------------------------							
						case 3:
							do {
								system("cls");
								printf("1. Dar nota \n2. Escrever avalia��o \n3. Voltar ao menu\n");
								printf("\nSelecione uma op��o: ");
								scanf("%d", &subopcao);
								
								switch (subopcao) {
									case 1:
										system("cls");
										mostrarFilmesDisponiveis(filmesDisponiveis, totalFilmes);
										printf("\n\nQual o n�mero do filme que deseja dar nota? ");
										scanf("%d", &escolha);
										
										if (escolha > 0 && escolha <= totalFilmes) {
											avaliarFilme(&filmesDisponiveis[escolha - 1]);
										} else {
											printf("Op��o inv�lida!");
										}
										break;
									
									case 2: 
										system("cls");
										mostrarFilmesDisponiveis(filmesDisponiveis, totalFilmes);
										printf("\n\nQual o n�mero do filme que deseja escrever uma avalia��o? ");
										scanf("%d", &escolha);
										
										if (escolha > 0 && escolha <= totalFilmes) {
											reviewFilme(&filmesDisponiveis[escolha - 1]);
										} else {
											printf("Op��o inv�lida!");
										}
										break;
										
									case 3:
										system("cls");
										break;
									
									default: 
										printf("Op��o inv�lida!\n");
								}
							} while(subopcao != 3);
							break;
						
						case 4:
							system("cls");
							break;
						
						default: 
						printf("Op��o inv�lida!\n");
					}
				} while (subopcao != 4);
				break;
			
//2. buscar filme----------------------------------------------------------------------	
			case 2:
				do {
					system("cls");
					ordenarFilmes(filmesDisponiveis, totalFilmes);
					
					printf("\nQual o nome do filme que deseja buscar? ");
					getchar();
					fgets(tituloFilme, sizeof(tituloFilme), stdin);
					tituloFilme[strcspn(tituloFilme, "\n")] = '\0';
					
					int pos = buscarFilme(filmesDisponiveis, totalFilmes, tituloFilme);
					
					if (pos != -1) {
						printf("\nFilme encontrado: \n");
						printf("\n==============================\n");
						printf("%s (%d)\n", filmesDisponiveis[pos].titulo, filmesDisponiveis[pos].ano);
						printf("\nINFORMA��ES:\n");
						printf("G�nero: %s\n", filmesDisponiveis[pos].genero);
						printf("Dire��o: %s\n", filmesDisponiveis[pos].diretor);
						printf("Sinopse: %s\n", filmesDisponiveis[pos].sinopse);
						
						if(filmesDisponiveis[pos].estrelas == -1){
							printf("\nEstrelas: Voc� ainda n�o avaliou esse filme\n");
						} else{
							printf("\nEstrelas: %d\n", filmesDisponiveis[pos].estrelas);
						}
						printf("Sua avalia��o: %s\n", filmesDisponiveis[pos].avaliacao);
						printf("\n==============================\n");
					
						printf("\n1. Adicionar na watchlist \n2. Avaliar filme \n3. Buscar outro filme \n0. Voltar ao menu\n");
						printf("\nSelecione uma op��o: ");
						scanf("%d", &subopcao);
						
						switch (subopcao){
							case 1:
								adicionarFilme(&watchlist, &qtdWatchlist, filmesDisponiveis[pos]);
								
								printf("\n1. Buscar mais filmes \n0. Voltar ao menu");
								printf("\nEscolha: ");
								scanf("%d", &escolha);
								
								if(escolha == 1){
									break;
								} else {
									subopcao = 3;
									system("cls");
								}
								break;
							
							case 2:
								do {
									system("cls");
									printf("1. Dar nota \n2. Escrever avalia��o \n3. Voltar ao menu\n");
									printf("\nSelecione uma op��o: ");
									scanf("%d", &subopcao);
									
									switch (subopcao) {
										case 1:
											system("cls");
											avaliarFilme(&filmesDisponiveis[pos]);
											break;
										
										case 2: 
											system("cls");
											reviewFilme(&filmesDisponiveis[pos]);
											break;
											
										case 3:
											system("cls");
											break;
										
										default: 
											printf("Op��o inv�lida!\n");
									}
								} while(subopcao != 3);
								break;
							
							case 3:
								system("cls");
								break;
							
							case 0:
								system("cls");
								break;
							
							default:
								printf("Op��o inv�lida!\n");
						}	
						
					} else {
						printf("\nFilme n�o encontrado.\n");
						getch();
						system("cls");
						break;
					}	
				} while (subopcao != 0);
				break;
		
//3. avaliar filme----------------------------------------------------------------	
			case 3: 
				do {
					system("cls");
					printf("1. Dar nota \n2. Escrever avalia��o \n3. Voltar ao menu\n");
					printf("\nSelecione uma op��o: ");
					scanf("%d", &subopcao);
					
					switch (subopcao) {
						case 1:
							system("cls");
							mostrarFilmesDisponiveis(filmesDisponiveis, totalFilmes);
							printf("\n\nQual o n�mero do filme que deseja dar nota? ");
							scanf("%d", &escolha);
							
							if (escolha > 0 && escolha <= totalFilmes) {
								avaliarFilme(&filmesDisponiveis[escolha - 1]);
							} else {
								printf("Op��o inv�lida!");
							}
							break;
						
						case 2: 
							system("cls");
							mostrarFilmesDisponiveis(filmesDisponiveis, totalFilmes);
							printf("\n\nQual o n�mero do filme que deseja escrever uma avalia��o? ");
							scanf("%d", &escolha);
							
							if (escolha > 0 && escolha <= totalFilmes) {
								reviewFilme(&filmesDisponiveis[escolha - 1]);
							} else {
								printf("Op��o inv�lida!");
							}
							break;
							
						case 3:
							system("cls");
							break;
						
						default: 
							printf("Op��o inv�lida!\n");
					}
				} while(subopcao != 3);
			
				break;
		
//4. funcao mostrar todos os filmes------------------------------------------------------	
			case 4:
				system("cls");
				mostrarFilmesDisponiveis(filmesDisponiveis, totalFilmes);
				getch();
				system("cls");
				break;
			
			case 0:
				printf("Saindo...\n");
				break;	
			
			default: 
				printf("Op��o inv�lida!\n");
		}	
	}
	 while (opcao != 0);{
	
	free(watchlist);
	}

	return 0;
}




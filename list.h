/*************************************************/
/* Estrutura de dados auxiliar - lista encadeada */
/*************************************************/
#define MAXSTR 512
typedef struct cel_struct{
    char key[MAXSTR];
    struct cel_struct * nxt;
} tnode;

typedef struct head{
    tnode * node;
    int size;
} thead;

//Funçao que inicializa a lista usada para achar a diferença e a interseccao.
 thead * l_init();
//Funçao usada para inserir os chars (vizinhança) na lista daquele vertice.
 void l_insert(thead * head, char * new);
//Funçao auxiliar para ajudar a debugar o programa.
 void l_print(thead * head);
 int l_size(thead * head);
/* Funcao recursiva para limpar lista a partir do ultimo no*/
 int rec_clear(tnode * node);
//Funçao para limpar a lista.
 int l_clear(thead * head);
// Desaloca memoria
 void l_free(thead *head);
// Busca sequencial de elemento na lista
 int l_search(thead* head, char * buscado);
//Funcao que verifica a interseccao entre os dois vertives.
 thead * l_intersection(thead *l1, thead * l2);
// cria uma copia da lista
 thead * l_copy(thead *list);
// Filtra l1 com os elementos da lista2
// (Retorna elementos de l1 nao encontrados em l2)
// Utilizado para calcular a diferenca de conjunto
 thead * l_filter(thead *l1, thead *l2);
/*************************************************/
/* Fim da estrutura de dados lista encadeada     */
/*************************************************/

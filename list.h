/*************************************************/
/* Estrutura de dados auxiliar - lista encadeada */
/*************************************************/
typedef struct cel_struct{
    char key[48];
    struct cel_struct * nxt;
} tnode;

typedef struct head{
    tnode * node;
    int size;
} thead;

//Funçao que inicializa a lista usada para achar a diferença e a interseccao.
static thead * l_init();
//Funçao usada para inserir os chars (vizinhança) na lista daquele vertice.
static void l_insert(thead * head, char * new);
//Funçao auxiliar para ajudar a debugar o programa.
static void l_print(thead * head);
static int l_size(thead * head);
/* Funcao recursiva para limpar lista a partir do ultimo no*/
static int rec_clear(tnode * node);
//Funçao para limpar a lista.
static int l_clear(thead * head);
// Desaloca memoria
static void l_free(thead *head);
// Busca sequencial de elemento na lista
static int l_search(thead* head, char * buscado);
//Funcao que verifica a interseccao entre os dois vertives.
static thead * l_intersection(thead *l1, thead * l2);
// cria uma copia da lista
static thead * l_copy(thead *list);
// Filtra l1 com os elementos da lista2
// (Retorna elementos de l1 nao encontrados em l2)
// Utilizado para calcular a diferenca de conjunto
static thead * l_filter(thead *l1, thead *l2);
/*************************************************/
/* Fim da estrutura de dados lista encadeada     */
/*************************************************/

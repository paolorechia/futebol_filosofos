/*************************************************/
/* Estrutura de dados auxiliar - lista encadeada */
/*************************************************/
typedef struct genl_struct{
    void * key;
    struct genl_struct * nxt;
} tgennode;

typedef struct head{
    tnode * node;
    int size;
} tgenhead;

//Funçao que inicializa a lista usada para achar a diferença e a interseccao.
 thead * genl_init();
//Funçao usada para inserir os chars (vizinhança) na lista daquele vertice.
 void genl_insert(thead * head, void * data);
//Funçao auxiliar para ajudar a debugar o programa.
 void genl_print(thead * head);
 int genl_size(thead * head);
/* Funcao recursiva para limpar lista a partir do ultimo no*/
 int rec_clear(tnode * node);
//Funçao para limpar a lista.
 int genl_clear(thead * head);
// Desaloca memoria
 void genl_free(thead *head);
// Busca sequencial de elemento na lista
 int genl_search(thead* head, char * buscado);
//Funcao que verifica a interseccao entre os dois vertives.
 thead * genl_intersection(thead *l1, thead * l2);
// cria uma copia da lista
 thead * genl_copy(thead *list);
// Filtra l1 com os elementos da lista2
// (Retorna elementos de l1 nao encontrados em l2)
// Utilizado para calcular a diferenca de conjunto
 thead * genl_filter(thead *l1, thead *l2);
/*************************************************/
/* Fim da estrutura de dados lista encadeada     */
/*************************************************/

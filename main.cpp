/* Estruturas de Dados - Trabalho pratico

Professor: Diego P. Rubert
Aluno(s): 

*/

#include <cstdio>
#include <string>

using std::string;

class No {
  friend class ArvBinBusca;
  
public:
  No(const int chave);

  void escreve(const char *sep = "");
  
private:
  int chave;
  No *pai;
  No *esq;
  No *dir;
};


class ArvBinBusca
{
public:
  ArvBinBusca();
  ArvBinBusca(const ArvBinBusca& outro); // construtor de cópia
  ~ArvBinBusca();
  ArvBinBusca& operator=(const ArvBinBusca& outro); // operador de atribuição
  
  void escreve_ordenado(); // escreve em percurso em-ordem
  void escreve();

  No *get_raiz(); // devolve a raiz
  No *busca(int k); // devolve o ponteiro para um elemento, se achar, ou NULL
  No *minimo(); // devolve o menor elemento da árvore
  No *maximo(); // devolve o maior elemento da árvore
  No *sucessor(No *x); // devolve o sucessor de um elemento
  No *predecessor(No *x); // devolve o predecessor de um elemento

  void insere(int chave); // insere um elemento
  bool remove(int chave); // busca e remove um elemento

  void limpa(); // remove todos elementos da árvore, liberando a memoria
  
private:
  No *raiz;

  void escreve_ordenado(No *x); // escreve em percurso em-ordem
  void escreve(const string& prefixo, No *x);
 
  No *busca(No *x, int k); // Parte recursiva da busca
  No *minimo(No *x); // Parte recursiva de minimo
  No *maximo(No *x); // Parte recursiva de maximo

  void insere(No *z); // Insercao, mas ja recebe pronto o no (nao a chave) a ser inserido
  void transplante(No *u, No *v); // Transplante
  void remove(No *z); // Recebe o no a ser removido (deve tratar todos os casos e fazer transplante, se necessario)
  
  void limpa(No *x); // dado um nó x, remove recursivamente elementos abaixo e deleta x
  
  void copia(const ArvBinBusca& T); // copia uma árvore T para a atual a partir da raiz,
                                    // usada no construtor de cópia e no operador de atribuição
  void copia(No *dest, No *orig);   // copia um nó e os descendentes recursivamente
};


int main(void)
{
  ArvBinBusca T; // construtor ArvBinBusca()
  int v[] = {10, 25, 0, 16, 20, 9, 15, 6, 14, 7, 18, 12, 22, 19, 3, 13};
  
  for (const auto &x : v)
    T.insere(x); //TODO: implemente primeiro o metodo insere
  
  printf("T:\n");
  T.escreve();
  printf("Valores de T em ordem crescente: ");
  T.escreve_ordenado(); //TODO: implemente depois escreve_ordenado

  return 0; //TODO: remover após implementar minimo, maximo, sucessor, predecessor

  No *raiz = T.get_raiz();
  printf("Raiz: ");
  raiz->escreve("\n");

  No *pre = T.predecessor(raiz);
  printf("Predecessor da raiz: ");
  pre->escreve("\n");
  No *suc = T.sucessor(raiz);
  printf("Sucessor da raiz: ");
  suc->escreve("\n");

  printf("Sucessor do predecessor da raiz (== raiz): ");
  T.sucessor(pre)->escreve("\n");
  printf("Predecessor do sucessor da raiz (== raiz): ");
  T.predecessor(suc)->escreve("\n");

  No *minimo = T.minimo();
  No *maximo = T.maximo();
  printf("Mínimo: ");
  minimo->escreve("\n");
  printf("Máximo: ");
  maximo->escreve("\n");

  return 0; //TODO: remover após implementar remoção

  T.remove(0); // Caso 1
  T.remove(13); // Caso 2
  T.remove(10); // Caso 3b + 3a

  printf("T:\n");
  T.escreve();

  return 0; //TODO: remover após implementar construtor de cópia e operador de atribuição
  
  ArvBinBusca T2(T); // construtor de cópia
  T2.insere(30);
  printf("T:\n");
  T.escreve();
  printf("T2:\n");
  T2.escreve();

  ArvBinBusca T3 = T; // construtor de cópia
  T3.insere(-8);
  printf("T:\n");
  T.escreve();
  printf("T3:\n");
  T3.escreve();

  T3 = T; // operador de atribuição
  T3.insere(100);
  printf("T:\n");
  T.escreve();
  printf("T3:\n");
  T3.escreve();
  
  return 0;
}


//***********************************
//*** IMPLEMENTAÇÕES DA CLASSE NO ***
//***********************************

No::No(const int chave) :
  chave(chave),
  pai(NULL),
  esq(NULL),
  dir(NULL) {
}

void No::escreve(const char *sep) {
  printf("%2d%s", chave, sep);
}


//********************************************
//*** IMPLEMENTAÇÕES DA CLASSE ARVBINBUSCA ***
//********************************************

ArvBinBusca::ArvBinBusca() {
  raiz = NULL;
}

ArvBinBusca::ArvBinBusca(const ArvBinBusca& outro) {
  copia(outro);
}

ArvBinBusca::~ArvBinBusca() {
  limpa();
}

ArvBinBusca& ArvBinBusca::operator=(const ArvBinBusca& outro) {
  limpa();
  copia(outro);
  return *this;
}

void ArvBinBusca::escreve_ordenado() {
  escreve_ordenado(raiz);
  putchar('\n');
}

void ArvBinBusca::escreve_ordenado(No *x) {
  //TODO: implementar (escrever em percurso em-ordem em uma única linha)
}

void ArvBinBusca::escreve() {
  escreve("", raiz);
}

void ArvBinBusca::escreve(const string& prefixo, No *x) {
  if (x == NULL)
    return;

  bool ehDireito = x->pai and x->pai->dir == x;
  bool temIrmaoEsq = x->pai and x->pai->esq;
  
  printf(prefixo.c_str());
  printf(ehDireito and temIrmaoEsq ? "├──" : "└──" );

  if (x->pai == NULL) // raiz
    x->escreve("\n");
  else
    x->escreve(ehDireito ? "d\n" : "e\n");
  
  escreve(prefixo + (ehDireito and temIrmaoEsq ? "│   " : "    "), x->dir);
  escreve(prefixo + (ehDireito and temIrmaoEsq ? "│   " : "    "), x->esq);
}

No *ArvBinBusca::get_raiz() {
  return raiz;
}

No *ArvBinBusca::busca(int k) {
  return busca(raiz, k);
}

No *ArvBinBusca::busca(No *x, int k) {
  //TODO: implementar
}

No *ArvBinBusca::minimo() {
  return raiz ? minimo(raiz) : NULL;
}

No *ArvBinBusca::minimo(No *x) {
  //TODO: implementar
}

No *ArvBinBusca::maximo() {
  return raiz ? maximo(raiz) : NULL;
}

No *ArvBinBusca::maximo(No *x) {
  //TODO: implementar
}

No *ArvBinBusca::sucessor(No *x) {
  //TODO: implementar
}

No *ArvBinBusca::predecessor(No *x) {
  //TODO: implementar
}

void ArvBinBusca::insere(int chave) {
  No *z = new No(chave);
  insere(z);
}

void ArvBinBusca::insere(No *z) { // implementado
    No *y = nullptr; //
    No *x = raiz;

    while (x != nullptr) {
        y = x;
        if (z->chave < x->chave){ // x é Pai (se chave for menor que nó pai, vai pra filho esquerda)
            x = x->esq;
        }     
        else{ // caso contrário, vai para filho direira
            x = x->dir;
        } 
        // se x for nulo, encontramos onde vamos inserir a chave       
    }
    z->pai = y; // filho recebe pai = y

    if (y == nullptr){ 
        raiz = z; // insere o primeiro elemento da arvore (no caso na raiz)
    }
    else{
        if (z->chave < y->chave){  // y = x (pai), que vai alocar 
            y->esq = z; // atribui a chave 
        }
        else{
            y->dir = z; // atribui a chave. 
        }
    }
}

void ArvBinBusca::transplante(No *u, No *v) {
  //TODO: implementar
}

bool ArvBinBusca::remove(int chave) {
  No *z = busca(raiz, chave);
  if (z == NULL)
    return false;

  remove(z);
  delete z;
  return true;
}

void ArvBinBusca::remove(No *z) {
  //TODO: implementar
}

void ArvBinBusca::limpa() {
  limpa(raiz);
  raiz = NULL;
}

void ArvBinBusca::limpa(No *x) {
  //TODO: implementar
}

void ArvBinBusca::copia(const ArvBinBusca& T) {
  if (T.raiz == NULL)
    raiz = NULL;
  else {
    raiz = new No(T.raiz->chave);
    copia(raiz, T.raiz);
  }
}

void ArvBinBusca::copia(No *dest, No *orig) {
  //TODO: implementar
}

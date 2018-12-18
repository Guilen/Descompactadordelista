#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>

using namespace std;

struct tipo_codigo
{
    string cod;
    string sig;
    struct tipo_codigo *lig_next, *lig_prev;
};
typedef struct tipo_codigo CODIGO;

typedef struct
{
    int n;
    CODIGO *head, *tail;
} Lista;

Lista *InicializaLista()
{
    Lista *lista = (Lista *)malloc(sizeof(Lista));
    lista->head=NULL;
    lista->tail = NULL;
    lista->n=0;
    return lista;
}

CODIGO *inserir(string x, string y, Lista*L)
{
    CODIGO *Pa;
    Pa = (CODIGO *)malloc(sizeof(CODIGO));
    Pa->cod = x;
    Pa->sig = y;
    Pa->lig_next = L->head;
    Pa->lig_prev = NULL;
    L->head = Pa;
    if
    (L->tail == NULL)
        L->tail = L->head;
    else
        ((L->head)->lig_next)->lig_prev = Pa;
    L ->n++;
    return Pa;
}

CODIGO *descompactador(string x,Lista*L)
{
    CODIGO *aux = L->head;
    while (aux)
    {
        if (aux->cod == x)
        {
            cout << aux->sig << endl;
            return NULL;
        }
            aux = aux->lig_next;
    }
}

void exibir(Lista *L)
{
    CODIGO *f = L->head;

    if (f == NULL)
    {
        cout << "\tLista vazia." << endl;
    }
    else
    {
        while(f)
        {
            cout << f->cod << " " << f->sig << endl;
            f= f->lig_next;
        }
    }
    cout << endl;
}

int main()
{
    string line;
    string procura;
    Lista *A = InicializaLista();
    ifstream tabela ("Codigos.txt");
    if (tabela.is_open())
    {
        while (! tabela.eof() )
        {
            getline (tabela,line);
            string delimiter = " ";
            size_t pos = 0;
            string token;
            while ((pos = line.find(delimiter)) != string::npos)
            {
                token = line.substr(0, pos);
                line.erase(0, pos + delimiter.length());
                inserir(line, token, A);
            }
        }
        tabela.close();
        cout << "Tabela de codigos:" << endl;
        exibir(A);
    }

    else
    {
        cout << "Nao foi possivel abrir o arquivo";
    }
    ifstream arq("ArqCompactado.txt");
    if (arq.is_open())
    {
        cout << "Arquivo a ser descompactado: ";
        cout << line << endl;
        while (! arq.eof())
        {
            getline (arq,line);
            cout << "Arquivo a ser descompactado: ";
            cout << line << endl;
            cout << "Arquivo descompactado: ";
            descompactador(line,A);
        }
        arq.close();
    }
    else
    {
        cout << "Nao foi possivel descompactar";
    }
    return 0;
}

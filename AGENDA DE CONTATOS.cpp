#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<conio.h>
#include<windows.h>

//lista
struct Contatos
{
char nome [50];
char telefone [30];
char email [200];
char endereco [300];
struct Contatos *next;
}* lista;

//funções para as cores
void SetColor (int ForgC)
{
WORD wColor;
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO csbi;

if(GetConsoleScreenBufferInfo (hStdOut, &csbi))
{
wColor = (csbi .wAttributes & 0xF0) + (ForgC & 0x0F);
SetConsoleTextAttribute (hStdOut, wColor);
}
return;
}

void ClearColor(){
SetColor(15);
}

void ClearConsoleToColors (int ForgC, int BackC)
{

WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
COORD coord = {0, 0};
DWORD count;
CONSOLE_SCREEN_BUFFER_INFO csbi;

SetConsoleTextAttribute (hStdOut, wColor);
if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
{
FillConsoleOutputCharacter (hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
FillConsoleOutputAttribute (hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi .dwSize.Y, coord, &count );
SetConsoleCursorPosition(hStdOut, coord);
}
return;
}

//adicionar para contatos
void addContato(char* nome, char* telefone, char* email, char* endereco)
{
struct Contatos * contatos = (struct Contatos *) malloc(sizeof(struct Contatos));
strcpy(contatos->nome, nome);
strcpy (contatos->telefone, telefone);
strcpy(contatos->email, email);
strcpy (contatos->endereco, endereco);
contatos->next = NULL;

if (lista==NULL){
lista = contatos;
}

else{
contatos->next = lista;
lista = contatos;
}

}

//listar contatos da lista
void listar()
{
	int ctt = 0;
	ClearConsoleToColors(15, 17);
	system("cls");
	fflush(stdin);
	printf("\n=============================================================================================\n");
	printf("\t\t-------------------------------------------------");
	printf("\n\t\t\t      LISTA DE CONTATOS     \n");
	printf("\t\t-------------------------------------------------");
	printf("\n=============================================================================================");
	
	struct Contatos * temp = lista;
	while(temp!=NULL){
		ctt =1;
		printf("\n\n  Nome: %s\n", temp->nome);
		printf("  Telefone: %s\n", temp->telefone);
		printf("  Email: %s\n", temp->email);
		printf("  Endereco: %s\n", temp->endereco);
		temp = temp->next;
	}
	if(ctt==0){
		printf("\n-------------------------------------------------------------------------------------------\n");
		printf("  LISTA VAZIA...");
		printf("\n-------------------------------------------------------------------------------------------\n");
	}
	printf("\n\n");
	system("pause");
	
}

//buscar contatos da lista
void buscar(char *nome)
{
	ClearConsoleToColors(15,17);
	int ctt=0;
	struct Contatos *temp = lista;
	while (temp != NULL)
	{
		if (strcmp(temp->nome, nome) == 0)
		{
			ctt= 1;
			system("cls");
			fflush(stdin);
			printf("\n=============================================================================================\n");
			printf("\t\t-------------------------------------------------");
			printf("\n\t\t\t      AREA DE CONTATOS     \n");
			printf("\t\t-------------------------------------------------");
			printf("\n=============================================================================================\n");
			printf("   CONTATO ENCONTRADO...");
			printf("\n---------------------------------------------------------------------------------------------\n");
			printf("  Nome: %s\n", temp->nome);
			printf("  Telefone: %s\n", temp->telefone);
			printf("  Email: %s\n", temp->email);
			printf("  Endereco: %s\n", temp->endereco);
			printf("\n---------------------------------------------------------------------------------------------\n");		
			printf("\n\n");
			system("pause");
			return;
		}
		temp = temp->next;
	}
	
	printf("\n---------------------------------------------------------------------------------------------\n");
	printf("  Nao ha contatos com esse nome -> %s", nome);
	printf("\n---------------------------------------------------------------------------------------------\n");
	system("pause");
}

//editar contatos da lista
void editar(char *nome, char *telefone, char *email, char *endereco)
{
	int ctt= 0;
	struct Contatos *temp = lista;
	while (temp != NULL)
	{
		
		if(strcmp(temp->nome, nome) == 0)
		{
			ctt=1;
			fflush(stdin);
			system("cls");
			printf("-------------------------------------------------------------------------------------------------\n");
			printf("  Contato Encontrado...\n");
			printf("  Dados atuais do contato:\n");
			printf("  Nome: %s\n  Telefone: %s\n  Email: %s\n  Endereco: %s\n", nome, telefone, email, endereco);
			printf("-------------------------------------------------------------------------------------------------\n");
			printf("  Insira os novos dados: \n\n");
			printf("  Nome: ");
			scanf("%50[^\n]", temp->nome);
			getchar();
			
			printf("  Telefone: ");
			scanf("%30[^\n]", temp->telefone);
			getchar();
			
			printf("  Email: ");
			scanf("%200[^\n]", temp->email);
			getchar();
			
			printf("  Endereco: ");
			scanf("%300[^\n]", temp->endereco);
			getchar();
			
			printf("\n\n-------------------------------------------------------------------------------------------------\n");
			printf("  EDICAO FEITA COM SUCESSO!!!");
			printf("\n-------------------------------------------------------------------------------------------------\n\n");
			fflush(stdin);
			system("pause");
			return;
		}
		temp = temp->next;
	}
	printf("\n---------------------------------------------------------------------------------------------\n");
	printf("  Contato nao encontrado!");
	printf("\n---------------------------------------------------------------------------------------------\n\n");
	system("pause");
	
}

//pegar os contatos adicionados na lista para deixa-los guardados
void listarArquivo(char *nome, char *telefone, char *email, char *endereco)
{
	ClearConsoleToColors(15,17);
	int f=0;
	FILE *agenda;
	agenda = fopen("agendactt.txt","r");
	fflush(stdin);
	system("cls");
	printf("\n=============================================================================================\n");
	printf("\t\t-------------------------------------------------");
	printf("\n\t\t\t      CONTATOS NO ARQUIVO     \n");
	printf("\t\t-------------------------------------------------");
	printf("\n=============================================================================================\n");
	
	while(fscanf(agenda,"%s %s %s %300[^\n] \n", nome, telefone, email, endereco) != EOF)
	{
		f=1;
		fflush(stdin);
		printf("\n  Nome: %s\n", nome);
		printf("  Telefone: %s\n", telefone);
		printf("  Email: %s\n", email);
		printf("  Endereco: %s\n", endereco);
	}
	fclose(agenda);
	if(f == 0){
	printf("\n---------------------------------------------------------------------------------------------\n");
	printf("  Nao ha contatos no arquivo...");
	printf("\n---------------------------------------------------------------------------------------------\n");
	}
	printf("\n");
	system("pause");
	
}

//remover contatos
void remover(char *nome, char *telefone, char *email, char *endereco)
{
	int ctt=0;
	struct Contatos *temp1 = lista;
	struct Contatos *temp2 = lista;
	while (temp1 !=NULL)
	{
		if(strcmp(temp1->nome,nome) == 0)
		{
			fflush(stdin);
			system("cls");
			printf("---------------------------------------------------------------------------------------------");
			printf("\n  Contato encontrado...\n");
			printf("  Dados do contato a ser excluido: \n\n");
			printf("  Nome: %s\n  Telefone: %s\n  Email: %s\n  Endereco: %s\n", nome, telefone, email, endereco);
			
			if(temp1 == temp2)
			{
				lista = lista->next;
				free(temp1);
			}
			else
			{
				temp2->next = temp1->next;
				free(temp1);
			}
			printf("\n---------------------------------------------------------------------------------------------\n");
			printf("  CONTATO EXCLUIDO COM SUCESSO!...");
			printf("\n---------------------------------------------------------------------------------------------\n\n");
			fflush(stdin);
			system("pause");
			return;		
		}
		temp2 = temp1;
		temp1 = temp1->next;		
	}
	printf("\n---------------------------------------------------------------------------------------------\n");
	printf("  Contato nao encontrado -> %s",nome);
	printf("\n---------------------------------------------------------------------------------------------\n\n");
	fflush(stdin);
	system("pause");
}

int main(){
	main:
	lista = NULL;
	int continuar;
	ClearConsoleToColors (15, 20);
	char nome [50];
	char telefone [30];
	char email [200];
	char endereco [300];
	do {
		ClearConsoleToColors (15, 20);
		system("cls");
		fflush(stdin);
		printf("\n=============================================================================================\n");
		printf("\t\t---------------------------------------------------------");
		printf("\n\t\t\t      BEM-VINDO A LISTA DE CONTATOS!     \n");
		printf("\t\t---------------------------------------------------------");
		printf("\n=============================================================================================\n");
		printf("\n [1] Adicionar contato\n");
		printf(" [2] Visualizar a agenda \n");
		printf(" [3] Buscar um contato\n");
		printf(" [4] Editar contato\n");
		printf(" [5] Remover contato\n");
		printf(" [6] Ler contatos salvos no arquivo\n");
		printf(" [0] Exit\n\n]");
		
		printf("Digite a opcao desejada: ");
		scanf("%d", &continuar);
		
		switch (continuar)
		{
			case 1:
			//adicionar os contatos
			//os contatos vão direto para o arquivo e ficam salvos no "agendactt.txt"
			//da mesma forma que ficam salvos na lista padrão do programa
			ClearConsoleToColors (15, 17);
			FILE *agenda;
			agenda = fopen("agendactt.txt", "a+");
			
			system("cls");
			fflush(stdin);
			printf("\n=============================================================================================\n");
			printf("\t\t---------------------------------------------------------");
			printf("\n\t\t\t          ADICIONAR CONTATOS     \n");
			printf("\t\t---------------------------------------------------------");
			printf("\n=============================================================================================\n");
			
			fflush(stdin);
			printf("\n  Insira o nome: ");
			scanf("%50[^\n]", nome);
			getchar();
			
			printf("  Insira o telefone: ");
			scanf("%30[^\n]", telefone);
			getchar();
			
			printf("  Insira o email: ");
			scanf("%200[^\n]", email);
			getchar();
			
			printf("  Insira o endereco: ");
			scanf("%300[^\n]", endereco);
			getchar();
			
			addContato(nome, telefone, email, endereco);
			fprintf(agenda, "%s %s %s %s\n\n", nome, telefone, email, endereco);
			fclose(agenda);
			printf("\n---------------------------------------------------------------------------------------------\n");
			printf("  CONTATO SALVO COM SUCESSO!");
			printf("\n---------------------------------------------------------------------------------------------\n\n");
			fflush(stdin);
			system("pause");
			break;
			
			case 2:
			//lista apenas os contatos da lista
			//os contatos do arquivo não irão aparecer nessa função
			listar();
			break;
			
			case 3:
			//buscar os contatos pelo nome
			//não serão constados no programa os contatos arquivados em "agendactt.txt"
			ClearConsoleToColors (15, 17);
			system("cls");
			fflush(stdin);
			printf("\n=============================================================================================\n");
			printf("\t\t---------------------------------------------------------");
			printf("\n\t\t\t      AREA DE CONTATOS     \n");
			printf("\t\t---------------------------------------------------------");
			printf("\n=============================================================================================\n");
			printf("\n\n  Insira o nome a ser buscado na agenda: ");
			scanf("%50[^\n]", nome);
			getchar();
			printf("\n\n");
			buscar(nome);
			break;
			
			case 4:
			//buscar contato pelo nome para ser editado
			//não serão constados no programa para edição os contatos arquivados em "agendactt.txt"
			ClearConsoleToColors (15, 17);
			system("cls");
			fflush(stdin);
			printf("\n=============================================================================================\n");
			printf("\t\t---------------------------------------------------------");
			printf("\n\t\t\t      EDICAO DE CONTATOS     \n");
			printf("\t\t---------------------------------------------------------");
			printf("\n=============================================================================================\n");
			printf("\n\n  Insira o nome do contato a ser editado na agenda: ");
			scanf("%50[^\n]", nome);
			getchar();
			printf("\n\n");
			editar(nome, telefone, email, endereco);
			break;
			
			case 5:
			//buscar contato pelo nome para ser removido
			ClearConsoleToColors (15, 17);
			system("cls");
			fflush(stdin);
			printf("\n=============================================================================================\n");
			printf("\t\t---------------------------------------------------------");
			printf("\n\t\t\t      REMOVER CONTATOS     \n");
			printf("\t\t---------------------------------------------------------");
			printf("\n=============================================================================================\n");
			printf("\n\n  Insira o nome do contato a ser removido da agenda: ");
			scanf("%50[^\n]", nome);
			getchar();
			printf("\n");
			remover(nome, telefone, email, endereco);
			break;
			
			case 6:
			//funçao para listar os contatos que estão no arquivo "agenda.ctt.txt"
			listarArquivo(nome, telefone, email, endereco);
			break;
			
			case 0:
			ClearConsoleToColors (15, 6);
			system("cls");
			fflush(stdin);
			printf("\n\n---------------------------------------------------------------------------------------------\n");
			printf("  SAINDO DA AGENDA...");
			printf("\n---------------------------------------------------------------------------------------------\n\n");
			
			break;
			
			default:
			ClearConsoleToColors (15, 6);
			system("cls");
			fflush(stdin);	
			printf("\n\n---------------------------------------------------------------------------------------------\n");
			printf("  OPCAO INVALIDA! TENTE NOVAMENTE!");
			printf("\n---------------------------------------------------------------------------------------------\n\n");
			system("pause");
			break;
	}
} while (continuar !=0);

}





















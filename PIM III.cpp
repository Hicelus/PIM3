#include <stdio.h>

//Construindo sessao
struct Sessao {int sala; char titulo[20]; int dia; int mes; int ano; int hora; int minuto; float preco; bool atividade; bool assento[240];};
Sessao sessao[2000];
void cadastrarSessao(void);

//sub-rotinas de conferecia de caracteres e esolhas
int conferirNumero(int limite);
char conferirLetra(char limite);
float conferirPreco(void);
void efetuarVenda(void);
float desconto(void);
void saldo(void);

//vendas
float vendas[100000];
int lancamento = 0;

int main(void){
	
	printf("\n\n***SISTEMA FERENCIADOR DE ASSENTOS***\n\n");
	
	//Inicialização de assentos e sessoes
	for(int i = 0; i < 200; i++){
		for(int ii = 0; ii < 240; ii++){
			sessao[i].assento[ii] = false;
		}
	}
	for(int i = 0; i < 240; i++){
		sessao[i].atividade = false;
	}
	
	//esolher funcao
	bool run = true;
	
	while(run){
		printf("\n\n****Escolha uma opcao***\n\nCadastrar sessao\nVender ingresso\nLancamentos e Saldo atual\nSair\n\n");
		
		//leitura da escolha
		char final;
		final = 'a';
		char opcao[20];
		for (int i = 0; final != '\n'; i++){
			opcao[i] = getchar();
			final = opcao[i];
			}
		
		//chamada da subrotina referente a escolha	
		switch(opcao[0]){
			case 'c': cadastrarSessao(); break;
			case 'v': efetuarVenda(); break;
			case 'l': saldo(); break;
			case 's': printf("Quer realmente finalizar?\n");
					  char resp[20];
					  scanf("%s", &resp);
					  if(resp[0] == 's'){
					  	run = false; break;
					  }
		}	
	}
	return 0;
}

void saldo(void){
	printf("Confira os lancamentos do dia:\n\n");
	float total = 0;
	
	for(int i = 0; i < lancamento; i++){
		total += vendas[i];
		printf ("R$ %.2f\n", vendas[i]);
	}
	printf ("Total : R$ %.2f\n", total);
}

void efetuarVenda(void){
	
	int codigo = 0;
	printf ("Codigo da sessao?\n");
	codigo = conferirNumero(2000);
	if (sessao[codigo].atividade){
		
		printf ("Fileira:\n");
		int fator;
		char fileira = conferirLetra('l');
		switch (fileira){
			case 'a': fator = 0;
			case 'b': fator = 1;
			case 'c': fator = 2;
			case 'd': fator = 3;
			case 'e': fator = 4;
			case 'f': fator = 5;
			case 'g': fator = 6;
			case 'h': fator = 7;
			case 'i': fator = 8;
			case 'j': fator = 9;
			case 'k': fator = 10;
			case 'l': fator = 11;
		}
		
		printf("Cadeira:\n");
		int cadeira = conferirNumero(20);
		int assento = 20 * fator + cadeira;
		
		if (sessao[codigo].assento[assento]){
			float desc = desconto();
			float preco = sessao[codigo].preco * desc;
			
			printf("\n\nSessao: %i - %s\n%i/%i/%i as %i:%i\nCadeira: %c%i\nPreco: R$ %.2f\n\nConfirma Venda?\n", codigo, sessao[codigo].titulo,
				   sessao[codigo].dia, sessao[codigo].mes, sessao[codigo].ano, sessao[codigo].hora, sessao[codigo].minuto, fileira, cadeira, preco);
			
			char final[20];
			scanf("%s", final);
	
			if(final[0] == 's'){
				sessao[codigo].assento[assento] = false;
				vendas[lancamento] = preco;
				lancamento++;
				printf("***Vendido!***\n\n");
			}
			else{
				printf("Operacao Cancelada\n");
			}
		}
		else{
			printf("Assento indisponivel, operacao Cancelada\n");
		}
	}
	else{
		printf("Sessao indisponivel, operacao Cancelada\n");
	}
}

void cadastrarSessao(void){
	
	printf("Titulo:\n");
	char final, titulo[20];
	for (int i = 0; final != '\n'; i++){
		titulo[i] = getchar();
		final = titulo[i];
	}
	printf("Codigo da sessao:\n");
	int codigo = conferirNumero(999);
	printf("Numero da sala:\n");
	int sala= conferirNumero(99);
	printf("Dia de exibicao:\n");
	int dia= conferirNumero(31);
	printf("Mes de exibicao:\n");
	int mes= conferirNumero(12);
	printf("Ano de exibicao:\n");
	int ano= conferirNumero(3000);
	printf("Hora de exibicao:\n");
	int hora= conferirNumero(23);
	printf("Minuto de exibicao:\n");
	int minuto= conferirNumero(59);
	printf("Preco:\n");
	float preco = conferirPreco();
	
	printf("\n\nSessao: %i - %s\n%i/%i/%i as %i:%i\nPreco: R$ %.2f\n\nConfirma inclusao?\n",codigo, titulo, dia, mes, ano, hora, minuto, preco);
	char opcao[20];
	scanf("%s", opcao);
	
	if(opcao[0] == 's'){
		for(int i = 0; i < 20; i++){
			sessao[codigo].titulo[i] = titulo[i];
		}
			
		sessao[codigo].sala = sala;
		sessao[codigo].dia = dia;
		sessao[codigo].mes = mes;
		sessao[codigo].ano = ano;
		sessao[codigo].hora = hora;
		sessao[codigo].minuto = minuto;
		sessao[codigo].preco = preco;
		sessao[codigo].atividade = true;
	
		for(int i = 0; i < 240; i++){
			sessao[codigo].assento[i] = true;
		}
		
		printf("Sessao cadastrada\n\n");
	}
	else{
		printf("Operacao Cancelada\n\n");
	}
	
	
}

float conferirPreco(void){
	float n;
	int erro = 0;
	bool run = true;
	
	while(run){
		scanf("%f", &n);
		
		if(n >= 0 && n <= 100000){
			return n;
		}
		else{
			printf("Resposta invalida, tente novamente\n");
			erro++;
			if(erro >2){
				printf("Erro. Item definido em \"0\"\n");
				return 0;
			}
		}
	}
}

int conferirNumero(int limite){
	
	int n;
	int erro = 0;
	bool run = true;
	
	while(run){
		scanf("%i", &n);
		
		if(n >= 0 && n <= limite){
			return n;
		}
		else{
			printf("Resposta invalida, tente novamente\n");
			erro++;
			if(erro >2){
				printf("Erro. Item definido em 0\n");
				return 0;
			}
		}
	}
}

char conferirLetra(char limite){
	
	char a;
	scanf("%c", &a);
	char final, opcao[20];
	int erro = 0;
	bool run = true;
	
	while(run){
		for (int i = 0; final != '\n'; i++){
			opcao[i] = getchar();
			final = opcao[i];
			}
		if(opcao[0] >= 'a' && opcao[0] <= limite){
			return opcao[0];
		}
		else{
			printf("Resposta invalida, tente novamente\n");
			erro++;
			if(erro >2){
				printf("Erro. Item definido em \"a\"\n");
				return a;
			}
		}
	}	
}

float desconto(){
	printf("Idade?\n");
	int idade;
	scanf("%i", &idade);
	if ((idade >= 2 && idade <= 8) || idade >= 60){
		printf("Desconto de 50%%!\n\n");
		printf("Cota gratuita de Terca-feira?\n");
		char resp[20];
		scanf("%s", &resp);
		if(resp[0] == 's'){
			return 0;
		}
		else{
			return 0.5;
		}
	}
	else{
		printf("Inserir desconto promocional?\n\n0 - Nao\n1 - Professor publico\n2 - Esudante\n3 - Cota gratuita de Terca-feira\n\n");
		int escolha = conferirNumero(3);
		switch(escolha){
			case 0: return 1;
			case 1: return 0.5;
			case 2: return 0.5;
			case 3: return 0;
		}
	}
}


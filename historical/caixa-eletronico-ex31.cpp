/*
Nome do programa......: Controle de Saldo 2000
Descricao do Programa.: Simula um caixa eletronico. Usa o comando do while e do while para
                         manter o menu funcionando ate que o usuario escolha a
                         opcao 0, permitindo consultar saldo, depositar e sacar.
Autor.................: Enhazo
*/
  //fstream (arquivo .txt) e iomanip (formatação em R$).
#include <iostream>
#include <fstream>//Permite criar, ler e escrever arquivos, como o .txt do seu programa.
#include <sstream>//Permite trabalhar com textos como se fossem fluxos de entrada/saída. É útil para converter ou organizar textos.
#include <iomanip>//Serve para formatar números, por exemplo:
#include <string>
#include <locale.h>

using namespace std;

/*Funcao auxiliar que formata um valor double no estilo R$ 1234,56*/
string formatarReal(double valor)
{
	ostringstream oss;
	oss << fixed << setprecision(2) << valor;//para mostrar 10.50 em vez de 10.5.
	string texto = oss.str();

	/*Troca o ponto (formato americano) pela virgula (formato brasileiro)*/
	for (int i = 0; i < texto.length(); i++)
	{
		if (texto[i] == '.')
		{
			texto[i] = ',';
		}
	}

	return "R$ " + texto;
}

int main()
{
	setlocale(0, "Portuguese");

	const double TAXA_DEPOSITO = 5.00;
	const double LIMITE_TAXA = 2000.00;
	const double LIMITE_NEGATIVO = 1000.00;

	double saldo = 0;
	double saldoInicial = 0;
	double valor = 0;
	double totalDepositos = 0;
	double totalSaques = 0;
	int qtdDepositos = 0;
	int qtdSaques = 0;
	int num = -1;
	char confirma;
	char opcao;
	bool continuarPrograma = true;

	do
	{
		system("cls");

		/*Zera as variaveis a cada nova execucao do programa*/
		saldo = 0;
		saldoInicial = 0;
		totalDepositos = 0;
		totalSaques = 0;
		qtdDepositos = 0;
		qtdSaques = 0;

		cout << "=== Maquina Eletronica ===";
		cout << "\nInforme o saldo inicial: ";
		cin >> saldo;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Valor invalido! Digite novamente o saldo inicial: ";
			cin >> saldo;
		}

		cin.ignore(1000, '\n');

		saldoInicial = saldo;

		do
		{
			system("cls");

			if (saldo < 0)
			{
				cout << "\033[31m";
				cout << "\nSeu saldo Atual e: " << formatarReal(saldo);
				cout << "\033[0m";
			}
			else
			{
				cout << "\nSeu saldo Atual e: " << formatarReal(saldo);
			}

			cout << "\n===========================";
			cout << "\n Para consultar digite-----1";
			cout << "\n Para depositar digite------2";
			cout << "\n Para sacar digite----------3";
			cout << "\n Para Sair digite------------0";
			cout << "\n===========================" << endl;
			cout << "Escolha uma opcao: ";
			cin >> num;

			while (cin.fail())
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Opcao invalida! Digite novamente: ";
				cin >> num;
			}

			cin.ignore(1000, '\n');

			if (num == 1)
			{
				cout << "\nPressione ENTER para continuar...";
				cin.get();
			}
			else if (num == 2)//se a primeira for falsa, verifica outra condição.
			{
				cout << "\nDigite o valor do deposito: ";
				cin >> valor;

				while (cin.fail())
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Valor invalido! Digite novamente: ";
					cin >> valor;
				}

				cin.ignore(1000, '\n');

				if (valor <= 0)
				{
					cout << "\nValor do deposito invalido !!!";
				}
				else
				{
					double valorCreditado = valor;

					if (valor > LIMITE_TAXA)
					{
						valorCreditado = valor - TAXA_DEPOSITO;

						cout << "\nComo o deposito foi maior que "
							 << formatarReal(LIMITE_TAXA)
							 << ", foi cobrada uma taxa de "
							 << formatarReal(TAXA_DEPOSITO) << ".";
					}

					saldo = saldo + valorCreditado;
					totalDepositos = totalDepositos + valorCreditado;
					qtdDepositos = qtdDepositos + 1;

					cout << "\nDeposito realizado! Saldo atualizado: "
						 << formatarReal(saldo);
				}

				cout << "\nPressione ENTER para continuar...";
				cin.get();
			}
			else if (num == 3)//se a primeira for falsa, verifica outra condição.
			{
				cout << "\nDigite o valor do saque: ";
				cin >> valor;

				while (cin.fail())
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Valor invalido! Digite novamente: ";
					cin >> valor;
				}

				cin.ignore(1000, '\n');

				if (valor <= 0)
				{
					cout << "\nValor do saque invalido !!!";
				}
				else if (saldo - valor < -LIMITE_NEGATIVO) //se a primeira for falsa, verifica outra condição.
				{
					cout << "\nOperacao nao permitida! Esse saque deixaria seu saldo mais de "
						 << formatarReal(LIMITE_NEGATIVO)
						 << " negativo.";
				}
				else if (saldo - valor < 0) //se a primeira for falsa, verifica outra condição.
				{
					cout << "\nEsse saque deixara seu saldo negativo. "
						 << "Confirma a operacao? (S/N): ";

					cin >> confirma;
					cin.ignore(1000, '\n');

					if (confirma == 's' || confirma == 'S')
					{
						saldo = saldo - valor;
						totalSaques = totalSaques + valor;
						qtdSaques = qtdSaques + 1;

						cout << "\nSaque realizado! Saldo atualizado: "
							 << formatarReal(saldo);
					}
					else
					{
						cout << "\nOperacao cancelada.";
					}
				}
				else
				{
					saldo = saldo - valor;
					totalSaques = totalSaques + valor;
					qtdSaques = qtdSaques + 1;

					cout << "\nSaque realizado! Saldo atualizado: "
						 << formatarReal(saldo);
				}

				cout << "\nPressione ENTER para continuar...";
				cin.get();
			}
			else if (num != 0)//se a primeira for falsa, verifica outra condição.
			{
				cout << "\nOpcao invalida!";
				cout << "\nPressione ENTER para continuar...";
				cin.get();
			}

		} while (num != 0);

		int totalOperacoes = qtdDepositos + qtdSaques;

		system("cls");

		cout << "\n=== Relatorio Final ===";
		cout << "\nSaldo Inicial: " << formatarReal(saldoInicial);
		cout << "\nTotal de depositos: " << formatarReal(totalDepositos);
		cout << "\nQuantidade de depositos: " << qtdDepositos;
		cout << "\nTotal de saques: " << formatarReal(totalSaques);
		cout << "\nQuantidade de saques: " << qtdSaques;
		cout << "\nTotal de operacoes: " << totalOperacoes;
		cout << "\nSaldo Final: " << formatarReal(saldo);

		/*Salva o relatorio final num arquivo txt*/
		ofstream arquivo("saldo.txt");

		if (arquivo.is_open())
		{
			arquivo << "=== Relatorio Final ===\n";
			arquivo << "Saldo Inicial: "
					<< formatarReal(saldoInicial) << "\n";
			arquivo << "Total de depositos: "
					<< formatarReal(totalDepositos) << "\n";
			arquivo << "Quantidade de depositos: "
					<< qtdDepositos << "\n";
			arquivo << "Total de saques: "
					<< formatarReal(totalSaques) << "\n";
			arquivo << "Quantidade de saques: "
					<< qtdSaques << "\n";
			arquivo << "Total de operacoes: "
					<< totalOperacoes << "\n";
			arquivo << "Saldo Final: "
					<< formatarReal(saldo) << "\n";

			arquivo.close();

			cout << "\n\n(Saldo salvo em saldo.txt)";
		}

		cout << "\n\nDeseja executar novamente? (S/N): ";
		cin >> opcao;

		if (opcao == 'n' || opcao == 'N')
		{
			cout << "\nTem certeza que deseja encerrar? (S/N): ";
			cin >> opcao;

			if (opcao == 's' || opcao == 'S')
			{
				cout << "\nEncerrando o programa...\n";
				continuarPrograma = false;
			}
			else
			{
				cout << "\nReiniciando...\n\n";
			}
		}

	} while (continuarPrograma);

	system("pause");

	return 0;
}
/*
      Foram adicionadas algumas funções extras ao código:

* Aviso quando o saque passar de **R$ 1.000 abaixo do zero**, impedindo o saque.
* Uso do **do while** no primeiro looping, de forma simples.
* Ao finalizar com **0**, o saldo é salvo em um arquivo **`.txt`**.Usei IA nesse
* Os valores agora aparecem formatados em **R$**. Usei IA nesse 
* Foi adicionada uma **taxa em depósitos acima de R$ 2.000**, enquanto saques acima desse valor não possuem taxa.
* É na parte onde detecta erros e os ignora tambem usei IA pra me ajudar a implementar.

*/

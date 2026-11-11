// CAIXA ELETRÔNICO

#include <iostream>
#include <string> 
#include <cmath>
#include <cctype>
#include <iomanip>
#include <limits>
#include <windows.h>
#include <locale.h>
#include <ctime>
#include <fstream>

using namespace std;

int main()
{
	//Verificação do horario local do computador
	time_t agora = time(NULL);
	tm* tempoLocal = localtime(&agora);
	int hora = (tempoLocal != NULL) ? tempoLocal->tm_hour : 12;
	
	cout << fixed << setprecision(2);
	char repeat = 's';
	
	if (__GNUC__ <= 9) {
		setlocale(LC_ALL, "Portuguese_Brazil");	
	}
	
	else {
		if(__GNUC__ >= 9) {
			SetConsoleOutputCP(CP_UTF8);	
		}
	}

    do {
    	string nome = "";
		double saldoinicial=0;
	    double saldo=0;
	    double deposito=0;
	    double saque=0;
	
	    double totaldepositos = 0;
	    double totalsaques = 0;
	
	    int opcao = -1;
	    char confirmacao = 'p';
	    
	    int contadorVermelho = 0;
	
	    // Entrada do saldo inicial
	    system("cls");
	    
	    cout << "======================================" << endl;
	    cout << "    C A I X A  E L E T R Ô N I C O" << endl;
	    cout << "======================================" << endl;
	    cout << "         Abertura de Conta" << endl;
	   	cout << "======================================" << endl;
		cout << "Informe seu nome: " << endl;
		getline(cin, nome);
		cout << "======================================" << endl;
	    cout << "Depósito inicial: R$ ";
	    cin >> saldoinicial;
	
	    saldo = saldoinicial;
	
	    // Menu
	    do
	    {
	        cout << "======================================" << endl;
	        
	        //Mostrar bom dia, boa tarde ou boa noite dependo do horário
	        if (hora >= 5 && hora < 12) {
		        cout << "Bom dia, ";
		    } else if (hora >= 12 && hora < 18) {
		        cout << "Boa tarde, ";
		    } else {
		        cout << "Boa noite, ";
		    }
		    
	        cout << nome << endl;
	        cout << "=============================================" << endl;
	        cout << "           --- MENU PRINCIPAL ---" << endl;
	        cout << "=============================================" << endl;
	        cout << "| [1] Consultar saldo | [3] Sacar dinheiro  |" << endl;
	        cout << "| [2] Depositar       | [0] Sair            |" << endl;
	        cout << "=============================================" << endl;
	        cout << "              Escolha uma opção" << endl;
	
	        cout << "Digite uma opção: ";
	        cin >> opcao;
			system("cls");
			cout << "======================================" << endl;
	    	cout << "    C A I X A  E L E T R Ô N I C O" << endl;
	    	cout << "======================================" << endl;
	
	        // OPÇÃO 1 - CONSULTAR SALDO
	        if (opcao == 1)
	        {
	            if (saldo < 0)
	            {
	                //Saldo negativo piscando em dois tons de vermelho
	                Beep(1000, 100);
	                contadorVermelho = 0;
	                do {
	                    cout << "\r\033[31m" << "Saldo atual: R$ " << saldo << flush;
	                    Sleep(250);
	                    cout << "\r\033[91m" << "Saldo atual: R$ " << saldo << flush;
	                    Sleep(250);
	                    contadorVermelho = contadorVermelho + 1;
	                } while (contadorVermelho != 3);
	                cout << "\033[0m" << endl;
	            }
	            else
	            {
	            	cout << "           CONSULTA SALDO             " << endl;
	        		cout << "======================================" << endl;
	                cout << "Saldo atual: R$ " << saldo << endl;
	            }
	        }
	
	        // OPÇÃO 2 - DEPÓSITO
	        else if (opcao == 2)
	        {
	        	cout << "              DEPÓSITO                " << endl;
	        	cout << "======================================" << endl;
				cout << "Informe o valor do depósito: R$ ";
	            cin >> deposito;
	            deposito = abs(deposito);
	            
	            if (deposito != 0) 
	            {
	            	saldo = saldo + deposito;
	            	totaldepositos = totaldepositos + deposito;
					cout << "======================================" << endl;
					cout << "\033[32m";
	            	cout << "Depósito realizado com sucesso!" << endl;
	            	cout << "\033[0m";
					cout << "======================================" << endl;
	              
	            	if (saldo < 0)
	            	{
	            		//Saldo negativo piscando em dois tons de vermelho
	            		Beep(1000, 100);
	            		contadorVermelho = 0;
	            		do {
	            		    cout << "\r\033[31m" << "Saldo atualizado: R$ " << saldo << flush;
	            		    Sleep(250);
	            		    cout << "\r\033[91m" << "Saldo atualizado: R$ " << saldo << flush;
	            		    Sleep(250);
	            		    contadorVermelho = contadorVermelho + 1;
	            		} while (contadorVermelho != 3);
	            		cout << "\033[0m" << endl;
	            	}
	            	else
	            	{
	            		cout << "Saldo atualizado: R$ " << saldo << endl;
	            	} 
	            }
	            else 
	            {
	            	cout << "======================================" << endl;
	                cout << "\033[31m";                             
	                cout << "      <<< Valor de depósito inválido, operação cancelada! >>>" << endl;
	                cout << "\033[0m";
	                cout << "======================================" << endl;
				}
	        }
	
	        // OPÇÃO 3 - SAQUE
	        else if (opcao == 3)
	        {
	        	cout << "                  SAQUE               " << endl;
	        	cout << "======================================" << endl;
	            cout << "Informe o valor do saque: R$ ";
	            cin >> saque;
	            saque = abs(saque);
	
	            if (saque != 0) 
	            {
					// Verifica se o saldo ficará negativo
	                if (saldo - saque < 0)
	                {
	                    cout << endl;
	                    
	                    cout << "\033[33m";
	                    cout << "==============================================" << endl;
	                    cout << "           CONFIRMAR OPERAÇÃO" << endl;
	                    cout << "==============================================" << endl;
	                    cout << "O saque deixará o saldo negativo." << endl;
	                    cout << "Você deseja realmente realizar esta operação?" << endl;
	                    cout << "----------------------------------------------" << endl;
	                    cout << "       [N] CANCELAR        [S] OK" << endl;
	                    cout << "==============================================" << endl;
	                    cout << "Escolha (s/n): ";
	                    cout << "\033[0m";
	                    cin >> confirmacao;
	                    confirmacao = char(tolower(confirmacao));
	
	                    if (confirmacao == 's')
	                    {
	                        saldo = saldo - saque;
	                        totalsaques = totalsaques + saque;
							
							cout << "\033[32m";
	                        cout << "Saque realizado com sucesso!" << endl;
	                        cout << "\033[0m";
	                    	cout << "======================================" << endl;
	                    }
	                    else
	                    {
	                    	cout << "======================================" << endl;
	                    	cout << "\033[31m";                             
	                        cout << "      <<< Operação cancelada >>>" << endl;
	                        cout << "\033[0m";
	                        cout << "======================================" << endl;
	                    }
	                }
	                else
	                {
	                    saldo = saldo - saque;
	                    totalsaques = totalsaques + saque;
						cout << "======================================" << endl;
						cout << "\033[32m";
	                    cout << "Saque realizado com sucesso!" << endl;
	                    cout << "\033[0m";
	                    cout << "======================================" << endl;
	                }
	
	                // Mostra o saldo atualizado
	                if (saldo < 0)
	                {
	                	//Saldo negativo piscando em dois tons de vermelho
	                	Beep(1000, 100);
	                	contadorVermelho = 0;
	                	do {
	                	    cout << "\r\033[31m" << "Saldo atualizado: R$ " << saldo << flush;
	                	    Sleep(250);
	                	    cout << "\r\033[91m" << "Saldo atualizado: R$ " << saldo << flush;
	                	    Sleep(250);
	                	    contadorVermelho = contadorVermelho + 1;
	                	} while (contadorVermelho != 3);
	                	cout << "\033[0m" << endl;
	                }
	                else
	                {
	                    cout << "Saldo atualizado: R$ " << saldo << endl;
	                }
	            }
	            else 
	            {
	            	cout << "======================================" << endl;
	                cout << "\033[31m";                             
	                cout << "      <<< Valor de saque inválido, operação cancelada >>>" << endl;
	                cout << "\033[0m";
	                cout << "======================================" << endl;
				}
	        }
	        
	        // OPÇÃO 0 - SAIR
	        else if (opcao == 0)
	        {
	            cout << endl;
	            cout << "Encerrando o sistema..." << endl;
	        }
	
	        // OPÇÃO INVÁLIDA
	        else
	        {
	        	cout << "\033[33m"; 
	            cout << "Opção inválida! Tente novamente." << endl;
	            cout << "\033[0m"; 
	        }
	
	    } while (opcao != 0);
	
	    // RESUMO FINAL
	    cout << endl;
	    cout << "======================================" << endl;
	    cout << "              RESUMO FINAL            " << endl;
	    cout << "======================================" << endl;
	
	    cout << "Saldo inicial:        R$ " << saldoinicial << endl;
	    cout << "Total de depósitos:   R$ " << totaldepositos << endl;
	    cout << "Total de saques:      R$ " << totalsaques << endl;
	
	    if (saldo < 0)
	    {
	    	//Saldo negativo piscando em dois tons de vermelho
	    	Beep(1000, 100);
	    	contadorVermelho = 0;
	    	do {
	    	    cout << "\r\033[31m" << "Saldo final:          R$ " << saldo << flush;
	    	    Sleep(250);
	    	    cout << "\r\033[91m" << "Saldo final:          R$ " << saldo << flush;
	    	    Sleep(250);
	    	    contadorVermelho = contadorVermelho + 1;
	    	} while (contadorVermelho != 3);
	    	cout << "\033[0m" << endl;
	    }
	    else
	    {
	        cout << "Saldo final:          R$ " << saldo << endl;
	    }
	
	    cout << "======================================" << endl;
	
	    /* Menu para escolher como o relatorio final sera salvo (fica dentro do loop, roda em toda sessao) */
	    int arquivos = -1;
	
	    cout << "======================================" << endl;
	    cout << "         SELECIONE A OPCAO DESEJADA" << endl;
	    cout << "======================================" << endl;
	    cout << "1 - Imprimir em .csv (Excel)" << endl;
	    cout << "2 - Imprimir em .txt" << endl;
	    cout << "3 - Imprimir em ambos" << endl;
	    cout << "0 - So fechar" << endl;
	    cout << "======================================" << endl;
	    cout << "Digite uma opcao: ";
	    cin >> arquivos;
	
	    /* Gera um horario para usar no nome do arquivo, assim cada relatorio sai com um nome diferente e nao apaga o anterior */
	    time_t agoraArquivo = time(NULL);
	    tm* tempoArquivo = localtime(&agoraArquivo);
	    char horarioArquivo[30];
	    strftime(horarioArquivo, sizeof(horarioArquivo), "%d-%m-%Y_%H-%M-%S", tempoArquivo);
	
	    /* Nomes finais dos arquivos, ja com o horario incluido */
	    string nomeArquivoCsv = "Saldo-" + string(horarioArquivo) + ".csv";
	    string nomeArquivoTxt = "Saldo-" + string(horarioArquivo) + ".txt";
	
	    if (arquivos == 1)
	    {
	        ofstream arquivo(nomeArquivoCsv.c_str());
	
	        if (arquivo.is_open())
	        {
	            arquivo << "Relatorio Final\n";
	            arquivo << "Saldo Inicial;" << saldoinicial << "\n";
	            arquivo << "Total de depositos;" << totaldepositos << "\n";
	            arquivo << "Total de saques;" << totalsaques << "\n";
	            arquivo << "Saldo Final;" << saldo << "\n";
	
	            arquivo.close();
	
	            cout << "\nSaldo salvo em " << nomeArquivoCsv << "!" << endl;
	        }
	        else
	        {
	            cout << "\nErro ao criar o arquivo " << nomeArquivoCsv << "!" << endl;
	        }
	    }
	    else if (arquivos == 2)
	    {
	        ofstream arquivo(nomeArquivoTxt.c_str());
	
	        if (arquivo.is_open())
	        {
	            arquivo << "======================================\n";
	            arquivo << "          RELATORIO FINAL\n";
	            arquivo << "======================================\n";
	            arquivo << "Saldo Inicial:       R$ " << saldoinicial << "\n";
	            arquivo << "Total de depositos:  R$ " << totaldepositos << "\n";
	            arquivo << "Total de saques:     R$ " << totalsaques << "\n";
	            arquivo << "Saldo Final:         R$ " << saldo << "\n";
	            arquivo << "======================================\n";
	
	            arquivo.close();
	
	            cout << "\nSaldo salvo em " << nomeArquivoTxt << "!" << endl;
	        }
	        else
	        {
	            cout << "\nErro ao criar o arquivo " << nomeArquivoTxt << "!" << endl;
	        }
	    }
	    else if (arquivos == 3)
	    {
	        /* ============================== */
	        /* ARQUIVO TXT */
	        /* ============================== */
	
	        ofstream arquivoTxt(nomeArquivoTxt.c_str());
	
	        if (arquivoTxt.is_open())
	        {
	            arquivoTxt << "======================================\n";
	            arquivoTxt << "          RELATORIO FINAL\n";
	            arquivoTxt << "======================================\n";
	            arquivoTxt << "Saldo Inicial:       R$ " << saldoinicial << "\n";
	            arquivoTxt << "Total de depositos:  R$ " << totaldepositos << "\n";
	            arquivoTxt << "Total de saques:     R$ " << totalsaques << "\n";
	            arquivoTxt << "Saldo Final:         R$ " << saldo << "\n";
	            arquivoTxt << "======================================\n";
	
	            arquivoTxt.close();
	
	            cout << "\nSaldo salvo em " << nomeArquivoTxt << "!" << endl;
	        }
	        else
	        {
	            cout << "\nErro ao criar o arquivo " << nomeArquivoTxt << "!" << endl;
	        }
	
	        /* ============================== */
	        /* ARQUIVO CSV */
	        /* ============================== */
	
	        ofstream arquivoCsv(nomeArquivoCsv.c_str());
	
	        if (arquivoCsv.is_open())
	        {
	            arquivoCsv << "Relatorio Final\n";
	            arquivoCsv << "Saldo Inicial;" << saldoinicial << "\n";
	            arquivoCsv << "Total de depositos;" << totaldepositos << "\n";
	            arquivoCsv << "Total de saques;" << totalsaques << "\n";
	            arquivoCsv << "Saldo Final;" << saldo << "\n";
	
	            arquivoCsv.close();
	
	            cout << "Saldo salvo em " << nomeArquivoCsv << "!" << endl;
	        }
	        else
	        {
	            cout << "Erro ao criar o arquivo " << nomeArquivoCsv << "!" << endl;
	        }
	    }
	    else if (arquivos == 0)
	    {
	        cout << "\nNenhum arquivo foi gerado." << endl;
	    }
	    else
	    {
	        cout << "\nOpcao invalida!" << endl;
	    }
	
	    cout << "\nDeseja repetir o programa? (s) ou (n)\n";
	    cin >> repeat;
	    
	    repeat = char(tolower(repeat));
	    
	    cin.ignore(numeric_limits<streamsize>::max(), '\n');
	    
	    do {
	    	if (repeat != 'n' and repeat != 's') {
		    	cout << "\nOpção inválida! (s) ou (n)\n";
		    	cin >> repeat;
			}
		} while (repeat != 'n' and repeat != 's');
	} while (repeat == 's');

	system("pause") ;
	
    return 0;
}

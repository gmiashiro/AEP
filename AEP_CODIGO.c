#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <windows.h>
#include <string.h>

	//COR DA letra
enum{  BLACK,                 //0
       BLUE,                  //1
       GREEN,                 //2
       CYAN,                  //3
       RED,                   //4
       MAGENTA,               //5
       BROWN,                 //6
       LIGHTGRAY,             //7
       DARKGRAY,              //8
       LIGHTBLUE,             //9
       LIGHTGREEN,            //10
       LIGHTCYAN,             //11
       LIGHTRED,              //12
       LIGHTMAGENTA,          //13
       YELLOW,                //14
       WHITE                  //15
       
       };  
  //COR DO FUNDO
enum{  _BLACK=0,                   //0
       _BLUE=16,                   //1
       _GREEN=32,                  //2
       _CYAN=48,                   //3
       _RED=64,                    //4
       _MAGENTA=80,                //5
       _BROWN=96,                  //6
       _LIGHTGRAY=112,             //7
       _DARKGRAY=128,              //8
       _LIGHTBLUE=144,             //9
       _LIGHTGREEN=160,            //10
       _LIGHTCYAN=176,             //11
       _LIGHTRED=192,              //12
       _LIGHTMAGENTA=208,          //13
       _YELLOW=224,                //14
       _WHITE=240                  //15       
       };
       
void linhaCol(int x, int y); //Função para colocar uma posição no prompt

void textColor(int letras, int fundo); //Mudar cor do texto/fundo

void box(int lin1, int col1, int lin2, int col2, char palavra[]); // Função para criação de caixas

int menu(int lin1, int col1, int qtd, char lista[3][40], int pulaLinha, int temTela, int *opcaoAtual); // função para criação de menu com opções selecionáveis

int leArq(int conta); // Função que lê o arquivo, coloca as linhas no vetor linhas e a quantidade de linhas em quant

void ordena(); // Procedimento que classifica e ordena os vetores

int validaSenha(char sen[]); // Função que valida a senha inserida pelo usuário

int escreveArq(char u[100]); // Função que escreve no arquivo txt

void addUsuario(); // Procedimento para adicionar novos usuários

int buscaUsuario(char * nome, char usuarios[][100], int totalusuarios); // Função para buscar os usuários no arquivo

void altUsuario(); // Procedimento para alterar o cadastro dos usuários

void listUsuario(); // procedimento para listar os usuários

void exUsuarios(); // Procedimento que exclui os usuários do TXT

void criptografar(); // Procedimento para criptografar 

void descriptografar();// Procedimento para descriptografar

char linha[200][100];  // Um vetor de strings onde vai armazenar os dados dos usuários - É ordenado
char linhaArq[200][100];  // Um vetor de strings onde vai armazenar os dados dos usuários - É igual está no TXT (não ordenado)
int quant = 0; // Quantidade de linhas

//--------------------------------------------------------------------------------------------------------

int main(){
	
	char menuOpcs[6][40]={"Incluir usuários","Alterar usuários","Excluir usuários","Listar usuários ","Créditos        ","Sair            "}; // lista com o nome das opções selecionáveis
	int opc=1,repete=0;
	char titulo[50];
	
	setlocale(LC_ALL, "Portuguese"); // permite acentuação
	setlocale(LC_ALL,"");
	
	system("mode 120,30"); // Inicializa o programa em uma janela com 120 colunas e 30 linhas

    leArq(0); // Lê o TXT e armazena as linhas no vetor
    ordena(); // Ordena o vetor
	
	while (repete==0){
	
		setlocale(LC_ALL,"C"); // Caixa que cobre toda a tela
		strcpy(titulo,""); // copia alguma palavra para colocar no titulo da caixa
	   	box(1,1,30,120,titulo);
	   	setlocale(LC_ALL,""); //permite a geração do sen[cont]ere que faz a caixa
		
		linhaCol(6,16); // Mensagem em cima do menu de opções
		printf("    Gerenciamento");
		linhaCol(7,21);
		printf("de usuários");
		

		opc = menu(9,16,6,menuOpcs,2,1,&opc);

		// explicação: opção recebe menu criando uma caixa a partir da linha 9 coluna 16 com 6 sen[cont]eres de espaço, usando a matrix menuOpcs como referencia, 2 linhas serão puladas a cada frase, o 1 serve para criação da tela (é possivel criar apenas as opções selecionáveis sem a caixa em volta trocando por um 0), por ultimo temos passagem por referencia de opc para sempre que sair de uma função a opção continuar na opção escolhida anteriormente

		switch(opc){
			case 1: //Incluir usuários
				setlocale(LC_ALL,"C"); // volta para o modo de texto padrão
				strcpy(titulo,"Incluir"); // copia o titulo que quer colocar nacaixa
				box(5,60,20,100,titulo); // faz a caixa com o titulo
                addUsuario();
				setlocale(LC_ALL,""); // modo de sen[cont]eres da caixa
				getch(); // espera comando
				system("cls");	//limpa tela	
			break;
			case 2: //Alterar usuários
				setlocale(LC_ALL,"C");
				strcpy(titulo,"Alterar");
				box(5,60,20,100,titulo);
				altUsuario();
                leArq(1); // Lê o arquivo para atualizar o vetor de nomes
                ordena(); // Ordena o vetor de nomes
				setlocale(LC_ALL,"");
				getch();
				system("cls");
			break;
			case 3: //Excluir usuários
				setlocale(LC_ALL,"C");
				strcpy(titulo,"Excluir");
				box(5,60,20,100,titulo);
                exUsuarios();
                leArq(1); // Lê o arquivo para atualizar o vetor de nomes
                ordena(); // Ordena o vetor de nomes
				setlocale(LC_ALL,"");
				getch();
				system("cls");
			break;
			case 4: //Listar usuários 
				setlocale(LC_ALL,"C");
				strcpy(titulo,"Listar");
				box(5,60,20,100,titulo);
				listUsuario();
				setlocale(LC_ALL,"");
				getch();
				system("cls");
			break;
			case 5: //Créditos
				linhaCol(25,60);        
				printf("Desenvolvido por: Gabriel Miashiro \n");
				linhaCol(26,78);
				printf("Laura Vitória \n");
				linhaCol(27,78);
				printf("Murilo Eduardo");
				getch();
				system("cls");	
			break;
			case 6: //Sair            
				repete=1;	
			break;
		}
	}
	return 0;
}

//--------------------------------------------------------------------------------------------------------
// Função que altera a cor do texto/fundo
void textColor(int letra, int fundo){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), letra + fundo);
}

//--------------------------------------------------------------------------------------------------------
// Função que adiciona um cursor para a interface (posicionamento)
void linhaCol(int lin, int col){
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){col-1,lin-1});// coordenada na tela

    //funcao para deixar o cursor invisivel
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

//--------------------------------------------------------------------------------------------------------
// Função para criar caixas
void box(int lin1, int col1, int lin2, int col2,char palavra[]){
	int i,j,tamlin,tamcol;
	
	tamlin = lin2 - lin1;
    tamcol = col2 - col1;
		
	for (i=col1; i<=col2; i++){ // linhas
        linhaCol(lin1,i);
        printf("%c",196);
        linhaCol(lin2,i);
        printf("%c",196);
    }	
    
	for (i=lin1; i<=lin2; i++){ //colunas
         linhaCol(i,col1);
         printf("%c",179);
         linhaCol(i,col2);
         printf("%c",179);
    } 
	   
	for (i=lin1+1;i<lin2;i++){
         for(j=col1+1;j<col2;j++)
		{
            linhaCol(i,j);printf("");
        }
	}
	//posição dos cantos
	linhaCol(lin1,col1);
    printf("%c%s",218,palavra);	
    linhaCol(lin1,col2);
    printf("%c",191);
    linhaCol(lin2,col1);
    printf("%c",192);
    linhaCol(lin2,col2);
    printf("%c",217);	
}

//--------------------------------------------------------------------------------------------------------
// Função para criar menus com opções selecionáveis
int menu(int lin1, int col1, int qtd, char lista[3][40], int pulaLinha, int temTela, int *opcaoAtual) { 
    int opc = *opcaoAtual; // Inicia com a última opção selecionada
    int lin2, col2, linha, i, tamMaxItem, tecla;
    char s[]="";
    
    // Calcula as coordenadas
    tamMaxItem = strlen(lista[0]);
    
    // Tamanho máximo do item
    for (i = 1; i < qtd; i++) {
        if (strlen(lista[i]) > tamMaxItem) {
            tamMaxItem = strlen(lista[i]);
        }
    }
    lin2 = lin1 + (qtd * 2 + 2);
    col2 = col1 + tamMaxItem + 4;
    
    // Monta Tela
    if (temTela == 1) {
        textColor(WHITE, _BLACK);
        setlocale(LC_ALL, "C");
        box(lin1, col1, lin2, col2,s);
        setlocale(LC_ALL, "");
    }

    // Laço das opções
    while (1) {
        linha = lin1 + 2;
        for (i = 0; i < qtd; i++) {
            if (i + 1 == opc) {
                textColor(BLACK, _WHITE);
            } else {
                textColor(WHITE, _BLACK);
            }
            linhaCol(linha, col1 + 2);
            printf("%s", lista[i]);
            linha += pulaLinha;
        }
        // Aguarda tecla
        linhaCol(1, 1);
        tecla = getch();
        linhaCol(22, 1);
        
        
        // Opções
        if (tecla == 27) { // ESC
            opc = 0;
            Beep (329, 50);
            break;
        } else if (tecla == 13) { // ENTER
            *opcaoAtual = opc; // Atualiza a posição selecionada
            Beep (329, 50);
            break;
        }
        // Seta para cima
        else if (tecla == 72) { // se possível, seleciona o item anterior - seta para cima
            if (opc > 1) {
                opc--; // Se a opção for maior que 1, pode voltar
            } else {
                opc = qtd; // Se estiver na primeira opção, vai para a última
            }
            Beep (329, 50);
        }
        // Seta para baixo
        else if (tecla == 80) { // seta para baixo
            if (opc < qtd) {
                opc++; // Se a opção for menor que a quantidade de itens, pode avançar
            } else {
                opc = 1; // Se estiver na última opção, vai para a primeira
            }
            Beep (329, 50);
        }
    }
    return opc;
}

//--------------------------------------------------------------------------------------------------------
//------------LÊ O ARQUIVO--------------
// Função que lê o arquivo txt
int leArq(int conta) {
    FILE *arq;  // tipo para arquivo
    int cont = 0;  // contador para o While
    char *resultado;  // variável de controle

    // conta == 0 -> primeira vez que vai ler o arquivo, então a variável quant recebe a quantidade de usuários
    // conta == 1 -> só está lendo o arquivo, não adiciona mais usuários para quant

    arq = fopen("Banco.txt", "rt");

    if (arq == NULL) { // Se não conseguir achar nada, mostra erro
        printf("Erro ao abrir o arquivo");
        return 0; // Fecha o programa
    }

    while(!feof(arq)) {  // Enquanto tem alguma coisa no arquivo
        resultado = fgets(linha[cont], 100, arq); // coloca em uma variável para ver se tem algo nela, e lê a linha em um vetor
        if (linha[cont][strlen(linha[cont]) -1] == '\n') {
            linha[cont][strlen(linha[cont]) -1] = '\0'; // Substitui o \n com \0
        }
        strcpy(linhaArq[cont], linha[cont]); // coloca no vetor que não será ordenado
        if (resultado) { 
            cont++; // começa no 0 e vai até não ter mais linhas
            if (conta == 0) {
                quant++; // Conta quantas linhas tem
            }
        }    
    }
    
    fclose(arq);
    return 0;
}

//--------------------------------------------------------------------------------------------------------
//-------------ORDENA OS VETORES----------------
//Classifica e ordena os vetores - Selection sort
void ordena() {
    int x, y;
    char tmp[100];
    
    for (x = 1; x < quant - 1; x++) {
      for (y = x + 1; y <= quant - 1; y++) {
         if (strcmp(linha[y], linha[x]) < 0) {
            strcpy(tmp, linha[x]);
            strcpy(linha[x], linha[y]);
            strcpy(linha[y], tmp);
         }
      }
    }
}

//--------------------------------------------------------------------------------------------------------
//------------ESCREVE NOS ARQUIVOS--------------
// Função que escreve no arquivo txt
int escreveArq(char u[100]) {
    FILE *arq;  // tipo para arquivo
    arq = fopen("Banco.txt", "a");

    if (arq == NULL) { // Se não conseguir achar nada, mostra erro
        printf("Erro ao abrir o arquivo");
        return 0; // Fecha o programa
    }
        
    strcpy(linha[quant], u); // Grava em uma linha de vetor, de acordo com a quantidade linhas
    strcpy(linhaArq[quant], u); // coloca na váriavel desordenada 

    fprintf(arq, "%s\n", linha[quant]); // Grava o input no arquivo! (nome + senha)
    fclose(arq);  // fecha o arquivo
    quant++; // Aumenta a quantidade de linhas
    ordena(); // Ordena o vetor com a nova linha
    return 0;
}

//--------------------------------------------------------------------------------------------------------
//-------------VALIDA SENHA----------------
// Função que valida a senha inserida pelo usuário
int validaSenha(char sen[]) {
    int quantLetMai, quantLetMin, quantNum, quantCar, cont, tam;
    quantLetMai = 0;
    quantLetMin = 0;
    quantNum = 0;
    quantCar = 0; 

    // Verifica se a senha tem:
    // 1 letra minúscula
    // 1 letra maiuscula
    // 1 numero
    // 1 caracter especial

    tam = strlen(sen);

    for (cont = 0; cont < tam; cont++) {
        if (sen[cont] >= 65 && sen[cont] <= 90) {
            quantLetMai++;
        } else if (sen[cont] >= 97 && sen[cont] <= 122) {
            quantLetMin++;
        } else if (sen[cont] >= 33 && sen[cont] <= 47) {
            quantCar++;
        } else if (sen[cont] >= 58 && sen[cont] <= 64) {
            quantCar++;
        } else if (sen[cont] >= 91 && sen[cont] <= 96) {
            quantCar++;
        } else if (sen[cont] >= 123 && sen[cont] < 127) {
            quantCar++;
        } else if (sen[cont] >= 48 && sen[cont] <= 57) {
            quantNum++;
        }
    }

    if (quantLetMai == 0 || quantLetMin == 0 || quantCar == 0 || quantNum == 0) {
        return 0;
    } else {
        return 1;
    }

}

//--------------------------------------------------------------------------------------------------------
//-------------ADICIONA USUÁRIOS----------------
// Procedimento para adicionar novos usuários
void addUsuario() {
    char nome[50], senha[50], usuario[100], senhas[50][100], usuariosLista[50][100], linhaPro[200];
    int vali, compr, cont, valiN;
	int totalusuarios = 0;

    while(totalusuarios <= quant){  // Divide a linha em nome e senha para buscar
        strcpy(linhaPro, linhaArq[totalusuarios]);
		char *token = strtok(linhaPro, " +\n");
		if(token != NULL){
			strcpy(usuariosLista[totalusuarios], token);
			token = strtok(NULL," +\n");
			if(token != NULL){
				strcpy(senhas[totalusuarios],token);
				//(totalusuarios)++;
			}
		}
        totalusuarios++;
	}
	if (totalusuarios > 0){
		descriptografar();
	}
    printf("\n");
    linhaCol(6,64);
    printf("Digite o nome: ");
    scanf("%s", nome);
    valiN = buscaUsuario(nome, usuariosLista, quant); // Busca o nome para ver se já tem igual

    if (valiN >= 0) {
        do {
            linhaCol(6,64);
            printf("                                  "); // Apaga qualquer coisa que estava nessa linha
            linhaCol(7,64);
            printf("                                  ");
            linhaCol(6,64);
            Sleep(300);
            Beep(1318.5, 100); 
            Beep(880, 150);
            printf("Nome já existe, tente outro");
            linhaCol(7,64);
            scanf("%s", nome);
            valiN = buscaUsuario(nome, usuariosLista, quant); // Busca o nome para ver se já tem igual
        } while (valiN >= 0);
    }

    Beep (329, 50);
    printf("\n");
    linhaCol(9,64); 
    printf("Digite uma senha com, no mínimo:");
    linhaCol(10,65); 
    printf("1 letra maiuscula;");
    linhaCol(11,65); 
    printf("1 letra minuscula;");
    linhaCol(12,65); 
    printf("1 número;");
    linhaCol(13,65); 
    printf("1 caracter especial;");
    linhaCol(14,65); 
    printf("8 caracteres;");
    linhaCol(16,64); 
    scanf("%s", senha);
    vali = validaSenha(senha);
    compr = strlen(senha);

    if (compr < 8 || vali == 0) { // Se for inválida, ele fala e pede de novo
        do {
            linhaCol(17,64);
            printf("                                  "); // Apaga qualquer coisa que estava nessa linha
            linhaCol(18,64);
            printf("                                  ");
            Sleep(300);
            linhaCol(17,64); 
            Beep(1318.5, 100);
            Beep(880, 150);
            printf("Senha inválida, digite novamente:");
            linhaCol(18,64); 
            scanf("%s", senha);
            vali = validaSenha(senha);
            compr = strlen(senha);
            } while (compr < 8 || vali == 0);
        }
        
    Beep (329, 50);
    printf("\n");

    strcpy(usuario, nome);  // Adiciona o nome do usuário
    strcat(usuario, " + ");  // Concatena com um sinal de mais entre dois espaços
    strcat(usuario, senha);  // Concatena com a senha

    linhaCol(17,64); 
    escreveArq(usuario); //Chama a função para gravar os dados do usuário no TXT
    Sleep(300); // Da uma leve delay para dar a impressao de estar fazendo algo

    for (cont = 6; cont <= 18; cont++) { // Limpa o quadrado
        linhaCol(cont,64);
        printf("                                   "); 
    }

    Beep(880, 80); // sons que indicam sucesso!
    Beep(1318.5, 130);
    linhaCol(11,64);
    printf("Cadastro realizado com sucesso!");
    linhaCol(19,67);
    printf("pressione ENTER para sair");
	criptografar();    
    
}
//--------------------------------------------------------------------------------------------------------
//-------------BUSCA USUÁRIOS----------------
// Função para buscar os usuários no arquivo
//parâmetro nome: o usuario que está sendo procurado, parâmetro usuários: contém todos os nomes de usuários, totalusuarios: número total de usuários
//Funcionamento: a função percorre todos os usuarios e compara atráves do strcmp cada nome. Se encontrar retorna o valor de i, senão retorna -1 
int buscaUsuario(char * nome, char usuarios[][100], int totalusuarios){
	int i;
	for(i=0;i<totalusuarios;i++){
		if(strcmp(usuarios[i],nome) == 0){
			return i; // retorna o número do usuário
		}
	}
	return -1; // retorna -1 se não encontrou
}
//--------------------------------------------------------------------------------------------------------
//-------------ALTERA USUÁRIOS----------------
// Procedimento para alterar usuários
// Funcionamento: pede o nome do usuário e chama o procedimento busca, se retornar o valor -1 vai repetir o loop e vai apresentar a mensagem de usuário não encotrado. Depois pede uma nova senha e confirma a senha, até que as senhas sejam 
// iguais.
void altUsuario(){
	char usuarios[20][100];
	char senhas[20][100];
	char nome[100], novaSenha[100],novaSenha2[100];
	int totalusuarios;
	int i;
	
	setlocale(LC_ALL,"Portuguese");
    descriptografar();
    //Faz a leitura do arquivo e adiciona a váriavel totalusuários a quantidade de registros no arquivo
    FILE * arquivo = fopen("Banco.txt", "r"); 
	if(arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
	}
	char linha[200];
	totalusuarios = 0;
	// o while continua enquanto o fgets(leitura do arquivo) lê as linhas não nulas do arquivo.
	// lê o arquivo e divide em duas partes com a função strtok separados por " + ", colocando o nome e senha nas váriaveis usuários e senhas e incrementa totalusuarios para contar o total de usuários. No final,
	// contém todos os nomes e senhas do arquivo.
	while(fgets(linha, sizeof(linha),arquivo) != NULL){ // O ponteiro char *token foi utilizado para dividir cada linha do arquivo. Ajuda a identificar uma parte de uma string, no caso " + "
		char *token = strtok(linha, " +\n");
		if(token != NULL){
			strcpy(usuarios[totalusuarios], token);
			token = strtok(NULL," +\n");
			if(token != NULL){
				strcpy(senhas[totalusuarios],token);
				(totalusuarios)++;
			}
		}
	}
	fclose(arquivo);
      
    //Para encontrar o usuário  
    do{
    	linhaCol(8,64);
    	printf("                          ");
    	printf("\n");
    	linhaCol(8,64);
    	printf("Digite o nome: ");
   	  	scanf("%s", nome);
    	Beep (329, 50);
    	i = buscaUsuario(nome,usuarios,totalusuarios);
    	if(i == -1){
    		printf("\n");
    		linhaCol(10,64); 
    		printf("Usuário não encontrado!");
		}
	} while (i == -1);
	
	//Para inserir uma nova senha
	do{
		linhaCol(10,64);
    	printf("                          ");
		printf("\n");
		linhaCol(10,64);
		printf("Nova Senha: ");
    	scanf(" %s", novaSenha);
    	Beep (329, 50);
    	linhaCol(12,64);
    	if (validaSenha(novaSenha)==0) {
    	    printf("Senha inválida, tente novamente!");
    	}
   	}while(validaSenha(novaSenha)==0);
   	
   	linhaCol(12,64);
    printf("                                 ");
    
    //Para confirmar a senha
    do{
    	printf("\n");
		linhaCol(12,64);
		printf("Repita a senha: ");
		scanf(" %s", novaSenha2);
		Beep (329, 50);
	} while (strcmp(novaSenha,novaSenha2) != 0);
	
	//Atualiza senha
	strcpy(senhas[i],novaSenha);
	printf("\n");
	linhaCol(14,64);
	printf("Senha alterada com sucesso!");
	linhaCol(16,64);
	printf("Pressione ENTER para sair");
	
	arquivo = fopen("Banco.txt", "w");
	for(i=0;i<totalusuarios;i++) {
		fprintf(arquivo, "%s + %s\n", usuarios[i], senhas[i]);
	}
	fclose(arquivo);
    criptografar();
}

//--------------------------------------------------------------------------------------------------------
//-------------LISTA USUÁRIOS----------------
// Procedimento que mostra os usuários
void listUsuario(){
	char nome[100], senha [100], stop;
	
	setlocale(LC_ALL,"Portuguese");
	descriptografar();
    FILE * filePointer;
	
    filePointer = fopen("Banco.txt", "r");
    int linha = 7, cont = 0;
    linhaCol(6,62);
    printf("USUÁRIO");
    linhaCol(6,75);
    printf("SENHA");


    
    while(fscanf(filePointer,"%s + %s", nome, senha) != EOF){
        linhaCol(linha,62);
    	printf("%s", nome);
    	linhaCol(linha,75);
    	printf("%s", senha);
    	linha++; 
        if(cont%9 == 0 && cont != 0 && cont < quant - 1) {  // se já mostrou 11 usuários e tem mais
            linhaCol(linha+1,66);
            printf("pressione algo para continuar");
            linhaCol(linha+2,62);
            scanf(" %c", &stop); // pede um input só para avançar
            Beep (329, 50);
            for (int i = 7; i <= 19; i++) { // limpa o quadrado
                linhaCol(i,62);
                printf("                                    ");  
            }
            linha = 7;
        }
        if (cont == quant - 1) {
            linhaCol(19,66);  // se acabou as linhas
            printf("pressione ENTER para continuar");
        }
        cont++;
	}
	
	fclose(filePointer);
	criptografar();	
}

//--------------------------------------------------------------------------------------------------------
//-------------EXCLUI USUÁRIOS----------------
// Procedimento que exclui usuários
void exUsuarios() {
    char esc, nomeUsu[50], senhas[50][100], usuarios[50][100];;
    int i, totalusuarios, cont;
	
	descriptografar();
	
    FILE * arquivo = fopen("Banco.txt", "r+"); 
	if(arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
	}
	char linhaPro[200];
	totalusuarios = 0;

    while(fgets(linhaPro, sizeof(linhaPro),arquivo) != NULL){  // Divide a linha em nome e senha
		char *token = strtok(linhaPro, " +\n");
		if(token != NULL){
			strcpy(usuarios[totalusuarios], token);
			token = strtok(NULL," +\n");
			if(token != NULL){
				strcpy(senhas[totalusuarios],token);
				(totalusuarios)++;
			}
		}
	}
	fclose(arquivo);

    linhaCol(8,64);
    printf("Digite o nome do usuario:");
    linhaCol(9,64);
    scanf("%s", nomeUsu);
    Beep (329, 50);
    i = buscaUsuario(nomeUsu,usuarios,totalusuarios); // vê se tem no arquivo
    if(i == -1){ // Se não tem esse usuário
    	printf("\n");
    	linhaCol(12,64); 
        Sleep(300); 
        Beep(1318.5, 100);
        Beep(880, 150);
    	printf("Usuário não encontrado!");
        linhaCol(19,66);
        printf("pressione ENTER para continuar");
	} else { // Se o usuário existe
        do {
            linhaCol(11,64); 
            printf("Tem certeza que deseja");
            linhaCol(12,64); 
            printf("excluir %s? (S/N)\n", nomeUsu);
            linhaCol(13,64); 
            scanf(" %c", &esc);
        } while (esc != 'S' && esc != 'N');
        Beep (329, 50);
    
        switch (esc) {
        case 'N':  // Se não vai mais excluir
            Sleep(200);
            linhaCol(16,64); 
            printf("Operação cancelada");
            linhaCol(19,66);
            printf("pressione ENTER para continuar");
            Beep(1318.5, 100);
            Beep(880, 150);
            break;
        case 'S':  // Se vai excluir
            Sleep(200);
            Beep(880, 100);
            Beep(1318.5, 150);

            FILE * temp = fopen("Temp.txt", "w"); // Abre o arquivo no modo W para apagar o conteúdo do arquivo

            if (arquivo == NULL) { // Se não conseguir achar nada, mostra erro
                printf("Erro ao abrir o arquivo");
            }
			
            for (cont = 0; cont < quant; cont++) {
                if(cont != i){
                	fprintf(temp,"%s + %s\n",usuarios[cont],senhas[cont]);
				}
            }

            fclose(temp);
            remove("Banco.txt");
            rename("Temp.txt","Banco.txt");
            
            quant--; // diminui a quantidade de usuários
            linhaCol(16,64); 
            printf("Usuário excluido!");
            linhaCol(19,66);
            printf("pressione ENTER para continuar");
            break;
        }
    }
    criptografar();
}
//--------------------------------------------------------------------------------------------------------
//-------------CRIPTOGRAFIA----------------
void criptografar() {
    FILE *arquivo = fopen("Banco.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    FILE *temp = fopen("Temp.txt", "w");
    if (temp == NULL) {
        printf("Erro ao criar o arquivo temporário.\n");
        fclose(arquivo);
        return;
    }

    char linha[100];
    char usuario[50], senha[50];

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        sscanf(linha, "%s + %s", usuario, senha);

        // Criptografa usuário e senha
        for (int i = 0; usuario[i] != '\0'; i++) {
            usuario[i] += 3;
        }
        for (int i = 0; senha[i] != '\0'; i++) {
            senha[i] += 3;
        }

        fprintf(temp, "%s + %s\n", usuario, senha);
    }

    fclose(arquivo);
    fclose(temp);

    remove("Banco.txt");
    rename("Temp.txt", "Banco.txt");
}
//--------------------------------------------------------------------------------------------------------
//-------------DESCRIPTOGRAFIA----------------
void descriptografar() {
    FILE *arquivo = fopen("Banco.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    FILE *temp = fopen("Temp.txt", "w");
    if (temp == NULL) {
        printf("Erro ao criar o arquivo temporário.\n");
        fclose(arquivo);
        return;
    }

    char linha[100];
    char usuario[50], senha[50];

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        sscanf(linha, "%s + %s", usuario, senha);

        // Descriptografa usuário e senha
        for (int i = 0; usuario[i] != '\0'; i++) {
            usuario[i] -= 3;
        }
        for (int i = 0; senha[i] != '\0'; i++) {
            senha[i] -= 3;
        }

        fprintf(temp, "%s + %s\n", usuario, senha);
    }

    fclose(arquivo);
    fclose(temp);

    remove("Banco.txt");
    rename("Temp.txt", "Banco.txt");
}

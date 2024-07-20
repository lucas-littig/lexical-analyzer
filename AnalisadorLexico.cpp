#include <iostream>
#include <fstream>
#include <string>

enum TokenType{
    NUMERO,
    COLC,
    CHAVES,
    OPER,
    PARE,
    VARI,
    END
};

struct Token {
    TokenType type;
};

/*--------------------------------------------------------------------------------------------------------------*/

class Lexer {
private:
    std::string input;
    std::size_t Posicao;
    char charAtual;

public:
    Lexer(const std::string& text) : input(text), Posicao(0), charAtual(input[0]) {}
    
    int pare = 0;
    int colc = 0;
    int chave = 0;
    int oper = 0;


    void leProximoCaractere() {
        Posicao++;
        if (Posicao < input.length()) {
            charAtual = input[Posicao];
        } else {
            charAtual = '\0';  // Marca o fim da entrada
        }
    }

    Token reconheceToken() {
        
        while (charAtual != '\0') {
            
            if (isspace(charAtual)) {
                leProximoCaractere();
                continue;
            }

            if (isdigit(charAtual)) {
                std::string numero;
                while (isdigit(charAtual)) {
                    numero.push_back(charAtual);
                    leProximoCaractere();
                }
                oper = 0;
                std::cout << "NUME" << std::endl;
                return {NUMERO};
            }


            if (isalpha(charAtual)) {
                std::string alfabeto;
                while (isalpha(charAtual)) {
                    alfabeto.push_back(charAtual);
                    leProximoCaractere();
                }
                oper = 0;
                std::cout << "VARI" << std::endl;
                return {VARI};
            }

            switch (charAtual) {
                case '(':
                    pare++;
                    std::cout << "PARE" << std::endl;
                    leProximoCaractere();
                    return {PARE};
                
                case ')':
                    
                    if(pare == 0){
                        std::cout << "Erro léxico encontrado: ')'\nEsperado '(' antes." << std::endl;
                        exit(1);
                    }else{
                        std::cout << "PARE" << std::endl;
                        pare--;
                        leProximoCaractere();
                        return {PARE};
                    }
                
                case '[':
                    colc++;
                    if(pare == 1 && colc == 1){
                        std::cout << "Erro léxico encontrado: '['\n'[]' não é permitido dentro de '()'." << std::endl;
                        exit(1);
                    }
                    leProximoCaractere();
                    std::cout << "COLC" << std::endl;
                    return {COLC};
                
                case ']':
                    if(pare == 1 && colc == 1){ //Caso em que [(], ou seja, parenteses ou colchentes sem fechar
                        std::cout << "Erro léxico encontrado: ']'\nEsperado ')'." << std::endl;
                        exit(1);
                    } 
                    if(colc == 0){
                        std::cout << "Erro léxico encontrado: ']'\nEsperado '[' antes." << std::endl;
                        exit(1);
                    }else{
                        std::cout << "COLC" << std::endl;    
                        colc--;
                        leProximoCaractere();
                        return {COLC};
                    }   

                case '{':
                    chave++;
                    if(colc == 1 && chave == 1){
                        std::cout << "Erro léxico encontrado: '{'\n'{}' nao é permitido dentro de '[].'" << std::endl;
                        exit(1);
                    }
                    if(pare == 1 && chave == 1){
                        std::cout << "Erro léxico encontrado: '{'\n'{}' nao é permitido dentro de '().'" << std::endl;
                        exit(1);
                    }
                    std::cout << "CHAVE" << std::endl;
                
                    leProximoCaractere();
                    return {CHAVES};
                
                case '}':
                    if(pare == 1 && chave == 1){ //Caso em que {(} ou {[}, ou seja, parenteses ou colchentes sem fechar
                        std::cout << "Erro léxico encontrado: '}'\nEsperado ')'." << std::endl;
                        exit(1);
                    } else if(colc == 1 && chave == 1){
                        std::cout << "Erro léxico encontrado: '}'\nEsperado ']'." << std::endl;
                        exit(1);
                    }

                    if(chave == 0){
                        std::cout << "Erro léxico encontrado: '}'\nEsperado '{' antes." << std::endl;
                        exit(1);
                    }else{
                        std::cout << "CHAVE" << std::endl;
                        chave--;
                        leProximoCaractere();
                        return {CHAVES};
                    }
                
                case '+':
                    
                    if(oper == 1){
                        std::cout << "Erro léxico encontrado: '+'\nEra(m) esperado(s) '0123456789abcdefghijklmnopqrstuvwxyz'." << std::endl;
                        exit(1);
                    }
                    oper = 1;
                    std::cout << "OPER" << std::endl;
                    leProximoCaractere();
                    return {OPER};
                
                case '/':
                    
                    if(oper == 1){
                        std::cout << "Erro léxico encontrado: '/'\nEra(m) esperado(s) '0123456789abcdefghijklmnopqrstuvwxyz'." << std::endl;
                        exit(1);
                    }
                    oper = 1;
                    std::cout << "OPER" << std::endl;
                    leProximoCaractere();
                    return {OPER};
                
                case '*':
                    
                    if(oper == 1){
                        std::cout << "Erro léxico encontrado: '*'\nEra(m) esperado(s) '0123456789abcdefghijklmnopqrstuvwxyz'." << std::endl;
                        exit(1);
                    }
                    oper = 1;
                    std::cout << "OPER" << std::endl;
                    leProximoCaractere();
                    return {OPER};
                
                case '-':

                    if(oper == 1){
                        std::cout << "Erro léxico encontrado: '-'\nEra(m) esperado(s) '0123456789abcdefghijklmnopqrstuvwxyz'." << std::endl;
                        exit(1);
                    }
                    oper = 1;
                    std::cout << "OPER" << std::endl;
                    leProximoCaractere();
                    return {OPER};
                default:
                    std::cerr << "Erro léxico encontrado: " << charAtual << "\nCaractere inválido." << std::endl;
                    exit(1);
            }
        }
        if(colc != 0){
            std::cout << "Erro léxico encontrado: Era(m) esperado(s) ']'" << std::endl;
        }
        if(pare != 0){
            std::cout << "Erro léxico encontrado: Era(m) esperado(s) ')'" << std::endl;
        }
        if(chave != 0){
            std::cout << "Erro léxico encontrado: Era(m) esperado(s) '}'" << std::endl;
        }
        if(oper == 1){
            std::cout << "Erro léxico encontrado: '""'\nEra(m) esperado(s) '0123456789abcdefghijklmnopqrstuvwxyz'." << std::endl;
        }

        return {END};
    }
};

/*--------------------------------------------------------------------------------------------------------------*/

int main() {
    std::string nomeArquivo = "arquivoTeste.txt";
    std::ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo!" << nomeArquivo << std::endl;
        return 1;
    }

    std::string conteudoArquivo;
    std::string linha;
    while (std::getline(arquivo, linha)) {
        conteudoArquivo += linha + "\n";
    }

    arquivo.close();

    Lexer lexer(conteudoArquivo);

    Token token = lexer.reconheceToken();
    while (token.type != END) {
        token = lexer.reconheceToken();
    }

    std::cout << "Analise lexica realizada com sucesso no arquivo entrada.txt" << std::endl;


    return 0;
}
 
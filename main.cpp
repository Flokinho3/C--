#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Fonte
{
    Font font;
    Text text;
public:
    // Construtor da classe Fonte
    Fonte(string fontName, string textString, int textSize, Color textColor, Vector2f textPosition)
    {
        // Tenta carregar a fonte e exibe uma mensagem de erro se falhar
        if (!font.loadFromFile(fontName))
        {
            cout << "Erro ao carregar a fonte " << fontName << endl;
            exit(1);
        }
        
        text.setFont(font);
        text.setString(textString);
        text.setCharacterSize(textSize);
        text.setFillColor(textColor);
        text.setPosition(textPosition);
    }

    // Método para desenhar o texto na janela
    void draw(RenderWindow &window)
    {
        window.draw(text);
    }
};

class Botao
{
    RectangleShape botao;
    Text texto;
    Fonte fonte;
public:
    // Construtor da classe Botao
    Botao(Vector2f tamanho, Vector2f posicao, string textoString, int textoTamanho, Color botaoCor, Color textoCor)
        : fonte("Fontes/daydream_3/Daydream.ttf", textoString, textoTamanho, textoCor, posicao)
    {
        botao.setSize(tamanho);
        botao.setPosition(posicao);
        botao.setFillColor(botaoCor);
    }

    // Método para desenhar o botão na janela
    void draw(RenderWindow &window)
    {
        window.draw(botao);
        fonte.draw(window);
    }

    // Método para verificar se o botão foi clicado
    bool isClicked(Vector2f mousePosition)
    {
        if (botao.getGlobalBounds().contains(mousePosition))
            return true;
        return false;
    }
};

int main() {
    // Cria uma janela de 800x600
    RenderWindow window(VideoMode(800, 600), "Game");

    // Botoes
    Botao botao1(Vector2f(200, 50), Vector2f(300, 200), "Botao 1", 30, Color::Green, Color::White);
    Botao botao2(Vector2f(200, 50), Vector2f(300, 300), "Botao 2", 30, Color::Red, Color::White);

    // Loop principal
    while (window.isOpen()) {
        // Evento de fechamento da janela
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    Vector2f mousePosition = window.mapPixelToCoords(Mouse::getPosition(window));
                    if (botao1.isClicked(mousePosition))
                        cout << "Botao 1 clicado" << endl;
                    if (botao2.isClicked(mousePosition))
                        cout << "Botao 2 clicado" << endl;
                }
            }
        }

        // Limpa a janela
        window.clear();
        
        // desenha os botões
        botao1.draw(window);
        botao2.draw(window);
        // Exibe o conteúdo da janela
        window.display();
    }

    return 0;
}

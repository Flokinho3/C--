#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Fonte
{
    Font font;
    Text text;
public:
    Fonte(string fontName, string textString, int textSize, Color textColor, Vector2f textPosition)
    {
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
    Color corOriginal;
    Color corHover;
    Color corClique;
public:
    Botao(Vector2f tamanho, Vector2f posicao, string textoString, int textoTamanho, Color corBotao, Color corTexto)
        : fonte("Fontes/daydream_3/Daydream.ttf", textoString, textoTamanho, corTexto, posicao)
    {
        botao.setSize(tamanho);
        botao.setPosition(posicao);
        corOriginal = corBotao;
        corHover = corBotao + Color(50, 50, 50); // um tom mais claro para o hover
        corClique = corBotao - Color(50, 50, 50); // um tom mais escuro para o clique
        botao.setFillColor(corOriginal);
    }

    void draw(RenderWindow &window)
    {
        window.draw(botao);
        fonte.draw(window);
    }

    bool isClicked(Vector2f mousePosition)
    {
        return botao.getGlobalBounds().contains(mousePosition);
    }

    void updateHover(Vector2f mousePosition)
    {
        if (botao.getGlobalBounds().contains(mousePosition))
        {
            botao.setFillColor(corHover);  // Cor do botão no hover
        }
        else
        {
            botao.setFillColor(corOriginal);  // Cor original
        }
    }

    void updateClick(Vector2f mousePosition, bool mousePressed)
    {
        if (mousePressed && botao.getGlobalBounds().contains(mousePosition))
        {
            botao.setFillColor(corClique); // Cor do botão quando clicado
        }
    }
};

int main() {
    // Cria uma janela de 800x600
    RenderWindow window(VideoMode(800, 600), "Game");

    // Botoes
    Botao botao1(Vector2f(200, 50), Vector2f(300, 200), "Botao 1", 30, Color::Green, Color::White);
    Botao botao2(Vector2f(200, 50), Vector2f(300, 300), "Botao 2", 30, Color::Red, Color::White);

    bool mousePressed = false;
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
                    mousePressed = true;  // Registra que o mouse foi pressionado
                }
            }
            else if (event.type == Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    mousePressed = false;  // Reseta o estado de "clicado"
                }
            }
        }

        // Pega a posição do mouse
        Vector2f mousePosition = window.mapPixelToCoords(Mouse::getPosition(window));

        // Atualiza o estado de hover e clique dos botões
        botao1.updateHover(mousePosition);
        botao2.updateHover(mousePosition);

        botao1.updateClick(mousePosition, mousePressed);
        botao2.updateClick(mousePosition, mousePressed);

        // Limpa a janela
        window.clear();
        
        // Desenha os botões
        botao1.draw(window);
        botao2.draw(window);

        // Exibe o conteúdo da janela
        window.display();
    }

    return 0;
}

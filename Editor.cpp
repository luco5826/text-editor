#include <SFML/Graphics.hpp>
#include "InputController.h"
#include "TextDocument.h"
#include "TextView.h"

int main(int argc, char* argv[]) {
#ifdef __linux__
    std::string workingDirectory = argv[0];
    workingDirectory = workingDirectory.substr(0, workingDirectory.find_last_of("/") + 1);
#elif defined _WIN32 || _WIN64
    std::string workingDirectory = "";
#endif

    std::string saveFileName;
    std::string loadFileName;

    if (argc == 2) {
        saveFileName = workingDirectory + argv[1];
        loadFileName = workingDirectory + argv[1];
    } else {
        saveFileName = workingDirectory + "txt/textoDePruebaGuardado.txt";
        loadFileName = workingDirectory + "txt/textoDePruebaGuardado.txt";
    }

    sf::RenderWindow window(sf::VideoMode(720, 405), "Jonno-text");
    window.setVerticalSyncEnabled(true);
    sf::Color backgroundColor = sf::Color(21, 29, 45);

    TextView textView(window, workingDirectory);
    TextDocument document;
    InputController inputController;

    document.init(loadFileName);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::Resized) {
                textView.setCameraBounds(event.size.width, event.size.height);
            }

            if (event.key.code == sf::Keyboard::S && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                if (document.hasChanged()) {
                    document.saveFile(saveFileName);
                    std::cout << "SAVED TO: " << saveFileName << "\n";
                }
            }

            inputController.handleEvents(document, textView, window, event);
        }

        inputController.handleConstantInput(document, textView, window);

        window.clear(backgroundColor);
        window.setView(textView.getCameraView());
        textView.draw(window, document);
        window.display();
    }

    return 0;
}

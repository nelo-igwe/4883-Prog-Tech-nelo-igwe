#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>

int main() {
    // Create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Enter Name Example");
    window.setFramerateLimit(60);

    // Load font
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        // Handle error
        return -1;
    }

    // Text objects for instructions and name display
    sf::Text instructionText("Enter your name:", font, 24);
    instructionText.setPosition(50, 200);
    instructionText.setFillColor(sf::Color::White);

    sf::Text nameText("", font, 24);
    nameText.setPosition(50, 250);
    nameText.setFillColor(sf::Color::Green);

    sf::Text displayName("", font, 30);
    displayName.setPosition(50, 50);
    displayName.setFillColor(sf::Color::Yellow);

    // Variables for input handling
    std::string userInput;
    bool nameEntered = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (!nameEntered) {
                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode == '\b') {
                        // Handle backspace
                        if (!userInput.empty()) {
                            userInput.pop_back();
                        }
                    } else if (event.text.unicode == '\r') {
                        // Handle enter
                        nameEntered = true;
                        displayName.setString("Hello, " + userInput + "!");
                    } else if (event.text.unicode < 128) {
                        // Handle valid characters
                        userInput += static_cast<char>(event.text.unicode);
                    }

                    nameText.setString(userInput);
                }
            }
        }

        // Clear the window
        window.clear(sf::Color::Black);

        // Draw the appropriate text
        if (!nameEntered) {
            window.draw(instructionText);
            window.draw(nameText);
        } else {
            window.draw(displayName);
        }

        // Display everything
        window.display();
    }

    return 0;
}

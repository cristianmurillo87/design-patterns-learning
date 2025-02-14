
/**
 * This is an example of the Builder pattern
 * The Builder Pattern is a design pattern used to construct complex objects step by step. 
 * It allows for more readable and maintainable code by separating the construction of an 
 * object from its representation.
 * 
 * Benefits of the Builder Pattern
 * Readability: The code is more readable and expressive, clearly showing the steps to construct
 * the object.
 * Maintainability: Changes to the construction process are localized within the builder,
 * making the code easier to maintain.
 * Flexibility: The builder can provide various methods to customize the construction process, 
 * allowing for different configurations of the object.
 * 
 */

#include <string>
#include <vector>
#include <sstream>
#include <iostream>

struct HTMLElement {
    std::string name;
    std::string text;
    std::vector<HTMLElement> elements;

    private:
        const size_t indent_size = 2;

    public:
        HTMLElement() {}

        HTMLElement(std::string &name, std::string &text): name(name), text(text) {}

        std::string str(int indent = 0) const {
            std::ostringstream oss;
            std::string i(indent_size * indent, ' ');

            oss << i << "<" << name << ">" << std::endl;
            if (text.size() > 0) {
                oss << std::string(indent_size * (indent + 1), ' ') << text << std::endl;
            }

            for(const auto& e: elements) {
                oss << e.str(indent + 1);
            }

            oss << i << "</" << name << ">" << std::endl;
            return oss.str();
        }

        static HTMLElementBuilder build(std::string root_name) {
            return HTMLElementBuilder{root_name};
        }

};

struct HTMLElementBuilder {
    private:
        HTMLElement root;

    public:
        HTMLElementBuilder(std::string root_name) {
            root.name = root_name;
        }

        HTMLElementBuilder& add_child(std::string child_name, std::string child_text) {
            HTMLElement e{child_name, child_text};
            root.elements.emplace_back(e);
        }

        std::string str() const {
            return root.str();
        }

        operator HTMLElement() const {
            return root;
        }
};


int main() {
    auto text = "hello";
    std::string output;
    output += "<p>";
    output += text;
    output += "</p>";

    std::cout << output << std::endl;

    std::string words[] = {"hello", "world"};
    std::ostringstream oss;
    oss << "<ul>";
    for (auto w: words) {
        oss << "<li>" << w << "</li>";
    }
    oss << "</ul>";
    std::cout << oss.str() << std::endl;

    // HTMLElement is not created directly, but created using HTMLElementBuilder
    // This is an example of the Builder pattern
    HTMLElementBuilder builder{"ul"};
    builder.add_child("li", "hello").add_child("li", "world");
    std::cout << builder.str() << std::endl;

    HTMLElement builder2 = HTMLElement::build("ul").add_child("li", "hello").add_child("li", "world");

    return 0;
}
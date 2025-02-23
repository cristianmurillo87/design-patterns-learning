/*
 * Strategy Design Pattern
 *
 * The Strategy pattern defines a family of algorithms, encapsulates each one, and makes them interchangeable.
 * It allows the algorithm to vary independently from clients that use it.
 * In this example, the TextProcessor class uses different strategies (MarkdownListStrategy, HtmlListStrategy)
 * to format a list of items in different ways.
 */

#include <sstream>
#include <string>
#include <memory>
#include <vector>
#include <iostream>

enum class OutputFormat
{
    MARKDOWN,
    HTML
};

struct ListStrategy
{
    virtual void start(std::ostringstream& oss) = 0;
    virtual void add_list_item(std::ostringstream& oss, const std::string& item) = 0;
    virtual void end(std::ostringstream& oss) = 0;
};

struct MarkdownListStrategy: ListStrategy
{
    void start(std::ostringstream& oss) override
    {
    }

    void add_list_item(std::ostringstream& oss, const std::string& item) override
    {
        oss << " * " << item << std::endl;
    }

    void end(std::ostringstream& oss) override
    {
    }
};

struct HtmlListStrategy: ListStrategy
{
    void start(std::ostringstream& oss) override
    {
        oss << "<ul>" << std::endl;
    }

    void add_list_item(std::ostringstream& oss, const std::string& item) override
    {
        oss << "  <li>" << item << "</li>" << std::endl;
    }

    void end(std::ostringstream& oss) override
    {
        oss << "</ul>" << std::endl;
    }
};



struct TextProcessor
{
    void clear()
    {
        oss.str("");
        oss.clear();
    }

    void append_list(const std::vector<std::string>& items)
    {
        list_strategy->start(oss);
        for (auto& item: items)
        {
            list_strategy->add_list_item(oss, item);
        }
        list_strategy->end(oss);
    }

    void set_output_format(const OutputFormat format)
    {
        switch (format)
        {
            case OutputFormat::MARKDOWN:
                list_strategy = std::make_unique<MarkdownListStrategy>();
                break;
            case OutputFormat::HTML:
                list_strategy = std::make_unique<HtmlListStrategy>();
                break;
        }
    }

    std::string str() const
    {
        return oss.str();
    }

private:
    std::unique_ptr<ListStrategy> list_strategy;
    std::ostringstream oss;
};

int main()
{
    std::vector<std::string> items{"foo", "bar", "baz"};

    TextProcessor tp;
    tp.set_output_format(OutputFormat::MARKDOWN);
    tp.append_list(items);
    std::cout << tp.str() << std::endl;

    tp.clear();
    tp.set_output_format(OutputFormat::HTML);
    tp.append_list(items);
    std::cout << tp.str() << std::endl;

    return 0;
}
#pragma once

#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <variant>
#include <vector>

namespace Json {

    class Node;

    using Array = std::vector<Node>;
    using Dict = std::map<std::string, Node>;

    class Node : std::variant<Array, Dict, bool, int, double, std::string> {
    public:
        using variant::variant;

        const variant& GetBase() const {
            return *this;
        }

        bool IsArray() const;

        const auto& AsArray() const;

        bool IsMap() const;

        const auto& AsMap() const;

        bool IsBool() const;

        bool AsBool() const;

        bool IsInt() const;

        int AsInt() const;

        bool IsPureDouble() const;

        bool IsDouble() const;

        double AsDouble() const;

        bool IsString() const;

        const auto& AsString() const;
    };

    class Document {
    public:
        explicit Document(Node root) : root(move(root)) {}

        const Node& GetRoot() const;

    private:
        Node root;
    };

    Node LoadNode(std::istream& input);

    Document Load(std::istream& input);

    void PrintNode(const Node& node, std::ostream& output);

    template<typename Value>
    void PrintValue(const Value& value, std::ostream& output) {
        output << value;
    }

    template<>
    void PrintValue<std::string>(const std::string& value, std::ostream& output);

    template<>
    void PrintValue<bool>(const bool& value, std::ostream& output);

    template<>
    void PrintValue<Array>(const Array& nodes, std::ostream& output);

    template<>
    void PrintValue<Dict>(const Dict& dict, std::ostream& output);

    void Print(const Document& document, std::ostream& output);

}


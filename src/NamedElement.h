/**
 * Abstract base class for named elements with descriptions.
 */
#include <string>


class NamedElement{
    public:
        virtual std::string name() = 0;
        virtual std::string name(std::string name) = 0;
        virtual std::string description() = 0;
        virtual std::string description(std::string description) = 0;
}

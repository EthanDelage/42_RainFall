#include <string.h>
#include <unistd.h>

class N
{
public:
    int n;
    int (N::*function)(N &);
    char annotation[100];

    N(int value): n(value)
    {
        this->function = &N::operator+;
    }

    int operator+(N &rhs)
    {
        return this->n + rhs.n;
    }

    int operator-(N &rhs)
    {
        return this->n - rhs.n;
    }

    void setAnnotation(char *str)
    {
        memcpy(this->annotation, str, strlen(str));
    }
};

void main(int argc, char **argv)
{
    if (argc < 2)
    {
        _exit(1);
    }

    N *first = new N(5);
    N *second = new N(6);

    first->setAnnotation(argv[1]);
    return second->*(second->function);
}

#ifndef SS_NOCOPYABLE_H
#define SS_NOCOPYABLE_H


class nocopyable
{
public:
    nocopyable(const nocopyable&) = delete;
    void operator=(const nocopyable&) = delete;
protected:
    nocopyable() = default;
    ~nocopyable() =default;
};

#endif //SS_NOCOPYABLE_H

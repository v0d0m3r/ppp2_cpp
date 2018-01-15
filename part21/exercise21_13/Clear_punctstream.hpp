//------------------------------------------------------------------------------

#ifndef CLEAR_PUNCTSTREAM_HPP
#define CLEAR_PUNCTSTREAM_HPP

//------------------------------------------------------------------------------

#include "../../part11/exercise11_8/src/punctstream.hpp"

//------------------------------------------------------------------------------

class Clear_punctstream : public Punct_stream
{
public:
    Clear_punctstream(istream& is)
        : Punct_stream{is}, plural{false} {}

    bool is_plural() const { return plural; }
    void set_plural(bool p) { plural = p; }

protected:
    void analyzer_ch(char& ch, char prev, char next) override
    {
        Punct_stream::analyzer_ch(ch, prev, next);
        if (plural && ch == 's'
                   && isalpha(prev)
                   && !isalpha(next))
            ch = ' ';
    }

private:
    bool plural;
};

//------------------------------------------------------------------------------

void end_of_loop(istream& ist, char term, const string& message);
void init_word_replace(const string& path, vector<Word_replace>& wr_tb);

//------------------------------------------------------------------------------

struct Sum_pair {
    int operator()(int v, const pair<string, int>& p)
        { return v + p.second; }
};

//------------------------------------------------------------------------------

template<typename A, typename B>
std::ostream& operator<<(std::ostream& os, const std::pair<A, B>& p)
{
    return os << '(' << p.first << ',' << p.second << ')';
}

//------------------------------------------------------------------------------

template<typename A, typename B>
std::ostream& operator<<(std::ostream& os, const map<A, B>& m)
{
    for (const auto& p : m) os << p << '\n';
    return os;
}

//------------------------------------------------------------------------------

#endif // CLEAR_PUNCTSTREAM_HPP

//------------------------------------------------------------------------------

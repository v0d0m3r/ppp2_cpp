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
        cout << "bla\n";
    }

private:
    bool plural;
};

//------------------------------------------------------------------------------

#endif // CLEAR_PUNCTSTREAM_HPP

//------------------------------------------------------------------------------

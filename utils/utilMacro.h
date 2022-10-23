#ifndef UTILMACRO_H
#define UTILMACRO_H

#define deleteIfReq(VAR)   \
    do {                   \
        if (VAR) {         \
            delete VAR;    \
            VAR = nullptr; \
        }                  \
    } while (0)

#define s_cast(TYPE, VALUE) static_cast<TYPE>(VALUE)
#define sc(TYPE, VALUE) static_cast<TYPE>(VALUE)
#define i_sc(VALUE) s_cast(int, VALUE)

#endif // UTILMACRO_H

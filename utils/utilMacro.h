#ifndef UTILMACRO_H
#define UTILMACRO_H

#define deleteIfReq(var)      \
    do {                   \
        if (var) {         \
            delete var;    \
            var = nullptr; \
        }                  \
    } while (0)

#endif // UTILMACRO_H

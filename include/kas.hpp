#ifndef KAS_HPP
#define KAS_HPP

struct Kas {
    long long saldo;
};

void muatDataKas(Kas* dataKas);
void simpanDataKas(const Kas* dataKas);

void cekSaldoKas(const Kas* dataKas);
void setorKas(Kas* dataKas);
void tarikKas(Kas* dataKas);
void tampilkanMenuKas(Kas* dataKas);

#endif
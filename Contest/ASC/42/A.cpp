#include <bits/stdc++.h>
using namespace std;

const int kN = 60 + 1;
string M[kN];

void Init() {
    M[1] = "1";
    M[2] = "2";
    M[3] = "5";
    M[4] = "14";
    M[5] = "42";
    M[6] = "138";
    M[7] = "466";
    M[8] = "1643";
    M[9] = "5919";
    M[10] = "21773";
    M[11] = "81279";
    M[12] = "307483";
    M[13] = "1175352";
    M[14] = "4534161";
    M[15] = "17626999";
    M[16] = "68992703";
    M[17] = "271641249";
    M[18] = "1075144364";
    M[19] = "4275274867";
    M[20] = "17071822275";
    M[21] = "68428152475";
    M[22] = "275217386092";
    M[23] = "1110375948303";
    M[24] = "4492641333003";
    M[25] = "18225081419544";
    M[26] = "74111194585752";
    M[27] = "302040709982249";
    M[28] = "1233513516920479";
    M[29] = "5047263602889870";
    M[30] = "20689263708206573";
    M[31] = "84949334206262879";
    M[32] = "349345074001746274";
    M[33] = "1438755674118223856";
    M[34] = "5933611424928724406";
    M[35] = "24502813518836240704";
    M[36] = "101308463872246981055";
    M[37] = "419352443456504201780";
    M[38] = "1737758382926884884787";
    M[39] = "7208610642710276963227";
    M[40] = "29932486157601312392705";
    M[41] = "124406147339354530823897";
    M[42] = "517522266914506588894582";
    M[43] = "2154696473102580710799557";
    M[44] = "8978338946984442473044370";
    M[45] = "37440604550209960816974236";
    M[46] = "156247055325309065584865137";
    M[47] = "652512886745843915042952541";
    M[48] = "2726852306372243993817739104";
    M[49] = "11402950058165311623596656239";
    M[50] = "47713850303960103939512934658";
    M[51] = "199771059598912947309106077359";
    M[52] = "836895844267519676318141873908";
    M[53] = "3507934041460718229215661754441";
    M[54] = "14711724149656097157973854970216";
    M[55] = "61730436584136777094319110947650";
    M[56] = "259149682271648444386724836737230";
    M[57] = "1088453635022058817785364441981187";
    M[58] = "4573723135955209534732522596303384";
    M[59] = "19227535766791938363842495481717085";
    M[60] = "80865762092285659541857627575454392";

}

int main() {
#ifdef ONLINE_JUDGE
    freopen("abstract.in", "r", stdin);
    freopen("abstract.out", "w", stdout);
#endif
    Init();
    int n, tc = 0;
    while (cin >> n) {
        if (n == 0) break;
        cout << "Case " << (++tc) << ": " << M[n] << endl;
    }
    return 0;
}

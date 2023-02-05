#include <iostream>
#include <fstream>

using namespace std;

/*
Jekabs Vanags

Uzdevums: Jaunais tīmekļa ziņu portāls „Mini Comments” savām ziņām ir ieviesis inovatīvu rakstu komentēšanas principu. Lasītājiem atļauts par ziņu komentāros atstāt tikai vienu vārdu, kas izsaka viņu attieksmi pret rakstu.

Sistēmas administrators no sistēmas var saņemt pārskatu par rakstiem un tiem izteiktajiem komentāriem. Diemžēl izstrādātāji paspējuši realizēt tikai ļoti primitīvu pārskatu, kas satur visu rakstu identifikatorus un visus komentārus to reģistrēšanas secībā. Administrators vēlas redzēt komentārus sagrupētus pie katra raksta, kur sākumā ir svaigākie komentāri, t.i., pretēji to reģistrēšanas secībai.

Jūsu uzdevums ir uzrakstīt programmu, kas administratoram pieejamo pārskatu pārveido viņam vēlamajā formātā.

Ieejā ir fails, kas satur rakstu skaitu, rakstu identifikatorus ar to nosaukumiem pēdiņās un visus komentārus (raksta identifikators un komentārs par šo rakstu).

Ieejas dati ir korekti saskaņā ar ieejas datu formātu un dotajiem ierobežojumiem.

04.05.2022.
*/

//Izveidojam staku kur glabat komentarus
class commentStack{

//Izveidojam objektu komentars kurs norada uz nakamo komentaru
private:
    struct comment
    {
        comment *prev = NULL;
        char value[30] = "";
    };
    comment *last = NULL;


public:

    //Inicializejam komentaru staku un izdzesam jebko kas palicis atmina
    ~commentStack()
    {
        comment *curelem = last;
        while(curelem != NULL)
            {
                last = curelem->prev;
                delete(curelem);
                curelem = last;
            }
    };

    //Funkcija lai varetu pievienot komentaru stakam, ka ari parbaudam lai tas ir tikai teksta vertibas
    void pushComment(char* val)
    {
        comment *curelem = new comment;
        int i = 0;
        while(val[i] != '\0')
            {
                if((val[i]>='a' && val[i]<='z') || (val[i]>='A' && val[i]<='Z'))curelem->value[i] = val[i];
                i++;
            }
        curelem->value[i] = '\0';

        //Pointeri nakamajam elementam un vai sis ir pedejais
        if(last == NULL)
            {
                last = curelem;
                curelem->prev = NULL;
            }
        else
            {
                curelem->prev = last;
                last = curelem;
            }
    }

    //Funkcija kas atgriez visus komentarus preteja seciba
    void popAll()
    {
        comment *curelem = last;
        if(curelem == NULL) cout<<'-';
        while(curelem != NULL)
            {
                cout<<curelem->value<<' ';
                last = curelem->prev;
                delete(curelem);
                curelem = last;
            }
    }
};

//Objekts article, kas satur komentarus kas asocieti ar so article
struct article
{
    char name[200];
    int id = 0;
    commentStack comments;
};

//Funkcija lai nonemtu pedinas no teksta
void printNoQuote(char* text)
{
    int i = 1;
    while(text[i]!='"')
        {
            cout<<text[i];
            i++;
        }
    cout<<endl;
}


int main()
{
    //Noradam alternativu ievades un izvades vietu
    freopen("articles.i6", "r", stdin);
    freopen("articles.out", "w", stdout);

    int articleNum = 0;
    int lowestArticle;

    //Nolasam katru article
    scanf("%d",&articleNum);
    cin.get();
    article articleList[articleNum];

    //Atrodam article ar mazako kartas numuru ka ari piepildam stream ar datiem par article
    for(int i = 0; i<articleNum; i++)
        {
             scanf("%d",&articleList[i].id);
             if(articleList[i].id < lowestArticle || lowestArticle == NULL) lowestArticle = articleList[i].id;
             cin.get();
             cin.getline(articleList[i].name,200);
        }

    //Nolasam komentarus un piesaistam tos atbilstosajam article
    while(cin)
        {
            int dataid;
            char comment[30];
            scanf("%d",&dataid);
            cin.get();
            cin.getline(comment,30);
            if(cin.eof())break;

            for(int i = 0; i<articleNum; i++)
            {
             if(articleList[i].id == dataid)
                {
                    dataid = i;
                    break;
                }
            }

            //Ievadam komentarus staka kas asociets ar konkreto article
            articleList[dataid].comments.pushComment(comment);
        }

        int printedout = 0;
        //Izvadam datus sakot ar zemako article numuru atrdarbibas nodrosinasani
        for(int i = lowestArticle; i<1000; i++)
        {
            for(int j = 0; j<articleNum;j++)
                {
                    if(articleList[j].id == i)
                        {
                            printNoQuote(articleList[j].name);
                            articleList[j].comments.popAll();
                            printedout += 1;
                            cout<<endl;
                            cout<<endl;
                            break;
                        }
                }
            //Beidzam loop ja zinam ka visi articles jau ir izvaditi
            if(printedout >= articleNum) break;
        }
}

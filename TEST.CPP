    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <iostream>
    #include <cstdlib>
    #include <fstream>
    #include <dirent.h>
    #include <vector>
    using namespace std;
    #define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])
    #define ALPHABET_SIZE (26)
    // Converts key current character into index
    // use only 'a' through 'z' and lower case
    #define CHAR_TO_INDEX(c) ((int)c - (int)'a')
    // trie node
    typedef struct trie_node trie_node_t;
    struct trie_node
    {
    int value;
    trie_node_t *children[ALPHABET_SIZE];
    };
    // trie ADT
    typedef struct trie trie_t;
    struct trie
    {
    trie_node_t *root;
    int count;
    //int occ[4];
    };
     trie_t trie;
    // Returns new trie node (initialized to NULLs)
    class search_word
    {
    public:
    trie_node_t *getNode(void)
    {
        trie_node_t *pNode = NULL;
        pNode = (trie_node_t *)malloc(sizeof(trie_node_t));

        if( pNode )
        {
        int i;

        pNode->value = 0;

        for(i = 0; i < ALPHABET_SIZE; i++)
        {
        pNode->children[i] = NULL;
        }
        }

        return pNode;
    }
    // Initializes trie (root is dummy node)
    void initialize(trie_t *pTrie)
    {
    pTrie->root = getNode();
    pTrie->count = 0;
    }

    // If not present, inserts key into trie
    // If the key is prefix of trie node, just marks leaf node
    void insert(trie_t *pTrie, char key[],int fileid)
    {
        cout<<"\n inserting word"<<key;
        int level;
        int length = strlen(key);
        int index;
        trie_node_t *trav;

        pTrie->count++;
        cout<<"  ::  count " <<pTrie->count;
        trav = pTrie->root;

        for( level = 0; level < length; level++ )
        {
        index = CHAR_TO_INDEX(key[level]);
        if( !trav->children[index] )
        {
        trav->children[index] = getNode();
        }

        trav = trav->children[index];
        }
         cout<<"\n value "<<trav->value;
        // mark last node as leaf
        trav->value = pTrie->count;

    }
    // Returns non zero, if key presents in trie
    int search(trie_t *pTrie, char key[])
    {
    int level;
    int length = strlen(key);
    int index;
    trie_node_t *trav;

    trav = pTrie->root;

    for( level = 0; level < length; level++ )
    {
    index = CHAR_TO_INDEX(key[level]);

    if( !trav->children[index] )
    {
        return 0;
    }

    trav = trav->children[index];
    }

    //return (0 != trav && trav->value);
    if(trav->value) return 1;
    else return 0;
    }
    void index()
    {

        //char word[30];
        int i,j,k;
        ifstream infile;
        //infile.open("ff.txt");
        std::vector<string> v;


        //char output[][32] = {"Not present in trie", "Present in trie"};

        initialize(&trie);

        // Construct trie

        DIR *dpdf;
    struct dirent *epdf;

    dpdf = opendir("./toindex");
    if (dpdf != NULL){
       while (epdf = readdir(dpdf)){

        if(!strcmp(epdf->d_name,".") || !strcmp(epdf->d_name,"..")  )
        {
            //cout<<"\n skipping . and  .. in ubuntu listing";
            continue;
        }
          v.push_back(epdf->d_name);

          cout<<"\n Indexed Filename "<<v.size()<<":"<<epdf->d_name;
          // std::out << epdf->d_name << std::endl;
       }
}
/*
    for(i=0;i<51;i++)
    {
        for(j=0;j<3;j++)
        {
        ht[i].count[j]=-1;
        ht[i].id[j]=-1;
        }
        ht[i].alpha[0]='\0';
    }

    */
    for(k=0;k<3;k++)
    {
        //infile.open(v[k].c_str());
        //infile.open(v[k]);
        if(k==0)
        infile.open("ff.txt");
         if(k==1)
        infile.open("hh.txt");
         if(k==2)
        infile.open("gg.txt");

    cout<<"\n now indexing ... "<<k;
        //infile.open();
    char word[30];
    int count = 0;
    while(!infile.eof())
    {
        infile>>word;
        //j=hash(word,51);
        cout<<"\n word is "<<word;
        insert(&trie,word,k);
/*

        if(ht[j].count[k]==-1)
        {
            ht[j].id[k]=k+1;
            ht[j].count[k]++;
            strcpy(ht[j].alpha,word);
        }
        else
        {
            if(strcmp(word,ht[j].alpha)==0)
            ht[j].count[k]++;
            else
            cout<<"collision"<<endl;

        }
        */
    }
    infile.close();
    }
}

void search_for()
{
    char w[20];
    char choice[30];
    do
    {
    cout<<"\n enter search query"<<endl;
    cin>>w;
    //int i;
    //int j=hash(w,51);
    if(search(&trie,w))
     cout<<"\n found";
    else
    cout<<"element not found"<<endl;
    cout<<"\n\n type bye to exit or any other string to continue";
    cin>>choice;
    }while(strcmp(choice,"bye"));

}
};
int main()
   {
        search_word a;
        a.index();
        a.search_for();
        return 0;
    }

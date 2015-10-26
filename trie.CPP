    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <iostream>
    #include <cstdlib>
    #include <fstream>
    #include <dirent.h>
    #include <vector>
    #include <bits/stdc++.h>
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
        list <int>fid;
    };

    // trie ADT

    // Returns new trie node (initialized to NULLs)
    class search_word
    {

    trie_node_t *root;
    int count;
    std::vector<string> v;

    public:


    trie_node_t *getNode(void)
    {
        trie_node_t *pNode = NULL;
        pNode = new trie_node_t;

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
    search_word()
    {
        root = getNode();
        count = 0;
    }

    // If not present, inserts key into trie
    // If the key is prefix of trie node, just marks leaf node
    void insert(char key[],int fileid)
    {
        cout<<"\n inserting word"<<key;
        int level;
        int length = strlen(key);
        int index;
        trie_node_t *trav;

        count++;
        cout<<"  ::  count " <<count;
        trav = root;

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
        trav->value = count;
        trav->fid.push_back(fileid);

    }
    // Returns non zero, if key presents in trie
    int search(char key[])
    {
        int level;
        int length = strlen(key);
        int index;
        trie_node_t *trav;

        trav = root;

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
        if(trav->value)
        {

            list <int>k=trav->fid;
            cout<<"files: ";
            while(!k.empty())
            {
                cout<<v[k.front()-1].c_str()<<" ";
                k.pop_front();
            }
            return 1;
        }
        else
            return 0;
    }
    void index()
    {

        //char word[30];
        int i,j,k;
        ifstream infile;
        string filepath;
        //infile.open("ff.txt");



        //char output[][32] = {"Not present in trie", "Present in trie"};



        // Construct trie

        DIR *dpdf;
        struct dirent *epdf;

        dpdf = opendir("./toindex");
        if (dpdf != NULL)
        {
            while (epdf = readdir(dpdf))
            {

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

        for(k=0;k<v.size();k++)
        {
            filepath = "./toindex/" + v[k];
            infile.open(filepath.c_str());
            //infile.open(v[k]);


            cout<<"\n now indexing ... "<<k+1;
                //infile.open();
            char word[30];
            int count = 0;
            while(!infile.eof())
            {
                infile>>word;
                if(infile.eof())
                    break;

                cout<<"\n word is "<<word;
                insert(word,k+1);

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
            if(search(w))
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

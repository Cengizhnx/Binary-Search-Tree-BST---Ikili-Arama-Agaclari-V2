// tree.cpp : Bu dosya 'main' işlevi içeriyor. Program yürütme orada başlayıp biter.
//

#include <iostream>
using namespace std;

struct node
{
    int data;
    struct node* left;
    struct node* right;
  
};

struct node* temp;
typedef struct node BTREE;

BTREE* new_node(int data)
{
    BTREE* p = new BTREE;
    p->data = data;
    p->left = NULL;
    p->right = NULL;
    return p;
}

BTREE* insert(BTREE* root, int data)
{
    if (root != NULL)//ağaç boş değilse
    {
        //ekleyeceğimiz veri root'un data'sından küçükse
        if (data < root->data) //5<15
            root->left = insert(root->left, data);
        //ekleyeceğimiz veri root'un data'sından büyük veya eşitse
        else //20>15
            root->right = insert(root->right, data);
    }
    else //ağac boş ise
        root = new_node(data); //kök düğüm
        return root;
}

void preorder(BTREE* root) //kök-sol-sağ
{
    if (root != NULL)
    {
        cout << root->data;
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(BTREE* root)//sol-kök-sağ
{
    if (root != NULL)
    {
        inorder(root->left);
        cout << root->data;       
        inorder(root->right);
    }
}

void postorder(BTREE* root)//sol-sağ-kök
{
    if (root != NULL)
    {
        postorder(root->left);
        postorder(root->right);
        cout << root->data;
    }
}

int mirror(BTREE* root) //ayna
{
    if (root == NULL)
    {
        return -1;
    }
    else
    {
       cout << root->data;
       mirror(temp = root->right);
       mirror(root->right = root->left);

    }

}
BTREE* searchTree(BTREE* tree, int data)
{
    if (tree!=NULL)//Ağac doluysa
    {
        if (tree->data==data)
        {
            return tree;
        }
        else if(tree->data > data)
        {
            searchTree(tree->left, data);
        }
        else
        {
            searchTree(tree->right, data);
        }
    }
    else//Ağac boş ise 
    {
        return NULL;
    }
}

bool isBinarySearchTree(BTREE* root)
{
    if (root==NULL)
        return true;
    if (root->left != NULL && maximumValue(root->left) > root->data)
        return false;
    if (root->right != NULL && minimumValue(root->right) <= root->data)
        return false;
    if (!isBinarySearchTree(root->left) || !isBinarySearchTree(root->right))
        return false;

    return true;
}

int minimumValue(BTREE* root)
{
    if (root==NULL)
        return 0;
    while (root->left!=NULL)
        root = root->left;
    return(root->data);
}

int maximumValue(BTREE* root)
{
    if (root == NULL)
        return 0;
    while (root->right != NULL)
        root = root->right;
    return(root->data);
}

int isBSTSame(BTREE* x, BTREE* y)//Ağaclar aynı mı değil mi
{
    if (x == NULL && y == NULL)
        return 1;
    else if (x != NULL && y != NULL)
        return (x->data == y->data && isBSTSame(x->left, y->left) && isBSTSame(x->right, y->right));
    else
        return 0;
}

BTREE* delete_node(BTREE* root, int x)
{
    BTREE* p, * q;
    if (root == NULL) //Ağac yoksa
        return NULL;
    if (root->data==x) //Aranan düğümü bulduysak
    {
        //1.case (yaprak düğüm)
        if (root->left==root->right)
        {
            free(root);
            return NULL;
        }
        else //2.case (tek çocuklu düğüm siilnecek)
        {
            if (root->left==NULL)
            {
                p = root->right;
                free(root);
                return p;
            }
            else if (root->right == NULL)
            {
                p = root->left;
                free(root);
                return p;
            }
            else
            {
                p = q = root->right;
                while (p->left !=NULL)
                {
                    p = p->left;
                }
                p->left = root->left;
                free(root);
                return q;
            }
        }
    }
    else if(root->data < x) //Aranan düğümü henüz bulamadıysa
        root->right = delete_node(root->right, x);
    else
        root->left = delete_node(root->left, x);
    return root;
}

int size(BTREE* root)
{
    if (root==NULL)
    {
        return 0;
    }
    else
    {
        return size(root->left) + 1 + size(root->right);
    }
}

int height(BTREE* root)
{
    if (root == NULL)
    {
        return -1;
    }
    else
    {
        int left_height, right_height;
        left_height = height(root->left);
        right_height = height(root->right);
        return size(root->left) + 1 + size(root->right);

        if (right_height>left_height)
            return right_height + 1;
        else
            return left_height + 1;
    }
}

int main()
{
    BTREE* cdroot = NULL;
    int i = 0;
    do
    {
        cout << "Agaca integer veri ekleyiniz..." << endl;
        cout << "Sayi : "<< endl;
        cin >> i;
        if (i != -1)
            cdroot = insert(cdroot, i);
    } while (i != -1);

    cout << endl;
    cout << "Preorder: ";
    preorder(cdroot);
    cout << endl;
    cout << "Inorder: ";
    inorder(cdroot);
    cout << endl;
    cout << "Postorder: ";
    postorder(cdroot);
    cout << endl;

    cout << endl;
    cout << "Agacin Boyutu: " << size(cdroot) << endl;

    cout << endl;
    cout << "Agacin Yuksekligi: " << height(cdroot) << endl;

    /*cout << endl;
    cout << "Mirror(Ayna): ";
    mirror(cdroot);
    cout << endl;*/

   /* for (int syc = 0; syc < 3; syc++)
    {
        cout << endl;
        cout << "Silinecek sayi: "; 
        cin >> i;
        delete_node(cdroot, i);
        inorder(cdroot);
    }*/

   /* cout << endl;
    cout << "Aranacak sayi: "; 
    cin >> i;
    searchTree(cdroot, i);
    inorder(cdroot);*/
    return 1907;
}

// Programı çalıştır: Ctrl + F5 veya Hata Ayıkla > Hata Ayıklamadan Başlat menüsü
// Programda hata ayıkla: F5 veya Hata Ayıkla > Hata Ayıklamayı Başlat menüsü

// Kullanmaya Başlama İpuçları: 
//   1. Dosyaları eklemek/yönetmek için Çözüm Gezgini penceresini kullanın
//   2. Kaynak denetimine bağlanmak için Takım Gezgini penceresini kullanın
//   3. Derleme çıktısını ve diğer iletileri görmek için Çıktı penceresini kullanın
//   4. Hataları görüntülemek için Hata Listesi penceresini kullanın
//   5. Yeni kod dosyaları oluşturmak için Projeye Git > Yeni Öğe ekle veya varolan kod dosyalarını projeye eklemek için Proje > Var Olan Öğeyi Ekle adımlarını izleyin
//   6. Bu projeyi daha sonra yeniden açmak için Dosya > Aç > Proje'ye gidip .sln uzantılı dosyayı seçin

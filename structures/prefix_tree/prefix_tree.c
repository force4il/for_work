#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET 26

// Эта структура представляет собой узел в 
// префиксном дереве. Она содержит массив 
// указателей TrieNode на дочерние узлы (26, все 
// они соответствуют строчным буквам английского 
// алфавита) и логический флаг, указывающий, 
// соответствует ли данный узел последней букве 
// какого-либо слова.
typedef struct TrieNode {
    struct TrieNode* node[ALPHABET];
    int is_end;
} Node;

// Приведенная функция динамически выделяет память 
// для нового объекта TrieNode и устанавливает для 
// флага isendofword значение false, а также 
// обнуляет все дочерние указатели. Сначала 
// создается новый узел Trie.
Node* createNode() {
    Node* node = malloc(sizeof(Node));
    if (node == NULL) {
        return node;
    }

    node->is_end = 0;
    for (int i = 0; i < ALPHABET; i++) {
        node->node[i] = NULL;
    }

    return node;
}

// Этот метод позволяет вставить ключ в префиксное 
// дерево. Он систематически просматривает каждый 
// бит ключа, определяет, в каком месте массива 
// дочерних узлов находится этот бит, и создает 
// новый узел, если соответствующего дочернего узла 
// не существует, а затем обозначает конечный узел, 
// завершающий слово.
void insert(Node* root, const char* key) {
    Node* cur = root;
    for (int i = 0; i < strlen(key); i++) {
        int ind = key[i] - 'a';

        if (cur->node[ind] == NULL) {
            cur->node[ind] = createNode();
        }
        cur = cur->node[ind];
    }

    cur->is_end = 1;
}

// Функция Trie search() ищет ключ. Чтобы найти его, 
// она просматривает все символы ключа и проверяет, 
// есть ли дочерний узел для каждого символа в 
// массиве children этого узла, который содержит 
// указатели на его потомков в качестве элементов. 
// Если какой-либо символ отсутствует в children 
// или если узел последнего символа не указывает на 
// то, что это слово, возвращается значение False, в 
// противном случае возвращается значение True, как 
// и раньше.
int search(Node* root, const char* key) {
    Node* cur = root;
    for (int i = 0; i < strlen(key); i++) {
        int ind = key[i] - 'a';
        if (cur->node[ind] == NULL) {
            return 0;
        }

        cur = cur->node[ind];
    }

    return (cur != NULL && cur->is_end);
}

int isempty(const Node* root) {
    for (int i = 0; i < ALPHABET; i++) {
        if (root->node[i] != NULL) {
            return 0;
        }
    }

    return 1;
}
// Приведенный выше фрагмент кода отвечает за 
// создание функции deletehelper, которая удаляет 
// ключ из Trie: она рекурсивно проходит по этой 
// структуре данных в поисках узла, соответствующего 
// тому же символу, что и последний символ ключа.
// Затем он помечает, что узел больше не является 
// конечной точкой слова, удаляя это свойство перед 
// тем, как начать удалять все дочерние узлы, пока 
// либо не будет найден другой узел, ответвляющийся 
// от текущего, либо пока не будут найдены все 
// связанные с ним слова.
// С другой стороны, deletekey, выступающий в 
// качестве метода интерфейса, передает ключ для 
// удаления из Trie в функцию deletehelper, которая 
// выполняет фактическое удаление узла, содержащего 
// ключ, вместе со всеми связанными значениями, 
// если это необходимо.
Node* del(Node* root, const char* key, int depth) {
    if (root == NULL) {
        return NULL;
    }

    if (depth == strlen(key)) {
        if (root->is_end) {
            root->is_end = 0;
        }

        if (isempty(root)) {
            free(root);
            root = NULL;
        }

        return root;
    }

    int ind = key[depth] - 'a';
    root->node[ind] = del(root->node[ind], key, depth + 1);
    
    if (isempty(root) && !root->is_end) {
        free(root);
        root = NULL;
    }

    return root;
}

void delkey(Node*root, const char *key) {
    del(root, key, 0);
}

int main() {
    Node* root = createNode();
    if (root == NULL) {
        return -1;
    }

    insert(root, "hello");
    insert(root, "world");

    printf("%s\n", search(root, "hello") ? "Found" : "Not Found");
    printf("%s\n", search(root, "world") ? "Found" : "Not Found");
    printf("%s\n", search(root, "geeks") ? "Found" : "Not Found");

    delkey(root, "hello");
    printf("%s\n", search(root, "hello") ? "Found" : "Not Found");
    printf("%s\n", search(root, "wor") ? "Found" : "Not Found");

    return 0;
}
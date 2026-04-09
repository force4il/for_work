class Node:
    def __init__(self, data):
        self.data = data #значение
        self.left = self.right = None #ветки

class Tree:
    def __init__(self):
        self.root = None #вершина

    #метод для поиска указанного значения в вершинах 
    def find(self, node, parent, value):
        if node is None: return None, parent, False #если вершины не существует

        if value == node.data: return node, parent, True #если нашли значение в дереве

        if value < node.data:
            if node.left: return self.find(node.left, node, value) #если на текущем уровне нет значения, и это значение меньше чем в текущей вершине, то ищем слева

        if value > node.data:
            if node.right: return self.find(node.right, node, value) #если на текущем уровне нет значения, и это значение больше чем в текущей вершине, то ищем справа

        return node, parent, False #если значение не найдено в дереве
    
    #добавление вершины
    def append(self, obj):
        #если это не объект класса Node
        if not isinstance(obj, Node): return None

        # если это первая вершина в дереве 
        if self.root is None:
            self.root = obj
            return obj
        
        #находим свободную вершину, её родителя и проверяем, чтобы нового значения не было в дереве
        cur, parent, flag = self.find(self.root, None, obj.data)
        
        #если дубликата нет и вершина, после которой мы хотим записать новое значение существует
        if flag == False and cur:
            if obj.data < cur.data: cur.left = obj
            else: cur.right = obj;

        return obj
    
    def show(self, node):
        if node is None: return None

        self.show(node.left)
        print(node.data, end=' ')
        self.show(node.right)

    def show_wide_tree(self, node):
        #если вершины, от которой мы хотим отобразить дерево, нет
        if node is None: return node

        v = [node] #список с текущими вершинами
        level = flag = 0
        while v:
            buf = []
            for top in v:
                if (flag == 0):
                    print(f"Level tree: {level}.", top.data, end=" ")
                    flag = 1
                else: print(top.data, end=" ")

                if top.left: buf += [top.left]
                if top.right: buf += [top.right]

            level += 1
            flag = 0
            print()
            v = buf

    #удаление листка 
    def del_leaf(self, cur, parent):
        if parent.left == cur: parent.left = None
        else: parent.right = None

    #удаление вершины
    def del_top(self, cur, parent):
        if parent.left == cur:
            if cur.right: parent.left = cur.right
            elif cur.left: parent.left = cur.left

        elif parent.right == cur:
            if cur.right: parent.right = cur.right
            elif cur.left: parent.right = cur.left

    #ищет минимальное значение в текущей ветке
    def find_min(self, node, parent):
        #наим. значение всегда будет в левом узле, поэтому пока он существует у текущей вершины, то мы идёт по нему
        if node.left: return self.find_min(node.left, node)

        return node, parent
    
    #удаление ветки
    def del_node(self, key):
        cur, parent, flag = self.find(self.root, None, key)

        #если значение key не найдено
        if not flag: return None 

        if isinstance(cur, Node):
            #если оба дочерних узло не опрделены, то это лист
            if cur.right is None and cur.left is None: self.del_leaf(cur, parent)

            #если только одна вершина имеет потомка, то удаляем как вершину
            elif cur.right is None or cur.left is None: self.del_top(cur, parent)   

            else:
                #если нужно удалить целый узел, то находим минимальное значение в правой ветке, записываем его в удаляемую вершину и удаляем вершину с этим мин. значением                cur_right, parent_right = self.find_min(cur, parent)
                cur_right, parent_right = self.find_min(cur, parent)
                cur.data = cur_right.data
                self.del_top(cur_right, parent_right)

v = [10, 5, 7, 16, 13, 2, 20]
#v = [20, 5, 24, 2, 16, 11, 18]
 
t = Tree()
for x in v:
    t.append(Node(x))
 
# t.del_node(5)
t.show_wide_tree(t.root)
t.show(t.root)
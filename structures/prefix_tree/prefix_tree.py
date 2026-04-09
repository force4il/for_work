class Node:

    def __init__(self, value):
        self.data = value
        self._is_key = False


class PrefixTree:

    def __init__(self):
        self.root = Node(None)

    def append(self, key, value):
        node = self.root
        for char in key:
            if hasattr(node, char):
                node = getattr(node, char)
            else:
                setattr(node, char, Node(None))
                node = getattr(node, char)
        if node._is_key:
            print('key already used')
            return None
        else:
            node.data = value
            node._is_key = True
            return node.data

    def _get_node(self, key):
        node = self.root
        for char in key:
            if hasattr(node, char):
                node = getattr(node, char)
            else:
                print(f'key "{key}" is not exist in this tree')
                return None
        if not node._is_key:
            print(f'key "{key}" is intermediate key of this tree and ready to value assignment')
            return None
        else:
            return node

    def get(self, key):
        node = self._get_node(key)
        if node is not None and node._is_key:
            return node.data
        else:
            return None

    def delete(self, key):
        node = self._get_node(key)
        if node is not None:
            result = node.data
            node.data = None
            node._is_key = False
            return result
        return None


tree = PrefixTree()
tree.append('dog', 'bark')
tree.append('time', 'high noon')
tree.append('booze', 'liquor')
tree.append('do', 'something')
tree.append('dome', 'half sphere')
tree.append('boobs', 'tits')

print(tree.get('time'))
print(tree.get('boobs'))

print(tree.get('ti'))
tree.append('ti', 'ge force')
print(tree.get('ti'))
tree.delete('ti')
print(tree.get('ti'))

tree.delete('boobs')
print(tree.get('boobs'))

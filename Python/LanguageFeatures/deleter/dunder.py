from copy import deepcopy


class MyClass:
    def __init__(self):
        self.start = 10
        self.enough = 100
        self.repr = "Haha you fool called my repr!"
        print("Init called!")

    def __del__(self):
        print("Deleter called!")

    def __repr__(self):
        return self.repr

    def __sub__(self):
        print("You can't substract me!")
        return self

    def __reversed__(self):
        a = deepcopy(self)
        a.repr = self.repr[::-1]
        return a

    def __neg__(self):
        print("Oh no you negated me")
        return self

    def __iter__(self):
        return self

    def __next__(self):
        if self.enough == 0:
            self.enough = 100
            raise StopIteration
        self.start = (self.start + 1) % 255
        self.enough -= 1
        return self.start

    def __sizeof__(self):
        return 1337


if __name__ == "__main__":
    my_class = MyClass()
    for i in my_class:
        print(i)
    print([x for x in my_class])
    print(reversed(my_class))

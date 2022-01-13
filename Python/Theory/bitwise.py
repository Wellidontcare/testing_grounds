class integer:
    def __init__(self, value: int):
        self._value = value

    def __and__(self, other: "integer"):
        if isinstance(other, int):
            return integer((self._value & other & 0xffffffff))
        return integer((self._value & other._value & 0xffffffff))

    def __gt__(self, other: "integer"):
        return self._value > other._value

    def __lt__(self, other: "integer"):
        return not (self > other)

    def __ge__(self, other: "integer"):
        return (self > other) or (self == other)

    def __le__(self, other: "integer"):
        return (self < other) or (self == other)

    def __not__(self):
        return integer(not self._value)

    def __or__(self, other: "integer"):
        if isinstance(other, int):
            return integer((self._value | other))
        return integer((self._value | other._value))

    def __invert__(self):
        return integer(self._value ^ 0xffffffff)

    def __eq__(self, other):
        if isinstance(other, int):
            return self._value == other
        return self._value == other._value

    def __ne__(self, other):
        return not (self == other)

    def __lshift__(self, other: int):
        return integer((self._value << other)  & 0xffffffff)

    def __rshift__(self, other: int):
        return integer((self._value >> other) & 0xffffffff)

    def __xor__(self, other: "integer"):
        return (self | other) & (~(self & other))

    def __add__(self, other: "integer"):
        a = self
        b = other
        while b != 0:
            carry = a & b
            a = a ^ b
            b = (carry << 1)
        return a

    def __sub__(self, other: "integer"):
        a = self
        b = other
        while b != 0:
            carry = (~a) & b
            a = a ^ b
            b = carry << 1
        return a

    def __mul__(self, other: "integer"):
        a = self._value
        while other != 1:
            self = self + a
            other = other - 1
        return self

    def __truediv__(self, other: "integer"):
        count = integer(0)
        while self >= other:
            self = self - other
            count = count + 1
        return count

    def __neg__(self):
        return integer(-self._value)


    def __repr__(self) -> str:
        return f"{self._value:032b} | {self._value}"



if __name__ == "__main__":
    a = integer(20000)
    b = integer(2048)
    print((a / b)*b)

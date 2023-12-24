from add_lib import add
import numpy as np

def test_add():
    assert(add(1, 2) == 3)
    for _ in range(100):
        a = np.random.randint(0, 100)
        b = np.random.randint(0, 100)
        assert(add.add(a, b) == a + b)

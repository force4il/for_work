import random
from dataclasses import dataclass


random.seed()


@dataclass
class TestClass:
    random_num: int
    title: str


def get_random_num() -> int:
    return random.randint(1, 100)


TestClass(get_random_num(), "from func: get_random_num")
print(TestClass)